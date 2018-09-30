#pragma once
#include "afxcmn.h"


// PE_YanChi 对话框

class PE_YanChi : public CDialogEx
{
	DECLARE_DYNAMIC(PE_YanChi)

public:
	PE_YanChi(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // 标准构造函数
	IMAGE_NT_HEADERS* PNt;
	LPBYTE PBuff;
	virtual ~PE_YanChi();

	DWORD PE_YanChi::rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva);

// 对话框数据
	enum { IDD = IDD_YanChi };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Pe_yanChi_List;
	virtual BOOL OnInitDialog();
};
