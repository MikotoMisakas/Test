#pragma once
#include "afxcmn.h"


// Tab_FuWu 对话框

class Tab_FuWu : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_FuWu)

public:
	Tab_FuWu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Tab_FuWu();

// 对话框数据
	enum { IDD = IDD_FuWu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Win_FuWu_List;
	int BeChosed;
	virtual BOOL OnInitDialog();
	afx_msg void On11111111();
	afx_msg void Onopenservice();
	afx_msg void OnRclickFuwuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void FuWu999();
};
