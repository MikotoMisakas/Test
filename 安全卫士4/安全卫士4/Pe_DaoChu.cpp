// Pe_DaoChu.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "Pe_DaoChu.h"
#include"resource.h"
#include "afxdialogex.h"


// Pe_DaoChu 对话框

IMPLEMENT_DYNAMIC(Pe_DaoChu, CDialogEx)

Pe_DaoChu::Pe_DaoChu(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
: CDialogEx(Pe_DaoChu::IDD, pParent)
, Pe_DaoChuBianLiang(0)
, PE_NT_DC_RVA(_T(""))
, PE_NT_DC_FOA(_T(""))
, PE_NT_DC_JS(_T(""))
, PE_NT_DC_HS？(_T(""))
, PE_NT_DC_HSMS(_T(""))
, PE_NT_DaoChuDiZhi(_T(""))
, PE_NT_DC_MC(_T(""))
, PE_NT_DC_XH(_T(""))
{
	PNt = PNT;
	PBuff = qBuff;

}
DWORD Pe_DaoChu::CalcOffsev1(DWORD Rva){
	//1 获取NT头
	PIMAGE_NT_HEADERS32 pNTHeader = (PIMAGE_NT_HEADERS32)((long)PBuff + ((PIMAGE_DOS_HEADER)PBuff)->e_lfanew);
	//2获取区段头表
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNTHeader);
	//3循环比较它在哪个区段中，不区段就继续循环
	while (1)
	{
		if (Rva >= pSectionHeader->VirtualAddress&&Rva < pSectionHeader->VirtualAddress + pSectionHeader->SizeOfRawData)
		{
			break;
		}
		else
		{
			if (pSectionHeader->PointerToRawData == 0)
			{
				break;
			}
			else
			{
				pSectionHeader++;
			}

		}

	}

	return Rva - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;


}


Pe_DaoChu::~Pe_DaoChu()
{
}

void Pe_DaoChu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DaoChuBiao_List, Pe_DaoChu1);
	DDX_Text(pDX, IDC_EDIT1, PE_NT_DC_RVA);
	DDX_Text(pDX, IDC_EDIT2, PE_NT_DC_FOA);
	DDX_Text(pDX, IDC_EDIT3, PE_NT_DC_JS);
	DDX_Text(pDX, IDC_EDIT6, PE_NT_DC_HS？);
	DDX_Text(pDX, IDC_EDIT7, PE_NT_DC_HSMS);
	DDX_Text(pDX, IDC_EDIT8, PE_NT_DaoChuDiZhi);
	DDX_Text(pDX, IDC_EDIT9, PE_NT_DC_MC);
	DDX_Text(pDX, IDC_EDIT10, PE_NT_DC_XH);
}


BEGIN_MESSAGE_MAP(Pe_DaoChu, CDialogEx)
END_MESSAGE_MAP()


// Pe_DaoChu 消息处理程序


BOOL Pe_DaoChu::OnInitDialog()
{
	CDialogEx::OnInitDialog();




	// TODO:  在此添加额外的初始化


	DWORD dwOldStyle = Pe_DaoChu1.GetExtendedStyle();//获取原来的风格




	//设置当前控件的扩展风格
	Pe_DaoChu1.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//获取list宽度
	CRect Re;
	Pe_DaoChu1.GetClientRect(Re);
	int nWidth = Re.Width();

	//为list插入列信息
	Pe_DaoChu1.InsertColumn(
		0,//当前列编号
		L"序号",
		0,
		nWidth / 3

		);
	Pe_DaoChu1.InsertColumn(
		1,//当前列编号
		L"RVA",
		0,
		nWidth / 3

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//当前列编号
	//	L"偏移",
	//	0,
	//	nWidth / 4

	//	);
	Pe_DaoChu1.InsertColumn(
		2,//当前列编号
		L"函数名",
		0,
		nWidth / 3

		);

	//获取扩展头的位置
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);
	
	//获取数据目录表第零项信息
	DWORD exRva = (pOh->DataDirectory[0]).VirtualAddress;
	if (	0==exRva)
	{
		MessageBox(L"没有导出表", NULL, 0);
	}
	else
	{
		//输出数据目录表的东西  RVA
		CString DaoChuRva;
		DaoChuRva.Format(_T("%d"), exRva);
		PE_NT_DC_RVA = DaoChuRva;





		//导出表的FOA
		DWORD exFoa = CalcOffsev1(exRva);

		CString DaoChuFoa;
		DaoChuFoa.Format(_T("%d"), exFoa);
		PE_NT_DC_FOA = DaoChuFoa;





		exFoa += (DWORD)PBuff;//真正的结构体地址
		//获取指向导出表的指针
		IMAGE_EXPORT_DIRECTORY * pEx = (IMAGE_EXPORT_DIRECTORY*)(exFoa);

		//导出表的奇数
		CString XHJS;
		XHJS.Format(_T("%d"), pEx->Base);
		PE_NT_DC_JS = XHJS;

		//导出表的


		CString DiZhiBiao;
		DaoChuFoa.Format(_T("%d"), &(pEx->AddressOfFunctions));
		PE_NT_DaoChuDiZhi = DaoChuFoa;




		////
		CString MC;
		MC.Format(_T("%d"), &(pEx->AddressOfNames));
		PE_NT_DC_MC = DaoChuRva;


		//
		CString XH;
		XH.Format(_T("%d"), &(pEx->AddressOfNameOrdinals));
		PE_NT_DC_XH = XH;




		//函数的数量
		CString HSSL;
		HSSL.Format(_T("%d"), pEx->NumberOfFunctions);
		PE_NT_DC_HS？ = HSSL;



		//函数名称数两
		CString HSMS;
		HSMS.Format(_T("%d"), pEx->NumberOfNames);
		PE_NT_DC_HSMS = HSMS;





		//
		//获取导出表的函数名称表的指针
		DWORD*eXName = (DWORD*)(CalcOffsev1(pEx->AddressOfNames) + PBuff);
		//获取导出表的函数序号表的指针
		WORD*eXOrdinals = (WORD*)(CalcOffsev1(pEx->AddressOfNameOrdinals) + PBuff);
		//获取导出表的函数地址表的指针
		DWORD*eXFunc = (DWORD*)(CalcOffsev1(pEx->AddressOfFunctions) + PBuff);
		int w = 0;
		for (int i = 0; i < pEx->NumberOfNames; i++)
		{

			CString a;
			a.Format(_T("%d"), eXOrdinals[i]);
			Pe_DaoChu1.InsertItem(w, a);


			CString d;
			d.Format(_T("%d"), eXFunc[eXOrdinals[i]]);
			Pe_DaoChu1.SetItemText(w, 1, d);



			DWORD NameAddress = (DWORD)(CalcOffsev1(eXName[i]) + PBuff);
			//printf("函数名称%s\n", (char*)NameAddress);
			////找到导出表的序号
			CString k = (CString)((char*)NameAddress);
			/*	k.Format(L"%s", (char*)NameAddress);*/
			Pe_DaoChu1.SetItemText(w, 2, k);
			w++;

		}






	}


	////输出数据目录表的东西  RVA
	//CString DaoChuRva;
	//	DaoChuRva.Format(_T("%d"), exRva);
	//PE_NT_DC_RVA = DaoChuRva;


	//


	////导出表的FOA
	//DWORD exFoa = CalcOffsev1(exRva);

	//CString DaoChuFoa;
	//DaoChuFoa.Format(_T("%d"), exFoa);
	//PE_NT_DC_FOA = DaoChuFoa;




 // 
	//exFoa += (DWORD)PBuff;//真正的结构体地址
	////获取指向导出表的指针
	//IMAGE_EXPORT_DIRECTORY * pEx = (IMAGE_EXPORT_DIRECTORY*)(exFoa);
	//
	////导出表的奇数
	//CString XHJS;
	//XHJS.Format(_T("%d"), pEx->Base);
	//PE_NT_DC_JS = XHJS;

	////导出表的


	//CString DiZhiBiao;
	//DaoChuFoa.Format(_T("%d"), &(pEx->AddressOfFunctions));
	//PE_NT_DaoChuDiZhi = DaoChuFoa;




	//////
	//CString MC;
	//MC.Format(_T("%d"), &(pEx->AddressOfNames));
	//PE_NT_DC_MC = DaoChuRva;


	////
	//CString XH;
	//XH.Format(_T("%d"), &(pEx->AddressOfNameOrdinals));
	//PE_NT_DC_XH =XH;




	////函数的数量
	//CString HSSL;
	//HSSL.Format(_T("%d"), pEx->NumberOfFunctions);
	//PE_NT_DC_HS？= HSSL;



	////函数名称数两
	//CString HSMS;
	//HSMS.Format(_T("%d"), pEx->NumberOfNames);
	//PE_NT_DC_HSMS = HSMS;





	////
	////获取导出表的函数名称表的指针
	//DWORD*eXName = (DWORD*)(CalcOffsev1(pEx->AddressOfNames) + PBuff);
	////获取导出表的函数序号表的指针
	//WORD*eXOrdinals = (WORD*)(CalcOffsev1(pEx->AddressOfNameOrdinals) + PBuff);
	////获取导出表的函数地址表的指针
	//DWORD*eXFunc = (DWORD*)(CalcOffsev1(pEx->AddressOfFunctions) + PBuff);
	//int w = 0;
	//for (int i = 0; i < pEx->NumberOfNames; i++)
	//{

	//	CString a;
	//	a.Format(_T("%d"), eXOrdinals[i]);
	//	Pe_DaoChu1.InsertItem(w,a);
	//
	//	
	//	CString d;
	//	d.Format(_T("%d"), eXFunc[eXOrdinals[i]]);
	//	Pe_DaoChu1.SetItemText(w,1, d);
	//	

	//
	//	DWORD NameAddress = (DWORD)(CalcOffsev1(eXName[i]) + PBuff);
	//	//printf("函数名称%s\n", (char*)NameAddress);
	//	////找到导出表的序号
	//	CString k = (CString)((char*)NameAddress);
	///*	k.Format(L"%s", (char*)NameAddress);*/
	//	Pe_DaoChu1.SetItemText(w, 2, k);		
	//		w++;

	//}



	//
	//

	UpdateData(FALSE);





	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
