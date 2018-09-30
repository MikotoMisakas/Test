#pragma once


// Tab_LaJi 对话框

class Tab_LaJi : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_LaJi)

public:
	Tab_LaJi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Tab_LaJi();

// 对话框数据
	enum { IDD = IDD_LaJi };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLaji();
	WCHAR szFullPath[MAX_PATH];
	ULARGE_INTEGER  EnumFoldAndDeleteFile(CString lpFoldPath, WCHAR *lpFileType);
	WIN32_FIND_DATA  w32FindData;
	ULARGE_INTEGER qwFileTotalSize ;  //文件总大小

	afx_msg void OnBnClickedZdljlj();
};
