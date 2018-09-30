#pragma once


// CMY_List_QuDuan

class CMY_List_QuDuan : public CListCtrl
{
	DECLARE_DYNAMIC(CMY_List_QuDuan)

public:
	CMY_List_QuDuan();
	virtual ~CMY_List_QuDuan();

protected:
	virtual void DoDataExchange(CDataExchange* pDx);
	DECLARE_MESSAGE_MAP()
public:
	CLinkCtrl m_List_QuDuan;
};


