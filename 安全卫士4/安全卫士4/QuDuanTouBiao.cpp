// QuDuanTouBiao.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "QuDuanTouBiao.h"
#include "afxdialogex.h"


// QuDuanTouBiao �Ի���

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


// QuDuanTouBiao ��Ϣ�������


BOOL QuDuanTouBiao::OnInitDialog()
{




	CDialogEx::OnInitDialog();

	DWORD dwOldStyle = m_List_QuDuan.GetExtendedStyle();//��ȡԭ���

	//���õ�ǰ�ؼ���չ���
	m_List_QuDuan.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//������ͼ
		LVS_EX_GRIDLINES//������
		);

	//��ȡlist�Ŀ��
	CRect Rc;
	m_List_QuDuan.GetClientRect(Rc);
	int nWidth = Rc.Width();


	//Ϊlist��������Ϣ
	m_List_QuDuan.InsertColumn(	0,L"������",0,nWidth / 5	);
	m_List_QuDuan.InsertColumn(
		2,//��ǰ�еı��
		L"RVA",//Ҫ�������Ϣ
		0,//���
		nWidth / 5//�еĿ�

		);
	m_List_QuDuan.InsertColumn(
		1,//��ǰ�еı��
		L"���δ�С",//Ҫ�������Ϣ
		0,//���
		nWidth / 5//�еĿ�

		);
	m_List_QuDuan.InsertColumn(
		3,//��ǰ�еı��
		L"FOA",//Ҫ�������Ϣ
		0,//���
		nWidth / 5//�еĿ�

		);
	m_List_QuDuan.InsertColumn(
		4,//��ǰ�еı��
		L"����",//Ҫ�������Ϣ
		0,//���
		nWidth / 5//�еĿ�

		);


	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(PNT);

	int i = 0;
	//ѭ��������α����Ϣ
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