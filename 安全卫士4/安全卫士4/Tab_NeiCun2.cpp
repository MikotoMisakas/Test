// Tab_NeiCun2.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include<psapi.h >
#include "Tab_NeiCun2.h"
#include "afxdialogex.h"


// Tab_NeiCun2 对话框

IMPLEMENT_DYNAMIC(Tab_NeiCun2, CDialogEx)

Tab_NeiCun2::Tab_NeiCun2(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_NeiCun2::IDD, pParent)
{

}

Tab_NeiCun2::~Tab_NeiCun2()
{
}

void Tab_NeiCun2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tab_NeiCun2, CDialogEx)
	ON_BN_CLICKED(IDC_QingLiNeiCun, &Tab_NeiCun2::OnBnClickedQinglineicun)
END_MESSAGE_MAP()


// Tab_NeiCun2 消息处理程序


BOOL Tab_NeiCun2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UINT pp[] = { 0x1111, 0x2222, 0x3333 };

	CStatusBar *m_bar = new CStatusBar;
	m_bar->Create(GetParent(), WS_CHILD | WS_VISIBLE | CBRS_BOTTOM);
	m_bar->SetIndicators(pp, 3);//设置状态栏项目栏数
	CRect rect;
	GetClientRect(&rect);
	m_bar->SetPaneInfo(0, 0x1111, SBPS_STRETCH, 0);
	m_bar->SetPaneInfo(1, 0x2222, SBPS_POPOUT, 320);
	m_bar->SetPaneInfo(2, 0x3333, SBPS_POPOUT, 120);//第三栏长度120单位
	m_bar->SetPaneText(0, L"御坂美琴");
	m_bar->SetPaneText(1, L"Love");
	m_bar->SetPaneText(2, L"孔令辉");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0x3333);
	;
	//
	// 窗格 以填满空间 第一栏显示IDS_STRING_MESSAGE 0 表示默认长度
	//m_bar.SetPaneInfo(0, , SBPS_STRETCH, 0);


	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void Tab_NeiCun2::OnBnClickedQinglineicun()
{

	//获取内存当前状态
	MEMORYSTATUSEX stcMemStatusEx = { 0 };

	stcMemStatusEx.dwLength = sizeof(stcMemStatusEx);
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG preUsMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;


	//清理内存
	DWORD dwPldList[1000] = { 0 };
	DWORD bufSize = sizeof(dwPldList);
	DWORD dwNeedSize = 0;
	EnumProcesses(dwPldList, bufSize, &dwNeedSize);

	for (DWORD i = 0; i < dwNeedSize / sizeof(DWORD);i++)
	{
		HANDLE hProcess = OpenProcess(PROCESS_SET_QUOTA, false, dwPldList[i]);
		SetProcessWorkingSetSize(hProcess, -1, -1);

	}

	//获取清理后的内存状态
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG afterCleanUsedMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;




	// TODO:  在此添加控件通知处理程序代码
}
