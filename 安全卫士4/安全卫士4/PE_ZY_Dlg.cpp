// PE_ZY_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "PE_ZY_Dlg.h"
#include "afxdialogex.h"


// PE_ZY_Dlg �Ի���

IMPLEMENT_DYNAMIC(PE_ZY_Dlg, CDialogEx)

PE_ZY_Dlg::PE_ZY_Dlg(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
	: CDialogEx(PE_ZY_Dlg::IDD, pParent)
{
	PNt = PNT;
	PBuff = qBuff;
}
void PE_ZY_Dlg::parseResources(LPBYTE pResDirRoot, IMAGE_RESOURCE_DIRECTORY* pDir, int nLevel ){

	static int count = 0;
	//�õ���һ��Ŀ¼��ڵ��ܸ���
	DWORD dwEntryCount = pDir->NumberOfIdEntries + pDir->NumberOfNamedEntries;
	//��ȡ����һ��Ŀ¼��Ŀ¼���������׵�ַ
	IMAGE_RESOURCE_DIRECTORY_ENTRY*pEntry = NULL;
	pEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pDir + 1);
	if (nLevel == 1)
	{
		for (DWORD i = 0; i < dwEntryCount; ++i)
		{
			//��һ���Ŀ¼����б�����������Ϣ;
			//1.id,������,һ������id�������ַ���id
			//������Դ������
			if (pEntry[i].NameIsString)
			{
				IMAGE_RESOURCE_DIR_STRING_U* pIdStr = (IMAGE_RESOURCE_DIR_STRING_U*)(pEntry[i].NameOffset + pResDirRoot);
				//wprintf(L"[%s]\n", pIdStr->NameString);
				/////////////////////////
				/*wchar_t aa[50] = { 0 };
				MultiByteToWideChar(CP_ACP,0,pIdStr->NameString)*/
				CString qwe;
				qwe.Format(L"%s", pIdStr->NameString);
				Pe_Zy_List.InsertItem(count++,qwe);/////////////////
				//Pe_Zy_List.SetItemText(i,1,);//
			}
			else
			{
				char * pIdName[] =
				{
					"",
					"���ָ�루Cursor��",
					"λͼ��Bitmap��",
					"ͼ��(Icon)",
					"�˵�(Menu)",
					"�Ի���(Dialog)",
					"�ַ����б�(String Table)",
					"����Ŀ¼(Font Directory)",
					"����(Font)",
					"��ݼ�(Acceletators)",
					"�Ǹ�ʽ����Դ(Unformatted)",
					"��Ϣ�б�(Message Table)",
					"���ָ����(Group Cursor)",
					"",
					"ͼ����(Group Icon)",
					"",
					"�汾��Ϣ(Version Information)"
				};

				if (pEntry[i].Id >= _countof(pIdName))
				{
					//printf("[%d]\n", pEntry[i].Id);
					

					CString aa;
					aa.Format(L"%x", pEntry[i].Id);

					Pe_Zy_List.InsertItem(count++, aa);
				}
				else
				{
					//printf("[%s]\n", pIdName[pEntry[i].Id]);
					wchar_t aaaaa[50] = { 0 };
					MultiByteToWideChar(CP_ACP, 0, pIdName[pEntry[i].Id], -1, aaaaa, 50);
					CString ab;
					ab.Format(L"%s", aaaaa);

					Pe_Zy_List.InsertItem(count++, ab);
				}
			}

			IMAGE_RESOURCE_DIRECTORY* p2Dir = NULL;
			p2Dir = (IMAGE_RESOURCE_DIRECTORY*)(pEntry[i].OffsetToDirectory + pResDirRoot);
			parseResources(pResDirRoot, p2Dir, 2);



		}



	}
	else if (nLevel == 2)
	{
		for (DWORD i = 0; i < dwEntryCount; i++)
		{
			//�����ڶ����Ŀ¼���;
			//1.id(��Դ��id�������ַ���,�����ͣ�

			if (pEntry[i].NameIsString)
			{
				IMAGE_RESOURCE_DIR_STRING_U* pIdStr = (IMAGE_RESOURCE_DIR_STRING_U*)(pEntry[i].NameOffset + pResDirRoot);
				//wprintf(L"[%s]\n", pIdStr->NameString);
				CString qwe;
				qwe.Format(L"%s", pIdStr->NameString);
				Pe_Zy_List.InsertItem(count++, 0);
				Pe_Zy_List.SetItemText(count - 1, 1, qwe);

			}
			else
			{
				//printf("\t%04d\n", (DWORD)pEntry[i].Id);

				CString aa;
				aa.Format(L"%x", pEntry[i].Id);

				Pe_Zy_List.InsertItem(count++, 0);
				Pe_Zy_List.SetItemText(count - 1, 1, aa);

			}

			//2.ƫ��(����Դ��Ŀ¼ƫ�ƣ�ƫ�Ƶ�������)
			IMAGE_RESOURCE_DIRECTORY*p3Dir = (IMAGE_RESOURCE_DIRECTORY*)(pEntry[i].OffsetToDirectory + pResDirRoot);



			//�ҵ���3��Ŀ¼���׵�ַ
			parseResources(pResDirRoot, p3Dir, 3);




		}


	}
	else if (nLevel == 3)
	{


		for (DWORD i = 0; i < dwEntryCount; ++i)
		{
			IMAGE_RESOURCE_DATA_ENTRY* pDataEntry = (IMAGE_RESOURCE_DATA_ENTRY*)(pEntry[i].OffsetToData + pResDirRoot);
			printf("\t\t��С:%08X λ��:%08X\n", pDataEntry->Size, pDataEntry->OffsetToData);
		
			CString aa;
			aa.Format(L"%x", pDataEntry->OffsetToData);
			CString bb;
			bb.Format(L"%x", pDataEntry->Size);

			//Pe_Zy_List.InsertItem(count++, 0);
			Pe_Zy_List.SetItemText(count - 1, 2, aa);
			Pe_Zy_List.SetItemText(count - 1, 3, bb);

		}

	}


}
DWORD PE_ZY_Dlg::rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva)
{

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

PE_ZY_Dlg::~PE_ZY_Dlg()
{
}

void PE_ZY_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_PE_ZY_LIST, PE_ZY_LIST);
	DDX_Control(pDX, IDC_PE_ZY_LIST, Pe_Zy_List);
}


BEGIN_MESSAGE_MAP(PE_ZY_Dlg, CDialogEx)
END_MESSAGE_MAP()


// PE_ZY_Dlg ��Ϣ�������


BOOL PE_ZY_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DWORD dwOldStyle = Pe_Zy_List.GetExtendedStyle();//��ȡԴ���

	Pe_Zy_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//����
		LVS_EX_GRIDLINES//������
		);

	//list���
	CRect Rc;
	Pe_Zy_List.GetClientRect(Rc);
	int nWidth = Rc.Width();

	//Ϊlist������Ϣ
	Pe_Zy_List.InsertColumn(0, L"��Դ����", 0, nWidth / 4);
	Pe_Zy_List.InsertColumn(1, L"��Դ����", 0, nWidth / 4);
	Pe_Zy_List.InsertColumn(2, L"RVA", 0, nWidth / 4);
	Pe_Zy_List.InsertColumn(3, L"��Դ��С", 0, nWidth / 4);


	//��ȡ��չͷ��λ��
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);
	//��ȡ��Դ��
	IMAGE_RESOURCE_DIRECTORY*pResDir = NULL;
	DWORD dwResTabRva = pOh->DataDirectory[2].VirtualAddress;
	DWORD dwResTabFoa = rva2foa(PNt, dwResTabRva);


	//
	pResDir = (IMAGE_RESOURCE_DIRECTORY*)(dwResTabFoa + PBuff);


	parseResources((LPBYTE)pResDir, pResDir);






	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
