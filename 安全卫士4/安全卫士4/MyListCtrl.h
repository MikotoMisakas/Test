#pragma once


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

protected:
	virtual void DoDataExchange(CDataExchange* pDx);
	DECLARE_MESSAGE_MAP()
	CListCtrl m_ListCtrl;//�����ϵ�List����
};


