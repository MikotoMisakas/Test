#pragma once
#include"resource.h"


// PE_ZY_LIST

class PE_ZY_LIST : public CListCtrl
{
	DECLARE_DYNAMIC(PE_ZY_LIST)

public:
	PE_ZY_LIST();
	virtual ~PE_ZY_LIST();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
public :
	CListCtrl Pe_Zy_List;
};


