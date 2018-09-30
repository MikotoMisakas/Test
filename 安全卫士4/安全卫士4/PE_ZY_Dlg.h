#pragma once

#include"resource.h"
#include "afxcmn.h"
// PE_ZY_Dlg �Ի���

class PE_ZY_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(PE_ZY_Dlg)

public:
	PE_ZY_Dlg(IMAGE_NT_HEADERS* PNT, LPBYTE qBuff, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PE_ZY_Dlg();
	IMAGE_NT_HEADERS* PNt;
	void parseResources(LPBYTE pResDirRoot, IMAGE_RESOURCE_DIRECTORY* pDir, int nLevel = 1);
	DWORD rva2foa(IMAGE_NT_HEADERS* pNt, DWORD dwRva);
	LPBYTE PBuff;
// �Ի�������
	enum { IDD = IDD_ZiYuanBiao };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl PE_ZY_LIST;
	CListCtrl Pe_Zy_List;
	virtual BOOL OnInitDialog();
};
