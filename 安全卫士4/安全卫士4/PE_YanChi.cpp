// PE_YanChi.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "PE_YanChi.h"
#include "PE_YANCHI_LIST.h"
#include "afxdialogex.h"


// PE_YanChi 对话框

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


// PE_YanChi 消息处理程序


BOOL PE_YanChi::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	DWORD dwOldStyle = Pe_yanChi_List.GetExtendedStyle();
	//设置当前控件的扩展风格
	Pe_yanChi_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//报表试图
		LVS_EX_GRIDLINES//网格线


		);
	CRect rc;
	Pe_yanChi_List.GetClientRect(rc);
	int nWidth = rc.Width();

	//为list添加信息
	Pe_yanChi_List.InsertColumn(
		0, L"延迟载入的dll名字", 0, nWidth / 3
		);
	Pe_yanChi_List.InsertColumn(
		1, L"延迟载入的IAT的RVA", 0, nWidth / 3
		);
	Pe_yanChi_List.InsertColumn(
		2, L"延迟载入的INT的RVA", 0, nWidth / 3
		);
	//获取扩展头的位置
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);

	//获取TLS表的RVA
	DWORD YanChi = pOh->DataDirectory[13].VirtualAddress;
	CString aaa;
	if (0 == YanChi)
	{

		MessageBox( 0,L" 没有延迟加载表", 0);


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
	// 异常:  OCX 属性页应返回 FALSE
}
