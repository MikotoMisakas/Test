#pragma once


// Pe_DaoChuBiao_List

class Pe_DaoChuBiao_List : public CLinkCtrl
{
	DECLARE_DYNAMIC(Pe_DaoChuBiao_List)

public:
	Pe_DaoChuBiao_List();
	virtual ~Pe_DaoChuBiao_List();

protected:
	virtual void DoDataExchange(CDataExchange* pDx);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Pe_DaoChu1;//list¿Ø¼þ±äÁ¿
	
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


