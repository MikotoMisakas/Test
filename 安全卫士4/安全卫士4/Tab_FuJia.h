#pragma once


// Tab_FuJia �Ի���

class Tab_FuJia : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_FuJia)

public:
	Tab_FuJia(CWnd* pParent = NULL);   // ��׼���캯��

	void adjustPrivilege();
	//�ϰ��
	BOOL m_isShow = TRUE;


	virtual ~Tab_FuJia();

// �Ի�������
	enum { IDD = IDD_FuJia };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLb();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBmd();
};
