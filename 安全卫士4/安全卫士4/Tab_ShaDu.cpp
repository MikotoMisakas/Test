// Tab_ShaDu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "md5.h"
#include "Tab_ShaDu.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// Tab_ShaDu �Ի���

IMPLEMENT_DYNAMIC(Tab_ShaDu, CDialogEx)
void Tab_ShaDu::md5CleanFile(const CString& path, char* md5Str){

	MD5_CTX ctx{};
	WIN32_FIND_DATA wd{};
	HANDLE hFile = FindFirstFile(path + "\\*", &wd);
	int md5Num = strlen(md5Str) / 32;

	if (INVALID_HANDLE_VALUE == hFile)
		return;
	do {
		if (wcscmp(wd.cFileName, L".") == 0 || wcscmp(wd.cFileName, L"..") == 0)
			continue;
		if (!(wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			CString szPath = path + "\\" + wd.cFileName;
			CStringA str(szPath);
			int nLen = str.GetLength();
			unsigned char* pPath = new unsigned char[nLen + 1]{};
			for (int i = 0; i < nLen; i++)
			{
				pPath[i] = str[i];
			}
			MD5Init(&ctx);
			MD5Update(&ctx, pPath, nLen);
			MD5Final(&ctx);
			char* resStr = (char*)Hex2ASC(ctx.digest, 16);
			for (int i = 0; i < md5Num; i++)
			{
				char* eachMd5 = new char[33]{};
				memcpy(eachMd5, md5Str + i * 32, 32);
				if (strcmp(resStr, md5Str) == 0)
				{
					DeleteFile(path + L"\\" + wd.cFileName);
				}
			}
			//printf(Hex2ASC(ctx.digest, 16));
		}
		if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			md5CleanFile(path + L"\\" + wd.cFileName, md5Str);
	} while (FindNextFile(hFile, &wd));




}

Tab_ShaDu::Tab_ShaDu(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_ShaDu::IDD, pParent)
{
	m_sock = NULL;
}
BOOL Tab_ShaDu::cmpMd5(const CString& path){

	MD5_CTX ctx{};
	WIN32_FIND_DATA wd{};
	HANDLE hFile = FindFirstFile(path + "\\*", &wd);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do {
			if (wd.cFileName == CString(".") || wd.cFileName == CString(".."))
				continue;
			if (!(wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{

				/*	MD5Init(&ctx);
					MD5Update();
					MD5Final(&ctx);
					char* res = Hex2ASC();*/
			}
			if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString temp = path + "\\" + wd.cFileName;
				cmpMd5(temp);
			}
		} while (FindNextFile(hFile, &wd));
	}


	return TRUE;
}

Tab_ShaDu::~Tab_ShaDu()
{
}

void Tab_ShaDu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tab_ShaDu, CDialogEx)
	ON_BN_CLICKED(IDC_Md5, &Tab_ShaDu::OnBnClickedMd5)
	ON_BN_CLICKED(IDC_BMD, &Tab_ShaDu::OnBnClickedBmd)
	ON_BN_CLICKED(IDC_QLJ, &Tab_ShaDu::OnBnClickedQlj)
	ON_BN_CLICKED(IDC_DEMO, &Tab_ShaDu::OnBnClickedDemo)
	ON_BN_CLICKED(IDC_CLOUDE, &Tab_ShaDu::OnBnClickedCloude)
END_MESSAGE_MAP()


// Tab_ShaDu ��Ϣ�������


void Tab_ShaDu::OnBnClickedMd5()
{

	CFolderPickerDialog dlg;
	dlg.DoModal();
	CString filePath = dlg.GetPathName();
	HANDLE AA=CreateFile(L"md5.txt", GENERIC_ALL, 0, 0, OPEN_EXISTING, 0, 0);
	char buff[33] = {0};
	DWORD rbuff;
	ReadFile(AA,buff,32,&rbuff,0);
	md5CleanFile(filePath,buff);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

DWORD CALLBACK ThreadProc(LPVOID lp)
{
	//���շ���˷�������Ϣ
	while (1)
	{
		SENDSTC ss{};
		recv(SOCKET(lp), (char*)&ss, sizeof(ss), 0);
		if (ss.type == CLOUDEKILL)
		{
			CStringA str;
			str.Format("�������Ʋ����ļ�:%s!�Ƿ�ɾ��?", ss.filePath);
			if (MessageBoxA(0, str, "����!", MB_YESNO) == IDYES)
				DeleteFileA(ss.filePath);
		}
	}
	return 0;
}
BOOL Tab_ShaDu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HINSTANCE hDLL = NULL;
	if ((hDLL = LoadLibrary(L"advapi32.dll")) > 0)
	{
		MD5Init = (PMD5Init)GetProcAddress(hDLL, "MD5Init");
		MD5Update = (PMD5Update)GetProcAddress(hDLL, "MD5Update");
		MD5Final = (PMD5Final)GetProcAddress(hDLL, "MD5Final");
	}
	//----------------------------------------------------------
	if (InitWinSock() == SOCKET_ERROR)
	{
		MessageBox(L"�׽��ֳ�ʼ��ʧ��!");
		return FALSE;
	}
	//connectSvr();
	if (conn("127.0.0.1", 9999) == SOCKET_ERROR)
	{
		MessageBox(L"������δ����");
		closesocket(m_sock);
		m_sock = NULL;
		WSACleanup();
		return FALSE;
	}
	CreateThread(NULL, 0, ThreadProc, (void*)m_sock, 0, NULL);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//------------------------------------------------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

bool Tab_ShaDu::isInWhiteList(char* szName){
	FILE* fp = NULL;
	if (fopen_s(&fp, "������.txt", "rb"))return true;
	char buf[128]{};
	while (!feof(fp))
	{
		fread(buf, 1, 128, fp);
		if (strcmp(szName, buf) == 0)
		{
			return true;
		}
	}
	fclose(fp);
	fp = NULL;
	return false;

}

void Tab_ShaDu::OnBnClickedBmd()
{




	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hSnap)
	{
		MessageBox(L"��������ʧ��!");
		return;
	}
	PROCESSENTRY32 pe{ sizeof(PROCESSENTRY32) };

	BOOL bSuccess = Process32First(hSnap, &pe);
	if (!bSuccess)
	{
		MessageBox(L"�Ҳ�����һ������!");
		return;
	}
	do {
		CStringA temp(pe.szExeFile);
		char buff[128]{};
		memcpy(buff, temp.GetBuffer(), 128);
		if (!isInWhiteList(buff))
		{
			HANDLE hPro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
			if (!hPro)return;
			CString str;
			str.Format(L"������������(%s)?", pe.szExeFile);
			if (MessageBox(str, L"����", MB_YESNO) == IDYES)
				TerminateProcess(hPro, 0);
		}
	} while (Process32Next(hSnap, &pe));
	CloseHandle(hSnap);





	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Tab_ShaDu::OnBnClickedQlj()
{
	
	//����D�̣�ɾ����׺��Ϊ.txt�������ļ�
	CFolderPickerDialog fDlg;
	fDlg.DoModal();
	CString path = fDlg.GetPathName();
	if (path.IsEmpty())return;
	AllPathKill(path);



	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
void Tab_ShaDu::AllPathKill(CString szPath)
{
	WIN32_FIND_DATA wd;
	HANDLE hFile = FindFirstFile(szPath + "\\*", &wd);
	if (!hFile)return;
	do{
		if (wcscmp(wd.cFileName, L".") == 0 || wcscmp(wd.cFileName, L"..") == 0)
			continue;
		else if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			AllPathKill(szPath + wd.cFileName);
		else
		{
			CString extension = PathFindExtension(wd.cFileName);
			if (wcscmp(extension, L".txt") == 0)
			{
				DeleteFile(szPath + L"\\" + wd.cFileName);
			}
		}
	} while (FindNextFile(hFile, &wd));
}
//-----------------------------
BOOL Tab_ShaDu::InitWinSock()
{
	WSADATA stcData;
	int nResult = 0;
	nResult = WSAStartup(MAKEWORD(2, 2), &stcData);
	if (nResult == SOCKET_ERROR) {
		return FALSE;
	}
	return TRUE;
}
int Tab_ShaDu::conn(char* ipAddr, int port)
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	//in_addr s = { 0 };
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
	return connect(m_sock, (sockaddr*)&addr, sizeof(sockaddr_in));
}


void Tab_ShaDu::OnBnClickedDemo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!m_sock)
	{
		MessageBox(L"δ���ӷ�����!");
		return;
	}
	CFileDialog fileDlg(TRUE);
	fileDlg.DoModal();
	CString path;
	path = fileDlg.GetPathName();
	if (!path.GetLength())return;
	mySendInfo(path, MD5INFO);
	MessageBox(L"�ύ�������!", L"��ʾ:", 0);
}
void Tab_ShaDu::mySendInfo(CString& path, int nType)
{
	MD5_CTX ctx{};
	SENDSTC ss{};
	ss.type = nType;
	CStringA str(path);
	memcpy(ss.filePath, str, str.GetLength());
	int nLen = str.GetLength();
	unsigned char* pPath = new unsigned char[nLen + 1]{};
	for (int i = 0; i < nLen; i++)
	{
		pPath[i] = str[i];
	}
	MD5Init(&ctx);
	MD5Update(&ctx, pPath, nLen);
	MD5Final(&ctx);
	char* resStr = (char*)Hex2ASC(ctx.digest, 16);
	memcpy(ss.md5, resStr, 32);
	send(m_sock, (char*)&ss, sizeof(ss), 0);
}


void Tab_ShaDu::OnBnClickedCloude()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!m_sock)
	{
		MessageBox(L"δ���ӷ�����!");
		return;
	}
	CFolderPickerDialog fileDlg;
	fileDlg.DoModal();
	//��ȡ�ļ���·��
	CString path;
	path = fileDlg.GetPathName();
	if (!path.GetLength())return;
	mySend(path, CLOUDEKILL);
}
void Tab_ShaDu::mySend(const CString& path, int nType)
{
	MD5_CTX ctx{};
	SENDSTC ss{};
	ss.type = nType;
	WIN32_FIND_DATA wd{};
	HANDLE hFile = FindFirstFile(path + "\\*", &wd);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	do {
		if (wcscmp(wd.cFileName, L".") == 0 || wcscmp(wd.cFileName, L"..") == 0)
			continue;
		if (!(wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			CString szPath = path + "\\" + wd.cFileName;
			CStringA str(szPath);
			memcpy(ss.filePath, str, str.GetLength());
			int nLen = str.GetLength();
			unsigned char* pPath = new unsigned char[nLen + 1]{};
			for (int i = 0; i < nLen; i++)
			{
				pPath[i] = str[i];
			}
			MD5Init(&ctx);
			MD5Update(&ctx, pPath, nLen);
			MD5Final(&ctx);
			char* resStr = (char*)Hex2ASC(ctx.digest, 16);
			memcpy(ss.md5, resStr, 33);
			//����
			send(m_sock, (char*)&ss, sizeof(ss), 0);
			//printf(Hex2ASC(ctx.digest, 16));
		}
		if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			mySend(path + L"\\" + wd.cFileName, nType);
	} while (FindNextFile(hFile, &wd));
}
