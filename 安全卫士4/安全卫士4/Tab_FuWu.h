#pragma once
#include "afxcmn.h"


// Tab_FuWu �Ի���

class Tab_FuWu : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_FuWu)

public:
	Tab_FuWu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_FuWu();

// �Ի�������
	enum { IDD = IDD_FuWu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
