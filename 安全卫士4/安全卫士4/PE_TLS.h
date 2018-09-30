#pragma once
#include "afxcmn.h"


// PE_TLS 对话框

class PE_TLS : public CDialogEx
{
	DECLARE_DYNAMIC(PE_TLS)

public:
	PE_TLS(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // 标准构造函数
	IMAGE_NT_HEADERS* PNt;
	LPBYTE PBuff;
	virtual ~PE_TLS();
	//添加的tls函数
	DWORD rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva);

// 对话框数据
	enum { IDD = IDD_TTLS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Pe_Tls_List;
	virtual BOOL OnInitDialog();
};
