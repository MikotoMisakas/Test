#pragma once


// Tab_YunSha �Ի���

class Tab_YunSha : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_YunSha)

public:
	Tab_YunSha(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_YunSha();

// �Ի�������
	enum { IDD = IDD_YunSha };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDemo();
	afx_msg void OnBnClickedTs();
	afx_msg void OnBnClickedTsexe();
};
