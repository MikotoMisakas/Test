// Tab_FuWu.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "WIN_FUWU_LIST.h"
#include "Tab_FuWu.h"
#include<windows.h>
#include "afxdialogex.h"
#include <winsvc.h>


// Tab_FuWu 对话框

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


// Tab_FuWu 消息处理程序

BOOL Tab_FuWu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString ab;
	ab = "正在运行";
	CString cc;
	cc = "已停止";

	// TODO:  在此添加额外的初始化

	DWORD dwOldStyle = Win_FuWu_List.GetExtendedStyle();
	//设置当前控件的扩展风格
	Win_FuWu_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//获取list宽度
	CRect Re;
	Win_FuWu_List.GetClientRect(Re);
	int nWidth = Re.Width();

	//为list插入列信息
	Win_FuWu_List.InsertColumn(
		0,//当前列编号
		L"名称",
		0,
		nWidth / 4

		);
	Win_FuWu_List.InsertColumn(
		1,//当前列编号
		L"PID",
		0,
		nWidth / 4

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//当前列编号
	//	L"偏移",
	//	0,
	//	nWidth / 4

	//	);
	Win_FuWu_List.InsertColumn(
		2,//当前列编号
		L"描述",
		0,
		nWidth / 4

		);

	Win_FuWu_List.InsertColumn(
		3,//当前列编号
		L"状态",
		0,
		nWidth / 4

		);
	
	///////////////////////////////////////////
	//遍历服务
	SC_HANDLE hScm = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);


	//第一次调用获取需要的内存大小
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatusEx(hScm, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,//所有服务状态
		NULL,//缓冲区
		0,//Huanchongqu daxiao
		&dwSize,//需要的大小
		&dwServiceNum,//缓冲区服务的个数
		NULL, NULL

		);
	//申请需要的内存
	LPENUM_SERVICE_STATUS_PROCESS pEnumSerice = (LPENUM_SERVICE_STATUS_PROCESS)new char[dwSize];

	//第二次枚举
	bool bStatus = FALSE;
	bStatus = EnumServicesStatusEx(hScm,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,//所有服务状态
		(PBYTE)pEnumSerice,//缓冲区
		dwSize,//缓冲区大小
		&dwSize,//需要的大小
		&dwServiceNum,//缓冲区中服务的个数
		NULL, NULL

		);

	CString qwe;//用来转换的
	//遍历信息
	for (DWORD i = 0; i < dwServiceNum;i++)
	{
		//获取基础信息pEnumSerice[i].lpServiceName
		//服务名
		
		qwe.Format(L"%s", pEnumSerice[i].lpServiceName);
		Win_FuWu_List.InsertItem(i, qwe);


		//获得服务状态   已停止 正在运行 正在暂停

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
	// 异常:  OCX 属性页应返回 FALSE
}



CString zxc;

void Tab_FuWu::Onopenservice()
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//打开服务
	//SC_HANDLE hService = OpenService()
	DWORD pos = (DWORD)Win_FuWu_List.GetFirstSelectedItemPosition();
	CString str = Win_FuWu_List.GetItemText(pos-1, 0);

	SC_HANDLE hService = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);


	SC_HANDLE aaa = OpenService(hService, str, SERVICE_START|SERVICE_STOP);


	StartService(aaa, NULL, NULL);
	char* aa = "正在运行";
	zxc = aa;

	Win_FuWu_List.SetItemText(pos-1, 3, zxc);
	//DWORD dwSize = 0;
	//QueryServiceConfig(hService, NULL, 0, &dwSize);
	//LPQUERY_SERVICE_CONFIG pS = (LPQUERY_SERVICE_CONFIG)new char[dwSize];

	//QueryServiceConfig(hService, pS, dwSize, &dwSize);
	////pS->

	Win_FuWu_List.DeleteAllItems();
	OnInitDialog();
	// TODO:  在此添加命令处理程序代码
}


void Tab_FuWu::OnRclickFuwuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
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
	char* aa = "已停止";
	zxc = aa;

	Win_FuWu_List.SetItemText(pos - 1, 3, zxc);
	Win_FuWu_List.DeleteAllItems();
	OnInitDialog();


	// TODO:  在此添加命令处理程序代码
}
