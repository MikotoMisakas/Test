// dbg.cpp : �������̨Ӧ�ó������ڵ㡣
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

//dll����
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

//�ڴ�ϵ�����
struct MemberPoint {
	LPVOID address;
	DWORD oldProtect;
	WORD type;
};
int g_isMemDbg = FALSE;

vector<MemberPoint> g_mem;// �ڴ�ϵ��б�

typedef struct BREAKPOINT {
	LPVOID address;
	BYTE   oldData;// ����int3�ϵ㸲�ǵ�1�ֽ�����
}BREAKPOINT;


typedef struct WeiLaoShi {
	LPVOID address;
	BYTE   oldData;// ����int3�ϵ㸲�ǵ�1�ֽ�����
	DWORD addd;
}BaoCunTiaoJianDuanDian;





typedef struct DLLINFO {
	LPVOID address;
	char NAME[100];
	char AllPath[MAX_PATH];
};
std::vector<BREAKPOINT> g_bps;// �ϵ��б�




//�����ϵ��б�
std::vector<WeiLaoShi> TiaoJian;// �ϵ��б�




std::vector<DLLINFO> g_dll;// dllģ���б�

BOOL   g_isDbgTf = FALSE;
HANDLE g_hProc = 0;
HANDLE g_hThread = 0;

//�ڴ�ִ�жϵ�
int Member = 0;
void showDisam(LPVOID address, int nLen = 10)
{
	// ��������Ĳ���:
	LPBYTE opcode = new BYTE[nLen * 15];
	SIZE_T dwRead = 0;
	// 1. �õ�������
	if (!ReadProcessMemory(g_hProc, address, opcode, nLen * 15, &dwRead)) {

	}
	// 2. ʹ�÷���������ȡ�������Ӧ�Ļ��
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
		if (len == -1) {/*����-1��ʾ�������޷��ҵ���Ӧ�Ļ��ָ��*/
			break;
		}

		// 3. ���.
		printf("%I64X | %s\n",
			da.VirtualAddr, da.CompleteInstr);
		da.VirtualAddr += len;
		da.EIP += len;
	}
}



DWORD getPeb(HANDLE hProcess)
{
	// ��ȡNTDLL.DLL�Ļ�ַ   
	HMODULE hModule = GetModuleHandle(TEXT("NTDLL.DLL"));
	if (hModule == NULL) return FALSE;

	// ��ȡZwQueryInformationProcess������ָ��   
	PZWQUERYINFORMATIONPROCESS pZwQueryInformationProcess =
		(PZWQUERYINFORMATIONPROCESS)GetProcAddress(hModule, "ZwQueryInformationProcess");

	// ��ѯ���̻�����Ϣ������PEB��ַ��   
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

// ����TF��������ϵ�
void setBreakpoint_tf() {
	// 1. ��ȡ�߳�������
	CONTEXT ct = { CONTEXT_ALL };
	if (!GetThreadContext(g_hThread, &ct)) {

	}
	EFLAGS* pEflags = (EFLAGS*)&ct.EFlags;
	// 2. �޸�TF��־λ
	pEflags->TF = 1;

	// 3. �����߳�������
	if (!SetThreadContext(g_hThread, &ct)) {

	}
}


void setBreakpoint_int3(LPVOID address) {
	BREAKPOINT bp = { 0 };
	//1. ���¶ϵ�ĵ�ַ��1�ֽڵ����ݱ���
	SIZE_T read = 0;
	if (!ReadProcessMemory(g_hProc, address, &bp.oldData, 1, &read)) {

	}
	//2. ��0xCCд���¶ϵ�ĵ�ַ
	if (!WriteProcessMemory(g_hProc, address, "\xCC", 1, &read)) {

	}
	bp.address = address;
	g_bps.push_back(bp);
}

void clearBreakpoint_int3(LPVOID address) {
	// 1. ���ֽڸ��ǻ�ȥ
	SIZE_T write = 0;
	for (auto& i : g_bps) {
		if (i.address == address) {
			if (!WriteProcessMemory(g_hProc, i.address, &i.oldData, 1, &write)) {
				printf("д��ʧ��\n");
			}
			// 2. ���߳������ĵ�eip--
			CONTEXT ct = { CONTEXT_ALL };
			if (!GetThreadContext(g_hThread, &ct)) {

			}
			ct.Eip--;
			if (!SetThreadContext(g_hThread, &ct)) {

			}

			// ����һ�������ϵ�, �������°�װint3�ϵ�.
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


	// *(DWORD*)(pInfo->lpImageName) ��������0, ���ܰ���msdn�����ж�
	// if ((NULL != pInfo) && (NULL != pInfo->lpImageName) && (NULL != *(DWORD*)(pInfo->lpImageName))) {

	// �������벻ͬDLLʱ, pInfo->lpBaseOfDll ���ǲ�ͬ��
	if ((NULL != pInfo) && (NULL != pInfo->lpBaseOfDll)) {
		// ��Ŀ��DLL�������е�dll���ư�
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
//����Ӳ��ִ�жϵ�
BOOL  SetBreakpoint_hardExec(HANDLE  g_hThread, DWORD  qq){

	CONTEXT ct = { CONTEXT_ALL };
	GetThreadContext(g_hThread, &ct);//��ȡ�̻߳�����
	DBG_REG7* pDr7 = (DBG_REG7*)&ct.Dr7;
	if (pDr7->L0 == 0)//FR0û�б�ʹ��
	{
		ct.Dr0 = qq;
		pDr7->RW0 = 0;
		pDr7->LEN0 = 0;//����������Ϊ0
		pDr7->L0 = 1;

	}
	else if (pDr7->L1 == 0)//dr1û�б�ʹ��
	{
		ct.Dr1 = qq;
		pDr7->RW1 = 0;
		pDr7->LEN1 = 0;
		pDr7->L1 = 1;

	}
	else if (pDr7->L2 == 0)//dr2û�б�ʹ��
	{
		ct.Dr2 = qq;
		pDr7->RW2 = 0;
		pDr7->LEN2 = 0;
		pDr7->L2 = 1;

	}
	else if (pDr7->L3 == 0)//dr2û�б�ʹ��
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

//�����ϵ�
BOOL IFDuanDian(DWORD DZ, string TJ, DWORD aaa){

	//setBreakpoint_int3((LPVOID)DZ);
	BREAKPOINT qwe;



	WeiLaoShi bp = { 0 };
	//1. ���¶ϵ�ĵ�ַ��1�ֽڵ����ݱ���
	SIZE_T read = 0;
	if (!ReadProcessMemory(g_hProc, (LPVOID)DZ, &bp.oldData, 1, &read)) {

	}
	//2. ��0xCCд���¶ϵ�ĵ�ַ
	if (!WriteProcessMemory(g_hProc, (LPVOID)DZ, "\xCC", 1, &read)) {

	}
	qwe.address = (LPVOID)DZ;
	qwe.oldData = bp.oldData;
	g_bps.push_back(qwe);
	bp.address = (LPVOID)DZ;//�ɴ���ַ�ϵ�����Ȣһ���ֽ�
	bp.addd = DZ;
	TiaoJian.push_back(bp);
	return TRUE;



}







//��ʾ�ڴ�
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


unsigned char* opcode = NULL;					//���ָ���׵�ַ
DWORD nCount = 0;

//�޸Ļ�����
void ToOpcode(char* szBuff, DWORD count)
{
	ks_engine *pengine = NULL;
	if (KS_ERR_OK != ks_open(KS_ARCH_X86, KS_MODE_32, &pengine))
	{
		printf("��������ʼ��ʧ��\n");
	}
	// ���õ���opcode�Ļ������׵�ַ
	UINT nOpcodeSize = 0; // ��������opcode���ֽ���


	int nRet = 0; // ���溯���ķ���ֵ�������жϺ����Ƿ�ִ�гɹ�
	size_t stat_count = 0; // ����ɹ�����ָ�������
	nRet = ks_asm(pengine, /* �����������ͨ��ks_open�����õ�*/
		szBuff, /*Ҫת���Ļ��ָ��*/
		0x401000, /*���ָ�����ڵĵ�ַ*/
		&opcode,/*�����opcode*/
		&nOpcodeSize,/*�����opcode���ֽ���*/
		&stat_count /*����ɹ�����ָ�������*/
		);
	nCount = nOpcodeSize;
	// ����ֵ����-1ʱ��������
	if (nRet == -1)
	{
		// ���������Ϣ
		// ks_errno ��ô�����
		// ks_strerror ��������ת�����ַ���������������ַ���
		printf("������Ϣ��%s\n", ks_strerror(ks_errno(pengine)));
	}
	// �رվ��
	ks_close(pengine);
}

//�����ڴ��
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

	// ��������Ĳ���:
	LPBYTE OPCODE = new BYTE[15 * 10];
	SIZE_T dwRead = 0;
	// 1. �õ�������
	if (!ReadProcessMemory(g_hProc, address, OPCODE, 15 * 10, &dwRead)) {
		printf("��ȡ�����ڴ�ʧ��");
	}
	for (int i = 0; i < nCount; i++)
	{
		OPCODE[i] = opcode[i];
	}
	if (!WriteProcessMemory(g_hProc, address, OPCODE, 15 * 10, &dwRead)) {
		printf("д������ڴ�ʧ��");
	}
}


//////Ӳ����д�ϵ�
BOOL SetBreakpoint_harRw(HANDLE hThread, ULONG_PTR uAddress, DWORD dwLen){
	//��ȡ������
	CONTEXT ct = { 0 };
	ct.ContextFlags = CONTEXT_ALL;
	GetThreadContext(hThread, &ct);


	//�Ե�ַ�ͳ��Ƚ��д���
	//������ȡ����
	if (dwLen == 1)//2�ֽڶ�������
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
	//�ж���Щ�Ĵ���û�б�ʹ��
	DBG_REG7* pDr7 = (DBG_REG7*)&ct.Dr7;
	if (pDr7->L0 == 0)//dr7û�б�ʹ��
	{
		ct.Dr0 = uAddress;
		pDr7->RW0 = 3;
		pDr7->LEN0 = dwLen;
		pDr7->L0 = 1;

	}
	else if (pDr7->L1 == 0)//DR1û�б�ʹ��
	{
		ct.Dr1 = uAddress;
		pDr7->RW1 = 3;
		pDr7->LEN1 = dwLen;
		pDr7->L1 = 1;
	}
	else if (pDr7->L2 == 0)//DR2û�б�ʹ��
	{
		ct.Dr2 = uAddress;
		pDr7->RW2 = 3;
		pDr7->LEN2 = dwLen;
		pDr7->L2 = 1;
	}
	else if (pDr7->L3 == 0)//DR2û�б�ʹ��
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
		printf("��ȡ�����ڴ�ʧ��");
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
	// ������int3�ϵ��������û�ȥ.
	SIZE_T read = 0;
	for (auto &i : g_bps) {
		//2. ��0xCCд���¶ϵ�ĵ�ַ
		if (!WriteProcessMemory(g_hProc, i.address, "\xCC", 1, &read)) {

		}
	}
	int a = 0;
	int len = g_mem.size();
	switch (pExcept->ExceptionCode)
	{

		// ��һ��������int3�쳣����ϵͳ�ϵ�.
	case EXCEPTION_BREAKPOINT:/*�ϵ��쳣,int3ָ���������쳣*/
	{
		static bool isSystemBreakpoint = true;
		if (isSystemBreakpoint) {
			//peb����
			hidePeb(g_hThread, g_hProc);
			isSystemBreakpoint = false;






			printf("����ϵͳ�ϵ�:%08X\n", pExcept->ExceptionAddress);
		}
		else {
			// �޸�int3�쳣
			// 1. ����int3���ǵ����ݻ�ԭ��ȥ.
			// 2. int3�������쳣, ����֮��, eipָ����int3����һ���ֽ�.
			//    ����Ҫ��eip--.





			clearBreakpoint_int3(pExcept->ExceptionAddress);


			CONTEXT ct = { 0 };
			ct.ContextFlags = CONTEXT_CONTROL;
			GetThreadContext(g_hThread, &ct);
			DWORD a = ct.Eax;
			//���������Ҫ��eax��ֵ�Ͱɶϵ�д��ȥ

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
	case EXCEPTION_ACCESS_VIOLATION:/*�ڴ�����쳣*/

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
			GetThreadContext(g_hThread, &ct);//��ȡ�̻߳�����
			if (ct.Eip != Member)
			{
				VirtualProtectEx(g_hProc, (LPVOID)Member, 1, PAGE_NOACCESS, (PDWORD)&a);
				ct.Eip++;
			}
			SetThreadContext(g_hThread, &ct);



			goto _DONE;
		}




		break;
	case EXCEPTION_SINGLE_STEP:/*Ӳ���ϵ��TF�����־�쳣*/
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
			//tf�ϵ�
		}
		// ���tf�ϵ�, ���û����뵥��֮����µ�
		// ���ǵ��������õ�.����ǵ��������õ�, �Ͳ���
		// ���������������
		//   		if (g_isDbgTf == TRUE) {
		//   
		// 			g_isDbgTf = FALSE;
		//   			return DBG_CONTINUE;
		//   		}
		SetThreadContext(g_hThread, &ct);
	}
		break;

	default:
		printf("�����Խ������������쳣:%08X\n", pExcept->ExceptionAddress);
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
		printf("����>");
		scanf_s("%s", cmd, 100);
		//��������
		if (_stricmp(cmd, "t") == 0) {

			setBreakpoint_tf();
			g_isDbgTf = FALSE;
			break;
		}//ִ������
		else if (_stricmp(cmd, "g") == 0) {
			break;
		}//�¶ϵ�
		else if (_stricmp(cmd, "bp") == 0) {
			SIZE_T addr = 0;
			scanf_s("%8X", &addr);
			setBreakpoint_int3((LPVOID)addr);
		}
		//�鿴�Ĵ���
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
		//�޸ļĴ���
		else if (_stricmp(cmd, "xgex") == 0) {
			string  aa;

			cin >> aa;
			DWORD bb;
			ct.ContextFlags = CONTEXT_ALL;
			GetThreadContext(g_hThread, &ct);
			if (aa == "eax")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Eax = bb;
				SetThreadContext(g_hThread, &ct);
			}
			else if (aa == "eip")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Eip = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "ebx")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Ebx = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "ecx")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Ecx = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "edx")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Edx = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "esi")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Esi = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "edi")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Edi = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "esp")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Esp = bb;
				SetThreadContext(g_hThread, &ct);

			}
			else if (aa == "ebp")
			{
				printf("������Ҫ�޸ĵ�ֵ\n");
				scanf_s("%x", &bb);
				ct.Ebp = bb;
				SetThreadContext(g_hThread, &ct);

			}

		}
		//Ӳ��ִ�жϵ�
		else if (_stricmp(cmd, "yjddr") == 0) {
			DWORD   qq;

			scanf_s("%x", &qq);
			SetBreakpoint_hardExec(g_hThread, qq);

		}
		//Ӳ����д�ϵ�
		else if (_stricmp(cmd, "yjwr") == 0) {

			DWORD   qq;
			printf("�������ַ\n");
			scanf_s("%x", &qq);

			DWORD down = 1;

			SetBreakpoint_harRw(g_hThread, qq, down);

		}


		//�鿴��ջ��
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
			//��ʾ�ڴ�
			int addr;
			//cin >> addr;
			scanf_s("%x", &addr);
			showMember((LPVOID)addr);
		}

		else if (_stricmp(cmd, "r") == 0) {
			//��������

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


		//�޸��ڴ�
		else if (_stricmp(cmd, "happy") == 0) {
			//�޸��ڴ�
			int nLen;
			scanf_s("%x", &nLen);
			string str;
			printf("\n%8x:", nLen);
			int d = 0;
			scanf_s("%X", &d);
			xiugaineicun((LPVOID)nLen, d);
		}//֧�ֲ��
		else if (_stricmp(cmd, "cj") == 0) {
			//����ı�д
			//����Ŀ¼�µ�dll



			//���������ļ����б�
			//vector<CString>StdStrDll;


			//����dll�ļ�
			//	WIN32_FIND_DATA wfd;
			//CString sPath = "*.dll";//����ָ��Ŀ¼�����и�ʽ���ļ�

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
				printf("��Ч\n");
				//return ;
			}
			do
			{//����ǵ�ǰĿ¼�������Լ�Ŀ¼
				if (wfd.cFileName == L"." || wfd.cFileName == L"..")
				{
					continue;
				}//�ж����ļ���
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
				//���p����0��˵��û�����������ж���������
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
		//////�޸Ļ�����
		else if (_stricmp(cmd, "502") == 0) {

			int addr;
			scanf("%8X", &addr);
			CStringA kk;
			kk.GetBufferSetLength(100);
			printf("�����������");
			getchar();
			gets_s(kk.GetBuffer(), 100);
			//scanf("%s", kk);
			setDisam((LPVOID)addr, kk.GetBuffer(), 1);



		}
		//�鿴���Գ���ģ����Ϣ
		else if (_stricmp(cmd, "501") == 0) {

			int len = g_dll.size();
			for (int i = 0; i < len; i++) {
				printf("����: %d ��ַ: %8X ����: %s\n", i, g_dll[i].address, g_dll[i].NAME);
			}
		}

		else if (_stricmp(cmd, "11") == 0) {
			//�ڴ�ִ�жϵ�
			printf("�������ַ��\n");

			int Addr;
			//PDWORD 	qwe;
			scanf_s("%x", &Addr);
			Member = Addr;
			//	VirtualProtectEx(g_hProc, (LPVOID)Addr, 1, PAGE_READWRITE, NULL);
			DWORD aa = 2;
			//////////////////////
			setMemberPoint(Addr, aa);



		}//�����ϵ�    hashagei
		else if (_stricmp(cmd, "666") == 0) {
			printf("�������ַ��");
			DWORD  cd;
			scanf("%x", &cd);
			printf("�������������\n");
			string aaa;
			DWORD  cc;

			//	scanf_s("%s", &aaa);
			cin >> aaa;
			scanf("%x", &cc);
			DiZhi = cc;

			//�����ϵ�
			IFDuanDian(cd, aaa, cc);



		}
		else if (_stricmp(cmd, "22") == 0) {
			//�ڴ��д


			printf("�������ַ��\n");

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

	 freopen("CONOUT$", "w+t", stdout);//�򿪿���̨

	 char path[MAX_PATH];
	 printf("");
	 gets_s(path, MAX_PATH);
	 
	STARTUPINFOA si = { sizeof(STARTUPINFOA) };
	PROCESS_INFORMATION pi = { 0 };

	//1. �������ԻỰ
	BOOL bRet =
		CreateProcessA(path,
		0,
		0,
		0,
		0,
		DEBUG_ONLY_THIS_PROCESS | CREATE_NEW_CONSOLE,/*���Խ��̱�־*/
		0,
		0,
		&si,
		&pi);
	if (bRet == FALSE) {

	}





	//2. ���յ��ԻỰ
	DEBUG_EVENT dbgEvent = { 0 };
	DWORD dwRet = 0;





	while (true)
	{
		// �ȴ������Խ��̵ĵ����¼�.
		// ��������˵����¼�, ��ô�¼���Ϣ�ᱻ���浽dbgEvent��.
		WaitForDebugEvent(&dbgEvent, -1);
		dwRet = DBG_CONTINUE;
		//����peb
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

			printf("�����Խ����н��̱�����\n");




			break;
		case CREATE_THREAD_DEBUG_EVENT:
			printf("�����Խ�����һ�����̱߳�����\n");
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			printf("�����Խ�����һ�������˳�\n");
			break;
		case EXIT_THREAD_DEBUG_EVENT:
			printf("�����Խ�����һ���߳��˳�\n");
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

		//3. �ظ�������ϵͳ
		//3.1 DBG_EXCEPTION_NOT_HANDLED : �쳣û�б�����
		//3.2 DBG_CONTINUE : ����ִ��.
		// һ�������, ���ظ�DBG_CONTINUE, �ڵ����¼���һ���쳣�¼�
		// ��ʱ��, �����쳣���ɵ���������������, �ڵ������޸��쳣֮��
		// ���Իظ�DBG_CONTINUE , ����쳣��Ӧ�ó������������,����
		// �ظ�DBG_EXCEPTION_NOT_HANDLED.���򱻵��ԵĽ����޷�����
		// ��ȥ.
		ContinueDebugEvent(dbgEvent.dwProcessId,
			dbgEvent.dwThreadId,
			dwRet);
		CloseHandle(g_hProc);
		CloseHandle(g_hThread);
	}

	return 0;
}

