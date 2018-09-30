
// 安全卫士4Dlg.h : 头文件
//

#pragma once
#include "MyTableCtrl.h"


// C安全卫士4Dlg 对话框
class C安全卫士4Dlg : public CDialogEx
{
// 构造
public:
	C安全卫士4Dlg(CWnd* pParent = NULL);	// 标准构造函数

	double FILETIME2Double(const _FILETIME& fileTime);
// 对话框数据
	enum { IDD = IDD_MY4_DIALOG };
	BOOL m_isShow = TRUE;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
