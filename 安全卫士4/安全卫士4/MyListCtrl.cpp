// MyListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}
void CMyListCtrl::DoDataExchange(CDataExchange* pDx){

	DDX_Control(pDx, IDC_LIST1, m_ListCtrl);//�ؼ�list ������󶨺���


}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CMyListCtrl ��Ϣ�������


