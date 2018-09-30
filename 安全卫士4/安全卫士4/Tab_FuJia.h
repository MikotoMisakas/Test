#pragma once


// Tab_FuJia 对话框

class Tab_FuJia : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_FuJia)

public:
	Tab_FuJia(CWnd* pParent = NULL);   // 标准构造函数

	void adjustPrivilege();
	//老板键
	BOOL m_isShow = TRUE;


	virtual ~Tab_FuJia();

// 对话框数据
	enum { IDD = IDD_FuJia };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLb();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBmd();
};
