// Tab_YunSha.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "Tab_YunSha.h"
#include "TiaoShi.h"
#include "afxdialogex.h"


// Tab_YunSha 对话框

IMPLEMENT_DYNAMIC(Tab_YunSha, CDialogEx)

Tab_YunSha::Tab_YunSha(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_YunSha::IDD, pParent)
{

}

Tab_YunSha::~Tab_YunSha()
{
}

void Tab_YunSha::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tab_YunSha, CDialogEx)
	//ON_BN_CLICKED(IDC_TS, &Tab_YunSha::OnBnClickedTs)
	ON_BN_CLICKED(IDC_TSEXE, &Tab_YunSha::OnBnClickedTsexe)
END_MESSAGE_MAP()


// Tab_YunSha 消息处理程序

//DWORD CALLBACK CallBackTs(LPVOID LPARAM){
//
//	//调试程序
//	
//	qqq();
//	return 0;
//}



//
//void Tab_YunSha::OnBnClickedTs()
//{
//	STARTUPINFO si;
//	PROCESS_INFORMATION ti;
//
//
//	ZeroMemory(&si, sizeof(si));
//	ZeroMemory(&ti, sizeof(ti));
//	// TODO:  在此添加控件通知处理程序代码
//	//bool hWnd= CreateProcess(L"D:\\cx\\安全卫士4\\debugg\\Debug\\debugg.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &ti);
//	//AllocConsole();
//
//	//freopen("CONOUT$", "w+t", stdout);//打开控制台
//
//	DWORD dwThreadId;
//	HANDLE hThread = CreateThread(0, 0, CallBackTs, 0, 0, &dwThreadId);
//
//
//}


void Tab_YunSha::OnBnClickedTsexe()
{
	// TODO:  在此添加控件通知处理程序代码
	STARTUPINFO si;
	PROCESS_INFORMATION ti;


	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&ti, sizeof(ti));
	
	bool hWnd= CreateProcess(L"D:\\安全卫士4\\debugg\\Debug\\debugg.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &ti);
}

