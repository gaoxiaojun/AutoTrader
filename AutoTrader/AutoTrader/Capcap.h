#pragma once
#include <vector>
#include <pcap.h>
#include <atlstr.h>
#include <afx.h>
using namespace std;
//using namespace ATL;

struct ListData
{
	char ID[10];
	char TotalPacket[10];
	bool Falg;
	char Protocol[20];
	char sIP[16],sMac[19],sPort[10];
	char dIP[16],dMac[19],dPort[10];
	char Len[10];
	char Text[50];
};


class CCapcap
{
public:
	CCapcap(void);
	~CCapcap(void);

	// 需要抓取的数据
	vector<CString> m_Get_Config;
	// 线程开关
	bool StartCapture();
	bool StopCapture();
	// 设置出配置
	bool SetConfig();
	vector<CString> GetConfig();
	bool AddConfig();

	static void DecodeChar(char *data,DWORD len);
	// 获取临时记录文件

public:
	// 终止进程判断
	bool bThreadStop;

private:
	
	// 适配器列表
	vector<CString> m_AdapterNameList;
	vector<CString> m_AdapterDescriptionList;
	pcap_if_t *AllDevs;
	// 所选的适配器名称
	static CString AdapterName;
	// 临时文件路径
	static CString CapFilePath;
	// 进程
	CWinThread *hCapThread;//抓取进程
	CRITICAL_SECTION  csThreadStop;
	HANDLE eThreadStart;

private:
	// 抓取循环进程 主过程
	static UINT CapThread(LPVOID lpParameter);
	// 临时记录文件 创建
	void _CreateCapFile();
	// 解析数据包
	void AnalsePacket(const pcap_pkthdr *header,const u_char *data);
	// 初始化
	void _init_();
	// 获取适配器列表
	void _GetAdapterList();
};

