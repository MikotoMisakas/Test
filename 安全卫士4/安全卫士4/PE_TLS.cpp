// PE_TLS.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "PE_TLS.h"
#include "PE_TLS_LIST.h"
#include "afxdialogex.h"


// PE_TLS �Ի���

IMPLEMENT_DYNAMIC(PE_TLS, CDialogEx)

PE_TLS::PE_TLS(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
	: CDialogEx(PE_TLS::IDD, pParent)
{
	PNt = PNT;
	PBuff = qBuff;

}

PE_TLS::~PE_TLS()
{
}
//
DWORD PE_TLS::rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva){


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
void PE_TLS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PE_TLS, Pe_Tls_List);
}


BEGIN_MESSAGE_MAP(PE_TLS, CDialogEx)
END_MESSAGE_MAP()


// PE_TLS ��Ϣ�������


BOOL PE_TLS::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	DWORD dwOldStyle = Pe_Tls_List.GetExtendedStyle();
	//���õ�ǰ�ؼ�����չ���
	Pe_Tls_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//������ͼ
		LVS_EX_GRIDLINES//������


		);
	CRect rc;
	Pe_Tls_List.GetClientRect(rc);
	int nWidth = rc.Width();

	//Ϊlist�����Ϣ
	Pe_Tls_List.InsertColumn(
		0, L"Դ������ʼλ��", 0, nWidth / 3
		);
	Pe_Tls_List.InsertColumn(
		1, L"Դ������ֹλ��", 0, nWidth / 3
		);
	Pe_Tls_List.InsertColumn(
		2, L"TLS�ص�������ַ��λ��", 0, nWidth / 3
		);
	//��ȡ��չͷ��λ��
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);

	//��ȡTLS���RVA
	DWORD TlsTableRva = pOh->DataDirectory[9].VirtualAddress;

	if (0==TlsTableRva)
	{
		MessageBox(L"��Ǹ", L"������û��tls", NULL);
	}
	else{
		//��ȡTLS��Ľṹ�����ڴ��е�λ��
		IMAGE_TLS_DIRECTORY * pTLSDir = (IMAGE_TLS_DIRECTORY*)(rva2foa(PNt, TlsTableRva) + PBuff);


		CString aaaa;
		aaaa.Format(L"%d", pTLSDir->StartAddressOfRawData);
		Pe_Tls_List.InsertItem(0, aaaa);

		aaaa.Format(L"%d", pTLSDir->EndAddressOfRawData);
		Pe_Tls_List.SetItemText(0, 1, aaaa);

		aaaa.Format(L"%d", pTLSDir->AddressOfCallBacks);
		Pe_Tls_List.SetItemText(0, 2, aaaa);

	}








	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
