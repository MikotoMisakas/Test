// PE_ChongDingWei.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "PE_ChongDingWei.h"
#include "afxdialogex.h"


// PE_ChongDingWei �Ի���
typedef struct Typeoffset
{
	WORD Offset : 12;//(1)��СΪ12Bit���ض�λƫ��
	WORD Type : 4;//(2)��СΪ4Bit���ض�λ��Ϣ����ֵ
}TypeOffset;


IMPLEMENT_DYNAMIC(PE_ChongDingWei, CDialogEx)

PE_ChongDingWei::PE_ChongDingWei(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
	: CDialogEx(PE_ChongDingWei::IDD, pParent)
{
	PNt = PNT;
	PBuff = qBuff;
	
}

PE_ChongDingWei::~PE_ChongDingWei()
{
}
DWORD PE_ChongDingWei::rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva){

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

void PE_ChongDingWei::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChongDingWei_Up, Pe_ChongDingWei_Up);
	DDX_Control(pDX, IDC_ChongDingWei_Down, Pe_ChongDingWei_List_Down);
}


BEGIN_MESSAGE_MAP(PE_ChongDingWei, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_ChongDingWei_Up, &PE_ChongDingWei::OnClickChongdingweiUp)
END_MESSAGE_MAP()


// PE_ChongDingWei ��Ϣ�������


BOOL PE_ChongDingWei::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ȡԴ���
	DWORD dwOldStyle = Pe_ChongDingWei_Up.GetExtendedStyle();


	//������չ���
	Pe_ChongDingWei_Up.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//����
		LVS_EX_GRIDLINES//����

		);

	//
	CRect Rc;
	Pe_ChongDingWei_Up.GetClientRect(Rc);
	int nWidth = Rc.Width();

	//Ϊlist����
	Pe_ChongDingWei_Up.InsertColumn(0, L"����", 0, nWidth / 4);
	Pe_ChongDingWei_Up.InsertColumn(1, L"����", 0, nWidth / 4);
	Pe_ChongDingWei_Up.InsertColumn(2, L"RVA", 0, nWidth / 4);
	Pe_ChongDingWei_Up.InsertColumn(3, L"��Ŀ", 0, nWidth / 4);

	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);



	//�õ��ض�λ��������׵�ַ
	DWORD dwRelTabRva = PNt->OptionalHeader.DataDirectory[5].VirtualAddress;

	//printf("%x\n", dwRelTabRva);

	DWORD dwRelTabFoa = rva2foa(PNt, dwRelTabRva);
	IMAGE_BASE_RELOCATION* pRelTab = (IMAGE_BASE_RELOCATION*)(dwRelTabFoa + PBuff);

	int i = 1;
	int j = 0;
	int k = 0;

	
	while (pRelTab->SizeOfBlock != 0)
	{
		
		TypeOffset* pTypeOffset = NULL;
		pTypeOffset = (TypeOffset *)(pRelTab + 1);








		DWORD dwCount = (pRelTab->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;

	
	/*	CString aa;
		aa.Format(_T("%x"), pRelTab->VirtualAddress);
		Pe_ChongDingWei_Up.SetItemText(k, 2, aa);*/
		IMAGE_SECTION_HEADER*pScnHdr = (IMAGE_SECTION_HEADER*)IMAGE_FIRST_SECTION(PNt);
		
		for (DWORD i = 0; i < PNt->FileHeader.NumberOfSections; ++i)
		{
			if (pRelTab->VirtualAddress >= pScnHdr[i].VirtualAddress&&pRelTab->VirtualAddress <= pScnHdr[i].VirtualAddress + pScnHdr[i].SizeOfRawData)
			{	
				//������
				CString qwer;
				qwer.Format(_T("%d"), k);
				Pe_ChongDingWei_Up.InsertItem(k, qwer);


				//�������������
				CString qaz = (CString)pScnHdr[i].Name;
				

				//���
				Pe_ChongDingWei_Up.SetItemText(k,1,qaz);
			
			

				//�����Ҫ�ض���ĸ���
				DWORD A = (pRelTab->SizeOfBlock-8)/2;
				CString ss;
				ss.Format(_T("%d"), A);
				Pe_ChongDingWei_Up.SetItemText(k, 3,ss);


				//�������RVA
				CString aa;
				aa.Format(_T("%x"), pRelTab->VirtualAddress);
				Pe_ChongDingWei_Up.SetItemText(k++, 2, aa);

			}
		}
		for (DWORD i = 0; i < dwCount; ++i)
		{
			//printf("\t[%d][%04X]\n", pTypeOffset[i].Type, pTypeOffset[i].Offset);




		}

		pRelTab = (IMAGE_BASE_RELOCATION*)((LPBYTE)pRelTab + pRelTab->SizeOfBlock);
		
	

	}










	///////////////////////////////////////////////////////////////
	//�ϱߵ�list




	///////////////////////////////////////
	//�±ߵ�list
	//��ȡԴ���
	DWORD dOldStyle = Pe_ChongDingWei_List_Down.GetExtendedStyle();//��ȡԴ���


	//������չ���
	Pe_ChongDingWei_List_Down.SetExtendedStyle(dOldStyle |
		LVS_EX_FULLROWSELECT |//����
		LVS_EX_GRIDLINES//����

		);

	//
	CRect Re;
	Pe_ChongDingWei_List_Down.GetClientRect(Re);
	int qWidth = Re.Width();

	//Ϊlist����
	Pe_ChongDingWei_List_Down.InsertColumn(0, L"����", 0, qWidth / 4);
	Pe_ChongDingWei_List_Down.InsertColumn(1, L"RVA", 0, qWidth / 4);
	Pe_ChongDingWei_List_Down.InsertColumn(2, L"����", 0, qWidth / 4);
	Pe_ChongDingWei_List_Down.InsertColumn(3, L"FAR", 0, qWidth / 4);



	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/////////////////////////
void PE_ChongDingWei::OnClickChongdingweiUp(NMHDR *pNMHDR, LRESULT *pResult)
{



	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	pNMItemActivate->iItem;//��ȡ���ѡ��
	*pResult = 0;




	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);



	//�õ��ض�λ��������׵�ַ
	DWORD dwRelTabRva = PNt->OptionalHeader.DataDirectory[5].VirtualAddress;

	//printf("%x\n", dwRelTabRva);

	DWORD dwRelTabFoa = rva2foa(PNt, dwRelTabRva);
	IMAGE_BASE_RELOCATION* pRelTab = (IMAGE_BASE_RELOCATION*)(dwRelTabFoa + PBuff);

	for (int i = 0; i < pNMItemActivate->iItem;i++)
	{
		pRelTab = (IMAGE_BASE_RELOCATION*)((LPBYTE)pRelTab + pRelTab->SizeOfBlock);
	}

	TypeOffset* pTypeOffset = NULL;
	pTypeOffset = (TypeOffset *)(pRelTab + 1);

	DWORD dwCount = (pRelTab->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;

	CString nTemp;
	for (int i = 0; i < dwCount; i++)
	{
		nTemp.Format(TEXT("%d"), i);
		Pe_ChongDingWei_List_Down.InsertItem(i, nTemp);

		nTemp.Format(TEXT("%04X"), pTypeOffset->Offset + pRelTab->VirtualAddress+PNt->OptionalHeader.AddressOfEntryPoint);
		Pe_ChongDingWei_List_Down.SetItemText(i, 1, nTemp);


		nTemp.Format(TEXT("%04X"), pTypeOffset->Type);
		Pe_ChongDingWei_List_Down.SetItemText(i,2, nTemp);

		DWORD AAA=  pRelTab->VirtualAddress + pTypeOffset->Offset;
		CString X;
		X.Format(_T("%x"), AAA);
		Pe_ChongDingWei_List_Down.SetItemText(i, 3, X);
		

		pTypeOffset++;
	}

}
