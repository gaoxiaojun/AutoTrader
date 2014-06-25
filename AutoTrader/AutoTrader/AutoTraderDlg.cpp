
// AutoTraderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoTrader.h"
#include "AutoTraderDlg.h"
#include "afxdialogex.h"

#include "pcap.h"
#include <pcap\usb.h>
#include <inc.h>
#include "ShowInfo.h"

#include <cstring>
#include "RegeditIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoTraderDlg 对话框



CAutoTraderDlg::CAutoTraderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoTraderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ShowDlg = NULL;
	// 设置策略主合约
	
	m_trader = new CTrader;
	m_Strategy.SetTrader(m_trader);
	m_Strategy.SetTradeCode(_T("i1409"));
	// 设置抓取合约
	AutoList.push_back(_T("ag1412"));
	AutoList.push_back(_T("i1409"));
	AutoList.push_back(_T("i1411"));
	AutoList.push_back(_T("i1501"));
	AutoList.push_back(_T("i1503"));
	AutoList.push_back(_T("i1505"));
	//AutoList.push_back(_T("rb1410"));
	//AutoList.push_back(_T("a1405"));
	vspdctomysql_AutoTrader = new VspdcToMySQL;
	for (int i=0; i<AutoList.size();i++)
	{
		AutoListTime.push_back(_T(""));
	}
	

	//fp = fopen("C:\\1.txt", "wt");
	for (int i=0;i<AutoList.size();i++)
	{
		FirstRun.push_back(TRUE);
	}
	//////////////////////////////////////////////////////////////////////////
	// 连接数据库测试
	char* Msg = "";//消息变量
	vspdctomysql_AutoTrader = new VspdcToMySQL;
	if(vspdctomysql_AutoTrader->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
	{
		//if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
		//MessageBox(_T("连接成功！"),_T("OK"),0);
		printf("连接成功/r/n");
		printf(Msg);
		m_Strategy.SetMySQLpt(vspdctomysql_AutoTrader);
	}
	else
	{
		MessageBox(_T("数据库连接失败"), _T("错误"),0);
		//CAutoTraderDlg::OnDestroy();
	}
	


}

void CAutoTraderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RES_STR, m_res_char);
	DDX_Control(pDX, IDC_COMBO_Net, m_Net_ComboBox);
	DDX_Control(pDX, IDC_ID, m_ID_Test);
}

BEGIN_MESSAGE_MAP(CAutoTraderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_CAPTURE, &CAutoTraderDlg::OnBnClickedStartCapture)
	ON_BN_CLICKED(IDC_STOP_CAPTURE, &CAutoTraderDlg::OnBnClickedStopCapture)
	ON_WM_CLOSE()
	//ON_COMMAND(ID_Exit, OnExit);
	//ON_COMMAND(ID_APP_EXIT, &CAutoTraderDlg::OnAppExit)
	ON_BN_CLICKED(IDC_SHOWDLG_SWITCH, &CAutoTraderDlg::OnBnClickedShowdlgSwitch)
	ON_BN_CLICKED(IDC_CONN_SQL, &CAutoTraderDlg::OnBnClickedConnSql)
	ON_BN_CLICKED(IDCANCEL, &CAutoTraderDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SMALL, &CAutoTraderDlg::OnBnClickedSmall)
	ON_WM_DESTROY()
	//ON_MESSAGE(WM_NC,OnNotifyIcon)
	//ON_MESSAGE(WM_SHOWTASK,OnShowTask);
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_Net, &CAutoTraderDlg::OnCbnSelchangeComboNet)
	ON_BN_CLICKED(IDC_STOP_STRATEGY, &CAutoTraderDlg::OnBnClickedStopStrategy)
	ON_BN_CLICKED(IDC_SIM_BUTTOM, &CAutoTraderDlg::OnBnClickedSimButtom)
END_MESSAGE_MAP()


// CAutoTraderDlg 消息处理程序

BOOL CAutoTraderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// TODO: 在此添加额外的初始化代码
	InitializeCriticalSection(&csThreadStop);
	eThreadStart=CreateEvent(0,
		false,//自动Reset
		false,//初始阻塞
		_T("ThreadCapture"));
	
	//////////////////////////////////////////////////////////////////////////
	//	预读网卡信息
	pcap_if_t *AllDevs;

	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE];
	// 获取设备列表
	if (pcap_findalldevs(&AllDevs, errbuf) == -1)
	{
		MessageBox(_T("不能得到网络适配器列表"));

	}
	// 数据列表 
	for(d= AllDevs; d; d=d->next)
	{
		CString temp1(d->name);
		//CString temp2 = d->addresses;
		m_Net_ComboBox.AddString(temp1);

		m_AllDevs_Vec.push_back(*d);
	}
	m_AllDevs = *AllDevs;

	//
	CRegeditIO reg;
	CString NetworkCardName = reg.ReadNetworkCardName();
	m_Net_ComboBox.SetWindowTextW(NetworkCardName);
	m_adpter_char = CString2CharPt(NetworkCardName);

// 	m_adpter_char = (LPTSTR)(LPCTSTR)NetworkCardName;
// 
// 	LPTSTR m_adpter_char = new TCHAR[NetworkCardName.GetLength()+1];
// 	_tcscpy(m_adpter_char, NetworkCardName);

	//m_adpter_char = NetworkCardName.GetBuffer();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutoTraderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//////////////////////////////////////////////////////////////////////////
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if(nID == SC_MAXIMIZE) //最大化
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
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoTraderDlg::OnPaint()
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
HCURSOR CAutoTraderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT CAutoTraderDlg::CapErrorThread( LPVOID lpParameter )
{
	CAutoTraderDlg* this3=(CAutoTraderDlg *)lpParameter;
	CString tempStatusStr = _T("");
	while(1)
	{
		if (this3->m_trader->GetStatusText() != tempStatusStr)
		{
			// 记录
			// 写文件
			tempStatusStr = this3->m_trader->GetStatusText();
			FILE* fp = fopen("C:\\status.txt", "at+");
			if(fp != NULL)
			{
				fseek(fp, 0, SEEK_END);
				fputs(this3->CString2CharPt(tempStatusStr), fp);//
				fputs("\r\n",fp);//或fputs("\r\n");
				fclose(fp);
			}

		}
		
		this3->m_trader->CloseError();
		if (this3->bThreadStop == true)
		{
			return 0;
		}
	}
	return 0;
}

//*************************************
// 函数名:  	
// 目的:	开始抓包
// 时间：   2014/03/20
//*************************************
void CAutoTraderDlg::OnBnClickedStartCapture()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL temp;
	hCapThread=AfxBeginThread(CapThread,(LPVOID)this);
	hCapErrorThread=AfxBeginThread(CapErrorThread,(LPVOID)this);

	WaitForSingleObject(eThreadStart, INFINITE);
	EnterCriticalSection(&csThreadStop);
	temp=bThreadStop;
	LeaveCriticalSection(&csThreadStop);
	if(temp)//线程自动退出
	{
		return;
	}
	else
	{
		//Status=1;
		printf("开始抓包");
	}
}

//*************************************
// 函数名:  	
// 目的:	结束抓包
// 时间：   2014/03/20
//*************************************
void CAutoTraderDlg::OnBnClickedStopCapture()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD result;

	EnterCriticalSection(&csThreadStop);
	bThreadStop=true;
	LeaveCriticalSection(&csThreadStop);

	result=WaitForSingleObject(hCapThread->m_hThread,1000);//可能在这行执行前线程就已退出
	result=WaitForSingleObject(hCapErrorThread->m_hThread,3000);//可能在这行执行前线程就已退出

	if(result==WAIT_TIMEOUT )
	{
		//MessageBox("工作线程超时不响应，强制结束！");
		TerminateThread(hCapThread->m_hThread,0);
		TerminateThread(hCapErrorThread->m_hThread,0);
	}
	//Status=0;
	//this->SetMenuStatus();
	printf("停止抓包");
	//MessageBox("停止抓包");
}

UINT CAutoTraderDlg::CapThread( LPVOID lpParameter )
{
	CAutoTraderDlg *this2;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_dumper_t *dumpfile;
	struct pcap_pkthdr *header;
	const u_char *data;
	DWORD res;
	bool bExit;
	static long i=0,j=0;
	bool bFilter=false;//true表示过滤掉

	ListData List;

	struct ether_header *eth;
	u_char* mac_string;
	struct iphead *IPHead;
	struct arphead *ARPHead;
	in_addr ipaddr;
	// 这里有个参数
	this2=(CAutoTraderDlg *)lpParameter;
	i=0;
	j=0;
	//const char * adpter_char = "\\Device\\NPF_{3788FA43-59ED-4C95-83F5-061E42A46329}";

	const char * adpter_char = this2->m_adpter_char;
	if((adhandle= pcap_open_live(adpter_char,65536,1 ,10,errbuf)) == NULL)
	{
		::MessageBox(0,_T("不能打开网络适配器,请在网卡设置中经行设置"),_T("错误"),0);
		EnterCriticalSection(&(this2->csThreadStop));
		this2->bThreadStop=true;
		LeaveCriticalSection(&(this2->csThreadStop));
		SetEvent(this2->eThreadStart);
		return 0; 
	}
	
// 	const char * CapFiePath = (char *)this2->CapFilePath.GetBuffer();
// 	dumpfile=pcap_dump_open(adhandle,CapFiePath);
// 	if(dumpfile==NULL)
// 	{
// 		::MessageBox(0,_T("不能打开记录文件"),_T("错误"),0);
// 		EnterCriticalSection(&(this2->csThreadStop));
// 		this2->bThreadStop=true;
// 		LeaveCriticalSection(&(this2->csThreadStop));
// 		SetEvent(this2->eThreadStart);
// 		return 0;
// 	}

	EnterCriticalSection(&(this2->csThreadStop));
	this2->bThreadStop=false;
	LeaveCriticalSection(&(this2->csThreadStop));
	SetEvent(this2->eThreadStart);

	//::MessageBox(0,_T("开始抓包"),_T("ok"),0);
	CString standard1 = _T("116"),standard2 = _T("236"),standard3 = _T("239"),standard4 = _T("129");
	CString tempIPs,xxx1,xxx2,xxx3,xxx4;
	//DWORD standardIP = inet_addr("116.236.239.129");
	DWORD standardIP = inet_addr(STANDARDIP);
	unsigned char *standIP = (unsigned char*)&standardIP;

	DWORD tempIP;
	wchar_t *WStrD;

	pcap_t *fp;
	while(1)
	{
		//////////////////////////////////////////////////////////////////////////
		// 判断 是否是 期货的ip地址 上海电信，这里还需要添加
		// 目标ip
		char *CStr = List.dIP;
		size_t len = strlen(CStr) + 1;
		size_t converted = 0;
		wchar_t *WStr;
		WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
		mbstowcs_s(&converted, WStr, len, CStr, _TRUNCATE);
		CString Str2 = _T("D:")+ *WStr;
		WStrD = WStr;
		// 源ip
		CStr = List.sIP;
		tempIPs = CStr;
		tempIP = inet_addr(CStr);

		len = strlen(CStr) + 1;
		converted = 0;
		WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
		mbstowcs_s(&converted, WStr, len, CStr, _TRUNCATE);
		//CString Str3 = _T("S:")+ *WStr;

		if (tempIP == standardIP)
		{
			//this2->m_Show_Res.SetWindowTextW(WStrD);
			//this2->m_Show_Res2.SetWindowTextW(WStr);
			CStr = List.Text;
			this2->DecodeChar(List.Text,45);
			len = strlen(CStr) + 1;
			converted = 0;
			WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
			mbstowcs_s(&converted, WStr, len, CStr, _TRUNCATE);
			CString Str3 = _T("S:")+ *WStr;
			//////////////////////////////////////////////////////////////////////////
			// 解析数据包
			struct pcap_pkthdr *header2;
			const u_char *data2;
			char *p;

			//AnalysePacket(header,data);
// 			if ((fp = pcap_open_offline(CapFiePath,errbuf)) == NULL)
// 			{
// 				::MessageBox(0,_T("不能找到记录文件"),_T("Error"),0);
// 				return 0;
// 			}


// 			for(j=0;j<i;j++)//找到选中项
// 				pcap_next_ex(fp, &header2, &data2);

// 			if(pcap_next_ex(fp, &header2, &data2)>0)
// 			{
				//this2->AnalysePacket(header2,data2);
			p=(char *)malloc((header->caplen+1)*sizeof(u_char));
			memcpy(p,data,header->caplen);
			p[header->caplen]='\0';
			this2->DecodeChar(p,header->caplen);
				//GetDlgItem(IDC_EDIT1)->SetWindowText(p);
			CString res(p);
			vector<CString> spList = this2->SplitString(res);
			// 如果解析后容器为50 则删掉第一个
			if (spList.size() == 50)
			{
				spList.erase(spList.begin());
			}
			//
			//CString tempCode = this2->GetTradeCode(spList.at(0));
			//this2->VectorIsHas(this2->AutoList,this2->GetTradeCode(spList.at(0)))

			// 如果容器为49个
			if (spList.size() == 49 && this2->VectorIsHas(this2->AutoList,this2->GetTradeCode(spList.at(0))) == true)
			{
				int codeIdx = this2->VectorPos(this2->AutoList,this2->GetTradeCode(spList.at(0)));// 交易码在 容器中位置
				// 分别对每种检测的品种进行第一次 过滤
				if( this2->AutoListTime.at(codeIdx) != spList.at(47) )
				{
					if (this2->m_ShowDlg->GetSafeHwnd() != NULL)
					{
						this2->updataShowDlg(spList);
					}

					if (this2->FirstRun.at(codeIdx) == true) // 检查是否第一次运行
					{
						char* Msg = "";//消息变量
						//VspdcToMySQL* tempSql = new VspdcToMySQL;
						//if(tempSql->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
						//if(this2->vspdctomysql->co)
						//{
							//if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
						
						//CString Code = this2->GetTradeCode(spList.at(0));
						//SELECT HSTimeStamp from c1409 ORDER BY ID desc LIMIT 0,1;
						CString SQL = _T("SELECT HSTimeStamp from ")+this2->GetTradeCode(spList.at(0))+_T(" ORDER BY ID desc LIMIT 0,1;");
						//string str = tempSql->SelectData(this2->CString2CharPt(SQL),1,1,Msg);
						if (this2->vspdctomysql_AutoTrader->mysql.net.buff == NULL)
						{
							this2->WriteError(_T("数据库重连....."));
							if(this2->vspdctomysql_AutoTrader->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
							{
								this2->WriteError(_T("数据库重连成功！"));
								printf("连接成功/r/n");
								printf(Msg);
							}
						}
						string str = this2->vspdctomysql_AutoTrader->SelectData(this2->CString2CharPt(SQL),1,1,Msg);
						CString getStr(str.c_str());
						vector<CString> tempVec = this2->SplitString(getStr);
						// 获取成交量
						SQL = _T("SELECT TradingVolume from ")+this2->GetTradeCode(spList.at(0))+_T(" ORDER BY ID desc LIMIT 0,1;");
						string str_vol = this2->vspdctomysql_AutoTrader->SelectData(this2->CString2CharPt(SQL),1,1,Msg);
						CString getStr_vol(str_vol.c_str());
						vector<CString> tempVec_vol = this2->SplitString(getStr_vol);
						//151425000
						HSTimer timeTester(spList.at(47));

// 						if (_ttoi(tempVec_vol.at(0)) == _ttoi(spList.at(14)))
// 						{
// 							// 相同的不写
// 							this2->WriteError(_T("相同成交量的不写"));
// 						}
						if (_ttoi(tempVec.at(0)) == _ttoi(spList.at(47)))
						{
							// 相同的不写
							this2->WriteError(_T("相同的不写"));
						}
						else if(timeTester.isInTradeTime() == false)
						{
							// 不在交易时间的不写
							this2->WriteError(_T("不在交易时间的不写"));
						}
						else
						{
							this2->FirstRun.at(codeIdx) = false;
							// 写入数据库
							this2->InsertSQL(spList,this2->GetTradeCode(spList.at(0)));
							this2->AutoListTime.at(codeIdx) = spList.at(47);//防止时间重写
						}
// 						}
// 						else
// 						{
// 							// 数据库连接不成功
// 							this2->WriteError(_T("数据库连接不成功"));
// 						}
					}
					else
					{
						// 写入数据库
						this2->InsertSQL(spList,this2->GetTradeCode(spList.at(0)));
						this2->AutoListTime.at(codeIdx) = spList.at(47);//防止时间重写
					}
					
				}
				
					
			}
			
			this2->m_res_char.SetWindowTextW(res);
			free(p);
			//}
			//this2->m_Get_Data.SetWindowTextW(WStr);
		}

		//////////////////////////////////////////////////////////////////////////
		EnterCriticalSection(&(this2->csThreadStop));
		bExit=this2->bThreadStop;
		LeaveCriticalSection(&(this2->csThreadStop));
		if(bExit)	return 0;

		res = pcap_next_ex(adhandle,&header,&data);
		if(res==0)
		{
			//Sleep(100);
			continue;
		}
		else if(res<0)
		{
			break;
		}

		//pcap_dump((u_char *)dumpfile, header, data);

		eth=(ether_header *)data;
		mac_string=eth->ether_shost;
		sprintf_s(List.sMac,"%02X:%02X:%02X:%02X:%02X:%02X",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
		mac_string=eth->ether_dhost;
		sprintf_s(List.dMac,"%02X:%02X:%02X:%02X:%02X:%02X",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
		ltoa(header->caplen,List.Len,10);
		memcpy(List.Text,data,45);//数据不含以太网头
		//memcpy(List.Text,data,90);//数据不含以太网头
		List.Text[45]='\0';
		this2->DecodeChar(List.Text,45);

		if (ntohs(eth->ether_type) == ETHERTYPE_IP)
		{
			IPHead=(iphead *)(data+14);
			ipaddr=IPHead->ip_souce_address;
			sprintf_s(List.sIP,"%d.%d.%d.%d",ipaddr.S_un.S_un_b.s_b1,ipaddr.S_un.S_un_b.s_b2,ipaddr.S_un.S_un_b.s_b3,ipaddr.S_un.S_un_b.s_b4);
			ipaddr=IPHead->ip_destination_address;
			sprintf_s(List.dIP,"%d.%d.%d.%d",ipaddr.S_un.S_un_b.s_b1,ipaddr.S_un.S_un_b.s_b2,ipaddr.S_un.S_un_b.s_b3,ipaddr.S_un.S_un_b.s_b4);


			switch(IPHead->ip_protocol)
			{
			case 6:
				//if(!this2->FilterSet.bAllProtocol && !this2->FilterSet.bTcp){bFilter=true;break;}
				strcpy(List.Protocol,"TCP");
				sprintf_s(List.sPort,"%d",ntohs( ((tcphead *)(data+16+20))->th_sport ));
				sprintf_s(List.dPort,"%d",ntohs( ((tcphead *)(data+16+20))->th_dport ));
				break;
			case 17:
				//if(!this2->FilterSet.bAllProtocol && !this2->FilterSet.bUdp){bFilter=true;break;}
				strcpy(List.Protocol,"UDP");
				sprintf_s(List.sPort,"%d",ntohs( ((udphead *)(data+16+20))->udp_source_port ));
				sprintf_s(List.dPort,"%d",ntohs( ((udphead *)(data+16+20))->udp_destinanion_port ));
				break;
			default:
				strcpy(List.Protocol,"未知IP包");
				strcpy(List.sIP,"----------");
				strcpy(List.dIP,"----------");
				strcpy(List.sPort,"--");
				strcpy(List.dPort,"--");
				break;
			}
			ltoa(i,List.ID,10);
			ltoa(j,List.TotalPacket,10);
		}
	}

	return 0;
}

void CAutoTraderDlg::DecodeChar( char *data,DWORD len )
{
	DWORD i;
	for(i=0;i<len;i++)
		if(data[i]=='\0')
			data[i]='.';
}


void CAutoTraderDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 	try
// 	{
// 		TerminateThread(hCapThread->m_hThread,0);
// 		TerminateThread(hCapErrorThread->m_hThread,0);
// 	}
// 	catch (CMemoryException* e)
// 	{
// 	}
// 	catch (CFileException* e)
// 	{
// 	}
// 	catch (CException* e)
// 	{
// 	}

	CDialogEx::OnClose();
}

vector<CString> CAutoTraderDlg::SplitString( CString input )
{
	// ·&Ouml;&cedil;&icirc;×&Ouml;·&ucirc;&acute;&reg;
// 	void Split(CString strArr , LPCTSTR strSplit , CStringArray& arr , BOOL bDeleteFirst)
// 	{
// 	if(bDeleteFirst)
// 		arr.RemoveAll();
	vector<CString> res;

	CString strArr = input;
	LPCTSTR strSplit = _T(",");
	CStringArray* arr = new CStringArray;

	int iStart = 0 , iFind = 0;
	do
	{
		iFind = strArr.Find(strSplit , iStart);
		if(iFind == -1)
			arr->Add(strArr.Mid(iStart));
		else
			arr->Add(strArr.Mid(iStart , iFind - iStart));
		iStart = iFind + 1;
	}while(iFind != -1);

	//arr->GetCount()
	for (int i=0; i<arr->GetCount();i++)
	{
		res.push_back(arr->GetAt(i));
	}
	return res;

}

void CAutoTraderDlg::updataShowDlg( vector<CString> input )
{
	m_ShowDlg->UpdateShowData(input);
}


void CAutoTraderDlg::OnBnClickedShowdlgSwitch()
{
	// TODO: 在此添加控件通知处理程序代码
	CShowInfo ss;
	m_ShowDlg = &ss;
	ss.DoModal();

}


void CAutoTraderDlg::OnBnClickedConnSql()
{
	// TODO: 在此添加控件通知处理程序代码
	char* Msg = "";//消息变量
	if (vspdctomysql_AutoTrader->mysql.net.buff == NULL)
	{
		vspdctomysql_AutoTrader  = new VspdcToMySQL;
		if(vspdctomysql_AutoTrader->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
		{
			//if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
			MessageBox(_T("连接成功！"),_T("OK"),0);
			printf("连接成功/r/n");
			printf(Msg);
		}
	}
	MessageBox(_T("连接已创建"));
// 	char* ag1412 = AG;
// 	char SQL = "insert into "+ *ag1412;
// 	if(vspdctomysql->InsertData(&SQL,Msg) == 0)
// 		printf("插入成功/r/n");
	//vspdctomysql->CloseMySQLConn();
}

void CAutoTraderDlg::InsertSQL( vector<CString> input)
{
	char* Msg = "";//消息变量
	if (vspdctomysql_AutoTrader->mysql.net.buff == NULL)
	{
		vspdctomysql_AutoTrader  = new VspdcToMySQL;
		if(vspdctomysql_AutoTrader->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
		{
			//if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
			MessageBox(_T("连接成功！"),_T("OK"),0);
			printf("连接成功/r/n");
			printf(Msg);
		}
	}
	//char SQL[500];
	char* ag1412 = AG;
	CString SQL_Head = _T("insert into Ag1412(CODE,YesterdaySettlementPrice,OpenPrice,SellPrice,BuyPrice,Unknow1,NewPrice,SellVolume,BuyVolume,Unknow2,HightPrice,LowPrice,AveragePrice,PriceChangePoint,TradingVolume,HoldPosition,TradeMoney,LimitUp,LimitDown,Unknow11,Unknow12,Unknow13,Unknow14,Unknow15,YesterdayClosePrice,AddPosition,UnknowNew,UnknowSettlement,HSTimeStamp,UnknowZero,UnknowGateway) values(");
	CString SQL_Value = _T("'")+GetTradeCode(input.at(0))+_T("',") + //代码
		input.at(1)+_T(",") +//昨日结算
		input.at(2)+_T(",") +//开盘
		input.at(7)+_T(",") +//卖价
		input.at(4)+_T(",") +//买价
		input.at(6)+_T(",") +//分割
		input.at(3)+_T(",") +//最新价
		input.at(8)+_T(",") +//卖量
		input.at(5)+_T(",") +//买量
 		input.at(9)+_T(",") +//分割2
 		input.at(10)+_T(",") +//最高价
 		input.at(11)+_T(",") +//最低价
 		input.at(12)+_T(",") +//均价
 		input.at(13)+_T(",") +//涨跌点数
 		input.at(14)+_T(",") +//成交量
		input.at(15)+_T(",") +//持仓量
		input.at(16)+_T(",") +//未知 交易量
		input.at(17)+_T(",") +//涨停
		input.at(18)+_T(",") +//跌停
		input.at(19)+_T(",") +//unknow1
		input.at(20)+_T(",") +//unknow2
		input.at(21)+_T(",") +//unknow3
		input.at(22)+_T(",") +//unknow4
		input.at(23)+_T(",") +//unknow5
		input.at(24)+_T(",") +//昨日收盘
		input.at(25)+_T(",") +//unknow 可能是昨日持仓
		input.at(26)+_T(",") +//可能是最新
		input.at(27)+_T(",") +//可能是结算
		_T("'")+input.at(47)+_T("',") +//恒生时间
		_T("'")+input.at(28)+_T(",")+input.at(29)+_T(",") +input.at(30)+_T(",")+//未知零
		input.at(31)+_T(",")+input.at(32)+_T(",") +input.at(33)+_T(",")+//未知零
		input.at(34)+_T(",")+input.at(35)+_T(",") +input.at(36)+_T(",")+//未知零
		input.at(37)+_T(",")+input.at(38)+_T(",") +input.at(39)+_T(",")+//未知零
		input.at(40)+_T(",")+input.at(41)+_T(",") +input.at(42)+_T(",")+//未知零
		input.at(43)+_T(",")+input.at(44)+_T(",") +input.at(45)+_T(",")+//未知零
		input.at(46)+_T("',")
		+_T("'")+input.at(48)+_T("'");//网关
	CString SQL_Tail = _T(")");
	CString SQL = SQL_Head + SQL_Value + SQL_Tail;

	char* SQL_char = this->CString2CharPt(SQL);
	if(vspdctomysql_AutoTrader->InsertData(SQL_char,Msg) == 0)
		printf("插入成功/r/n");

	//vspdctomysql->CloseMySQLConn();
}

void CAutoTraderDlg::InsertSQL( vector<CString> input, CString TableName )
{
	char* Msg = "";//消息变量
	//vspdctomysql = new VspdcToMySQL;
	if (vspdctomysql_AutoTrader->mysql.net.buff == NULL)
	{
		if(vspdctomysql_AutoTrader->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
		{
			this->WriteError(_T("写入数据是数据库重连成功！"));
		 	//if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
		 	printf("连接成功/r/n");
		 	printf(Msg);
		}
	}

// 	if(vspdctomysql->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
// 	{
// 		//if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
// 		printf("连接成功/r/n");
// 		printf(Msg);
// 	}
	CString SQL_Head = _T("insert into ")+TableName+_T("(CODE,YesterdaySettlementPrice,OpenPrice,SellPrice,BuyPrice,Unknow1,NewPrice,SellVolume,BuyVolume,Unknow2,HightPrice,LowPrice,AveragePrice,PriceChangePoint,TradingVolume,HoldPosition,TradeMoney,LimitUp,LimitDown,Unknow11,Unknow12,Unknow13,Unknow14,Unknow15,YesterdayClosePrice,AddPosition,UnknowNew,UnknowSettlement,HSTimeStamp,UnknowZero,HSDate,UnknowGateway) values(");//HSDate,
	HSTimer timeTester(input.at(47));
	SYSTEMTIME st;
	GetSystemTime(&st);
	CString u_Year,u_Month,u_Day,u_Res;
	u_Year.Format(_T("%d"),st.wYear);u_Month.Format(_T("%d"),st.wMonth);u_Day.Format(_T("%d"),st.wDay);
	u_Res = u_Year+_T("-")+u_Month+_T("-")+u_Day;

	CString SQL_Value = _T("'")+ 
		GetTradeCode(input.at(0)) +_T("',") + //代码
		input.at(1)+_T(",") +//昨日结算
		input.at(2)+_T(",") +//开盘
		input.at(7)+_T(",") +//卖价
		input.at(4)+_T(",") +//买价
		input.at(6)+_T(",") +//分割
		input.at(3)+_T(",") +//最新价
		input.at(8)+_T(",") +//卖量
		input.at(5)+_T(",") +//买量
		input.at(9)+_T(",") +//分割2
		input.at(10)+_T(",") +//最高价
		input.at(11)+_T(",") +//最低价
		input.at(12)+_T(",") +//均价
		input.at(13)+_T(",") +//涨跌点数
		input.at(14)+_T(",") +//成交量
		input.at(15)+_T(",") +//持仓量
		input.at(16)+_T(",") +//交易金额
		input.at(17)+_T(",") +//涨停
		input.at(18)+_T(",") +//跌停
		input.at(19)+_T(",") +//unknow1
		input.at(20)+_T(",") +//unknow2
		input.at(21)+_T(",") +//unknow3
		input.at(22)+_T(",") +//unknow4
		input.at(23)+_T(",") +//unknow5
		input.at(24)+_T(",") +//昨日收盘
		input.at(25)+_T(",") +//unknow 可能是昨日持仓
		input.at(26)+_T(",") +//可能是最新
		input.at(27)+_T(",") +//可能是结算
		_T("'")+ timeTester.m_StringTimer +_T("',") +//恒生时间
		_T("'")+input.at(28)+_T(",")+// 未知零
		input.at(29)+_T(",") +input.at(30)+_T(",")+//未知零
		input.at(31)+_T(",")+input.at(32)+_T(",") +input.at(33)+_T(",")+//未知零
		input.at(34)+_T(",")+input.at(35)+_T(",") +input.at(36)+_T(",")+//未知零
		input.at(37)+_T(",")+input.at(38)+_T(",") +input.at(39)+_T(",")+//未知零
		input.at(40)+_T(",")+input.at(41)+_T(",") +input.at(42)+_T(",")+//未知零
		input.at(43)+_T(",")+input.at(44)+_T(",") +input.at(45)+_T(",")+//未知零
		input.at(46)+_T("',") +
		_T("'")+ u_Res+_T("',") +// 日期
		+_T("'")+input.at(48)+_T("'");//网关
	CString SQL_Tail = _T(")");
	CString SQL = SQL_Head + SQL_Value + SQL_Tail;

	char* SQL_char = this->CString2CharPt(SQL);
	if(vspdctomysql_AutoTrader->InsertData(SQL_char,Msg) == 0)
		printf("插入成功/r/n");

	//vspdctomysql->CloseMySQLConn();
}

char* CAutoTraderDlg::Wstr2Astr( WCHAR *wstr )
{
	unsigned long i = lstrlen (wstr);
	char *astr;
	astr = (char*) malloc (i+1);
	if (astr == NULL)
		return NULL;
	else 
		memset (astr, '\0', i+1);

	wcstombs(astr, wstr, i+1);
	return astr;
}


//*************************************
// 函数名:  	CString2CharPt
// 目的:	CString转char指针
// 时间：   2014/02/28
//*************************************
char* CAutoTraderDlg::CString2CharPt( CString InputString )
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


void CAutoTraderDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	// TODO: 在此处添加消息处理程序代码
// 	try
// 	{
// 		TerminateThread(hCapThread->m_hThread,0);
// 		TerminateThread(hCapErrorThread->m_hThread,0);
// 	}
// 	catch (CMemoryException* e)
// 	{
// 	}
// 	catch (CFileException* e)
// 	{
// 	}
// 	catch (CException* e)
// 	{
// 	}
	vspdctomysql_AutoTrader->CloseMySQLConn();
	CDialogEx::DestroyWindow();
}


void CAutoTraderDlg::OnBnClickedSmall()
{
	//m_Strategy.GetTableNum(_T("OrderNow"));
	//vspdctomysql->GetTableNum(_T("OrderNow"));
// 	HSTimer tt(_T("152017000"));
// 	bool ssp = tt.isInTradeTime();
// 
// 	time_t t = time(0); 
// 	char tmp[64]; 
// 	strftime( tmp, sizeof(tmp), "%H:%M:%S",localtime(&t) ); 
// 	CString testTime(tmp);
// 	puts( tmp ); 
// 	
// 	m_Strategy.SetSentOrderStauts(_T("123"),_T("Open"),_T("Buy"),_T("1"));

	// TODO: 在此添加控件通知处理程序代码
// 	NotifyIcon.cbSize=sizeof(NOTIFYICONDATA);
// 	NotifyIcon.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
// 	NotifyIcon.hWnd=m_hWnd;
// 	lstrcpy(NotifyIcon.szTip,_T("NotifyIcon Test"));
// 	NotifyIcon.uCallbackMessage=WM_NC;
// 	NotifyIcon.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
// 	Shell_NotifyIcon(NIM_ADD,&NotifyIcon);
// 	ShowWindow(SW_HIDE);
// 	m_trader->SetCode(_T("i1410"));
// 	m_trader->SetBuy_Sell(0);
// 	m_trader->SetOpenClose(1);
// 	m_trader->SetValue(_T("100"));
// 	m_trader->SetVolume(_T("200"));
// 	m_trader->SendOrder();
	//CString test = m_trader->GetStatusText();
// 	// 写文件
// 	fp = fopen("C:\\1.txt", "at+");
// 	if(fp != NULL)
// 	{
// 		fseek(fp, 0, SEEK_CUR);
// 		CString ssd = _T("asdfasdf啊塑料袋放进了");
// 		fputs(CString2CharPt(ssd), fp);//
// 		fputs("\r\n",fp);//或fputs("\r\n");
// 		
// 		//你想写几行都可以啊，但是你的程序本来就只有写一行。
// // 		fputs(InputStr, fp);//
// // 		fputs("\r\n",fp);//或fputs("\r\n");
// 
// 		fclose(fp);
// 	}

	//m_trader->TestList();


	//VspdcToMySQL * sssff = new VspdcToMySQL;
// 	if (vspdctomysql->mysql.status == NULL)
// 	{
// 
// 	}


// 	char* Msg = "";//消息变量
// 	mysql_status ss = sssff->mysql.status;
// 	if(sssff->ConnMySQL(HOST,PORT,DBNAME,DatabaseUSER,PASSWD,CHARSET,Msg) == 0)
// 	{
// 		//if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
// 		printf("连接成功/r/n");
// 		printf(Msg);
// 		//sssff->mysql.net.buff
// 	}
// 	ss = sssff->mysql.status;
// 	sssff->CloseMySQLConn();
// 	ss=sssff->mysql.status;


	//151425000
	//HSTimer sss(_T("151425000"));
	//bool sst = sss.isInTradeTime();
	// 策略
	//m_Strategy.CheckOrderSuccessfull(_T("1121"));
	//m_Strategy.SentBuyOrd(_T("1234"));
	//m_Strategy.WriteLogDatabase(_T("1234"),_T("Open"),_T("Buy"),m_Strategy.Int2CString(1));
	//m_Strategy.ChangeOrderToHold();
	//m_Strategy.HolderType();
	m_Strategy.Start();
}


void CAutoTraderDlg::OnDestroy()
{
	// TODO: 在此处添加消息处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &m_nid);             
	//return CDialogEx::DestroyWindow();

	vspdctomysql_AutoTrader->CloseMySQLConn();

// 	DWORD ExitCode=0;
// 	GetExitCodeThread( hCapThread->m_hThread,&ExitCode);
// 	//p为需要销毁的CWindThreadZ指针,其在创建线程时可以拿到.
// 	if(ExitCode>0 )
// 		AfxEndThread(ExitCode,true);

// 	// 结束线程
// 	HANDLE hp=hCapThread->m_hThread;
// 	if (hp) 
// 	{
// 		if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
// 		{
// 			TerminateThread(hp,0);
// 		}
// 		CloseHandle(hp);
// 	}


	//hCapThread->Delete();
// 	if ( hCapThread!= NULL && hCapThread->m_hThread != NULL)
// 	{
// 		TerminateThread(hCapThread->m_hThread,0);
// 	}
// 	if (hCapErrorThread->m_hThread != NULL)
// 	{
// 		TerminateThread(hCapErrorThread->m_hThread,0);
// 	}
	

// 	try
// 	{
// 		TerminateThread(hCapThread->m_hThread,0);
// 		TerminateThread(hCapErrorThread->m_hThread,0);
// 	}
// 	catch (CMemoryException* e)
// 	{
// 	}
// 	catch (CFileException* e)
// 	{
// 	}
// 	catch (CException* e)
// 	{
// 	}
	CDialogEx::OnDestroy();
}

void CAutoTraderDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	if ((lParam == WM_LBUTTONDOWN) || (lParam == WM_RBUTTONDOWN))
	{ 
		ModifyStyleEx(0,WS_EX_TOPMOST);
		ShowWindow(SW_SHOW);
		//Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);
	}
}


//*************************************
// 函数名:  	GetTradeCode
// 目的:	获取交易代码
// 时间：   2014/03/25
//*************************************
CString CAutoTraderDlg::GetTradeCode( CString data )
{
	//data = _T(" \x16赜鳊.\x14x櫅?.E(.釪H..u\x11?t祜伬?{\vU\vr.伟?  192rb1410");
	CString res = _T("");
	CString temp;

	int roo1 = 0;
	int recordIndex = 0;
	for (int i=data.GetLength(); i>0; i--)
	{
		temp = data.GetAt(i);
		//char* tempChar = temp.GetBuffer(0);
		//if((temp.GetBuffer()>=_T('0') && temp<='9') || temp == '.')
		if(((int)temp.GetAt(0)>=48&&(int)temp.GetAt(0)<=57))
		{
			printf("");
			if (roo1 == 0)
			{
				recordIndex = i;
			}
			roo1 = roo1+1;

			// 数字计数不为1时
			if (roo1 != 1)
			{
				if (abs(i - recordIndex ) != 1)
				{
					return res;
				}
			}
			
			// 
			recordIndex = i;
			res = temp + res;
		}
		else
		{
			res = temp + res;
		}
	}

	return res;
}

bool CAutoTraderDlg::IsNum( CString str )
{
	bool bNumFlag = true;
	bool bFloatFlag = false;

	for(int i=0;i<str.GetLength();i++)
	{
		if(((int)str.GetAt(i)>=48&&(int)str.GetAt(i)<=57))continue;	
		else if(str.GetAt(i)=='.')
		{
			if(bFloatFlag)
			{
				bNumFlag = false;
				break; 
			}
			else
			{
				bFloatFlag = true;
				continue;
			}

		}
		else
		{
			bNumFlag = false;
			break;
		}
	}
	return bNumFlag;
}



bool CAutoTraderDlg::VectorIsHas( vector<CString> vec, CString str )
{
	for (int i=0;i<vec.size();i++)
	{
		if (vec.at(i) == str)
		{
			return true;
		}
	}
	return false;
}


int CAutoTraderDlg::VectorPos( vector<CString> vec, CString str )
{
	for (int i=0;i<vec.size();i++)
	{
		if (vec.at(i) == str)
		{
			return i;
		}
	}
	return -1;
}

void CAutoTraderDlg::WriteError( CString errorStr )
{
	FILE* fp = fopen("C:\\Error.txt", "at+");
	if(fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		fputs(CString2CharPt(errorStr), fp);//
		fputs("\r\n",fp);//或fputs("\r\n");
		fclose(fp);
	}
}

LRESULT CAutoTraderDlg::OnShowTask( WPARAM wParam, LPARAM lParam )
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


void CAutoTraderDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(nType == SIZE_MINIMIZED)  
	{  
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口              
	}  
}

void CAutoTraderDlg::LetItSmall()
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
	lstrcpyW(m_nid.szTip, L"MyTrader");
	::Shell_NotifyIcon(NIM_ADD,&m_nid );
	this->ShowWindow(SW_HIDE);

}


void CAutoTraderDlg::OnCbnSelchangeComboNet()
{
	// TODO: 在此添加控件通知处理程序代码
	pcap_if_t d;
	CString temp;
	CString sss;
	char* sst;
	CString pWideChar;
	int i;
	i=m_Net_ComboBox.GetCurSel();
	if(i<0)return;
	m_Net_ComboBox.GetLBText(i,temp);
	//(*pName)=temp;
	
	//m_AllDevs.addresses
	for(i = 0; i<m_AllDevs_Vec.size(); i++)
	{
		d = m_AllDevs_Vec.at(i);
		if(temp==d.name)
		{
			//sss(d.description);
			//const char * adpter_char = "\\Device\\NPF_{3788FA43-59ED-4C95-83F5-061E42A46329}";
			sst = d.description;
			// 写注册表 d。name
			CString NetworkName(d.name);
			CRegeditIO reg;
			reg.WriteNetworkCardName(NetworkName);

			m_adpter_char = d.name;
			int charLen = strlen(sst);
			int len = MultiByteToWideChar(CP_ACP,0,sst,charLen,NULL,0);
			TCHAR *buf = new TCHAR[len + 1];
			MultiByteToWideChar(CP_ACP,0,sst,charLen,buf,len);
			buf[len] = '\0'; //添加字符串结尾，注意不是len+1
			
			pWideChar.Append(buf);
			delete []buf;

			//CString theString = chArray;
			//sss.Format(_T("%s"), sst);
			GetDlgItem(IDC_STATIC_Net)->SetWindowText(pWideChar);

		}
	}
}


void CAutoTraderDlg::OnBnClickedStopStrategy()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Strategy.Stop();
}


void CAutoTraderDlg::OnBnClickedSimButtom()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_Strategy.Sim();
	while (m_Strategy.CheckOrderSuccessfullbySnap(_T("")))
	{
		printf("ss");
	}
	printf("xx");
}

void CAutoTraderDlg::SetTestText( CStatic ss )
{
	m_ID_Test.SetWindowTextW(_T("sss"));
}
