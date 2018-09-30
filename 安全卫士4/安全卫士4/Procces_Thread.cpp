// Procces_Thread.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "Procces_Thread.h"
#include "tlhelp32.h"
#include "afxdialogex.h"


// Procces_Thread 对话框

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


// Procces_Thread 消息处理程序


BOOL Procces_Thread::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwOldStyle = Process_Thread_List_BL.GetExtendedStyle();//获取原来的风格




	//设置当前控件的扩展风格
	Process_Thread_List_BL.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//获取list宽度
	CRect Re;
	Process_Thread_List_BL.GetClientRect(Re);
	int nWidth = Re.Width();

	//为list插入列信息
	Process_Thread_List_BL.InsertColumn(
		0,//当前列编号
		L"线程id",
		0,
		nWidth / 3

		);
	Process_Thread_List_BL.InsertColumn(
		1,//当前列编号
		L"所属进程id",
		0,
		nWidth / 3

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//当前列编号
	//	L"偏移",
	//	0,
	//	nWidth / 4

	//	);
	Process_Thread_List_BL.InsertColumn(
		2,//当前列编号
		L"线程优先级",
		0,
		nWidth / 3

		);
	//	Thread32First

	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, Thread_ID);


	//用来保存线程信息
	THREADENTRY32 stcTe32 = { sizeof(THREADENTRY32) };

	//获取第一个线程
	Thread32First(hThreadSnap, &stcTe32);

	CString szTemp;
	int i = 1;
	do
	{
		// 筛选指定进程下的线程,插入到线程列表控件中
		if (stcTe32.th32OwnerProcessID == Thread_ID)
		{
			// 当前线程ID
			szTemp.Format(L"%d", stcTe32.th32ThreadID);
			Process_Thread_List_BL.InsertItem(0, 0);
			Process_Thread_List_BL.SetItemText(i, 0, szTemp);
				//PE_DR_LIST.InsertItem(i, q);
				//PE_DR_LIST.SetItemText(i, 1, qwe);
			// 所属进程ID
			szTemp.Format(L"%d", stcTe32.th32OwnerProcessID);

			Process_Thread_List_BL.SetItemText(i, 1, szTemp);



			// 线程优先级
			szTemp.Format(L"%d", stcTe32.tpBasePri);
			Process_Thread_List_BL.SetItemText(i, 2, szTemp);
		}
	} while (Thread32Next(hThreadSnap, &stcTe32));


	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
