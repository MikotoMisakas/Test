// Pe_DaoRu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Pe_DaoRu.h"
#include "afxdialogex.h"


// Pe_DaoRu �Ի���

IMPLEMENT_DYNAMIC(Pe_DaoRu, CDialogEx)

Pe_DaoRu::Pe_DaoRu(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
	: CDialogEx(Pe_DaoRu::IDD, pParent)
	, PE_NT_DR(0)
{
	PNt = PNT;
	QBuff = qBuff;

}

Pe_DaoRu::~Pe_DaoRu()
{
}
DWORD Pe_DaoRu::CalcOffsev1(DWORD Rva){
	//1 ��ȡNTͷ
	PIMAGE_NT_HEADERS32 pNTHeader = (PIMAGE_NT_HEADERS32)((long)QBuff + ((PIMAGE_DOS_HEADER)QBuff)->e_lfanew);
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


void Pe_DaoRu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DaoRu_List, PE_DR_LIST);
}


BEGIN_MESSAGE_MAP(Pe_DaoRu, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DaoRu_List, &Pe_DaoRu::OnLvnItemchangedDaoruList)
END_MESSAGE_MAP()


// Pe_DaoRu ��Ϣ�������


BOOL Pe_DaoRu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//PE_DR_LIST.InsertColumn(0,L"dll����",0,nWidth/4);
	//PE_DR_LIST.InsertColumn(1, L"ThankRVA");
	//PE_DR_LIST.InsertColumn(2, L"��ʾ");
	//PE_DR_LIST.InsertColumn(3, L"API����");

	DWORD dwOldStyle = PE_DR_LIST.GetExtendedStyle();
	//���õ�ǰ�ؼ�����չ���
	PE_DR_LIST.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//������ͼ
		LVS_EX_GRIDLINES//������


		);
	CRect rc;
	PE_DR_LIST.GetClientRect(rc);
	int nWidth = rc.Width();

	//Ϊlist�����Ϣ
	PE_DR_LIST.InsertColumn(
		0, L"Dll", 0, nWidth / 3
		);
	PE_DR_LIST.InsertColumn(
		1, L"�����±�", 0, nWidth / 3
		);
	PE_DR_LIST.InsertColumn(
		2, L"������", 0, nWidth / 3
		);




	//��ȡ��չͷ��λ��
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);

	//��ȡ������Rva
	DWORD ImpTRva = pOh->DataDirectory[1].VirtualAddress;
	//����õ�����������ĵ�ַ
	if (0==ImpTRva)
	{
		MessageBox(L"û�е����",NULL, 0);
	}
	else
	{

		IMAGE_IMPORT_DESCRIPTOR *iid = (IMAGE_IMPORT_DESCRIPTOR*)(CalcOffsev1(ImpTRva) + QBuff);

		int i = 0; int k = 1;
		while (iid->OriginalFirstThunk)
		{
			//�ҵ�������Name��RVA
			DWORD NameRva = iid->Name;
			DWORD NameTrue = (DWORD)(CalcOffsev1(iid->Name) + QBuff);




			DWORD INTRVA = iid->OriginalFirstThunk;
			IMAGE_THUNK_DATA* pITD = (IMAGE_THUNK_DATA*)(CalcOffsev1(INTRVA) + QBuff);
			while (pITD->u1.AddressOfData)
			{

				if (!IMAGE_SNAP_BY_ORDINAL(pITD->u1.Ordinal))
				{
					IMAGE_IMPORT_BY_NAME * iibn = (IMAGE_IMPORT_BY_NAME*)(CalcOffsev1(pITD->u1.AddressOfData) + QBuff);
					CString q = ((CString)(char*)NameTrue);
					PE_DR_LIST.InsertItem(i, q);



					CString qwe;
					qwe.Format(_T("%d"), iibn->Hint);

					PE_DR_LIST.SetItemText(i, 1, qwe);




					//printf("��������%s\n", iibn->Name);
					CString qwer;
					wchar_t aa[70] = { 0 };
					MultiByteToWideChar(CP_ACP, 0, iibn->Name, -1, aa, 70);
					qwer.Format(L"%s", aa);

					PE_DR_LIST.SetItemText(i, 2, qwer);



					k++; i++;

				}
				pITD++;
			}

			iid++;

		}


	}
//	IMAGE_IMPORT_DESCRIPTOR *iid = (IMAGE_IMPORT_DESCRIPTOR*)(CalcOffsev1(ImpTRva) + QBuff);
//
//	int i = 0;int k=1;
//	while (iid->OriginalFirstThunk)
//	{
//		//�ҵ�������Name��RVA
//		DWORD NameRva = iid->Name;
//		DWORD NameTrue = (DWORD)(CalcOffsev1(iid->Name) + QBuff);
//		
//		
//		
//		
//		DWORD INTRVA = iid->OriginalFirstThunk;
//		IMAGE_THUNK_DATA* pITD = (IMAGE_THUNK_DATA*)(CalcOffsev1(INTRVA) + QBuff);
//		while (pITD->u1.AddressOfData)
//		{
//
//			if (!IMAGE_SNAP_BY_ORDINAL(pITD->u1.Ordinal))
//			{
//				IMAGE_IMPORT_BY_NAME * iibn = (IMAGE_IMPORT_BY_NAME*)(CalcOffsev1(pITD->u1.AddressOfData) + QBuff);
//CString q = ((CString)(char*)NameTrue);
//PE_DR_LIST.InsertItem(i, q);
//		
//
//		
//				CString qwe;
//				qwe.Format(_T("%d"), iibn->Hint);
//				
//				PE_DR_LIST.SetItemText(i ,1, qwe);
//
//
//
//
//				//printf("��������%s\n", iibn->Name);
//				CString qwer;
//				wchar_t aa[70] = { 0 };
//				MultiByteToWideChar(CP_ACP, 0, iibn->Name, -1, aa, 70);
//				qwer.Format(L"%s", aa);
//		
//				PE_DR_LIST.SetItemText(i,2, qwer);
//
//
//			
//k++;i++;	
//			
//			}
//			pITD++;	
//		}
//
//		iid++;
//		
//	}
//



	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Pe_DaoRu::OnLvnItemchangedDaoruList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
