#pragma once
#include "afxcmn.h"


// Process_MoKuai �Ի���

class Process_MoKuai : public CDialogEx
{
	DECLARE_DYNAMIC(Process_MoKuai)

public:
	Process_MoKuai(DWORD pppid,CWnd* pParent = NULL);   // ��׼���캯��
	DWORD Thread_ID;
	virtual ~Process_MoKuai();

// �Ի�������
	enum { IDD = IDD_Process_MoKuai };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Process_MoKuai_List;
	virtual BOOL OnInitDialog();
};
