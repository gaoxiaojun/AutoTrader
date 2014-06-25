
// ProtectProgressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProtectProgress.h"
#include "ProtectProgressDlg.h"
#include "afxdialogex.h"
//#include "tinyxml.h"
//#include "tinystr.h"
#include "tinyxml.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProtectProgressDlg 对话框
#define AbortWinName _T("Microsoft Visual C++ Debug Library")
#define AutoTraderWinName _T("AutoTrader")
#define AutoTrader _T("Auto Trader")


CProtectProgressDlg::CProtectProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProtectProgressDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProtectProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProtectProgressDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CProtectProgressDlg::OnBnClickedOk)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_BN_CLICKED(IDC_StartCap, &CProtectProgressDlg::OnBnClickedStartcap)
END_MESSAGE_MAP()


// CProtectProgressDlg 消息处理程序

BOOL CProtectProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	restartSwitch = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProtectProgressDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProtectProgressDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProtectProgressDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// start main progress while
	BeginProgress();
	//ReStartTradeMaster();
	//StartCaptureData();

	//CDialogEx::OnOK();
}

BOOL CALLBACK EnumChild_1L(HWND hwnd,LPARAM lParam)
{
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	WINTUPLE tempTuple;
	CString titleName(szTitle);
	CString className(szClassName);
	if (className == _T("Button") && titleName == _T("中止(&A)") )
	{
		this2->m_Abort_hwnd = hwnd;
		SendMessage(hwnd,WM_LBUTTONDOWN,0,0);
		SendMessage(hwnd,WM_LBUTTONUP,0,0);
		this2->restartSwitch = true;
		Sleep(1000*5);
	}

	return TRUE;
}

//*************************************
// 函数名:  	
// 目的:	查找程序主进程句柄
// 时间：   2014/03/25
//*************************************
BOOL CALLBACK EnumMainWinTrade(HWND hwnd,LPARAM lParam)
{
	if (hwnd == NULL)
	{
		return FALSE;
	}

	TCHAR szTitle[MAX_PATH] = {0};
	LPWSTR* ss = new LPWSTR();
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	GetClassName(hwnd,*ss,10);
	//
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;
	if (_tcsicmp(szTitle, AbortWinName) == 0)
	{
		// 枚举所有子窗口
		EnumChildWindows(hwnd, EnumChild_1L, (LPARAM)this2);
	}
	return TRUE;
}

void CProtectProgressDlg::GetTheAbortWin()
{
	m_TupleVec.clear();
	EnumWindows(EnumMainWinTrade, (LPARAM)this);

	//m_OK_Tuple = m_TupleVec.at(0);// 终止按钮 14
}

UINT CProtectProgressDlg::RuntimeThread( LPVOID lpParameter )
{
	CProtectProgressDlg *this2;
	this2 = (CProtectProgressDlg *)lpParameter;

	while(1)
	{
		this2->GetAutoTraderWin();
		if (this2->m_TupleAutoTraderVec.size() == 0)
		{
			this2->restartSwitch = false;
			//this2->m_OK_Tuple = this2->m_TupleVec.at(0);// stop buttom
			this2->ReStartTradeMaster();
			this2->StartCaptureData();
		}

		this2->GetTheAbortWin();
		Sleep(1000*3);
		if (this2->restartSwitch == true )
		{
			this2->restartSwitch = false;
			//this2->m_OK_Tuple = this2->m_TupleVec.at(0);// stop buttom
			this2->ReStartTradeMaster();
			this2->StartCaptureData();
		}
		
	}
	return 0;
}


void CProtectProgressDlg::BeginProgress()
{
	hCapThread=AfxBeginThread(RuntimeThread,(LPVOID)this);
}

void CProtectProgressDlg::ReStartTradeMaster()
{
	CString TradeMasterPath = _T("C:\\Users\\Lio\\Documents\\Visual Studio 2012\\Projects\\AutoTrader\\test\\Win32\\AutoTrader.exe");
	char * Trademaster = CString2CharPt(TradeMasterPath);
	STARTUPINFO StartInfo;
	PROCESS_INFORMATION pinfo;
	//对程序的启动信息不作任何设定，全部清0
	memset(&StartInfo,0,sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);//设定结构的大小

	//CreateProcess(TradeMasterPath,NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&StartInfo,&pinfo);
	//ShellExecute(this->m_hWnd,"open","calc.exe","","",       SW_SHOW       );   
	//ShellExecute(NULL,"open","C:\\Test.txt",NULL,NULL,SW_SHOWNORMAL);
	int ss = WinExec(Trademaster,SW_SHOW);
}

char* CProtectProgressDlg::CString2CharPt( CString InputString )
{
	CString str = InputString;
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = str.GetLength();     // n = 14, len = 18
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len+1];   //以字节为单位
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP,0,str,str.GetLength() + 1 ,pFileName,len + 1 ,NULL,NULL);
	return pFileName;
}

BOOL CALLBACK EnumCapButtom(HWND hwnd,LPARAM lParam)
{
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;

	if (hwnd == NULL)
	{
		return FALSE;
	}
	TCHAR szTitle[MAX_PATH] = {0};
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	WINTUPLE tempTuple;
	CString titleName(szTitle);
	CString className(szClassName);
	if (className == _T("Button") && titleName == _T("开始抓包") )
	{
		this2->m_Abort_hwnd = hwnd;
		SendMessage(hwnd,WM_LBUTTONDOWN,0,0);
		SendMessage(hwnd,WM_LBUTTONUP,0,0);
	}

	return TRUE;
}

//*************************************
// 函数名:  	
// 目的:	查找程序主进程句柄
// 时间：   2014/03/25
//*************************************
BOOL CALLBACK EnumAutoTraderWinTrade(HWND hwnd,LPARAM lParam)
{
	if (hwnd == NULL)
	{
		return FALSE;
	}

	TCHAR szTitle[MAX_PATH] = {0};
	LPWSTR* ss = new LPWSTR();
	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	GetClassName(hwnd,*ss,10);
	//
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;
	if (_tcsicmp(szTitle, AutoTraderWinName) == 0)
	{
		// 枚举所有子窗口
		EnumChildWindows(hwnd, EnumCapButtom, (LPARAM)this2);
	}
	return TRUE;
}

void CProtectProgressDlg::StartCaptureData()
{
	m_AutoTrader_Vec.clear();
	EnumWindows(EnumAutoTraderWinTrade, (LPARAM)this);
}


void CProtectProgressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//////////////////////////////////////////////////////////////////////////
// 	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
// 	{
// 		CAboutDlg dlgAbout;
// 		dlgAbout.DoModal();
// 	}
	if(nID == SC_MAXIMIZE) //最大化
	{
		this->ShowWindow(SW_SHOW);
	}
	else if(nID == SC_MINIMIZE) //最小化，把他隐藏起来
	{
		LetItSmall();
		//this->ShowWindow(SW_HIDE);
		
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
	//CDialogEx::OnSysCommand(nID, lParam);
}

void CProtectProgressDlg::LetItSmall()
{
	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	char * ch=new char[50];
	WCHAR *p=new WCHAR[25];
	p=_T("made by crazy!");
	//strcpy(m_nid.szTip, p);                // 信息提示条为"服务器程序"，VS2008 UNICODE编码用wcscpy_s()函数
	lstrcpyW(m_nid.szTip, L"ProtectPrgess");
	::Shell_NotifyIcon(NIM_ADD,&m_nid );
	this->ShowWindow(SW_HIDE);
}

LRESULT CProtectProgressDlg::OnShowTask( WPARAM wParam, LPARAM lParam )
{
	if(wParam != IDR_MAINFRAME)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();                    // 声明一个弹出式菜单
			//menu.AppendMenu(MF_STRING, WM_DESTROY, "关闭");
			//menu.AppendMenuW(MF_STRING,WM_DESTROY,"退出");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
		{
			if (this->IsWindowVisible() == FALSE)
			{
				this->ShowWindow(SW_SHOWNORMAL);
			}
			else
			{
				LetItSmall();
			}
		}
		break;
	}
	return 0;
}


void CProtectProgressDlg::OnBnClickedStartcap()
{
	// TODO: 在此添加控件通知处理程序代码
	ReStartTradeMaster();
	StartCaptureData();
}



BOOL CALLBACK EnumAutoTrade(HWND hwnd,LPARAM lParam)
{
	if (hwnd == NULL)
	{
		return FALSE;
	}

	TCHAR szTitle[MAX_PATH] = {0};
	LPWSTR* ss = new LPWSTR();

	GetWindowText(hwnd, szTitle, ARRAYSIZE(szTitle));
	CHAR szClassName[MAX_PATH];
	GetClassNameA(hwnd, szClassName, MAX_PATH);
	CString comm(szTitle);
	CString className(szClassName);
	//
	CProtectProgressDlg *this2 = (CProtectProgressDlg*)lParam;
	if (comm == _T("AutoTrader") || comm == _T("Auto Trader"))
	{
		// 枚举所有子窗口
		tuple<HWND, CString, CString> tempTup;
		get<0>(tempTup) = hwnd;get<1>(tempTup) = comm;
		get<2>(tempTup) = className;
		this2->m_TupleAutoTraderVec.push_back(tempTup);
		//EnumChildWindows(hwnd, EnumChild_1L, (LPARAM)this2);
	}
	return TRUE;
}

void CProtectProgressDlg::GetAutoTraderWin()
{
	m_TupleAutoTraderVec.clear();
	EnumWindows(EnumAutoTrade, (LPARAM)this);
}
