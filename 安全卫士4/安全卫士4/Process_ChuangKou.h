#pragma once
#include "afxcmn.h"


// Process_ChuangKou �Ի���

class Process_ChuangKou : public CDialogEx
{
	DECLARE_DYNAMIC(Process_ChuangKou)

public:
	Process_ChuangKou(DWORD ppppid ,CWnd* pParent = NULL);   // ��׼���캯��
	DWORD PID;
	LPTSTR szWindowName;

	virtual ~Process_ChuangKou();

// �Ի�������
	enum { IDD = IDD_ChuangKou };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��������list
	CListCtrl Process_Ck_List;
	virtual BOOL OnInitDialog();
};
