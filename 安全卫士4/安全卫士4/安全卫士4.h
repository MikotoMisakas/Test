
// ��ȫ��ʿ4.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��ȫ��ʿ4App: 
// �йش����ʵ�֣������ ��ȫ��ʿ4.cpp
//

class C��ȫ��ʿ4App : public CWinApp
{
public:
	C��ȫ��ʿ4App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��ȫ��ʿ4App theApp;