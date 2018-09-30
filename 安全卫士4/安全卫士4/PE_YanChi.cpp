// PE_YanChi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "PE_YanChi.h"
#include "PE_YANCHI_LIST.h"
#include "afxdialogex.h"


// PE_YanChi �Ի���

IMPLEMENT_DYNAMIC(PE_YanChi, CDialogEx)
DWORD PE_YanChi::rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva){


	IMAGE_SECTION_HEADER*pScnHdr = (IMAGE_SECTION_HEADER*)IMAGE_FIRST_SECTION(pNt);
	for (DWORD i = 0; i < pNt->FileHeader.NumberOfSections; ++i)
	{
		if (dwRva >= pScnHdr[i].VirtualAddress&&dwRva <= pScnHdr[i].VirtualAddress + pScnHdr[i].SizeOfRawData)
		{
			return dwRva - pScnHdr[i].VirtualAddress + pScnHdr[i].PointerToRawData;
		}
	}
	return -1;


}

PE_YanChi::PE_YanChi(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
	: CDialogEx(PE_YanChi::IDD, pParent)
{
	PNt = PNT;
	PBuff = qBuff;
		 
}

PE_YanChi::~PE_YanChi()
{
}

void PE_YanChi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PE_YC_LIST, Pe_yanChi_List);
}


BEGIN_MESSAGE_MAP(PE_YanChi, CDialogEx)
END_MESSAGE_MAP()


// PE_YanChi ��Ϣ�������


BOOL PE_YanChi::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	DWORD dwOldStyle = Pe_yanChi_List.GetExtendedStyle();
	//���õ�ǰ�ؼ�����չ���
	Pe_yanChi_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//������ͼ
		LVS_EX_GRIDLINES//������


		);
	CRect rc;
	Pe_yanChi_List.GetClientRect(rc);
	int nWidth = rc.Width();

	//Ϊlist�����Ϣ
	Pe_yanChi_List.InsertColumn(
		0, L"�ӳ������dll����", 0, nWidth / 3
		);
	Pe_yanChi_List.InsertColumn(
		1, L"�ӳ������IAT��RVA", 0, nWidth / 3
		);
	Pe_yanChi_List.InsertColumn(
		2, L"�ӳ������INT��RVA", 0, nWidth / 3
		);
	//��ȡ��չͷ��λ��
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);

	//��ȡTLS���RVA
	DWORD YanChi = pOh->DataDirectory[13].VirtualAddress;
	CString aaa;
	if (0 == YanChi)
	{

		MessageBox( 0,L" û���ӳټ��ر�", 0);


	}
	else
	{

		IMAGE_DELAYLOAD_DESCRIPTOR * pTLSDir = (IMAGE_DELAYLOAD_DESCRIPTOR*)(rva2foa(PNt, YanChi) + PBuff);

		aaa.Format(L"%08X", pTLSDir->DllNameRVA);
		Pe_yanChi_List.InsertItem(0, aaa);


		aaa.Format((_T("%x")), pTLSDir->ImportAddressTableRVA);
		Pe_yanChi_List.SetItemText(0, 1, aaa);

		aaa.Format((_T("%x")), pTLSDir->ImportNameTableRVA);
		Pe_yanChi_List.SetItemText(0, 2, aaa);



	}

	
	//IMAGE_DELAYLOAD_DESCRIPTOR * pTLSDir = (IMAGE_DELAYLOAD_DESCRIPTOR*)(rva2foa(PNt, YanChi) + PBuff);

	//aaa.Format(L"%08X", pTLSDir->DllNameRVA);
	//Pe_yanChi_List.InsertItem(0, aaa);


	//aaa.Format((_T("%x")), pTLSDir->ImportAddressTableRVA);
	//Pe_yanChi_List.SetItemText(0, 1, aaa);

	//aaa.Format((_T("%x")), pTLSDir->ImportNameTableRVA);
	//Pe_yanChi_List.SetItemText(0, 2, aaa);




	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
