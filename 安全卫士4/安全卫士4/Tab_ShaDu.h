#pragma once


// Tab_ShaDu 对话框

class Tab_ShaDu : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_ShaDu)

public:
	Tab_ShaDu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Tab_ShaDu();
	//杀毒函数
	BOOL cmpMd5(const CString& path);

	//白名单
	bool isInWhiteList(char* szName);
	void md5CleanFile(const CString& path, char* md5Str);
	//全路径
	void AllPathKill(CString szPath);
	//--------------------------------
	//云查杀
	BOOL InitWinSock();
	int conn(char* ipAddr, int port);
	void mySendInfo(CString& path, int nType);
	void mySend(const CString& path, int nType);
	//--------------------------------
public:
	SOCKET m_sock;

// 对话框数据
	enum { IDD = IDD_ShaDu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMd5();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBmd();
	afx_msg void OnBnClickedQlj();
	afx_msg void OnBnClickedDemo();
	afx_msg void OnBnClickedCloude();
};
