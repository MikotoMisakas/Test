
// 安全卫士4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "安全卫士4Dlg.h"
#include"Tab_FuJia.h"
#include"Tab_FuWu.h"
#include"MyListCtrl.h"
#include"resource.h"
#include"Tab_LaJi.h"
#include"Tab_NeiCun2.h"
#include <time.h>

#include"Tab_Pe.h"
#include"Tab_Process1.h"
#include <WINDEF.H>
#include <windows.h>
#include"Tab_ShaDu.h"
#include"Tab_YunSha.h"
#include "afxdialogex.h"
#include <WINDEF.H>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <WINDEF.H>
#include <TlHelp32.h>
#define  WM_CPUMESSAGE WM_USER+0x232

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C安全卫士4Dlg 对话框



C安全卫士4Dlg::C安全卫士4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C安全卫士4Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C安全卫士4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_MyTable);
}

BEGIN_MESSAGE_MAP(C安全卫士4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(WM_CPUMESSAGE, &C安全卫士4Dlg::OnCpumessage)
END_MESSAGE_MAP()





//void OnTimera1w(){
//
//	switch (nIDEvent)
//	{
//	case 2:{
//		//cpu      空闲时间  内核时间   用户时间
//		_FILETIME idleTime, KernelTime, userTime;
//
//		//获取时间
//		GetSystemTimes(&idleTime, &KernelTime, &userTime);
//
//		//等待1000毫秒
//
//
//		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//		//等待1000毫秒 内核对象等待会更加精准
//
//		WaitForSingleObject(hEvent, 1000);
//
//		//获取新的时间
//		_FILETIME newIdleTime, newKernelTime, newUserTime;
//
//		GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);
//
//
//		//将各个时间转换
//		double dOldidleTime = FILETIME2Double(idleTime);
//		double dNewIdleTime = FILETIME2Double(newIdleTime);
//		double dOldKernelTime = FILETIME2Double(KernelTime);
//		double dNewKernelTime = FILETIME2Double(newKernelTime);
//		double dOldUserTime = FILETIME2Double(userTime);
//		double dNewUserTime = FILETIME2Double(newUserTime);
//
//		int w;
//		//计算出使用率
//		w = (100.0 - (dNewIdleTime - dOldidleTime) / (dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime)*100.0);
//		CString cTemp = L"";
//		cTemp.Format(L"CPU:%d", w);
//		m_bar->SetPaneText(1, cTemp);
//
//
//
//	}
//		break;
//	case 3:{
//
//
//
//
//
//
//
//
//	}
//
//		break;
//
//
//
//		KillTimer(nIDEvent);
//		CDialogEx::OnTimer(nIDEvent);
//
//
//	}
//}

// C安全卫士4Dlg 消息处理程序



//VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime){
//
//	void CALLBACK TIMERPROC(HWND hWnd ,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
//
//
//
//
//}

//void CALLBACK TIMERPROC(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime){

	//switch (uMsg)
	//{
	//case 2:{
	//	//cpu      空闲时间  内核时间   用户时间
	//	_FILETIME idleTime, KernelTime, userTime;

	//	//获取时间
	//	GetSystemTimes(&idleTime, &KernelTime, &userTime);

	//	//等待1000毫秒


	//	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//	//等待1000毫秒 内核对象等待会更加精准

	//	WaitForSingleObject(hEvent, 1000);

	//	//获取新的时间
	//	_FILETIME newIdleTime, newKernelTime, newUserTime;

	//	GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);


	//	//将各个时间转换
	//	double dOldidleTime = FILETIME2Double(idleTime);
	//	double dNewIdleTime = FILETIME2Double(newIdleTime);
	//	double dOldKernelTime = FILETIME2Double(KernelTime);
	//	double dNewKernelTime = FILETIME2Double(newKernelTime);
	//	double dOldUserTime = FILETIME2Double(userTime);
	//	double dNewUserTime = FILETIME2Double(newUserTime);

	//	int w;
	//	//计算出使用率
	//	w = (100.0 - (dNewIdleTime - dOldidleTime) / (dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime)*100.0);
	//	CString cTemp = L"";
	//	cTemp.Format(L"CPU:%d", w);
	//	m_bar->SetPaneText(1, cTemp);

	//	MEMORYSTATUS ms;
	//	::GlobalMemoryStatus(&ms);

	//	ms.dwMemoryLoad;
	//	CString aaaq;
	//	aaaq.Format(L"内存:%d", ms.dwMemoryLoad);

	//	m_bar->SetPaneText(2, aaaq);




	//}
	//	break;


	//}


//}

double  FILETIME2Double(const _FILETIME& fileTime){

	return double(fileTime.dwHighDateTime*4.294967296E9) + double(fileTime.dwLowDateTime);




}

unsigned int _stdcall cppcpp(void*dummy)
{
	while (1)
	{

		

		_FILETIME idleTime, KernelTime, userTime;

		//获取时间
		GetSystemTimes(&idleTime, &KernelTime, &userTime);

		//等待1000毫秒

		SleepEx(500, 1);
		// 		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		// 		//等待1000毫秒 内核对象等待会更加精准
		// 
		// 		WaitForSingleObject(hEvent, 1000);

		//获取新的时间
		_FILETIME newIdleTime, newKernelTime, newUserTime;

		GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);


		//将各个时间转换
		double dOldidleTime = FILETIME2Double(idleTime);
		double dNewIdleTime = FILETIME2Double(newIdleTime);
		double dOldKernelTime = FILETIME2Double(KernelTime);
		double dNewKernelTime = FILETIME2Double(newKernelTime);
		double dOldUserTime = FILETIME2Double(userTime);
		double dNewUserTime = FILETIME2Double(newUserTime);

		int w;
		//计算出使用率
		w = (100.0 - (dNewIdleTime - dOldidleTime) / (dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime)*100.0);
		SendMessage((HWND)dummy, WM_CPUMESSAGE, w, 0);
	}



}




BOOL C安全卫士4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	BOOL bb = RegisterHotKey(GetSafeHwnd(), 0x6789, MOD_CONTROL, 'F');
	m_MyTable.InsertItem(0, L"进程");
	m_MyTable.InsertItem(1, L"内存");
	m_MyTable.InsertItem(2, L"垃圾清理");
	m_MyTable.InsertItem(3, L"服务");
	m_MyTable.InsertItem(4, L"杀毒");
	m_MyTable.InsertItem(5, L"调试");
	m_MyTable.InsertItem(6, L"pe");
	m_MyTable.InsertItem(7, L"附加");



	//给子窗口指针赋值

	m_MyTable.m_Dia[0] = new Tab_Process1;

	m_MyTable.m_Dia[1] = new Tab_NeiCun2;

	m_MyTable.m_Dia[2] = new Tab_LaJi;

	m_MyTable.m_Dia[3] = new Tab_FuWu;

	m_MyTable.m_Dia[4] = new Tab_ShaDu;

	m_MyTable.m_Dia[5] = new Tab_YunSha;

	m_MyTable.m_Dia[6] = new Tab_Pe;

	m_MyTable.m_Dia[7] = new Tab_FuJia;



	///创建子窗口

	m_MyTable.m_Dia[0]->Create(IDD_Process, &m_MyTable);

	m_MyTable.m_Dia[1]->Create(IDD_JinShiDun, &m_MyTable);
	m_MyTable.m_Dia[2]->Create(IDD_LaJi, &m_MyTable);
	m_MyTable.m_Dia[3]->Create(IDD_FuWu, &m_MyTable);
	m_MyTable.m_Dia[4]->Create(IDD_ShaDu, &m_MyTable);
	m_MyTable.m_Dia[5]->Create(IDD_YunSha, &m_MyTable);
	m_MyTable.m_Dia[6]->Create(IDD_Pe, &m_MyTable);
	m_MyTable.m_Dia[7]->Create(IDD_FuJia, &m_MyTable);


	//m_MyTable.m_Dia[1]->SetParent(this);
	//控制两个窗口的大小
	CRect rc;

	m_MyTable.GetClientRect(rc);

	rc.DeflateRect(2, 23, 2, 2);

	m_MyTable.m_Dia[0]->MoveWindow(rc);
	
	m_MyTable.m_Dia[1]->MoveWindow(rc);

	m_MyTable.m_Dia[2]->MoveWindow(rc);
	m_MyTable.m_Dia[3]->MoveWindow(rc);
	m_MyTable.m_Dia[4]->MoveWindow(rc);
	m_MyTable.m_Dia[5]->MoveWindow(rc);
	m_MyTable.m_Dia[6]->MoveWindow(rc);
	m_MyTable.m_Dia[7]->MoveWindow(rc);


	//显示第一个子窗口

	m_MyTable.m_Dia[0]->ShowWindow(SW_SHOW);


	m_MyTable.m_Dia[1]->ShowWindow(SW_HIDE);
	m_MyTable.m_Dia[2]->ShowWindow(SW_HIDE);
	m_MyTable.m_Dia[3]->ShowWindow(SW_HIDE);
	m_MyTable.m_Dia[4]->ShowWindow(SW_HIDE);
	m_MyTable.m_Dia[5]->ShowWindow(SW_HIDE);
	m_MyTable.m_Dia[6]->ShowWindow(SW_HIDE);
	m_MyTable.m_Dia[7]->ShowWindow(SW_HIDE);




	////////////////////////////////////////////////////

	UINT pp[] = { 0x1111, 0x2222, 0x3333, 0x4444};

	m_bar = new CStatusBar;
	m_bar->Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM);
	m_bar->SetIndicators(pp, 3);//设置状态栏项目栏数
	CRect rect;
	GetClientRect(&rect);// SBPS_STRETCH
	m_bar->SetPaneInfo(0, 0x1111, SBPS_STRETCH, 0);
	m_bar->SetPaneInfo(1, 0x2222, SBPS_POPOUT, 120);
	m_bar->SetPaneInfo(2, 0x3333, SBPS_POPOUT, 120);//第三栏长度120单位
	
	m_bar->SetPaneText(0, L"cpu/内存");
	m_bar->SetPaneText(1, L"CPU:");
	m_bar->SetPaneText(2, L"内存:");

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0x3333);

	SetTimer(2, 300, NULL);//定时器 一秒触发一次的定时器
	//SetTimer(3, 2000, NULL);//定时器 一秒触发一次的定时器
	

	HANDLE hthread = (HANDLE)_beginthreadex(0, 0, cppcpp, (void*)(this->m_hWnd), 0, 0);






	//if (!DebugPrivilege(TRUE))return 0;
	PROCESSENTRY32 pe{ sizeof(PROCESSENTRY32) };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL b = Process32First(hSnap, &pe);
	int pId = -1;
	if (b)
	{
		do {
			if (wcscmp(pe.szExeFile, L"Taskmgr.exe") == 0)
			{
				pId = pe.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnap, &pe));
	}
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	if (!hProcess)
	{
		//printf("获取进程句柄失败!");
		return 0;
	}
	//64位DLL路径
	char path[] = "D:\\cx\\dllzhuru\\x64\\Debug\\dllzhuru.dll";
	//32位DLL路径
	//擦汗ar path[] = "D:\\c代码\\HOOK\\Debug\\hookDLL.dll";
	int nLen = sizeof(path);
	//VirtualAllocEx(hProcess, pBuff, 0x1000, MEM_COMMIT, PAGE_READWRITE);
	LPVOID pBuff = VirtualAllocEx(hProcess, 0, nLen, MEM_COMMIT, PAGE_READWRITE);
	SIZE_T beWriten = 0;
	WriteProcessMemory(hProcess, pBuff, path, sizeof(path), &beWriten);
	LPTHREAD_START_ROUTINE pStartAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	//DWORD iiiiiiiiid;
	HANDLE hThr = CreateRemoteThread(hProcess, 0, 0, pStartAddr, pBuff, 0, 0);
	//WaitForSingleObject(hThr, -1);
	//hThr = CreateRemoteThread(hProcess, 0, 0, LPTHREAD_START_ROUTINE(FreeLibrary), pBuff, 0, 0);
	




















	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C安全卫士4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C安全卫士4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C安全卫士4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


double C安全卫士4Dlg::FILETIME2Double(const _FILETIME& fileTime){

	return double(fileTime.dwHighDateTime*4.294967296E9) + double(fileTime.dwLowDateTime);




}
void C安全卫士4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	
//	switch (nIDEvent)
//	{
//	case 2:{
//		//cpu      空闲时间  内核时间   用户时间
//		_FILETIME idleTime, KernelTime, userTime;
//
//		//获取时间
//		GetSystemTimes(&idleTime, &KernelTime, &userTime);
//
//		//等待1000毫秒
//
//		SleepEx(100,1);
//// 		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//// 		//等待1000毫秒 内核对象等待会更加精准
//// 
//// 		WaitForSingleObject(hEvent, 1000);
//
//		//获取新的时间
//		_FILETIME newIdleTime, newKernelTime, newUserTime;
//
//		GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);
//
//
//		//将各个时间转换
//		double dOldidleTime = FILETIME2Double(idleTime);
//		double dNewIdleTime = FILETIME2Double(newIdleTime);
//		double dOldKernelTime = FILETIME2Double(KernelTime);
//		double dNewKernelTime = FILETIME2Double(newKernelTime);
//		double dOldUserTime = FILETIME2Double(userTime);
//		double dNewUserTime = FILETIME2Double(newUserTime);
//
//		int w;
//		//计算出使用率
//		w = (100.0 - (dNewIdleTime - dOldidleTime) / (dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime)*100.0);
//		CString cTemp = L"";
//		cTemp.Format(L"CPU:%d", w);
//		m_bar->SetPaneText(1, cTemp);
//
//		MEMORYSTATUS ms;
//		::GlobalMemoryStatus(&ms);
//
//		ms.dwMemoryLoad;
//		CString aaaq;
//		aaaq.Format(L"内存:%d", ms.dwMemoryLoad);
//
//		m_bar->SetPaneText(2, aaaq);
//
//
//
//
//	}
//		break;
//
//
//	}

//	KillTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);

}

afx_msg LRESULT C安全卫士4Dlg::OnCpumessage(WPARAM wParam, LPARAM lParam)
{

	CString cTemp = L"";
	cTemp.Format(L"CPU:%d", wParam);
	m_bar->SetPaneText(1, cTemp);

	MEMORYSTATUS ms;
	::GlobalMemoryStatus(&ms);

	ms.dwMemoryLoad;
	CString aaaq;
	aaaq.Format(L"内存:%d", ms.dwMemoryLoad);

	m_bar->SetPaneText(2, aaaq);
	return 0;
}


BOOL C安全卫士4Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_HOTKEY && pMsg->wParam == 0x6789)
	{
		if (m_isShow == TRUE)
		{
			ShowWindow(SW_HIDE);
			m_isShow = FALSE;
		}
		else
		{
			ShowWindow(SW_SHOW);
			m_isShow = TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
