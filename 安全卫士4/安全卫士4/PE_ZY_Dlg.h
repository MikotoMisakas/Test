#pragma once

#include"resource.h"
#include "afxcmn.h"
// PE_ZY_Dlg 对话框

class PE_ZY_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(PE_ZY_Dlg)

public:
	PE_ZY_Dlg(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PE_ZY_Dlg();
	IMAGE_NT_HEADERS* PNt;
	void parseResources(LPBYTE pResDirRoot, IMAGE_RESOURCE_DIRECTORY* pDir, int nLevel = 1);
	DWORD rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva);
	LPBYTE PBuff;
// 对话框数据
	enum { IDD = IDD_ZiYuanBiao };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl PE_ZY_LIST;
	CListCtrl Pe_Zy_List;
	virtual BOOL OnInitDialog();
};
