#pragma once


// Tab_NeiCun2 对话框

class Tab_NeiCun2 : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_NeiCun2)

public:
	Tab_NeiCun2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Tab_NeiCun2();

// 对话框数据
	enum { IDD = IDD_JinShiDun };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedQinglineicun();
};
