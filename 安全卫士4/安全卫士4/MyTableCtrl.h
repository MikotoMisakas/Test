#pragma once


// CMyTableCtrl

class CMyTableCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTableCtrl)

public:
	CDialogEx *m_Dia[8];//tab�а˸���
	CMyTableCtrl();
	virtual ~CMyTableCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


