// Pe_DaoChu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Pe_DaoChu.h"
#include"resource.h"
#include "afxdialogex.h"


// Pe_DaoChu �Ի���

IMPLEMENT_DYNAMIC(Pe_DaoChu, CDialogEx)

Pe_DaoChu::Pe_DaoChu(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
: CDialogEx(Pe_DaoChu::IDD, pParent)
, Pe_DaoChuBianLiang(0)
, PE_NT_DC_RVA(_T(""))
, PE_NT_DC_FOA(_T(""))
, PE_NT_DC_JS(_T(""))
, PE_NT_DC_HS��(_T(""))
, PE_NT_DC_HSMS(_T(""))
, PE_NT_DaoChuDiZhi(_T(""))
, PE_NT_DC_MC(_T(""))
, PE_NT_DC_XH(_T(""))
{
	PNt = PNT;
	PBuff = qBuff;

}
DWORD Pe_DaoChu::CalcOffsev1(DWORD Rva){
	//1 ��ȡNTͷ
	PIMAGE_NT_HEADERS32 pNTHeader = (PIMAGE_NT_HEADERS32)((long)PBuff + ((PIMAGE_DOS_HEADER)PBuff)->e_lfanew);
	//2��ȡ����ͷ��
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNTHeader);
	//3ѭ���Ƚ������ĸ������У������ξͼ���ѭ��
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
	DDX_Text(pDX, IDC_EDIT6, PE_NT_DC_HS��);
	DDX_Text(pDX, IDC_EDIT7, PE_NT_DC_HSMS);
	DDX_Text(pDX, IDC_EDIT8, PE_NT_DaoChuDiZhi);
	DDX_Text(pDX, IDC_EDIT9, PE_NT_DC_MC);
	DDX_Text(pDX, IDC_EDIT10, PE_NT_DC_XH);
}


BEGIN_MESSAGE_MAP(Pe_DaoChu, CDialogEx)
END_MESSAGE_MAP()


// Pe_DaoChu ��Ϣ�������


BOOL Pe_DaoChu::OnInitDialog()
{
	CDialogEx::OnInitDialog();




	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	DWORD dwOldStyle = Pe_DaoChu1.GetExtendedStyle();//��ȡԭ���ķ��




	//���õ�ǰ�ؼ�����չ���
	Pe_DaoChu1.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES


		);



	//��ȡlist���
	CRect Re;
	Pe_DaoChu1.GetClientRect(Re);
	int nWidth = Re.Width();

	//Ϊlist��������Ϣ
	Pe_DaoChu1.InsertColumn(
		0,//��ǰ�б��
		L"���",
		0,
		nWidth / 3

		);
	Pe_DaoChu1.InsertColumn(
		1,//��ǰ�б��
		L"RVA",
		0,
		nWidth / 3

		);
	//Pe_DaoChu1.InsertColumn(
	//	2,//��ǰ�б��
	//	L"ƫ��",
	//	0,
	//	nWidth / 4

	//	);
	Pe_DaoChu1.InsertColumn(
		2,//��ǰ�б��
		L"������",
		0,
		nWidth / 3

		);

	//��ȡ��չͷ��λ��
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);
	
	//��ȡ����Ŀ¼���������Ϣ
	DWORD exRva = (pOh->DataDirectory[0]).VirtualAddress;
	if (	0==exRva)
	{
		MessageBox(L"û�е�����", NULL, 0);
	}
	else
	{
		//�������Ŀ¼��Ķ���  RVA
		CString DaoChuRva;
		DaoChuRva.Format(_T("%d"), exRva);
		PE_NT_DC_RVA = DaoChuRva;





		//�������FOA
		DWORD exFoa = CalcOffsev1(exRva);

		CString DaoChuFoa;
		DaoChuFoa.Format(_T("%d"), exFoa);
		PE_NT_DC_FOA = DaoChuFoa;





		exFoa += (DWORD)PBuff;//�����Ľṹ���ַ
		//��ȡָ�򵼳����ָ��
		IMAGE_EXPORT_DIRECTORY * pEx = (IMAGE_EXPORT_DIRECTORY*)(exFoa);

		//�����������
		CString XHJS;
		XHJS.Format(_T("%d"), pEx->Base);
		PE_NT_DC_JS = XHJS;

		//�������


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




		//����������
		CString HSSL;
		HSSL.Format(_T("%d"), pEx->NumberOfFunctions);
		PE_NT_DC_HS�� = HSSL;



		//������������
		CString HSMS;
		HSMS.Format(_T("%d"), pEx->NumberOfNames);
		PE_NT_DC_HSMS = HSMS;





		//
		//��ȡ������ĺ������Ʊ��ָ��
		DWORD*eXName = (DWORD*)(CalcOffsev1(pEx->AddressOfNames) + PBuff);
		//��ȡ������ĺ�����ű��ָ��
		WORD*eXOrdinals = (WORD*)(CalcOffsev1(pEx->AddressOfNameOrdinals) + PBuff);
		//��ȡ������ĺ�����ַ���ָ��
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
			//printf("��������%s\n", (char*)NameAddress);
			////�ҵ�����������
			CString k = (CString)((char*)NameAddress);
			/*	k.Format(L"%s", (char*)NameAddress);*/
			Pe_DaoChu1.SetItemText(w, 2, k);
			w++;

		}






	}


	////�������Ŀ¼��Ķ���  RVA
	//CString DaoChuRva;
	//	DaoChuRva.Format(_T("%d"), exRva);
	//PE_NT_DC_RVA = DaoChuRva;


	//


	////�������FOA
	//DWORD exFoa = CalcOffsev1(exRva);

	//CString DaoChuFoa;
	//DaoChuFoa.Format(_T("%d"), exFoa);
	//PE_NT_DC_FOA = DaoChuFoa;




 // 
	//exFoa += (DWORD)PBuff;//�����Ľṹ���ַ
	////��ȡָ�򵼳����ָ��
	//IMAGE_EXPORT_DIRECTORY * pEx = (IMAGE_EXPORT_DIRECTORY*)(exFoa);
	//
	////�����������
	//CString XHJS;
	//XHJS.Format(_T("%d"), pEx->Base);
	//PE_NT_DC_JS = XHJS;

	////�������


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




	////����������
	//CString HSSL;
	//HSSL.Format(_T("%d"), pEx->NumberOfFunctions);
	//PE_NT_DC_HS��= HSSL;



	////������������
	//CString HSMS;
	//HSMS.Format(_T("%d"), pEx->NumberOfNames);
	//PE_NT_DC_HSMS = HSMS;





	////
	////��ȡ������ĺ������Ʊ��ָ��
	//DWORD*eXName = (DWORD*)(CalcOffsev1(pEx->AddressOfNames) + PBuff);
	////��ȡ������ĺ�����ű��ָ��
	//WORD*eXOrdinals = (WORD*)(CalcOffsev1(pEx->AddressOfNameOrdinals) + PBuff);
	////��ȡ������ĺ�����ַ���ָ��
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
	//	//printf("��������%s\n", (char*)NameAddress);
	//	////�ҵ�����������
	//	CString k = (CString)((char*)NameAddress);
	///*	k.Format(L"%s", (char*)NameAddress);*/
	//	Pe_DaoChu1.SetItemText(w, 2, k);		
	//		w++;

	//}



	//
	//

	UpdateData(FALSE);





	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
