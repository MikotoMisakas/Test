// Tab_FuJia.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Tab_FuJia.h"
#include "afxdialogex.h"


// Tab_FuJia �Ի���

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


// Tab_FuJia ��Ϣ�������


void Tab_FuJia::OnBnClickedLb()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	

	BOOL bb = RegisterHotKey(GetSafeHwnd(), 0x6789, MOD_CONTROL, 'F');


}


BOOL Tab_FuJia::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���




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





	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
