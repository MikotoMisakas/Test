// Tab_LaJi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include<vector>
#include "Tab_LaJi.h"
#include "afxdialogex.h"
#include <Strsafe.h>
using namespace std;

// Tab_LaJi �Ի���

IMPLEMENT_DYNAMIC(Tab_LaJi, CDialogEx)

Tab_LaJi::Tab_LaJi(CWnd* pParent /*=NULL*/)
: CDialogEx(Tab_LaJi::IDD, pParent)
{

}

Tab_LaJi::~Tab_LaJi()
{
}

void Tab_LaJi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tab_LaJi, CDialogEx)
	ON_BN_CLICKED(IDC_LaJi, &Tab_LaJi::OnBnClickedLaji)
	ON_BN_CLICKED(IDC_ZDLJLJ, &Tab_LaJi::OnBnClickedZdljlj)
END_MESSAGE_MAP()


// Tab_LaJi ��Ϣ�������
ULARGE_INTEGER  Tab_LaJi::EnumFoldAndDeleteFile(CString lpFoldPath, WCHAR *lpFileType)
{
	//1.��ʼ��·���ַ���
	HANDLE hFindFile = FindFirstFile(lpFoldPath + "\\*", &w32FindData);
	//3.ѭ��������ȡ��ǰĿ¼���ļ���Ϣ
	do
	{
		//ȥ����������Ŀ¼
		if ((!wcscmp(w32FindData.cFileName, L".")) || (!wcscmp(w32FindData.cFileName, L"..")))
		{
			continue;
		}
		if (w32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//�ļ��У�����ɾ���ļ����������
			WCHAR szSubfoldPath[MAX_PATH];
			StringCchPrintf(szSubfoldPath, MAX_PATH, L"%s\\", lpFoldPath);
			StringCchCat(szSubfoldPath, MAX_PATH, w32FindData.cFileName);

			wcscpy_s(szFullPath, MAX_PATH, szSubfoldPath);
			//��Ŀ¼��
			qwFileTotalSize = EnumFoldAndDeleteFile(szSubfoldPath, lpFileType);
		}
		else
		{
			//��ȡ�ļ��ĺ�׺
			WCHAR szSubfoldPath[MAX_PATH];
			StringCchPrintf(szSubfoldPath, MAX_PATH, L"%s\\", lpFoldPath);
			StringCchCat(szSubfoldPath, MAX_PATH, w32FindData.cFileName);
			LPWSTR FileSuffix = PathFindExtension(szSubfoldPath);
			if (!lstrcmp(FileSuffix, L".tlog") || !lstrcmp(FileSuffix, L".obj") ||
				!lstrcmp(FileSuffix, L".log") ||
				!lstrcmp(FileSuffix, L".pch") || !lstrcmp(FileSuffix, L".ilk") ||
				!lstrcmp(FileSuffix, L".pdb"))
			{
				ULARGE_INTEGER filesize;  //��¼�ļ��Ĵ�С
				filesize.HighPart = w32FindData.nFileSizeHigh;
				filesize.LowPart = w32FindData.nFileSizeLow;
				qwFileTotalSize.QuadPart += filesize.QuadPart;

				DeleteFile(szSubfoldPath);

			}
		}
	} while (FindNextFile(hFindFile, &w32FindData));



	//MessageBox(L"������ϣ�", L"��ʾ��", 0);
	return qwFileTotalSize;
}

void Tab_LaJi::OnBnClickedLaji()
{

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog dlg;
	dlg.DoModal();
	CString m_path = dlg.GetFolderPath();

	WCHAR* filetype = L"\\*.obj";
	EnumFoldAndDeleteFile(m_path, filetype);

	MessageBox(L"������ϣ�", L"��ʾ��", 0);


}
CString aaa;
DWORD WINAPI EnumWindowsProc(LPVOID lpParameter){
	

	aaa.Format(L"%s",lpParameter);
	
	WIN32_FIND_DATAW* wfd=new WIN32_FIND_DATAW;
	aaa += L"\\*";



HANDLE hfile=	FindFirstFile(aaa, wfd);
if (hfile == INVALID_HANDLE_VALUE)
{
	MessageBox(0, 0, 0, 0);
	return 0;
}
do 
{

	if (wfd->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
	{
		WCHAR*p = new WCHAR[MAX_PATH];
		swscanf_s(aaa + wfd->cFileName, L"%s", p,70);
		EnumWindowsProc((LPVOID)p);
		delete[70] p;
	}
	else
	{
		WCHAR *szSubfoldPath=new WCHAR[MAX_PATH];
		StringCchPrintf(szSubfoldPath, MAX_PATH, L"%s\\", aaa);
		StringCchCat(szSubfoldPath, MAX_PATH, wfd->cFileName);
		LPWSTR FileSuffix = PathFindExtension(szSubfoldPath);
		if (!lstrcmp(FileSuffix, L".tlog") || !lstrcmp(FileSuffix, L".obj") ||
			!lstrcmp(FileSuffix, L".log") ||
			!lstrcmp(FileSuffix, L".pch") || !lstrcmp(FileSuffix, L".ilk") ||
			!lstrcmp(FileSuffix, L".pdb")){



		
			DeleteFile(aaa);

		}
		


		delete[MAX_PATH] szSubfoldPath;












	}







} while (FindNextFile(hfile,wfd));




	//DeleteFile(aaa);
	//CreateFile(aaa, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, NULL);



delete wfd;


MessageBox(0, 0, 0, 0);

	return true;
}

void Tab_LaJi::OnBnClickedZdljlj()
{
	CString  aab("C:\\Users\\admin\\AppData\\Local\\Temp");
	WCHAR woqu[50] = { L"C:\\Users\\admin\\AppData\\Local\\Temp" };
	HANDLE aaa = CreateThread(NULL,//��ȫ����
		0x20000000,//��ջ��С
		EnumWindowsProc,//��ں���
		(LPVOID*)(woqu),//��������
		NULL,//����ѡ��
		NULL//����߳�id
		);

	//WaitForSingleObject(aaa, -1);
	

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
