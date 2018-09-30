// PE_ZY_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "PE_ZY_Dlg.h"
#include "afxdialogex.h"


// PE_ZY_Dlg 对话框

IMPLEMENT_DYNAMIC(PE_ZY_Dlg, CDialogEx)

PE_ZY_Dlg::PE_ZY_Dlg(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent /*=NULL*/)
	: CDialogEx(PE_ZY_Dlg::IDD, pParent)
{
	PNt = PNT;
	PBuff = qBuff;
}
void PE_ZY_Dlg::parseResources(LPBYTE pResDirRoot, IMAGE_RESOURCE_DIRECTORY* pDir, int nLevel ){

	static int count = 0;
	//得到这一层目录入口的总个数
	DWORD dwEntryCount = pDir->NumberOfIdEntries + pDir->NumberOfNamedEntries;
	//获取到这一层目录的目录入口数组的首地址
	IMAGE_RESOURCE_DIRECTORY_ENTRY*pEntry = NULL;
	pEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pDir + 1);
	if (nLevel == 1)
	{
		for (DWORD i = 0; i < dwEntryCount; ++i)
		{
			//第一层的目录入口中保存了两个信息;
			//1.id,有两类,一是整型id，二是字符串id
			//解析资源的类型
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
					"鼠标指针（Cursor）",
					"位图（Bitmap）",
					"图标(Icon)",
					"菜单(Menu)",
					"对话框(Dialog)",
					"字符串列表(String Table)",
					"字体目录(Font Directory)",
					"字体(Font)",
					"快捷键(Acceletators)",
					"非格式化资源(Unformatted)",
					"消息列表(Message Table)",
					"鼠标指针组(Group Cursor)",
					"",
					"图标组(Group Icon)",
					"",
					"版本信息(Version Information)"
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
			//解析第二层的目录入口;
			//1.id(资源的id）（有字符串,有整型）

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

			//2.偏移(以资源根目录偏移，偏移到第三层)
			IMAGE_RESOURCE_DIRECTORY*p3Dir = (IMAGE_RESOURCE_DIRECTORY*)(pEntry[i].OffsetToDirectory + pResDirRoot);



			//找到第3层目录的首地址
			parseResources(pResDirRoot, p3Dir, 3);




		}


	}
	else if (nLevel == 3)
	{


		for (DWORD i = 0; i < dwEntryCount; ++i)
		{
			IMAGE_RESOURCE_DATA_ENTRY* pDataEntry = (IMAGE_RESOURCE_DATA_ENTRY*)(pEntry[i].OffsetToData + pResDirRoot);
			printf("\t\t大小:%08X 位置:%08X\n", pDataEntry->Size, pDataEntry->OffsetToData);
		
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


// PE_ZY_Dlg 消息处理程序


BOOL PE_ZY_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwOldStyle = Pe_Zy_List.GetExtendedStyle();//获取源风格

	Pe_Zy_List.SetExtendedStyle(dwOldStyle |
		LVS_EX_FULLROWSELECT |//报表
		LVS_EX_GRIDLINES//网格线
		);

	//list宽度
	CRect Rc;
	Pe_Zy_List.GetClientRect(Rc);
	int nWidth = Rc.Width();

	//为list插入信息
	Pe_Zy_List.InsertColumn(0, L"资源类型", 0, nWidth / 4);
	Pe_Zy_List.InsertColumn(1, L"资源名称", 0, nWidth / 4);
	Pe_Zy_List.InsertColumn(2, L"RVA", 0, nWidth / 4);
	Pe_Zy_List.InsertColumn(3, L"资源大小", 0, nWidth / 4);


	//获取扩展头的位置
	IMAGE_OPTIONAL_HEADER *pOh = NULL;
	pOh = &(PNt->OptionalHeader);
	//获取资源表
	IMAGE_RESOURCE_DIRECTORY*pResDir = NULL;
	DWORD dwResTabRva = pOh->DataDirectory[2].VirtualAddress;
	DWORD dwResTabFoa = rva2foa(PNt, dwResTabRva);


	//
	pResDir = (IMAGE_RESOURCE_DIRECTORY*)(dwResTabFoa + PBuff);


	parseResources((LPBYTE)pResDir, pResDir);






	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
