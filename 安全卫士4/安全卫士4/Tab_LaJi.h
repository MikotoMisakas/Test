#pragma once


// Tab_LaJi �Ի���

class Tab_LaJi : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_LaJi)

public:
	Tab_LaJi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_LaJi();

// �Ի�������
	enum { IDD = IDD_LaJi };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLaji();
	WCHAR szFullPath[MAX_PATH];
	ULARGE_INTEGER  EnumFoldAndDeleteFile(CString lpFoldPath, WCHAR *lpFileType);
	WIN32_FIND_DATA  w32FindData;
	ULARGE_INTEGER qwFileTotalSize ;  //�ļ��ܴ�С

	afx_msg void OnBnClickedZdljlj();
};
