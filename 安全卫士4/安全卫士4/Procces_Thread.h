#pragma once
#include "afxcmn.h"


// Procces_Thread 对话框

class Procces_Thread : public CDialogEx
{
	DECLARE_DYNAMIC(Procces_Thread)

public:
	Procces_Thread(DWORD ppppid, CWnd* pParent = NULL);   // 标准构造函数
	DWORD Thread_ID;
	virtual ~Procces_Thread();

// 对话框数据
	enum { IDD = IDD_Thread };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Process_Thread_List_BL;
	virtual BOOL OnInitDialog();
};
