// Tab_NeiCun2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include<psapi.h >
#include "Tab_NeiCun2.h"
#include "afxdialogex.h"


// Tab_NeiCun2 �Ի���

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


// Tab_NeiCun2 ��Ϣ�������


BOOL Tab_NeiCun2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UINT pp[] = { 0x1111, 0x2222, 0x3333 };

	CStatusBar *m_bar = new CStatusBar;
	m_bar->Create(GetParent(), WS_CHILD | WS_VISIBLE | CBRS_BOTTOM);
	m_bar->SetIndicators(pp, 3);//����״̬����Ŀ����
	CRect rect;
	GetClientRect(&rect);
	m_bar->SetPaneInfo(0, 0x1111, SBPS_STRETCH, 0);
	m_bar->SetPaneInfo(1, 0x2222, SBPS_POPOUT, 320);
	m_bar->SetPaneInfo(2, 0x3333, SBPS_POPOUT, 120);//����������120��λ
	m_bar->SetPaneText(0, L"��������");
	m_bar->SetPaneText(1, L"Love");
	m_bar->SetPaneText(2, L"�����");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0x3333);
	;
	//
	// ���� �������ռ� ��һ����ʾIDS_STRING_MESSAGE 0 ��ʾĬ�ϳ���
	//m_bar.SetPaneInfo(0, , SBPS_STRETCH, 0);


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Tab_NeiCun2::OnBnClickedQinglineicun()
{

	//��ȡ�ڴ浱ǰ״̬
	MEMORYSTATUSEX stcMemStatusEx = { 0 };

	stcMemStatusEx.dwLength = sizeof(stcMemStatusEx);
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG preUsMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;


	//�����ڴ�
	DWORD dwPldList[1000] = { 0 };
	DWORD bufSize = sizeof(dwPldList);
	DWORD dwNeedSize = 0;
	EnumProcesses(dwPldList, bufSize, &dwNeedSize);

	for (DWORD i = 0; i < dwNeedSize / sizeof(DWORD);i++)
	{
		HANDLE hProcess = OpenProcess(PROCESS_SET_QUOTA, false, dwPldList[i]);
		SetProcessWorkingSetSize(hProcess, -1, -1);

	}

	//��ȡ�������ڴ�״̬
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG afterCleanUsedMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;




	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
