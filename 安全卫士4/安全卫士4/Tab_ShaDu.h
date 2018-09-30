#pragma once


// Tab_ShaDu �Ի���

class Tab_ShaDu : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_ShaDu)

public:
	Tab_ShaDu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_ShaDu();
	//ɱ������
	BOOL cmpMd5(const CString& path);

	//������
	bool isInWhiteList(char* szName);
	void md5CleanFile(const CString& path, char* md5Str);
	//ȫ·��
	void AllPathKill(CString szPath);
	//--------------------------------
	//�Ʋ�ɱ
	BOOL InitWinSock();
	int conn(char* ipAddr, int port);
	void mySendInfo(CString& path, int nType);
	void mySend(const CString& path, int nType);
	//--------------------------------
public:
	SOCKET m_sock;

// �Ի�������
	enum { IDD = IDD_ShaDu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMd5();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBmd();
	afx_msg void OnBnClickedQlj();
	afx_msg void OnBnClickedDemo();
	afx_msg void OnBnClickedCloude();
};
