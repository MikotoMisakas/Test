// dbg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TiaoShi.h"
#include <windows.h>
#include "keystone/keystone.h"
#pragma comment (lib,"keystone/x86/keystone_x86.lib")
//#include "mydebugregister.h"
#include <vector>
#include <atlstr.h>
#include <DbgHelp.h>
#include <iostream>
#include <string>
#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL
using namespace std;

//dll函数
typedef bool(*DllInt)();
#include "BeaEngine_4.1\\Win32\\headers\\BeaEngine.h"

#ifdef _WIN64
#pragma comment(lib,"BeaEngine_4.1\\Win64\\Win64\\Lib\\BeaEngine.lib")
#else
#pragma comment(lib,"BeaEngine_4.1\\Win32\\Win32\\Lib\\BeaEngine.lib")
#endif // _WIN32
#pragma comment(linker, "/NODEFAULTLIB:\"crt.lib\"")
#pragma comment(lib, "Dbghelp.lib")


typedef LONG(__stdcall *PZWQUERYINFORMATIONPROCESS)
(HANDLE ProcessHandle,
ULONG ProcessInformationClass,
PVOID ProcessInformation,
ULONG ProcessInformationLength,
PULONG ReturnLength);
HANDLE   HookJu;
typedef struct _PROCESS_BASIC_INFORMATION {
	DWORD ExitStatus;
	ULONG PebBaseAddress;
	ULONG AffinityMask;
	LONG BasePriority;
	ULONG UniqueProcessId;
	ULONG InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION, *PPROCESS_BASIC_INFORMATION;

//内存断点数组
struct MemberPoint {
	LPVOID address;
	DWORD oldProtect;
	WORD type;
};
int g_isMemDbg = FALSE;

vector<MemberPoint> g_mem;// 内存断点列表

typedef struct BREAKPOINT {
	LPVOID address;
	BYTE   oldData;// 保存int3断点覆盖的1字节数据
}BREAKPOINT;


typedef struct WeiLaoShi {
	LPVOID address;
	BYTE   oldData;// 保存int3断点覆盖的1字节数据
	DWORD addd;
}BaoCunTiaoJianDuanDian;





typedef struct DLLINFO {
	LPVOID address;
	char NAME[100];
	char AllPath[MAX_PATH];
};
std::vector<BREAKPOINT> g_bps;// 断点列表




//条件断点列表
std::vector<WeiLaoShi> TiaoJian;// 断点列表




std::vector<DLLINFO> g_dll;// dll模块列表

BOOL   g_isDbgTf = FALSE;
HANDLE g_hProc = 0;
HANDLE g_hThread = 0;

//内存执行断点
int Member = 0;
void showDisam(LPVOID address, int nLen = 10)
{
	// 输出反汇编的步骤:
	LPBYTE opcode = new BYTE[nLen * 15];
	SIZE_T dwRead = 0;
	// 1. 得到机器码
	if (!ReadProcessMemory(g_hProc, address, opcode, nLen * 15, &dwRead)) {

	}
	// 2. 使用返汇编引擎获取机器码对应的汇编
	DISASM da = { 0 };
	da.EIP = (UIntPtr)opcode;
	da.VirtualAddr = (UINT64)address;
#ifdef _WIN64
	da.Archi = 64;
#else
	da.Archi = 0;
#endif // _WIN64

	while (nLen--)
	{
		int len = Disasm(&da);
		if (len == -1) {/*返回-1表示机器码无法找到对应的汇编指令*/
			break;
		}

		// 3. 输出.
		printf("%I64X | %s\n",
			da.VirtualAddr, da.CompleteInstr);
		da.VirtualAddr += len;
		da.EIP += len;
	}
}



DWORD getPeb(HANDLE hProcess)
{
	// 获取NTDLL.DLL的基址   
	HMODULE hModule = GetModuleHandle(TEXT("NTDLL.DLL"));
	if (hModule == NULL) return FALSE;

	// 获取ZwQueryInformationProcess函数的指针   
	PZWQUERYINFORMATIONPROCESS pZwQueryInformationProcess =
		(PZWQUERYINFORMATIONPROCESS)GetProcAddress(hModule, "ZwQueryInformationProcess");

	// 查询进程基本信息（包含PEB地址）   
	PROCESS_BASIC_INFORMATION pbi = { NULL };
	if (pZwQueryInformationProcess(hProcess, 0, (LPVOID)&pbi, sizeof(pbi), NULL) < 0)
		return -1;
	return pbi.PebBaseAddress;
}


void hidePeb(HANDLE hThread, HANDLE hProc) {
	DWORD peb = getPeb(hProc);
	char buf = 0;
	WriteProcessMemory(hProc, (LPVOID)(peb + 0x2), &buf, 1, 0);
	buf = 2;
	WriteProcessMemory(hProc, (LPVOID)(peb + 0x18 + 0x0c), &buf, 1, 0);
	buf = 0;
	WriteProcessMemory(hProc, (LPVOID)(peb + 0x18 + 0x10), &buf, 1, 0);
	WriteProcessMemory(hProc, (LPVOID)(peb + 0x68), &buf, 1, 0);

}

// 设置TF单步步入断点
void setBreakpoint_tf() {
	// 1. 获取线程上下文
	CONTEXT ct = { CONTEXT_ALL };
	if (!GetThreadContext(g_hThread, &ct)) {

	}
	EFLAGS* pEflags = (EFLAGS*)&ct.EFlags;
	// 2. 修改TF标志位
	pEflags->TF = 1;

	// 3. 设置线程上下文
	if (!SetThreadContext(g_hThread, &ct)) {

	}
}


void setBreakpoint_int3(LPVOID address) {
	BREAKPOINT bp = { 0 };
	//1. 将下断点的地址的1字节的数据备份
	SIZE_T read = 0;
	if (!ReadProcessMemory(g_hProc, address, &bp.oldData, 1, &read)) {

	}
	//2. 将0xCC写入下断点的地址
	if (!WriteProcessMemory(g_hProc, address, "\xCC", 1, &read)) {

	}
	bp.address = address;
	g_bps.push_back(bp);
}

void clearBreakpoint_int3(LPVOID address) {
	// 1. 将字节覆盖回去
	SIZE_T write = 0;
	for (auto& i : g_bps) {
		if (i.address == address) {
			if (!WriteProcessMemory(g_hProc, i.address, &i.oldData, 1, &write)) {
				printf("写入失败\n");
			}
			// 2. 将线程上下文的eip--
			CONTEXT ct = { CONTEXT_ALL };
			if (!GetThreadContext(g_hThread, &ct)) {

			}
			ct.Eip--;
			if (!SetThreadContext(g_hThread, &ct)) {

			}

			// 设置一个单步断点, 用于重新安装int3断点.
			//  			setBreakpoint_tf();
			//  			g_isDbgTf = TRUE;
		}
	}
}
char* OnDebugEvent_LOAD_DLL_DEBUG_EVENT_m1(PROCESS_INFORMATION& pi, DEBUG_EVENT& dbgEvent, DWORD& dwContinueStatus) {
	LOAD_DLL_DEBUG_INFO* pInfo = NULL;
	dwContinueStatus = DBG_EXCEPTION_NOT_HANDLED;
	char szBuf[MAX_PATH] = { '\0' };
	SIZE_T nNumberOfBytesRead = 0;

	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	IMAGE_EXPORT_DIRECTORY* pExportDir = NULL;
	IMAGE_EXPORT_DIRECTORY ExportDir;
	DWORD dwAddrDllName = 0;
	WORD wLenDllName = 0;

	pInfo = &dbgEvent.u.LoadDll;


	// *(DWORD*)(pInfo->lpImageName) 里面总是0, 不能按照msdn上来判断
	// if ((NULL != pInfo) && (NULL != pInfo->lpImageName) && (NULL != *(DWORD*)(pInfo->lpImageName))) {

	// 看到载入不同DLL时, pInfo->lpBaseOfDll 总是不同的
	if ((NULL != pInfo) && (NULL != pInfo->lpBaseOfDll)) {
		// 读目标DLL导出表中的dll名称吧
		do {
			if (!ReadProcessMemory(pi.hProcess, pInfo->lpBaseOfDll, &dosHeader, sizeof(dosHeader), &nNumberOfBytesRead)) {
				break;
			}

			if (!ReadProcessMemory(pi.hProcess, (void*)((DWORD)pInfo->lpBaseOfDll + dosHeader.e_lfanew), &ntHeader, sizeof(ntHeader), &nNumberOfBytesRead)) {
				break;
			}

			pDataDir = &ntHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
			pExportDir = (IMAGE_EXPORT_DIRECTORY*)((DWORD)pInfo->lpBaseOfDll + pDataDir->VirtualAddress);
			if (!ReadProcessMemory(pi.hProcess, pExportDir, &ExportDir, sizeof(ExportDir), &nNumberOfBytesRead)) {
				break;
			}

			dwAddrDllName = (DWORD)pInfo->lpBaseOfDll + ExportDir.Name;
			if (!ReadProcessMemory(pi.hProcess, (void*)dwAddrDllName, &szBuf, sizeof(szBuf), &nNumberOfBytesRead)) {
				break;
			}

		} while (0);
	}
	return szBuf;
}
//设置硬件执行断点
BOOL  SetBreakpoint_hardExec(HANDLE  g_hThread, DWORD  qq){

	CONTEXT ct = { CONTEXT_ALL };
	GetThreadContext(g_hThread, &ct);//获取线程环境快
	DBG_REG7* pDr7 = (DBG_REG7*)&ct.Dr7;
	if (pDr7->L0 == 0)//FR0没有被使用
	{
		ct.Dr0 = qq;
		pDr7->RW0 = 0;
		pDr7->LEN0 = 0;//长度域设置为0
		pDr7->L0 = 1;

	}
	else if (pDr7->L1 == 0)//dr1没有被使用
	{
		ct.Dr1 = qq;
		pDr7->RW1 = 0;
		pDr7->LEN1 = 0;
		pDr7->L1 = 1;

	}
	else if (pDr7->L2 == 0)//dr2没有被使用
	{
		ct.Dr2 = qq;
		pDr7->RW2 = 0;
		pDr7->LEN2 = 0;
		pDr7->L2 = 1;

	}
	else if (pDr7->L3 == 0)//dr2没有被使用
	{
		ct.Dr3 = qq;
		pDr7->RW3 = 0;
		pDr7->LEN3 = 0;
		pDr7->L3 = 1;

	}
	else
	{
		return FALSE;
	}

	SetThreadContext(g_hThread, &ct);
	return TRUE;


}

//条件断点
BOOL IFDuanDian(DWORD DZ, string TJ, DWORD aaa){

	//setBreakpoint_int3((LPVOID)DZ);
	BREAKPOINT qwe;



	WeiLaoShi bp = { 0 };
	//1. 将下断点的地址的1字节的数据备份
	SIZE_T read = 0;
	if (!ReadProcessMemory(g_hProc, (LPVOID)DZ, &bp.oldData, 1, &read)) {

	}
	//2. 将0xCC写入下断点的地址
	if (!WriteProcessMemory(g_hProc, (LPVOID)DZ, "\xCC", 1, &read)) {

	}
	qwe.address = (LPVOID)DZ;
	qwe.oldData = bp.oldData;
	g_bps.push_back(qwe);
	bp.address = (LPVOID)DZ;//吧代地址上的数据娶一个字节
	bp.addd = DZ;
	TiaoJian.push_back(bp);
	return TRUE;



}







//显示内存
void showMember(LPVOID address) {
	BYTE buf[0x80] = {};
	DWORD dwRead = 0;
	ReadProcessMemory(g_hProc, address, buf, 0x80, &dwRead);
	for (int i = 0; i < 8; i++) {
		printf("%8X: ", (int)address + 16 * i);
		for (int j = 0; j < 4; j++) {
			printf(" %8X ", *(int*)&buf[16 * i + j * 4]);
		}
		printf("\n");
	}
}

//
void xiugaineicun(LPVOID address, int buf) {
	DWORD dwRead = 0;
	WriteProcessMemory(g_hProc, address, &buf, 4, &dwRead);
}


unsigned char* opcode = NULL;					//汇编指令首地址
DWORD nCount = 0;

//修改汇编代码
void ToOpcode(char* szBuff, DWORD count)
{
	ks_engine *pengine = NULL;
	if (KS_ERR_OK != ks_open(KS_ARCH_X86, KS_MODE_32, &pengine))
	{
		printf("汇编引擎初始化失败\n");
	}
	// 汇编得到的opcode的缓冲区首地址
	UINT nOpcodeSize = 0; // 汇编出来的opcode的字节数


	int nRet = 0; // 保存函数的返回值，用于判断函数是否执行成功
	size_t stat_count = 0; // 保存成功汇编的指令的条数
	nRet = ks_asm(pengine, /* 汇编引擎句柄，通过ks_open函数得到*/
		szBuff, /*要转换的汇编指令*/
		0x401000, /*汇编指令所在的地址*/
		&opcode,/*输出的opcode*/
		&nOpcodeSize,/*输出的opcode的字节数*/
		&stat_count /*输出成功汇编的指令的条数*/
		);
	nCount = nOpcodeSize;
	// 返回值等于-1时反汇编错误
	if (nRet == -1)
	{
		// 输出错误信息
		// ks_errno 获得错误码
		// ks_strerror 将错误码转换成字符串，并返回这个字符串
		printf("错误信息：%s\n", ks_strerror(ks_errno(pengine)));
	}
	// 关闭句柄
	ks_close(pengine);
}

//设置内存点
BOOL setMemberPoint(DWORD addr, DWORD type) {
	MemberPoint mem = {};
	mem.type = type;
	mem.address = (LPVOID)addr;
	VirtualProtectEx(g_hProc, (LPVOID)addr, 1, PAGE_NOACCESS, &mem.oldProtect);
	g_mem.push_back(mem);
	return TRUE;
}




void setNextPoint(int len) {
	CONTEXT ct = { 0 };
	ct.ContextFlags = CONTEXT_CONTROL;
	GetThreadContext(g_hThread, &ct);
	setBreakpoint_int3((LPVOID)(ct.Eip + len));
}



void setDisam(LPVOID address, char* p, DWORD count)
{

	ToOpcode(p, count);

	// 输出反汇编的步骤:
	LPBYTE OPCODE = new BYTE[15 * 10];
	SIZE_T dwRead = 0;
	// 1. 得到机器码
	if (!ReadProcessMemory(g_hProc, address, OPCODE, 15 * 10, &dwRead)) {
		printf("读取进程内存失败");
	}
	for (int i = 0; i < nCount; i++)
	{
		OPCODE[i] = opcode[i];
	}
	if (!WriteProcessMemory(g_hProc, address, OPCODE, 15 * 10, &dwRead)) {
		printf("写入进程内存失败");
	}
}


//////硬件读写断点
BOOL SetBreakpoint_harRw(HANDLE hThread, ULONG_PTR uAddress, DWORD dwLen){
	//获取环境块
	CONTEXT ct = { 0 };
	ct.ContextFlags = CONTEXT_ALL;
	GetThreadContext(hThread, &ct);


	//对地址和长度进行处理
	//（向上取整）
	if (dwLen == 1)//2字节对齐粒度
	{
		uAddress = uAddress - uAddress % 2;
	}
	else if (dwLen == 3)
	{
		uAddress = uAddress - uAddress % 4;


	}
	else if (dwLen > 3)
	{
		return FALSE;

	}
	//判断哪些寄存器没有被使用
	DBG_REG7* pDr7 = (DBG_REG7*)&ct.Dr7;
	if (pDr7->L0 == 0)//dr7没有被使用
	{
		ct.Dr0 = uAddress;
		pDr7->RW0 = 3;
		pDr7->LEN0 = dwLen;
		pDr7->L0 = 1;

	}
	else if (pDr7->L1 == 0)//DR1没有被使用
	{
		ct.Dr1 = uAddress;
		pDr7->RW1 = 3;
		pDr7->LEN1 = dwLen;
		pDr7->L1 = 1;
	}
	else if (pDr7->L2 == 0)//DR2没有被使用
	{
		ct.Dr2 = uAddress;
		pDr7->RW2 = 3;
		pDr7->LEN2 = dwLen;
		pDr7->L2 = 1;
	}
	else if (pDr7->L3 == 0)//DR2没有被使用
	{
		ct.Dr3 = uAddress;
		pDr7->RW3 = 3;
		pDr7->LEN3 = dwLen;
		pDr7->L3 = 1;
	}
	else
	{
		return FALSE;
	}


	SetThreadContext(hThread, &ct);
	return TRUE;


}




int getLenNow() {
	CONTEXT ct = { 0 };
	LPBYTE opcode = new BYTE[15];
	ct.ContextFlags = CONTEXT_CONTROL;
	SIZE_T dwRead = 0;
	GetThreadContext(g_hThread, &ct);
	if (!ReadProcessMemory(g_hProc, (LPVOID)ct.Eip, opcode, 15, &dwRead)) {
		printf("读取进程内存失败");
	}
	if (opcode[0] != 0xe8) {
		return -1;
	}
	DISASM da = { 0 };
	da.EIP = (UIntPtr)opcode;
	da.VirtualAddr = (UINT64)ct.Eip;
#ifdef _WIN64
	da.Archi = 64;
#else
	da.Archi = 0;
#endif // _WIN64
	return Disasm(&da);
}
DWORD DiZhi = 0;


DWORD OnException(EXCEPTION_RECORD* pExcept)
{


	CONTEXT ct = { CONTEXT_ALL };
	// 将所有int3断点重新设置回去.
	SIZE_T read = 0;
	for (auto &i : g_bps) {
		//2. 将0xCC写入下断点的地址
		if (!WriteProcessMemory(g_hProc, i.address, "\xCC", 1, &read)) {

		}
	}
	int a = 0;
	int len = g_mem.size();
	switch (pExcept->ExceptionCode)
	{

		// 第一个触发的int3异常就是系统断点.
	case EXCEPTION_BREAKPOINT:/*断点异常,int3指令引发的异常*/
	{
		static bool isSystemBreakpoint = true;
		if (isSystemBreakpoint) {
			//peb隐藏
			hidePeb(g_hThread, g_hProc);
			isSystemBreakpoint = false;






			printf("到达系统断点:%08X\n", pExcept->ExceptionAddress);
		}
		else {
			// 修复int3异常
			// 1. 将被int3覆盖的数据还原回去.
			// 2. int3是陷阱异常, 断下之后, eip指向了int3的下一个字节.
			//    还需要将eip--.





			clearBreakpoint_int3(pExcept->ExceptionAddress);


			CONTEXT ct = { 0 };
			ct.ContextFlags = CONTEXT_CONTROL;
			GetThreadContext(g_hThread, &ct);
			DWORD a = ct.Eax;
			//如果等于我要的eax的值就吧断点写回去

			if (ct.Eax == DiZhi)
			{

			}
			else
			{
				return DBG_CONTINUE;
			}

			SetThreadContext(g_hThread, &ct);





		}
	}
		break;
	case EXCEPTION_ACCESS_VIOLATION:/*内存访问异常*/

		GetThreadContext(g_hThread, &ct);
		VirtualProtectEx(g_hProc, pExcept->ExceptionAddress, 1, PAGE_EXECUTE_READWRITE, (PDWORD)&a);
		for (int i = 0; i < len; i++) {
			MemberPoint single = g_mem[i];
			if (single.address == pExcept->ExceptionAddress) {
				g_mem.erase(g_mem.begin() + i);
				break;
			}
			setBreakpoint_tf();
			g_isDbgTf = true;
			g_isMemDbg = true;

			CONTEXT ct = { CONTEXT_ALL };
			GetThreadContext(g_hThread, &ct);//获取线程环境快
			if (ct.Eip != Member)
			{
				VirtualProtectEx(g_hProc, (LPVOID)Member, 1, PAGE_NOACCESS, (PDWORD)&a);
				ct.Eip++;
			}
			SetThreadContext(g_hThread, &ct);



			goto _DONE;
		}




		break;
	case EXCEPTION_SINGLE_STEP:/*硬件断点和TF陷阱标志异常*/
	{
		GetThreadContext(g_hThread, &ct);
		DBG_REG6*aa = (DBG_REG6*)&ct.Dr6;
		DBG_REG7* bb = (DBG_REG7*)&ct.Dr7;
		if (aa->B0)
		{
			bb->L0 = 0;
		}
		else if (aa->B1)
		{
			bb->L1 = 0;
		}
		else if (aa->B2)
		{
			bb->L2 = 0;
		}
		else if (aa->B3)
		{
			bb->L3 = 0;
		}
		else
		{
			//tf断点
		}
		// 这个tf断点, 是用户输入单步之后断下的
		// 还是调试器设置的.如果是调试器设置的, 就不能
		// 接收命令的输入了
		//   		if (g_isDbgTf == TRUE) {
		//   
		// 			g_isDbgTf = FALSE;
		//   			return DBG_CONTINUE;
		//   		}
		SetThreadContext(g_hThread, &ct);
	}
		break;

	default:
		printf("被调试进程自身触发了异常:%08X\n", pExcept->ExceptionAddress);
		getchar();
		return DBG_EXCEPTION_NOT_HANDLED;
		break;
	}

	if (!GetThreadContext(g_hThread, &ct)) {

	}
	showDisam((LPVOID)ct.Eip, 10);

	while (true)
	{
		char cmd[100];
		printf("命令>");
		scanf_s("%s", cmd, 100);
		//单步步入
		if (_stricmp(cmd, "t") == 0) {

			setBreakpoint_tf();
			g_isDbgTf = FALSE;
			break;
		}//执行命令
		else if (_stricmp(cmd, "g") == 0) {
			break;
		}//下断点
		else if (_stricmp(cmd, "bp") == 0) {
			SIZE_T addr = 0;
			scanf_s("%8X", &addr);
			setBreakpoint_int3((LPVOID)addr);
		}
		//查看寄存器
		else if (_stricmp(cmd, "look") == 0) {
			CONTEXT ct = { 0 };
			ct.ContextFlags = CONTEXT_ALL;
			GetThreadContext(g_hThread, &ct);
			printf("EAX:%08x\n", ct.Eax);
			printf("Ebx:%08x\n", ct.Ebx);
			printf("Ecx:%08x\n", ct.Ecx);
			printf("Edx:%08x\n", ct.Edx);
			printf("Ebp:%08x\n", ct.Ebp);
			printf("Edi:%08x\n", ct.Edi);
			printf("EFlags:%08x\n", ct.EFlags);
			printf("Eip:%08x\n", ct.Eip);
			printf("Esi:%08x\n", ct.Esi);
			printf("Edi:%08x\n", ct.Edi);
			printf("Esp:%08x\n", ct.Esp);
		}
		//修改寄存器
		else if (_stricmp(cmd, "xgex") == 0) {
			string  aa;

			cin >> aa;
			DWORD bb;
			ct.ContextFlags = CONTEXT_ALL;
			GetThreadContext(g_hThread, &ct);
			if (aa == "eax")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Eax = bb;
				SetThreadContext(g_hThread, &ct);
			}
			else if (aa == "eip")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Eip = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "ebx")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Ebx = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "ecx")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Ecx = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "edx")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Edx = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "esi")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Esi = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "edi")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Edi = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "esp")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Esp = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "ebp")
			{
				printf("请输入要修改的值\n");
				scanf_s("%x", &bb);
				ct.Ebp = bb;
				SetThreadContext(g_hThread, &ct);

			}

		}
		//硬件执行断点
		else if (_stricmp(cmd, "yjddr") == 0) {
			DWORD   qq;

			scanf_s("%x", &qq);
			SetBreakpoint_hardExec(g_hThread, qq);

		}
		//硬件读写断点
		else if (_stricmp(cmd, "yjwr") == 0) {

			DWORD   qq;
			printf("请输入地址\n");
			scanf_s("%x", &qq);

			DWORD down = 1;

			SetBreakpoint_harRw(g_hThread, qq, down);

		}


		//查看堆栈段
		else if (_stricmp(cmd, "static") == 0) {

			CONTEXT ct = { 0 };
			ct.ContextFlags = CONTEXT_CONTROL;
			GetThreadContext(g_hThread, &ct);
			BYTE buff[512];
			DWORD dwRead = 0;
			ReadProcessMemory(g_hProc, (LPVOID)ct.Esp, buff, 512, &dwRead);
			for (int i = 0; i < 5; ++i)
			{
				printf("%08x\n", ((DWORD*)buff)[i]);
			}



		}
		else if (_stricmp(cmd, "mengxiang") == 0) {
			//显示内存
			int addr;
			//cin >> addr;
			scanf_s("%x", &addr);
			showMember((LPVOID)addr);
		}

		else if (_stricmp(cmd, "r") == 0) {
			//单步步过

			int len = getLenNow();
			CONTEXT ct = { CONTEXT_ALL };
			GetThreadContext(g_hThread, &ct);
			if (len < 0) {
				setBreakpoint_tf();
				g_isDbgTf = FALSE;
			}
			else {
				setNextPoint(len);
			}
			break;


		}


		//修改内存
		else if (_stricmp(cmd, "happy") == 0) {
			//修改内存
			int nLen;
			scanf_s("%x", &nLen);
			string str;
			printf("\n%8x:", nLen);
			int d = 0;
			scanf_s("%X", &d);
			xiugaineicun((LPVOID)nLen, d);
		}//支持插件
		else if (_stricmp(cmd, "cj") == 0) {
			//插件的编写
			//遍历目录下的dll



			//用来储存文件名列表
			//vector<CString>StdStrDll;


			//查找dll文件
			//	WIN32_FIND_DATA wfd;
			//CString sPath = "*.dll";//查找指定目录下所有格式的文件

			//HANDLE hFile = FindFirstFile(sPath.GetBuffer(), &wfd);
			//do 
			//{
			//	StdStrDll.push_back(wfd.cFileName);



			//} while (FindNextFile(hFile,&wfd));



			vector<CString>StdStrDll;
			WIN32_FIND_DATA wfd;
			CString sPath = L"D:\\cx\\debugg\\debugg";
			HANDLE hFile = FindFirstFile(sPath + "\\*", &wfd);

			if (hFile == (HANDLE)-1)
			{
				printf("无效\n");
				//return ;
			}
			do
			{//如果是当前目录或者下以及目录
				if (wfd.cFileName == L"." || wfd.cFileName == L"..")
				{
					continue;
				}//判断是文件夹
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					continue;
				}
				CString aa;

				aa = PathFindExtension(wfd.cFileName);
				if (aa == ".dll")
				{
					StdStrDll.push_back(wfd.cFileName);

				}
			} while (FindNextFile(hFile, &wfd));
			for (vector<CString>::iterator it = StdStrDll.begin(); it != StdStrDll.end(); ++it)
			{
				bool(*p)();
				HMODULE DllHandle = LoadLibrary(*it);
				p = (DllInt)(GetProcAddress(DllHandle, "fun"));
				//如果p等于0就说明没有这个函数就卸载这个函数
				if (p == 0)
				{
					FreeLibrary(DllHandle);
					//printf("%s", *it);
				}
				else
				{
					p();
				}

			}






		}
		//////修改汇编代码
		else if (_stricmp(cmd, "502") == 0) {

			int addr;
			scanf("%8X", &addr);
			CStringA kk;
			kk.GetBufferSetLength(100);
			printf("请输入汇编代码");
			getchar();
			gets_s(kk.GetBuffer(), 100);
			//scanf("%s", kk);
			setDisam((LPVOID)addr, kk.GetBuffer(), 1);



		}
		//查看调试程序模块信息
		else if (_stricmp(cmd, "501") == 0) {

			int len = g_dll.size();
			for (int i = 0; i < len; i++) {
				printf("索引: %d 基址: %8X 名称: %s\n", i, g_dll[i].address, g_dll[i].NAME);
			}
		}

		else if (_stricmp(cmd, "11") == 0) {
			//内存执行断点
			printf("请输入地址：\n");

			int Addr;
			//PDWORD 	qwe;
			scanf_s("%x", &Addr);
			Member = Addr;
			//	VirtualProtectEx(g_hProc, (LPVOID)Addr, 1, PAGE_READWRITE, NULL);
			DWORD aa = 2;
			//////////////////////
			setMemberPoint(Addr, aa);



		}//条件断点    hashagei
		else if (_stricmp(cmd, "666") == 0) {
			printf("请输入地址：");
			DWORD  cd;
			scanf("%x", &cd);
			printf("请输入你的条件\n");
			string aaa;
			DWORD  cc;

			//	scanf_s("%s", &aaa);
			cin >> aaa;
			scanf("%x", &cc);
			DiZhi = cc;

			//条件断点
			IFDuanDian(cd, aaa, cc);



		}
		else if (_stricmp(cmd, "22") == 0) {
			//内存读写


			printf("请输入地址：\n");

			int Addr;
			//PDWORD 	qwe;
			scanf_s("%x", &Addr);
			Member = Addr;
			//	VirtualProtectEx(g_hProc, (LPVOID)Addr, 1, PAGE_READWRITE, NULL);
			DWORD aa = 2;
			//////////////////////
			setMemberPoint(Addr, aa);



		}



	}

_DONE:
	return DBG_CONTINUE;
}




 int  qqq()
{
	 AllocConsole();

	 freopen("CONOUT$", "w+t", stdout);//打开控制台

	 char path[MAX_PATH];
	 printf("");
	 gets_s(path, MAX_PATH);
	 
	STARTUPINFOA si = { sizeof(STARTUPINFOA) };
	PROCESS_INFORMATION pi = { 0 };

	//1. 创建调试会话
	BOOL bRet =
		CreateProcessA(path,
		0,
		0,
		0,
		0,
		DEBUG_ONLY_THIS_PROCESS | CREATE_NEW_CONSOLE,/*调试进程标志*/
		0,
		0,
		&si,
		&pi);
	if (bRet == FALSE) {

	}





	//2. 接收调试会话
	DEBUG_EVENT dbgEvent = { 0 };
	DWORD dwRet = 0;





	while (true)
	{
		// 等待被调试进程的调试事件.
		// 如果产生了调试事件, 那么事件信息会被保存到dbgEvent中.
		WaitForDebugEvent(&dbgEvent, -1);
		dwRet = DBG_CONTINUE;
		//隐藏peb
		//hidePeb(g_hThread, g_hProc);
		g_hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dbgEvent.dwProcessId);
		g_hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dbgEvent.dwThreadId);



		switch (dbgEvent.dwDebugEventCode)
		{
		case EXCEPTION_DEBUG_EVENT:
			dwRet = OnException(&dbgEvent.u.Exception.ExceptionRecord);
			break;
		case CREATE_PROCESS_DEBUG_EVENT:

			//hidePeb(g_hThread, g_hProc);

			printf("被调试进程有进程被创建\n");




			break;
		case CREATE_THREAD_DEBUG_EVENT:
			printf("被调试进程有一个新线程被创建\n");
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			printf("被调试进程有一个进程退出\n");
			break;
		case EXIT_THREAD_DEBUG_EVENT:
			printf("被调试进程有一个线程退出\n");
			break;
		case LOAD_DLL_DEBUG_EVENT:
		{
			CString str;
			DWORD status = 0;
			char* fileName = OnDebugEvent_LOAD_DLL_DEBUG_EVENT_m1(pi, dbgEvent, status);
			DLLINFO info;
			info.address = dbgEvent.u.LoadDll.lpBaseOfDll;
			strcpy(info.NAME, fileName);
			str.Format(_T("%s"), info.NAME);
			str = str.Left('.');
			HMODULE hModule = GetModuleHandle(str);
			str = info.AllPath;
			GetModuleFileName(hModule, str.GetBuffer(), MAX_PATH);
			//strcpy(info.AllPath, CStringA(str));
			g_dll.push_back(info);
			SymLoadModule64(g_hProc, dbgEvent.u.LoadDll.hFile, 0, 0, (DWORD64)dbgEvent.u.LoadDll.lpBaseOfDll, 0);
		}

			break;
		case UNLOAD_DLL_DEBUG_EVENT:
		{
			int len = g_dll.size();
			for (int i = 0; i < len; i++) {
				if (g_dll[i].address == dbgEvent.u.UnloadDll.lpBaseOfDll) {
					g_dll.erase(g_dll.begin() + i);
					break;
				}
			}
		}

			break;
		case OUTPUT_DEBUG_STRING_EVENT: break;
		case RIP_EVENT: break;
		}

		//3. 回复调试子系统
		//3.1 DBG_EXCEPTION_NOT_HANDLED : 异常没有被处理
		//3.2 DBG_CONTINUE : 继续执行.
		// 一般情况下, 都回复DBG_CONTINUE, 在调试事件是一个异常事件
		// 的时候, 并且异常是由调试器主动触发的, 在调试器修复异常之后
		// 可以回复DBG_CONTINUE , 如果异常是应用程序自身产生的,必须
		// 回复DBG_EXCEPTION_NOT_HANDLED.否则被调试的进程无法运行
		// 下去.
		ContinueDebugEvent(dbgEvent.dwProcessId,
			dbgEvent.dwThreadId,
			dwRet);
		CloseHandle(g_hProc);
		CloseHandle(g_hThread);
	}

	return 0;
}

