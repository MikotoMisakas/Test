// Process_ChuangKou.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Process_ChuangKou.h"
#include <windows.h>
#define WINDOW_TEXT_LENGTH 256
#include <TlHelp32.h>
#include "afxdialogex.h"
#include <windows.h>
#define WINDOW_TEXT_LENGTH 256
#include <TlHelp32.h>








// Process_ChuangKou �Ի���

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


// Process_ChuangKou ��Ϣ�������

BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lparam){

	static int count = 0;
	WCHAR * szWindowName=new WCHAR[100];

	CString aaaa; 
	WCHAR* szClassName=new WCHAR[100];
	//��ȡ���ڵ�����
	GetWindowText(hWnd, szWindowName, MAXBYTE);
	CListCtrl* lparam1 = (CListCtrl*)(lparam);

	aaaa.Format(L"%s", szWindowName);
	lparam1->InsertItem(count, aaaa);



	aaaa.Format(_T("%d"), hWnd);
	lparam1->SetItemText(count,1, aaaa);


	//��ȡ��������
	GetClassName(hWnd, szClassName, MAXBYTE);

	aaaa.Format(_T("%s"), szClassName);
	lparam1->SetItemText(count++, 2, aaaa);



	//�жϱ����Ĵ����Ƿ�����
	IsWindowVisible(hWnd);
	delete[100] szClassName;
	delete[100] szWindowName;
		return TRUE;//����True�����������һ������ ����FALSE����������


}


BOOL Process_ChuangKou::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	//��������
	DWORD dwOldStyle = Process_Ck_List.GetExtendedStyle();
	//���õ�ǰ�ؼ�����չ���
	Process_Ck_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//������ͼ
		LVS_EX_GRIDLINES//������


		);
	CRect rc;
	Process_Ck_List.GetClientRect(rc);
	int nWidth = rc.Width();

	//Ϊlist�����Ϣ
	Process_Ck_List.InsertColumn(
		0, L"������", 0, nWidth / 3
		);
	Process_Ck_List.InsertColumn(
		1, L"���ھ��", 0, nWidth / 3
		);
	Process_Ck_List.InsertColumn(
		2, L"��������", 0, nWidth / 3
		);
	//�ص�������ʵ�ֵľ������
	//LPTSTR szWindowName;
	//BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lparam){


	//	

	//	//��ȡ���ڵ�����
	//	GetWindowText(hWnd, szWindowName, MAXBYTE);


	//	//��ȡ��������
	//	GetClassName(hWnd, szClassName, MAXBYTE);


	//	//�жϱ����Ĵ����Ƿ�����
	//	IsWindowVisible(hWnd)

	//		return TRUE;//����True�����������һ������ ����FALSE����������


	//}


	








	EnumWindows(EnumWindowCallBack, (LPARAM)(&Process_Ck_List));












	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
