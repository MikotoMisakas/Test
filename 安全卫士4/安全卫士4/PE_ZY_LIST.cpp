// PE_ZY_LIST.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "PE_ZY_LIST.h"


// PE_ZY_LIST

IMPLEMENT_DYNAMIC(PE_ZY_LIST, CListCtrl)

PE_ZY_LIST::PE_ZY_LIST()
{

}

PE_ZY_LIST::~PE_ZY_LIST()
{
}
void  PE_ZY_LIST::DoDataExchange(CDataExchange* pDX){
	DDX_Control(pDX, IDC_PE_ZY_LIST, Pe_Zy_List);

}


BEGIN_MESSAGE_MAP(PE_ZY_LIST, CListCtrl)
END_MESSAGE_MAP()



// PE_ZY_LIST ��Ϣ�������


