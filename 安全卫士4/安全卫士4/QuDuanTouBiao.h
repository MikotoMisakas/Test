#pragma once
#include"resource.h"
#include"Tab_Pe.h"
#include "afxcmn.h"


// QuDuanTouBiao �Ի���

class QuDuanTouBiao : public CDialogEx
{
	DECLARE_DYNAMIC(QuDuanTouBiao)

public:
	QuDuanTouBiao(PIMAGE_NT_HEADERS pP, CWnd* pParent = NULL);   // ��׼���캯��
	
	//QuDuanTouBiao(IMAGE_NT_HEADERS* pParent /*=NULL*/);
	//QuDuanTouBiao(IMAGE_NT_HEADERS* nnn, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~QuDuanTouBiao();

// �Ի�������
	enum { IDD = IDD_QuDuanTouBiao };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int QuDuanTouBiaoBianLiang;
	CString Pe_Section_quduan1;
	CString M_PATH;
	HANDLE M_Path;
	LPBYTE ppBuff;
	PIMAGE_NT_HEADERS PNT;
	CListCtrl m_List_QuDuan;
	virtual BOOL OnInitDialog();
};
