// PE_TLS.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "PE_TLS.h"
#include "PE_TLS_LIST.h"
#include "afxdialogex.h"


// PE_TLS 对话框

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


// PE_TLS 消息处理程序


BOOL PE_TLS::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	DWORD dwOldStyle = Pe_Tls_List.GetExtendedStyle();
	//设置当前控件的扩展风格
	Pe_Tls_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//报表试图
		LVS_EX_GRIDLINES//网格线


		);
	CRect rc;
	Pe_Tls_List.GetClientRect(rc);
	int nWidth = rc.Width();

	//为list添加信息
	Pe_Tls_List.InsertColumn(
		0, L"源数据起始位置", 0, nWidth / 3
		);
	Pe_Tls_List.InsertColumn(
		1, L"源数据终止位置", 0, nWidth / 3
		);
	Pe_Tls_List.InsertColumn(
		2, L"TLS回调函数地址表位置", 0, nWidth / 3
		);
	//获取扩展头的位置
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);

	//获取TLS表的RVA
	DWORD TlsTableRva = pOh->DataDirectory[9].VirtualAddress;

	if (0==TlsTableRva)
	{
		MessageBox(L"抱歉", L"本进程没有tls", NULL);
	}
	else{
		//获取TLS表的结构体在内存中的位置
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
	// 异常:  OCX 属性页应返回 FALSE
}
