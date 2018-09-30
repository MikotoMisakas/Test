// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}
void CMyListCtrl::DoDataExchange(CDataExchange* pDx){

	DDX_Control(pDx, IDC_LIST1, m_ListCtrl);//控件list 与变量绑定函数


}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CMyListCtrl 消息处理程序


