// Tab_FuWu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "WIN_FUWU_LIST.h"
#include "Tab_FuWu.h"
#include<windows.h>
#include "afxdialogex.h"
#include <winsvc.h>


// Tab_FuWu �Ի���

IMPLEMENT_DYNAMIC(Tab_FuWu, CDialogEx)

Tab_FuWu::Tab_FuWu(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_FuWu::IDD, pParent)
{

}

Tab_FuWu::~Tab_FuWu()
{
}

void Tab_FuWu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FUWU_LIST, Win_FuWu_List);
}


BEGIN_MESSAGE_MAP(Tab_FuWu, CDialogEx)
	//ON_COMMAND(ID_11111111, &Tab_FuWu::On11111111)
	ON_COMMAND(ID_11111111, &Tab_FuWu::Onopenservice)
	ON_NOTIFY(NM_RCLICK, IDC_FUWU_LIST, &Tab_FuWu::OnRclickFuwuList)
	ON_COMMAND(ID_32779, &Tab_FuWu::FuWu999)
END_MESSAGE_MAP()


// Tab_FuWu ��Ϣ�������

BOOL Tab_FuWu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString ab;
	ab = "��������";
	CString cc;
	cc = "��ֹͣ";

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	DWORD dwOldStyle = Win_FuWu_List.GetExtendedStyle();
	//���õ�ǰ�ؼ�����չ���
	Win_FuWu_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//��ȡlist���
	CRect Re;
	Win_FuWu_List.GetClientRect(Re);
	int nWidth = Re.Width();

	//Ϊlist��������Ϣ
	Win_FuWu_List.InsertColumn(
		0,//��ǰ�б��
		L"����",
		0,
		nWidth / 4

		);
	Win_FuWu_List.InsertColumn(
		1,//��ǰ�б��
		L"PID",
		0,
		nWidth / 4

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//��ǰ�б��
	//	L"ƫ��",
	//	0,
	//	nWidth / 4

	//	);
	Win_FuWu_List.InsertColumn(
		2,//��ǰ�б��
		L"����",
		0,
		nWidth / 4

		);

	Win_FuWu_List.InsertColumn(
		3,//��ǰ�б��
		L"״̬",
		0,
		nWidth / 4

		);
	
	///////////////////////////////////////////
	//��������
	SC_HANDLE hScm = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);


	//��һ�ε��û�ȡ��Ҫ���ڴ��С
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatusEx(hScm, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,//���з���״̬
		NULL,//������
		0,//Huanchongqu daxiao
		&dwSize,//��Ҫ�Ĵ�С
		&dwServiceNum,//����������ĸ���
		NULL, NULL

		);
	//������Ҫ���ڴ�
	LPENUM_SERVICE_STATUS_PROCESS pEnumSerice = (LPENUM_SERVICE_STATUS_PROCESS)new char[dwSize];

	//�ڶ���ö��
	bool bStatus = FALSE;
	bStatus = EnumServicesStatusEx(hScm,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,//���з���״̬
		(PBYTE)pEnumSerice,//������
		dwSize,//��������С
		&dwSize,//��Ҫ�Ĵ�С
		&dwServiceNum,//�������з���ĸ���
		NULL, NULL

		);

	CString qwe;//����ת����
	//������Ϣ
	for (DWORD i = 0; i < dwServiceNum;i++)
	{
		//��ȡ������ϢpEnumSerice[i].lpServiceName
		//������
		
		qwe.Format(L"%s", pEnumSerice[i].lpServiceName);
		Win_FuWu_List.InsertItem(i, qwe);


		//��÷���״̬   ��ֹͣ �������� ������ͣ

		pEnumSerice[i].ServiceStatusProcess.dwCurrentState;



		qwe.Format(L"%d", pEnumSerice[i].ServiceStatusProcess.dwCurrentState);

		if (4 == pEnumSerice[i].ServiceStatusProcess.dwCurrentState)
		{
			
			Win_FuWu_List.SetItemText(i, 3,ab );



		}
		else
		{
			Win_FuWu_List.SetItemText(i, 3, cc);

		}

	



		qwe.Format(L"%s", pEnumSerice[i].lpDisplayName);
			Win_FuWu_List.SetItemText(i, 2, qwe);



				qwe.Format(L"%d", pEnumSerice[i].ServiceStatusProcess.dwProcessId);
			Win_FuWu_List.SetItemText(i, 1, qwe);


		

	}






	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



CString zxc;

void Tab_FuWu::Onopenservice()
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�򿪷���
	//SC_HANDLE hService = OpenService()
	DWORD pos = (DWORD)Win_FuWu_List.GetFirstSelectedItemPosition();
	CString str = Win_FuWu_List.GetItemText(pos-1, 0);

	SC_HANDLE hService = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);


	SC_HANDLE aaa = OpenService(hService, str, SERVICE_START|SERVICE_STOP);


	StartService(aaa, NULL, NULL);
	char* aa = "��������";
	zxc = aa;

	Win_FuWu_List.SetItemText(pos-1, 3, zxc);
	//DWORD dwSize = 0;
	//QueryServiceConfig(hService, NULL, 0, &dwSize);
	//LPQUERY_SERVICE_CONFIG pS = (LPQUERY_SERVICE_CONFIG)new char[dwSize];

	//QueryServiceConfig(hService, pS, dwSize, &dwSize);
	////pS->

	Win_FuWu_List.DeleteAllItems();
	OnInitDialog();
	// TODO:  �ڴ���������������
}


void Tab_FuWu::OnRclickFuwuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CPoint pt;
	GetCursorPos(&pt);

	Win_FuWu_List.ScreenToClient(&pt);

	LVHITTESTINFO HitTestInfo;

	HitTestInfo.pt = pt;

	int nItem = Win_FuWu_List.HitTest(&HitTestInfo);

	if (nItem != -1)
	{

		BeChosed = nItem;
		CMenu menu;
		menu.LoadMenuW(IDR_MENU2);
		CPoint point;
		GetCursorPos(&point);
		CMenu *pSubMebu = menu.GetSubMenu(0);
		pSubMebu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	}

}


void Tab_FuWu::FuWu999()
{

	DWORD pos = (DWORD)Win_FuWu_List.GetFirstSelectedItemPosition();
	CString str = Win_FuWu_List.GetItemText(pos - 1, 0);

	SC_HANDLE hService = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);


	SC_HANDLE aaa = OpenService(hService, str, SERVICE_START | SERVICE_STOP);

	SERVICE_STATUS serviceStatus = { 0 };
	ControlService(aaa, SERVICE_CONTROL_STOP, &serviceStatus);
	char* aa = "��ֹͣ";
	zxc = aa;

	Win_FuWu_List.SetItemText(pos - 1, 3, zxc);
	Win_FuWu_List.DeleteAllItems();
	OnInitDialog();


	// TODO:  �ڴ���������������
}
