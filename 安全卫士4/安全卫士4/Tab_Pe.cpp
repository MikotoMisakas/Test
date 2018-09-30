// Tab_Pe.cpp : 实现文件
//

#include "stdafx.h"
#include "安全卫士4.h"
#include "Tab_Pe.h"
#include"Pe_DaoRu.h"
#include"Pe_DaoChu.h"
#include"PE_ChongDingWei.h"
#include"QuDuanTouBiao.h"
#include"PE_ZY_Dlg.h"
#include"PE_YanChi.h"
#include"PE_TLS.h"
#include "afxdialogex.h"


// Tab_Pe 对话框

IMPLEMENT_DYNAMIC(Tab_Pe, CDialogEx)

Tab_Pe::Tab_Pe(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_Pe::IDD, pParent)
	, AddFile(_T(""))
	, Pe_Nt_File_QuDuan(_T(""))
	, Pe_Nt_File_KZTDIGSHOR(_T(""))
	, Pe_Nt_File_PingTai(_T(""))
	, Pe_Nt_Option_RuKou(_T(""))
	, Pe_Nt_Option_MoRenJiZhi(_T(""))
	, Pe_Nt_Option_Code(_T(""))
	, Pe_Nt_Option_DaTa(_T(""))
	, Pe_Nt_Option_NeiCun(_T(""))
	, Pe_Nt_Option_File(_T(""))
	, Pe_Nt_Option_XuYaoNeiCun(_T(""))
	, Pe_Nt_Option_JiaoYan(_T(""))
	, Pe_Nt_Option_ZiXiTong(_T(""))
	, Pe_Nt_Option_Dll(_T(""))
	, Pe_Nt_Option_MuLu(_T(""))
{

}

Tab_Pe::~Tab_Pe()
{
}

void Tab_Pe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AddFile, AddFile);
	DDX_Text(pDX, IDC_EDIT2, Pe_Nt_File_QuDuan);
	DDX_Text(pDX, IDC_EDIT3, Pe_Nt_File_KZTDIGSHOR);
	DDX_Text(pDX, IDC_EDIT4, Pe_Nt_File_PingTai);
	DDX_Text(pDX, IDC_EDIT5, Pe_Nt_Option_RuKou);
	DDX_Text(pDX, IDC_EDIT6, Pe_Nt_Option_MoRenJiZhi);
	DDX_Text(pDX, IDC_EDIT7, Pe_Nt_Option_Code);
	DDX_Text(pDX, IDC_EDIT8, Pe_Nt_Option_DaTa);
	DDX_Text(pDX, IDC_EDIT9, Pe_Nt_Option_NeiCun);
	DDX_Text(pDX, IDC_EDIT10, Pe_Nt_Option_File);
	DDX_Text(pDX, IDC_EDIT11, Pe_Nt_Option_XuYaoNeiCun);
	DDX_Text(pDX, IDC_EDIT12, Pe_Nt_Option_JiaoYan);
	DDX_Text(pDX, IDC_EDIT13, Pe_Nt_Option_ZiXiTong);
	DDX_Text(pDX, IDC_EDIT14, Pe_Nt_Option_Dll);
	DDX_Text(pDX, IDC_EDIT15, Pe_Nt_Option_MuLu);
}


BEGIN_MESSAGE_MAP(Tab_Pe, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_QuDuanTouBiao, &Tab_Pe::OnBnClickedQuduantoubiao)
	ON_BN_CLICKED(IDC_DaoChu, &Tab_Pe::OnBnClickedDaochu)
	ON_BN_CLICKED(IDC_DaoRu, &Tab_Pe::OnBnClickedDaoru)
	ON_BN_CLICKED(IDC_ZhiYuan, &Tab_Pe::OnBnClickedZhiyuan)
	ON_BN_CLICKED(IDC_ChongDingWei, &Tab_Pe::OnBnClickedChongdingwei)
	ON_BN_CLICKED(IDC_TLS, &Tab_Pe::OnBnClickedTls)
	ON_BN_CLICKED(IDC_YanChi, &Tab_Pe::OnBnClickedYanchi)
END_MESSAGE_MAP()


// Tab_Pe 消息处理程序


void Tab_Pe::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	wchar_t aa[50] = { 0 };
	DragQueryFile(hDropInfo, 0, aa, 50);
	AddFile = aa;

	
	LPCTSTR peZhuan = aa;
	UpdateData(FALSE);

	
         G_File = CreateFile(peZhuan, GENERIC_WRITE |
		GENERIC_READ,//文件的读写属性
		FILE_SHARE_READ,//和其他程序共享内存
		NULL,
		OPEN_EXISTING,//文件存在才打开
		FILE_ATTRIBUTE_NORMAL,//一个普通文件
		NULL
		);

	if (G_File==(HANDLE)-1)
	{

		MessageBox(L"123",L"456",0);

	}

	//使用对应结构体解析内存中的数
	DWORD size = GetFileSize(G_File, NULL);
	LPBYTE pBuff = new BYTE[size];
	DWORD dwRead = 0;
	ReadFile(G_File, pBuff, size, &dwRead, 0);
	PBUFF = pBuff;//给Pbuff赋值


	IMAGE_DOS_HEADER* pDos = NULL;
	pDos = (IMAGE_DOS_HEADER*)pBuff;

	if (pDos->e_magic!=IMAGE_DOS_SIGNATURE)
	{
		return;//不是pe文件格式

	}

	//找到nt
	IMAGE_NT_HEADERS* pNt = NULL;
	
	pNt = (IMAGE_NT_HEADERS*)(pDos->e_lfanew + pBuff);
	G_pNt = pNt;
	if (pNt->Signature!=IMAGE_NT_SIGNATURE)
	{
		return;//不是有效的pe格式

	}
	//nt文件头  区段头表数量
	CString Pt;
	Pt.Format(L"%x", pNt->FileHeader.NumberOfSections);
	Pe_Nt_File_QuDuan = Pt;


	//nt头扩展头大小
	CString Kzt;
	Kzt.Format(L"%x", pNt->FileHeader.SizeOfOptionalHeader);
	Pe_Nt_File_KZTDIGSHOR = Kzt;





	//nt   文件头运行平台

	CString PingTai;
	//= (pNt->FileHeader.Machine);
	PingTai.Format(L"%x", pNt->FileHeader.Machine);
	Pe_Nt_File_PingTai= PingTai;



	//////////////////////
	//扩展头
	CString OpenKou;
	OpenKou.Format(L"%x", pNt->OptionalHeader.AddressOfEntryPoint);
	Pe_Nt_Option_RuKou = OpenKou;




	//默认加载基址
	CString JXJZ;
	JXJZ.Format(L"%x", pNt->OptionalHeader.ImageBase);
	Pe_Nt_Option_MoRenJiZhi = JXJZ;



	//起始代码
	//代码基址
	CString Code;
	Code.Format(L"%x", pNt->OptionalHeader.BaseOfCode);
	Pe_Nt_Option_Code = Code;


	//数据基址
	CString DATA;
	DATA.Format(L"%x", pNt->OptionalHeader.ImageBase);
	Pe_Nt_Option_DaTa= DATA;


	//内存对齐
	CString KDQ;
	KDQ.Format(L"%x", pNt->OptionalHeader.SectionAlignment);
	Pe_Nt_Option_NeiCun= KDQ;


	//文件对齐
	CString FileDQ;
	FileDQ.Format(L"%x", pNt->OptionalHeader.FileAlignment);
	Pe_Nt_Option_File= FileDQ;


	//内存大小
	CString FileNeiCun;
	FileNeiCun.Format(L"%x", pNt->OptionalHeader.SizeOfImage);
	Pe_Nt_Option_XuYaoNeiCun = FileNeiCun;



	//校验和
	CString XY;
	XY.Format(L"%x", pNt->OptionalHeader.CheckSum);
	Pe_Nt_Option_JiaoYan= XY;


	//子系统
	CString ZXT;
	ZXT.Format(L"%x", pNt->OptionalHeader.Subsystem);
	Pe_Nt_Option_ZiXiTong = ZXT;


	//DLL标志
	CString TZ;
	TZ.Format(L"%x", pNt->OptionalHeader.DllCharacteristics);
	Pe_Nt_Option_Dll= TZ;

//目录个数

	CString MuLu;
	MuLu.Format(L"%x", pNt->OptionalHeader.NumberOfRvaAndSizes);
	Pe_Nt_Option_MuLu = MuLu;









	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}


void Tab_Pe::OnBnClickedQuduantoubiao()
{
	
	
	QuDuanTouBiao Obj(G_pNt,NULL);
	Obj.DoModal();




	// TODO:  在此添加控件通知处理程序代码
}


void Tab_Pe::OnBnClickedDaochu()
{
	Pe_DaoChu Obj(G_pNt, PBUFF, NULL);
	Obj.DoModal();



	// TODO:  在此添加控件通知处理程序代码
}


void Tab_Pe::OnBnClickedDaoru()
{
	Pe_DaoRu Obj(G_pNt, PBUFF,NULL);
	Obj.DoModal();

	// TODO:  在此添加控件通知处理程序代码
}


void Tab_Pe::OnBnClickedZhiyuan()
{
	PE_ZY_Dlg Obj(G_pNt, PBUFF, NULL);
	Obj.DoModal();


	// TODO:  在此添加控件通知处理程序代码
}


void Tab_Pe::OnBnClickedChongdingwei()
{
	PE_ChongDingWei Obj(G_pNt, PBUFF, NULL);
	Obj.DoModal();

	// TODO:  在此添加控件通知处理程序代码
}


void Tab_Pe::OnBnClickedTls()
{

	PE_TLS Obj(G_pNt, PBUFF, NULL);
	Obj.DoModal();

	// TODO:  在此添加控件通知处理程序代码
}


void Tab_Pe::OnBnClickedYanchi()
{
	PE_YanChi Obj(G_pNt, PBUFF, NULL);
	Obj.DoModal();

	// TODO:  在此添加控件通知处理程序代码
}
