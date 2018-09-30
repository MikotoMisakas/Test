// Process_ChuangKou.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "Process_ChuangKou.h"
#include <windows.h>
#define WINDOW_TEXT_LENGTH 256
#include <TlHelp32.h>
#include "afxdialogex.h"
#include <windows.h>
#define WINDOW_TEXT_LENGTH 256
#include <TlHelp32.h>








// Process_ChuangKou 对话框

IMPLEMENT_DYNAMIC(Process_ChuangKou, CDialogEx)

Process_ChuangKou::Process_ChuangKou(DWORD ppppid ,CWnd* pParent /*=NULL*/)
	: CDialogEx(Process_ChuangKou::IDD, pParent)
{
	ppppid = PID;
}

Process_ChuangKou::~Process_ChuangKou()
{
}

void Process_ChuangKou::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChuangKou, Process_Ck_List);
}


BEGIN_MESSAGE_MAP(Process_ChuangKou, CDialogEx)
END_MESSAGE_MAP()


// Process_ChuangKou 消息处理程序

BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lparam){

	static int count = 0;
	WCHAR * szWindowName=new WCHAR[100];

	CString aaaa; 
	WCHAR* szClassName=new WCHAR[100];
	//获取窗口的名称
	GetWindowText(hWnd, szWindowName, MAXBYTE);
	CListCtrl* lparam1 = (CListCtrl*)(lparam);

	aaaa.Format(L"%s", szWindowName);
	lparam1->InsertItem(count, aaaa);



	aaaa.Format(_T("%d"), hWnd);
	lparam1->SetItemText(count,1, aaaa);


	//获取窗口类名
	GetClassName(hWnd, szClassName, MAXBYTE);

	aaaa.Format(_T("%s"), szClassName);
	lparam1->SetItemText(count++, 2, aaaa);



	//判断遍历的窗口是否被隐藏
	IsWindowVisible(hWnd);
	delete[100] szClassName;
	delete[100] szWindowName;
		return TRUE;//返回True会继续遍历下一个窗口 返回FALSE将结束遍历


}


BOOL Process_ChuangKou::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	//遍历窗口
	DWORD dwOldStyle = Process_Ck_List.GetExtendedStyle();
	//设置当前控件的扩展风格
	Process_Ck_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//报表试图
		LVS_EX_GRIDLINES//网格线


		);
	CRect rc;
	Process_Ck_List.GetClientRect(rc);
	int nWidth = rc.Width();

	//为list添加信息
	Process_Ck_List.InsertColumn(
		0, L"窗口名", 0, nWidth / 3
		);
	Process_Ck_List.InsertColumn(
		1, L"窗口句柄", 0, nWidth / 3
		);
	Process_Ck_List.InsertColumn(
		2, L"窗口类名", 0, nWidth / 3
		);
	//回调函数中实现的具体操作
	//LPTSTR szWindowName;
	//BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lparam){


	//	

	//	//获取窗口的名称
	//	GetWindowText(hWnd, szWindowName, MAXBYTE);


	//	//获取窗口类名
	//	GetClassName(hWnd, szClassName, MAXBYTE);


	//	//判断遍历的窗口是否被隐藏
	//	IsWindowVisible(hWnd)

	//		return TRUE;//返回True会继续遍历下一个窗口 返回FALSE将结束遍历


	//}


	








	EnumWindows(EnumWindowCallBack, (LPARAM)(&Process_Ck_List));












	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
