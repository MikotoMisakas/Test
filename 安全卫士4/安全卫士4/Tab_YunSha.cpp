// Tab_YunSha.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Tab_YunSha.h"
#include "TiaoShi.h"
#include "afxdialogex.h"


// Tab_YunSha �Ի���

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


// Tab_YunSha ��Ϣ�������

//DWORD CALLBACK CallBackTs(LPVOID LPARAM){
//
//	//���Գ���
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
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	//bool hWnd= CreateProcess(L"D:\\cx\\��ȫ��ʿ4\\debugg\\Debug\\debugg.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &ti);
//	//AllocConsole();
//
//	//freopen("CONOUT$", "w+t", stdout);//�򿪿���̨
//
//	DWORD dwThreadId;
//	HANDLE hThread = CreateThread(0, 0, CallBackTs, 0, 0, &dwThreadId);
//
//
//}


void Tab_YunSha::OnBnClickedTsexe()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	STARTUPINFO si;
	PROCESS_INFORMATION ti;


	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&ti, sizeof(ti));
	
	bool hWnd= CreateProcess(L"D:\\��ȫ��ʿ4\\debugg\\Debug\\debugg.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &ti);
}

