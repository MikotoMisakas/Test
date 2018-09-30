// Process_MoKuai.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Process_MoKuai.h"
#include "tlhelp32.h"
#include<Psapi.h >
#include<iostream>
#include<string>
#include<windows.h>
#include "afxdialogex.h"
#include <processthreadsapi.h>
using namespace std;

// Process_MoKuai �Ի���

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


// Process_MoKuai ��Ϣ�������


BOOL Process_MoKuai::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	DWORD dwOldStyle = Process_MoKuai_List.	GetExtendedStyle();//��ȡԭ���ķ��

	



	//���õ�ǰ�ؼ�����չ���
	Process_MoKuai_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//��ȡlist���
	CRect Re;
	Process_MoKuai_List.GetClientRect(Re);
	int nWidth = Re.Width();

	//Ϊlist��������Ϣ
	Process_MoKuai_List.InsertColumn(
		0,//��ǰ�б��
		L"ģ������",
		0,
		nWidth / 5

		);
	Process_MoKuai_List.InsertColumn(
		1,//��ǰ�б��
		L"��ַ",
		0,
		nWidth / 5

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//��ǰ�б��
	//	L"ƫ��",
	//	0,
	//	nWidth / 4

	//	);
	Process_MoKuai_List.InsertColumn(
		2,//��ǰ�б��
		L"��ڵ�",
		0,
		nWidth / 5

		);
	Process_MoKuai_List.InsertColumn(
		3,//��ǰ�б��
		L"�ڴ��С",
		0,
		nWidth / 5

		);
	Process_MoKuai_List.InsertColumn(
		4,//��ǰ�б��
		L"ģ��·��",
		0,
		nWidth / 5

		);
	//	Thread32First

	////����ģ�����
	//HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Thread_ID);
	//HANDLE        hModuleSnap = INVALID_HANDLE_VALUE;

	//MODULEENTRY32 Module32;
	// hModuleSnap = CreateToolhelp32Snapshot(
	//	           TH32CS_SNAPMODULE,  // ָ�����յ�����
	//			   Thread_ID);            // ָ������

	// Module32First(hModuleSnap, &Module32);
	// do
	// {
	//	 //����ȡ����Ϣ��ʾ������
	//	 CString szTemp;
	//	 szTemp.Format(L"%08X", Module32.);






	// } while (Module32Next, &Module32);//��ȡ��һ��ģ�����Ϣ

	HANDLE hProcess = NULL;
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Thread_ID);

	HMODULE hModules[0x2000] = {};//���ڻ�ȡģ��������

	DWORD dwNeed = 0;//��ȡģ��������

	//ö�ٽ���ģ�� ���ģ��������
	DWORD dwBuffsize = 0;
	EnumProcessModulesEx(hProcess, NULL, 0, &dwBuffsize, LIST_MODULES_ALL);
	HMODULE* pModuleHandleArr = (HMODULE*)new char[dwBuffsize];


	EnumProcessModulesEx(hProcess, pModuleHandleArr, dwBuffsize, &dwBuffsize, LIST_MODULES_ALL);

	TCHAR szModuleName[MAX_PATH];//��������ģ����������
	CString nTemp;
		//ӦΪdwBuffsize���ֽ��� ����ģ�����ĸ��� Ҫ����ÿ��������ֽ���
	for (int i = 0; i < dwBuffsize / sizeof(HMODULE); ++i)
	{
		MODULEINFO stcModuieInfo = { 0 };
		//���ݽ��̾�� ģ���� ��ȡģ����Ϣ�ĺ���
		GetModuleInformation(hProcess,//ģ���������̾��
			pModuleHandleArr[i],//Ҫ��ȡ��Ϣ��ģ��ľ��
			&stcModuieInfo,//�����ģ����Ϣ
			sizeof(stcModuieInfo)
			);
		//���ݽ��̾����ģ������ȡģ���·��
		GetModuleFileNameEx(hProcess,//ģ���������̾��
			pModuleHandleArr[i],//ģ����
			szModuleName,//��������ģ�����Ļ�����
			MAX_PATH//��������С


			);
		//nTemp.Format(L"%s", szModuleName[MAX_PATH]);


	//	Process_MoKuai_List.InsertItem(i, nTemp);
		//Process_MoKuai_List.SetItemText(i, 0, szTemp);

		//szModuleName[MAX_PATH];
		//ģ����ػ�ַ
		nTemp.Format(_T("%x"), stcModuieInfo.lpBaseOfDll);
		Process_MoKuai_List.InsertItem(i, 0);
		Process_MoKuai_List.SetItemText(i, 1, nTemp);
		
		//ģ����ڵ�ַ
		nTemp.Format(_T("%x"), stcModuieInfo.EntryPoint);
		Process_MoKuai_List.SetItemText(i, 2, nTemp);
		


		//ģ����ռ�ڴ��С
		nTemp.Format(_T("%x"), stcModuieInfo.SizeOfImage);
		Process_MoKuai_List.SetItemText(i, 3, nTemp);


		//
		nTemp.Format(L"%s", szModuleName);
		Process_MoKuai_List.SetItemText(i, 4, nTemp);

		//ƥ��ض��ַ���
		CString str = szModuleName;//�ַ���
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



	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
