#pragma once
#include "afxcmn.h"


// Procces_Thread �Ի���

class Procces_Thread : public CDialogEx
{
	DECLARE_DYNAMIC(Procces_Thread)

public:
	Procces_Thread(DWORD ppppid, CWnd* pParent = NULL);   // ��׼���캯��
	DWORD Thread_ID;
	virtual ~Procces_Thread();

// �Ի�������
	enum { IDD = IDD_Thread };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Process_Thread_List_BL;
	virtual BOOL OnInitDialog();
};
