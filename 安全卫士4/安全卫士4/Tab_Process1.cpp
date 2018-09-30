// Tab_Process1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include<tlhelp32.h>
#include"Process_MoKuai.h"
#include"resource.h"
#include <windows.h>
#include"Process_ChuangKou.h"
#include"Procces_Thread.h"
#include "Tab_Process1.h"
#include "afxdialogex.h"
#include <windows.h>


// Tab_Process1 �Ի���

IMPLEMENT_DYNAMIC(Tab_Process1, CDialogEx)

Tab_Process1::Tab_Process1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_Process1::IDD, pParent)
{

}

Tab_Process1::~Tab_Process1()
{
}

void Tab_Process1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(Tab_Process1, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &Tab_Process1::OnRclickList1)
	ON_COMMAND(ID_32771, &Tab_Process1::Menu_Command)
	ON_COMMAND(ID_OLE_VERB_POPUP, &Tab_Process1::Menu_MoKuai)
	ON_COMMAND(ID_Menu, &Tab_Process1::OnMenu)
	ON_COMMAND(ID_32775, &Tab_Process1::On32775)
	ON_BN_CLICKED(IDC_SXProcess, &Tab_Process1::OnBnClickedSxprocess)
END_MESSAGE_MAP()


// Tab_Process1 ��Ϣ�������


BOOL Tab_Process1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwOldStyle = m_ListCtrl.GetExtendedStyle();//��ȡԪ���

	//���õ�ǰ�ؼ���չ���
	m_ListCtrl.SetExtendedStyle(dwOldStyle |//������ͼ��ʽ
		LVS_EX_FULLROWSELECT //������


		);



	//��ȡlist���

	CRect Rc;
	m_ListCtrl.GetClientRect(Rc);
	int nWidth = Rc.Width();


	//Ϊlist��������Ϣ
	m_ListCtrl.InsertColumn(
		0,//��ǰ�б��
		L"������",//Ҫ��������Ϣ
		0,//���
		nWidth / 2//�еĿ�

		);
	m_ListCtrl.InsertColumn(
		1,//��ǰ���к�
		L"PID",
		0,
		nWidth / 2
		);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessShot;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hProcessShot, &pe32))//��ȡ��һ�����̿���
	{
		for (int i = 0; Process32Next(hProcessShot, &pe32); i++)
		{
			//��ӡ������
			m_ListCtrl.InsertItem(i,//�к�
				pe32.szExeFile
				);
			//LPCTSTR
			CString str;
			//��ӡ����pid
			str.Format(_T("%d"), pe32.th32ProcessID);
		
			m_ListCtrl.SetItemText(i, 1, str);

		}


	}









	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Tab_Process1::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CPoint pt;
	GetCursorPos(&pt);

	m_ListCtrl.ScreenToClient(&pt);

	LVHITTESTINFO HitTestInfo;

	HitTestInfo.pt = pt;

	int nItem = m_ListCtrl.HitTest(&HitTestInfo);

	if (nItem != -1)
	{

		Menu_ID = nItem;


		CMenu menu;
		menu.LoadMenuW(IDR_MENU1);
		CPoint point;
		GetCursorPos(&point);

		CMenu *pSubMebu = menu.GetSubMenu(0);
		pSubMebu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	}
	



	//Menu_ID;
	//CMenu menu;//���������Ҫ�õ���cmenu����
	//menu.LoadMenu(IDR_MENU1);
	//CMenu* pPopup = menu.GetSubMenu(0);//��ȡ��һ���˵��������Ӳ˵�

	//CPoint point1;//����һ������ȷ�����λ�õ�λ��
	//GetCursorPos(&point1);//��ȡ��ǰ���λ�ã��Ա�˵����Ը�����


	////��ָ��λ����ʾ�����˵�
	//pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, GetParent());




	*pResult = 0;
}


void Tab_Process1::Menu_Command()
{
	CString gg;
	WCHAR woqu[50] = { 0 };
	m_ListCtrl.GetItemText(Menu_ID, 1, woqu, 50);
	
	swscanf_s(woqu, L"%d", &ppppid);
	HANDLE hpro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ppppid);
//	Thread32First
//	CreateToolhelp32Snapshot(,)
	int aaaa = 2;


	Procces_Thread Obj(ppppid,NULL);
	Obj.DoModal();
	// TODO:  �ڴ���������������
}


void Tab_Process1::Menu_MoKuai()
{
	CString gg;
	WCHAR woqu[50] = { 0 };
	m_ListCtrl.GetItemText(Menu_ID, 1, woqu, 50);

	swscanf_s(woqu, L"%d", &ppppid);
	Process_MoKuai Obj(ppppid, NULL);
	Obj.DoModal();
	// TODO:  �ڴ���������������
}


void Tab_Process1::OnMenu()
{
	CString gg;
	WCHAR woqu[50] = { 0 };
	m_ListCtrl.GetItemText(Menu_ID, 1, woqu, 50);

	swscanf_s(woqu, L"%d", &ppppid);


	Process_ChuangKou Obj(ppppid,NULL);
	Obj.DoModal();


	// TODO:  �ڴ���������������
}


void Tab_Process1::On32775()
{
	CString gg;
	WCHAR woqu[50] = { 0 };
	m_ListCtrl.GetItemText(Menu_ID, 1, woqu, 50);

	swscanf_s(woqu, L"%d", &ppppid);

	
	
	HANDLE AAA = OpenProcess(PROCESS_TERMINATE, FALSE, ppppid);
	TerminateProcess(AAA,0);
	m_ListCtrl.DeleteItem(Menu_ID);


	//HWND hh = GetProcessTopWindows
	// TODO:  �ڴ���������������
}


void Tab_Process1::OnBnClickedSxprocess()
{

	m_ListCtrl.DeleteAllItems();//�����ǰ��list

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessShot;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hProcessShot, &pe32))//��ȡ��һ�����̿���
	{
		for (int i = 0; Process32Next(hProcessShot, &pe32); i++)
		{
			//��ӡ������
			m_ListCtrl.InsertItem(i,//�к�
				pe32.szExeFile
				);
			//LPCTSTR
			CString str;
			//��ӡ����pid
			str.Format(_T("%d"), pe32.th32ProcessID);

			m_ListCtrl.SetItemText(i, 1, str);

		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
