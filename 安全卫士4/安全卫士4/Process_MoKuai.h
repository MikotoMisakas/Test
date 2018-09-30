#pragma once
#include "afxcmn.h"


// Process_MoKuai 对话框

class Process_MoKuai : public CDialogEx
{
	DECLARE_DYNAMIC(Process_MoKuai)

public:
	Process_MoKuai(DWORD pppid,CWnd* pParent = NULL);   // 标准构造函数
	DWORD Thread_ID;
	virtual ~Process_MoKuai();

// 对话框数据
	enum { IDD = IDD_Process_MoKuai };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Process_MoKuai_List;
	virtual BOOL OnInitDialog();
};
