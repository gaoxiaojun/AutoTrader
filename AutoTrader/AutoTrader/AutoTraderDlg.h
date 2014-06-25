
// AutoTraderDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include "ShowInfo.h"
#include "VspdcToMySQL.h"
#include "Trader.h"
#include "Strategy.h"
#include "AutoInfo.h"

 #include "pcap.h"
// #include <pcap\usb.h>
 //#include <inc.h>

using namespace std;


#define WM_SHOWTASK WM_USER+8
// #ifndef ListData
// 
// struct ListData
// {
// 	char ID[10];
// 	char TotalPacket[10];
// 	bool Falg;
// 	char Protocol[20];
// 	char sIP[16],sMac[19],sPort[10];
// 	char dIP[16],dMac[19],dPort[10];
// 	char Len[10];
// 	char Text[50];
// };
// 
// #endif




// CAutoTraderDlg 对话框
class CAutoTraderDlg : public CDialogEx
{
// 构造
public:
	//CAutoTraderDlg();
	CAutoTraderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTOTRADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	//CVspdCToMySQL * vspdctomysql = new CVspdCToMySQL;
	VspdcToMySQL * vspdctomysql_AutoTrader;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	// 触发事件
	afx_msg void OnBnClickedStartCapture();
	afx_msg void OnBnClickedStopCapture();
	afx_msg void OnClose();
	afx_msg void OnBnClickedShowdlgSwitch();
	afx_msg void OnBnClickedConnSql();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSmall();
	afx_msg void OnDestroy();
	//afx_msg LRESULT OnSystemTray(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNotifyIcon(WPARAM wParam, LPARAM lParam);

	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
//////////////////////////////////////////////////////////////////////////
public:
	NOTIFYICONDATA m_nid;
	CStrategy m_Strategy;
	// 监控list
	vector<CString> AutoList;
	// 监控次数列表，保证每个合约只过滤一次
	vector<CString> AutoListTime;
	// 最小化图标
	NOTIFYICONDATA NotifyIcon;
	// 控制进程 防止异常退出
	CWinThread *hCapThread;// 抓取主进程
	CWinThread *hCapErrorThread;// 检查进程
	CRITICAL_SECTION  csThreadStop;
	HANDLE eThreadStart;
	bool bThreadStop; // 异常结束开关
	CString CapFilePath;
	CString OldTimer; // 旧的时间值
	// 显示获取字符串	
	CStatic m_res_char;
	// 抓取结果列表
	vector<CString> m_resList;
	// 显示对话框
	CShowInfo* m_ShowDlg;
	// trader
	CTrader* m_trader;
	// 文件
	FILE* fp;
	// 是否第一次运行开关
	vector<bool> FirstRun;


//////////////////////////////////////////////////////////////////////////
// 处理函数
	static UINT CapThread(LPVOID lpParameter);// 抓取函数
	static UINT CapErrorThread(LPVOID lpParameter);//  检查错误对话框
	// 处理抓取数据字符串
	vector<CString> SplitString(CString input);
	// 数据库插入数据
	void InsertSQL(vector<CString> input);
	void InsertSQL(vector<CString> input, CString TableName);
	// 更新显示对话框
	void updataShowDlg(vector<CString> input);
	// 最小化处理
	void LetItSmall();
	// 预读网卡

private:
	char* Wstr2Astr(WCHAR *wstr);
	char* CString2CharPt(CString InputString);
	// 数据尾部转换代码
	void DecodeChar(char *data,DWORD len);
	// 切割代号
	CString GetTradeCode(CString data);
	// 判断是否是数字
	bool IsNum(CString str);
	// vector中是否有cstring
	bool VectorIsHas(vector<CString> vec, CString str);
	int VectorPos(vector<CString> vec, CString str);
	void WriteError(CString errorStr);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CComboBox m_Net_ComboBox;
	pcap_if_t m_AllDevs;
	vector<pcap_if_t> m_AllDevs_Vec;
	const char * m_adpter_char;
	afx_msg void OnCbnSelchangeComboNet();
	afx_msg void OnBnClickedStopStrategy();
	afx_msg void OnBnClickedSimButtom();
	CStatic m_ID_Test;
	void SetTestText(CStatic ss);
};

//extern CAutoTraderDlg theAppDlg;
