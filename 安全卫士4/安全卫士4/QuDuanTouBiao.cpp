// QuDuanTouBiao.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "QuDuanTouBiao.h"
#include "afxdialogex.h"


// QuDuanTouBiao 对话框

IMPLEMENT_DYNAMIC(QuDuanTouBiao, CDialogEx)

QuDuanTouBiao::QuDuanTouBiao(IMAGE_NT_HEADERS* pP,CWnd* pParent /*=NULL*/)
	: CDialogEx(QuDuanTouBiao::IDD, pParent)
	, QuDuanTouBiaoBianLiang(0)
	, Pe_Section_quduan1(_T(""))
{
	PNT = pP;
}



QuDuanTouBiao::~QuDuanTouBiao()
{
}


void QuDuanTouBiao::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT1, Pe_Section_quduan1);
	DDX_Control(pDX, IDC_LIST1, m_List_QuDuan);
}










BEGIN_MESSAGE_MAP(QuDuanTouBiao, CDialogEx)
END_MESSAGE_MAP()


// QuDuanTouBiao 消息处理程序


BOOL QuDuanTouBiao::OnInitDialog()
{




	CDialogEx::OnInitDialog();

	DWORD dwOldStyle = m_List_QuDuan.GetExtendedStyle();//获取原风格

	//设置当前控件扩展风格
	m_List_QuDuan.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//报表试图
		LVS_EX_GRIDLINES//网格线
		);

	//获取list的宽度
	CRect Rc;
	m_List_QuDuan.GetClientRect(Rc);
	int nWidth = Rc.Width();


	//为list插入列信息
	m_List_QuDuan.InsertColumn(	0,L"区段名",0,nWidth / 5	);
	m_List_QuDuan.InsertColumn(
		2,//当前列的编号
		L"RVA",//要插入的信息
		0,//风格
		nWidth / 5//列的宽

		);
	m_List_QuDuan.InsertColumn(
		1,//当前列的编号
		L"区段大小",//要插入的信息
		0,//风格
		nWidth / 5//列的宽

		);
	m_List_QuDuan.InsertColumn(
		3,//当前列的编号
		L"FOA",//要插入的信息
		0,//风格
		nWidth / 5//列的宽

		);
	m_List_QuDuan.InsertColumn(
		4,//当前列的编号
		L"属性",//要插入的信息
		0,//风格
		nWidth / 5//列的宽

		);


	// TODO:  在此添加消息处理程序代码和/或调用默认值
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(PNT);

	int i = 0;
	//循环输出区段表的信息
	while (pSectionHeader->PointerToRawData)
	{
		m_List_QuDuan.InsertItem(i, NULL);
		CString nnn = (CString)pSectionHeader->Name;
		m_List_QuDuan.SetItemText(i, 0,nnn);
		

		
		CString w;

		w.Format(_T("%d"), pSectionHeader->Misc.VirtualSize);
		
		m_List_QuDuan.SetItemText(0, 1, w);
		


		CString h;

		h.Format(_T("%d"), pSectionHeader->VirtualAddress);

		m_List_QuDuan.SetItemText(0, 2, h);


		CString o;

		o.Format(_T("%d"), pSectionHeader->PointerToRawData);

		m_List_QuDuan.SetItemText(0, 3, o);




		CString ShuXing;

		ShuXing.Format(_T("%d"), pSectionHeader->Characteristics);

		m_List_QuDuan.SetItemText(0, 4, ShuXing);





		++pSectionHeader;

	}


	return 0;


}