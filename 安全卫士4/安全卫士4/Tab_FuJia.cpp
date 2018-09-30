// Tab_FuJia.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "Tab_FuJia.h"
#include "afxdialogex.h"


// Tab_FuJia 对话框

IMPLEMENT_DYNAMIC(Tab_FuJia, CDialogEx)

Tab_FuJia::Tab_FuJia(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_FuJia::IDD, pParent)
{

}

Tab_FuJia::~Tab_FuJia()
{
}

void Tab_FuJia::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tab_FuJia, CDialogEx)
	
	ON_BN_CLICKED(IDC_BMD, &Tab_FuJia::OnBnClickedBmd)
END_MESSAGE_MAP()


// Tab_FuJia 消息处理程序


void Tab_FuJia::OnBnClickedLb()
{
	// TODO:  在此添加控件通知处理程序代码

	

	BOOL bb = RegisterHotKey(GetSafeHwnd(), 0x6789, MOD_CONTROL, 'F');


}


BOOL Tab_FuJia::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类




	return CDialogEx::PreTranslateMessage(pMsg);
}
void Tab_FuJia::adjustPrivilege(){
	HANDLE hToken = NULL;
	HANDLE hPro = GetCurrentProcess();
	OpenProcessToken(hPro, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp{};
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);




}


void Tab_FuJia::OnBnClickedBmd()
{

	adjustPrivilege();
	LockWorkStation();





	// TODO:  在此添加控件通知处理程序代码
}
