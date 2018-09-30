// Procces_Thread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Procces_Thread.h"
#include "tlhelp32.h"
#include "afxdialogex.h"


// Procces_Thread �Ի���

IMPLEMENT_DYNAMIC(Procces_Thread, CDialogEx)

Procces_Thread::Procces_Thread(DWORD ppppid,CWnd* pParent /*=NULL*/)
	: CDialogEx(Procces_Thread::IDD, pParent)
{
	Thread_ID = ppppid;
}

Procces_Thread::~Procces_Thread()
{
}

void Procces_Thread::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, Process_Thread_List_BL);
}


BEGIN_MESSAGE_MAP(Procces_Thread, CDialogEx)
END_MESSAGE_MAP()


// Procces_Thread ��Ϣ�������


BOOL Procces_Thread::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwOldStyle = Process_Thread_List_BL.GetExtendedStyle();//��ȡԭ���ķ��




	//���õ�ǰ�ؼ�����չ���
	Process_Thread_List_BL.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//��ȡlist���
	CRect Re;
	Process_Thread_List_BL.GetClientRect(Re);
	int nWidth = Re.Width();

	//Ϊlist��������Ϣ
	Process_Thread_List_BL.InsertColumn(
		0,//��ǰ�б��
		L"�߳�id",
		0,
		nWidth / 3

		);
	Process_Thread_List_BL.InsertColumn(
		1,//��ǰ�б��
		L"��������id",
		0,
		nWidth / 3

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//��ǰ�б��
	//	L"ƫ��",
	//	0,
	//	nWidth / 4

	//	);
	Process_Thread_List_BL.InsertColumn(
		2,//��ǰ�б��
		L"�߳����ȼ�",
		0,
		nWidth / 3

		);
	//	Thread32First

	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, Thread_ID);


	//���������߳���Ϣ
	THREADENTRY32 stcTe32 = { sizeof(THREADENTRY32) };

	//��ȡ��һ���߳�
	Thread32First(hThreadSnap, &stcTe32);

	CString szTemp;
	int i = 1;
	do
	{
		// ɸѡָ�������µ��߳�,���뵽�߳��б�ؼ���
		if (stcTe32.th32OwnerProcessID == Thread_ID)
		{
			// ��ǰ�߳�ID
			szTemp.Format(L"%d", stcTe32.th32ThreadID);
			Process_Thread_List_BL.InsertItem(0, 0);
			Process_Thread_List_BL.SetItemText(i, 0, szTemp);
				//PE_DR_LIST.InsertItem(i, q);
				//PE_DR_LIST.SetItemText(i, 1, qwe);
			// ��������ID
			szTemp.Format(L"%d", stcTe32.th32OwnerProcessID);

			Process_Thread_List_BL.SetItemText(i, 1, szTemp);



			// �߳����ȼ�
			szTemp.Format(L"%d", stcTe32.tpBasePri);
			Process_Thread_List_BL.SetItemText(i, 2, szTemp);
		}
	} while (Thread32Next(hThreadSnap, &stcTe32));


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
