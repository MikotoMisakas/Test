#pragma once
#include "afxcmn.h"


// PE_ChongDingWei �Ի���

class PE_ChongDingWei : public CDialogEx
{
	DECLARE_DYNAMIC(PE_ChongDingWei)

public:

	DWORD rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva);
	PE_ChongDingWei(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PE_ChongDingWei();
	IMAGE_NT_HEADERS* PNt;
	LPBYTE PBuff;

// �Ի�������
	enum { IDD = IDD_CDW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Pe_ChongDingWei_Up;
	virtual BOOL OnInitDialog();
	CListCtrl Pe_ChongDingWei_List_Down;
	afx_msg void OnClickChongdingweiUp(NMHDR *pNMHDR, LRESULT *pResult);
};
