#pragma once


// Tab_Pe �Ի���

class Tab_Pe : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_Pe)

public:
	Tab_Pe(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_Pe();

// �Ի�������
	enum { IDD = IDD_Pe };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString AddFile;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString Pe_Nt_File_QuDuan;
	CString Pe_Nt_File_KZTDIGSHOR;
	CString Pe_Nt_File_PingTai;
	CString Pe_Nt_Option_RuKou;
	CString Pe_Nt_Option_MoRenJiZhi;
	CString Pe_Nt_Option_Code;
	CString Pe_Nt_Option_DaTa;
	HANDLE G_File;//�򿪵��ļ����
	LPBYTE PBUFF;//�ļ��Ļ�ַ
	IMAGE_NT_HEADERS* G_pNt;
	CString Pe_Nt_Option_NeiCun;
	CString Pe_Nt_Option_File;
	CString Pe_Nt_Option_XuYaoNeiCun;
	CString Pe_Nt_Option_JiaoYan;
	CString Pe_Nt_Option_ZiXiTong;
	CString Pe_Nt_Option_Dll;
	CString Pe_Nt_Option_MuLu;
	afx_msg void OnBnClickedQuduantoubiao();
	afx_msg void OnBnClickedDaochu();
	afx_msg void OnBnClickedDaoru();
	afx_msg void OnBnClickedZhiyuan();
	afx_msg void OnBnClickedChongdingwei();
	afx_msg void OnBnClickedTls();
	afx_msg void OnBnClickedYanchi();
};
