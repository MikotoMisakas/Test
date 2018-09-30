// MyTableCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include"resource.h"
#include "MyTableCtrl.h"


// CMyTableCtrl

IMPLEMENT_DYNAMIC(CMyTableCtrl, CTabCtrl)

CMyTableCtrl::CMyTableCtrl()
{

}

CMyTableCtrl::~CMyTableCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTableCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTableCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTableCtrl 消息处理程序




void CMyTableCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{



	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	int nNum = GetCurSel();

	switch (nNum)
	{

	case 0:{
		m_Dia[0]->ShowWindow(SW_SHOW);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_HIDE);
	

	}
		break;

	case 1:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_SHOW);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_HIDE);
		
	}
		break;
	case 2:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_SHOW);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_HIDE);
	

	}
		break;
	case 3:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_SHOW);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_HIDE);
	

	}
		break;
	case 4:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_SHOW);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_HIDE);
	

	}
		break;
	case 5:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_SHOW);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_HIDE);


	}
		break;
	case 6:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_SHOW);
		m_Dia[7]->ShowWindow(SW_HIDE);
	

	}
		break;
	case 7:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_SHOW);


	}
		break;
	case 8:{
		m_Dia[0]->ShowWindow(SW_HIDE);
		m_Dia[1]->ShowWindow(SW_HIDE);
		m_Dia[2]->ShowWindow(SW_HIDE);
		m_Dia[3]->ShowWindow(SW_HIDE);
		m_Dia[4]->ShowWindow(SW_HIDE);
		m_Dia[5]->ShowWindow(SW_HIDE);
		m_Dia[6]->ShowWindow(SW_HIDE);
		m_Dia[7]->ShowWindow(SW_HIDE);
	

	}
		break;




	default:
		break;
	}




}
