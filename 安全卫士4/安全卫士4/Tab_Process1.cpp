// Tab_Process1.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include<tlhelp32.h>
#include"Process_MoKuai.h"
#include"resource.h"
#include <windows.h>
#include"Process_ChuangKou.h"
#include"Procces_Thread.h"
#include "Tab_Process1.h"
#include "afxdialogex.h"
#include <windows.h>


// Tab_Process1 对话框

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


// Tab_Process1 消息处理程序


BOOL Tab_Process1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwOldStyle = m_ListCtrl.GetExtendedStyle();//获取元风格

	//设置当前控件扩展风格
	m_ListCtrl.SetExtendedStyle(dwOldStyle |//报表视图形式
		LVS_EX_FULLROWSELECT //网格线


		);



	//获取list宽度

	CRect Rc;
	m_ListCtrl.GetClientRect(Rc);
	int nWidth = Rc.Width();


	//为list插入列信息
	m_ListCtrl.InsertColumn(
		0,//当前列编号
		L"进程名",//要求插入的信息
		0,//风格
		nWidth / 2//列的宽

		);
	m_ListCtrl.InsertColumn(
		1,//当前序列号
		L"PID",
		0,
		nWidth / 2
		);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessShot;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hProcessShot, &pe32))//获取下一个进程快照
	{
		for (int i = 0; Process32Next(hProcessShot, &pe32); i++)
		{
			//打印进程名
			m_ListCtrl.InsertItem(i,//行号
				pe32.szExeFile
				);
			//LPCTSTR
			CString str;
			//打印进程pid
			str.Format(_T("%d"), pe32.th32ProcessID);
		
			m_ListCtrl.SetItemText(i, 1, str);

		}


	}









	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void Tab_Process1::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码

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
	//CMenu menu;//定义下面的要用到的cmenu函数
	//menu.LoadMenu(IDR_MENU1);
	//CMenu* pPopup = menu.GetSubMenu(0);//获取第一个菜单必须有子菜单

	//CPoint point1;//定义一个用于确定光标位置的位置
	//GetCursorPos(&point1);//获取当前光标位置，以便菜单可以跟随光标


	////在指定位置显示弹出菜单
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
	// TODO:  在此添加命令处理程序代码
}


void Tab_Process1::Menu_MoKuai()
{
	CString gg;
	WCHAR woqu[50] = { 0 };
	m_ListCtrl.GetItemText(Menu_ID, 1, woqu, 50);

	swscanf_s(woqu, L"%d", &ppppid);
	Process_MoKuai Obj(ppppid, NULL);
	Obj.DoModal();
	// TODO:  在此添加命令处理程序代码
}


void Tab_Process1::OnMenu()
{
	CString gg;
	WCHAR woqu[50] = { 0 };
	m_ListCtrl.GetItemText(Menu_ID, 1, woqu, 50);

	swscanf_s(woqu, L"%d", &ppppid);


	Process_ChuangKou Obj(ppppid,NULL);
	Obj.DoModal();


	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
}


void Tab_Process1::OnBnClickedSxprocess()
{

	m_ListCtrl.DeleteAllItems();//清除以前的list

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessShot;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hProcessShot, &pe32))//获取下一个进程快照
	{
		for (int i = 0; Process32Next(hProcessShot, &pe32); i++)
		{
			//打印进程名
			m_ListCtrl.InsertItem(i,//行号
				pe32.szExeFile
				);
			//LPCTSTR
			CString str;
			//打印进程pid
			str.Format(_T("%d"), pe32.th32ProcessID);

			m_ListCtrl.SetItemText(i, 1, str);

		}
	}
	// TODO:  在此添加控件通知处理程序代码
}
