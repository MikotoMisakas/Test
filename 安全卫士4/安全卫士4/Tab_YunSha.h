#pragma once


// Tab_YunSha 对话框

class Tab_YunSha : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_YunSha)

public:
	Tab_YunSha(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Tab_YunSha();

// 对话框数据
	enum { IDD = IDD_YunSha };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDemo();
	afx_msg void OnBnClickedTs();
	afx_msg void OnBnClickedTsexe();
};
