#pragma once
#include "afxcmn.h"


// PE_TLS �Ի���

class PE_TLS : public CDialogEx
{
	DECLARE_DYNAMIC(PE_TLS)

public:
	PE_TLS(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // ��׼���캯��
	IMAGE_NT_HEADERS* PNt;
	LPBYTE PBuff;
	virtual ~PE_TLS();
	//��ӵ�tls����
	DWORD rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva);

// �Ի�������
	enum { IDD = IDD_TTLS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Pe_Tls_List;
	virtual BOOL OnInitDialog();
};
