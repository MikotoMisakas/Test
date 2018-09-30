// MY_List_QuDuan.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "MY_List_QuDuan.h"


// CMY_List_QuDuan

IMPLEMENT_DYNAMIC(CMY_List_QuDuan, CListCtrl)

CMY_List_QuDuan::CMY_List_QuDuan()
{

}

CMY_List_QuDuan::~CMY_List_QuDuan()
{
}

void  CMY_List_QuDuan::DoDataExchange(CDataExchange* pDx){

	DDX_Control(pDx, IDC_LIST1, m_List_QuDuan);

}

BEGIN_MESSAGE_MAP(CMY_List_QuDuan, CListCtrl)
END_MESSAGE_MAP()



// CMY_List_QuDuan 消息处理程序


