#pragma once
#include "afxcmn.h"


// Pe_DaoRu 对话框

class Pe_DaoRu : public CDialogEx
{
	DECLARE_DYNAMIC(Pe_DaoRu)

public:
	DWORD Pe_DaoRu::CalcOffsev1(DWORD Rva);
	Pe_DaoRu(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Pe_DaoRu();

// 对话框数据
	enum { IDD = IDD_DaoRu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int PE_NT_DR;
	IMAGE_NT_HEADERS* PNt;
	LPBYTE QBuff;
	virtual BOOL OnInitDialog();
	CListCtrl PE_DR_LIST;
	afx_msg void OnLvnItemchangedDaoruList(NMHDR *pNMHDR, LRESULT *pResult);
};
