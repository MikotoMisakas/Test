#pragma once


// Process_Thread_List

class Process_Thread_List : public CListCtrl
{
	DECLARE_DYNAMIC(Process_Thread_List)

public:
	Process_Thread_List();
	virtual ~Process_Thread_List();

protected:
	DECLARE_MESSAGE_MAP()
};


