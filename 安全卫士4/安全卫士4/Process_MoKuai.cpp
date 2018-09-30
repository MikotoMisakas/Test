// Process_MoKuai.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "Process_MoKuai.h"
#include "tlhelp32.h"
#include<Psapi.h >
#include<iostream>
#include<string>
#include<windows.h>
#include "afxdialogex.h"
#include <processthreadsapi.h>
using namespace std;

// Process_MoKuai 对话框

IMPLEMENT_DYNAMIC(Process_MoKuai, CDialogEx)

Process_MoKuai::Process_MoKuai(DWORD pppid, CWnd* pParent /*=NULL*/)
	: CDialogEx(Process_MoKuai::IDD, pParent)
{
	Thread_ID = pppid;
}

Process_MoKuai::~Process_MoKuai()
{
}

void Process_MoKuai::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Process_MoKuai_List, Process_MoKuai_List);
}


BEGIN_MESSAGE_MAP(Process_MoKuai, CDialogEx)
END_MESSAGE_MAP()


// Process_MoKuai 消息处理程序


BOOL Process_MoKuai::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	DWORD dwOldStyle = Process_MoKuai_List.	GetExtendedStyle();//获取原来的风格

	



	//设置当前控件的扩展风格
	Process_MoKuai_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//获取list宽度
	CRect Re;
	Process_MoKuai_List.GetClientRect(Re);
	int nWidth = Re.Width();

	//为list插入列信息
	Process_MoKuai_List.InsertColumn(
		0,//当前列编号
		L"模块名称",
		0,
		nWidth / 5

		);
	Process_MoKuai_List.InsertColumn(
		1,//当前列编号
		L"基址",
		0,
		nWidth / 5

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//当前列编号
	//	L"偏移",
	//	0,
	//	nWidth / 4

	//	);
	Process_MoKuai_List.InsertColumn(
		2,//当前列编号
		L"入口点",
		0,
		nWidth / 5

		);
	Process_MoKuai_List.InsertColumn(
		3,//当前列编号
		L"内存大小",
		0,
		nWidth / 5

		);
	Process_MoKuai_List.InsertColumn(
		4,//当前列编号
		L"模块路径",
		0,
		nWidth / 5

		);
	//	Thread32First

	////创建模块快照
	//HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Thread_ID);
	//HANDLE        hModuleSnap = INVALID_HANDLE_VALUE;

	//MODULEENTRY32 Module32;
	// hModuleSnap = CreateToolhelp32Snapshot(
	//	           TH32CS_SNAPMODULE,  // 指定快照的类型
	//			   Thread_ID);            // 指定进程

	// Module32First(hModuleSnap, &Module32);
	// do
	// {
	//	 //将获取的信息显示到界面
	//	 CString szTemp;
	//	 szTemp.Format(L"%08X", Module32.);






	// } while (Module32Next, &Module32);//获取下一个模块的信息

	HANDLE hProcess = NULL;
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Thread_ID);

	HMODULE hModules[0x2000] = {};//用于获取模块句柄个数

	DWORD dwNeed = 0;//获取模块句柄个数

	//枚举进程模块 输出模块句柄数组
	DWORD dwBuffsize = 0;
	EnumProcessModulesEx(hProcess, NULL, 0, &dwBuffsize, LIST_MODULES_ALL);
	HMODULE* pModuleHandleArr = (HMODULE*)new char[dwBuffsize];


	EnumProcessModulesEx(hProcess, pModuleHandleArr, dwBuffsize, &dwBuffsize, LIST_MODULES_ALL);

	TCHAR szModuleName[MAX_PATH];//用来保存模块名的数组
	CString nTemp;
		//应为dwBuffsize是字节数 不是模块句柄的个数 要除以每个句柄的字节数
	for (int i = 0; i < dwBuffsize / sizeof(HMODULE); ++i)
	{
		MODULEINFO stcModuieInfo = { 0 };
		//根据进程句柄 模块句柄 获取模块信息的函数
		GetModuleInformation(hProcess,//模块所属进程句柄
			pModuleHandleArr[i],//要获取信息的模块的句柄
			&stcModuieInfo,//输出的模块信息
			sizeof(stcModuieInfo)
			);
		//根据进程句柄和模块句柄获取模块的路径
		GetModuleFileNameEx(hProcess,//模块所属进程句柄
			pModuleHandleArr[i],//模块句柄
			szModuleName,//用来保存模块名的缓冲区
			MAX_PATH//缓冲区大小


			);
		//nTemp.Format(L"%s", szModuleName[MAX_PATH]);


	//	Process_MoKuai_List.InsertItem(i, nTemp);
		//Process_MoKuai_List.SetItemText(i, 0, szTemp);

		//szModuleName[MAX_PATH];
		//模块加载基址
		nTemp.Format(_T("%x"), stcModuieInfo.lpBaseOfDll);
		Process_MoKuai_List.InsertItem(i, 0);
		Process_MoKuai_List.SetItemText(i, 1, nTemp);
		
		//模块入口地址
		nTemp.Format(_T("%x"), stcModuieInfo.EntryPoint);
		Process_MoKuai_List.SetItemText(i, 2, nTemp);
		


		//模块所占内存大小
		nTemp.Format(_T("%x"), stcModuieInfo.SizeOfImage);
		Process_MoKuai_List.SetItemText(i, 3, nTemp);


		//
		nTemp.Format(L"%s", szModuleName);
		Process_MoKuai_List.SetItemText(i, 4, nTemp);

		//匹配截断字符串
		CString str = szModuleName;//字符串
		//USES_CONVERSION;
		//W2A()//A2W()
		int nP1 = 0;
		while (true)
		{
			int nP2=str.Find(L"\\", nP1 + 1);
			if (nP2 != -1)
			{
				nP1 = nP2;
			}
			else
				break;
		}
		CString cName = str.Mid(nP1 + 1, str.GetLength() - nP1 - 1);
		//str = szModuleName;

		Process_MoKuai_List.SetItemText(i, 0, cName);


	}



	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
