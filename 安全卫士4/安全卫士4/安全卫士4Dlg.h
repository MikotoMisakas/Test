
// ��ȫ��ʿ4Dlg.h : ͷ�ļ�
//

#pragma once
#include "MyTableCtrl.h"


// C��ȫ��ʿ4Dlg �Ի���
class C��ȫ��ʿ4Dlg : public CDialogEx
{
// ����
public:
	C��ȫ��ʿ4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	double FILETIME2Double(const _FILETIME& fileTime);
// �Ի�������
	enum { IDD = IDD_MY4_DIALOG };
	BOOL m_isShow = TRUE;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CStatusBar *m_bar;
public:
	CMyTableCtrl m_MyTable;
	afx_msg void   OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnCpumessage(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
