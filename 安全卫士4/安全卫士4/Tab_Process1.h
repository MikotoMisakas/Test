#pragma once
#include "afxcmn.h"


// Tab_Process1 �Ի���

class Tab_Process1 : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_Process1)

public:
	DWORD ppppid = 0;
	Tab_Process1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_Process1();

// �Ի�������
	enum { IDD = IDD_Process };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DWORD Menu_ID;
	CListCtrl m_ListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void Menu_Command();
	afx_msg void Menu_MoKuai();
	afx_msg void OnMenu();
	afx_msg void On32775();
	afx_msg void OnBnClickedSxprocess();
};
