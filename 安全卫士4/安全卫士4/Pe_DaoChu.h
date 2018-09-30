#pragma once
#include "afxcmn.h"


// Pe_DaoChu 对话框

class Pe_DaoChu : public CDialogEx
{
	DECLARE_DYNAMIC(Pe_DaoChu)

public:
	DWORD CalcOffsev1(DWORD Rva);






	
	Pe_DaoChu(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Pe_DaoChu();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int Pe_DaoChuBianLiang;
	PIMAGE_NT_HEADERS PNt;
	LPBYTE PBuff;
	virtual BOOL OnInitDialog();
	CListCtrl Pe_DaoChu1;
	CString PE_NT_DC_RVA;
	CString PE_NT_DC_FOA;
	CString PE_NT_DC_JS;
	CString PE_NT_DC_HS？;
	CString PE_NT_DC_HSMS;
	CString PE_NT_DaoChuDiZhi;
	CString PE_NT_DC_MC;
	CString PE_NT_DC_XH;
};
