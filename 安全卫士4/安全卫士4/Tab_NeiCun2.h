#pragma once


// Tab_NeiCun2 �Ի���

class Tab_NeiCun2 : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_NeiCun2)

public:
	Tab_NeiCun2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_NeiCun2();

// �Ի�������
	enum { IDD = IDD_JinShiDun };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedQinglineicun();
};
