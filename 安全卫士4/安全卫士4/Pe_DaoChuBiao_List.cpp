// Pe_DaoChuBiao_List.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ȫ��ʿ4.h"
#include "Pe_DaoChuBiao_List.h"


// Pe_DaoChuBiao_List

IMPLEMENT_DYNAMIC(Pe_DaoChuBiao_List, CLinkCtrl)


Pe_DaoChuBiao_List::Pe_DaoChuBiao_List()
{

}

Pe_DaoChuBiao_List::~Pe_DaoChuBiao_List()
{
}
void  Pe_DaoChuBiao_List::DoDataExchange(CDataExchange* pDx)
{
	DDX_Control(pDx, IDC_DaoChuBiao_List, Pe_DaoChu1);

}

BEGIN_MESSAGE_MAP(Pe_DaoChuBiao_List, CLinkCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &Pe_DaoChuBiao_List::OnNMClick)
END_MESSAGE_MAP()



// Pe_DaoChuBiao_List ��Ϣ�������




void Pe_DaoChuBiao_List::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{



	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;



}
