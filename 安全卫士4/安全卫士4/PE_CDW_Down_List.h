#pragma once


// PE_CDW_Down_List

class PE_CDW_Down_List : public CLinkCtrl
{
	DECLARE_DYNAMIC(PE_CDW_Down_List)

public:
	PE_CDW_Down_List();
	virtual ~PE_CDW_Down_List();

protected:
	//virtual void DoDataExchange(CDataExchange* pDx);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Pe_ChongDingWei_List_Down;
};


