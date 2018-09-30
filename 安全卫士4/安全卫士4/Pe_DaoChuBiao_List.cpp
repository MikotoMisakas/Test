// Pe_DaoChuBiao_List.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
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



// Pe_DaoChuBiao_List 消息处理程序




void Pe_DaoChuBiao_List::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{



	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;



}
