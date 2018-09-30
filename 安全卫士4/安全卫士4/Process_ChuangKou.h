#pragma once
#include "afxcmn.h"


// Process_ChuangKou 对话框

class Process_ChuangKou : public CDialogEx
{
	DECLARE_DYNAMIC(Process_ChuangKou)

public:
	Process_ChuangKou(DWORD ppppid ,CWnd* pParent = NULL);   // 标准构造函数
	DWORD PID;
	LPTSTR szWindowName;

	virtual ~Process_ChuangKou();

// 对话框数据
	enum { IDD = IDD_ChuangKou };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 遍历窗口list
	CListCtrl Process_Ck_List;
	virtual BOOL OnInitDialog();
};
