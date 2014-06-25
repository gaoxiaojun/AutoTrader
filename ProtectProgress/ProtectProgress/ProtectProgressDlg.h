
// ProtectProgressDlg.h : 头文件
//

#pragma once
#include <vector>
#include <tuple>

#define WM_SHOWTASK WM_USER+8

using namespace std;
// 定义单个数据单元 句柄，标题，类型名称
typedef tuple<HWND,CString,CString> WINTUPLE;
typedef vector<tuple<HWND,CString,CString>> TUPLEVEC;

// CProtectProgressDlg 对话框
class CProtectProgressDlg : public CDialogEx
{
// 构造
public:
	CProtectProgressDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PROTECTPROGRESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	TUPLEVEC m_TupleVec;
	TUPLEVEC m_TupleAutoTraderVec;
	TUPLEVEC m_AutoTrader_Vec;
	WINTUPLE m_OK_Tuple;
	CWinThread *hCapThread;// 抓取主进程 实时更新进程
	// find the abort window
	bool restartSwitch;
	void GetTheAbortWin();
	void GetAutoTraderWin();

	void BeginProgress();
	static UINT RuntimeThread(LPVOID lpParameter);// 抓取函数
	void ReStartTradeMaster();
	void StartCaptureData();
	char* CString2CharPt( CString InputString );
	//
	HWND m_Abort_hwnd;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	NOTIFYICONDATA m_nid;
	// 最小化处理
	void LetItSmall();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedStartcap();
};
