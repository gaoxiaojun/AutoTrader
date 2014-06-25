#pragma once
#include "resource.h"
#include "afxwin.h"
#include <vector>

#ifndef AG
#define AG "ag1412"
#endif


using namespace std;
// CShowInfo 对话框

class CShowInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CShowInfo)

public:
	CShowInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	

	DECLARE_MESSAGE_MAP()
public:
	void UpdateShowData(vector<CString> input);
	CStatic m_ID;
	CStatic m_ZJS_Value;
	CStatic m_Open;
	CStatic m_Sell_Value;
	CStatic m_Buy_Value;
	CStatic m_S_Split;
	CStatic m_Buy_Volume;
	CStatic m_New_Value;
	CStatic m_Sell_Volume;
	CStatic m_S_Split2;
	CStatic m_height_value;
	CStatic m_low_value;
	CStatic m_Jun_Value;
	CStatic m_ZD_Point;
	CStatic m_CJ_Volume;
	CStatic m_CC_Volume;
	CStatic m_Unknow;
	CStatic m_ZT_Value;
	CStatic m_DT_Value;
	CStatic m_UnKnow2;
	CStatic m_UnKnow3;
	CStatic m_UnKnow4;
	CStatic m_UnKnow5;
	CStatic m_UnKnow6;
	CStatic m_ZS_Value;
	CStatic m_Unknow7;
	CStatic m_UnknowZX;
	CStatic m_Unknow_JS;
	CStatic m_w1;
	CStatic m_w2;
	CStatic m_w3;
	CStatic m_w4;
	CStatic m_w5;
	CStatic m_w6;
	CStatic m_w7;
	CStatic m_w8;
	CStatic m_w9;
	CStatic m_w10;
	CStatic m_w11;
	CStatic m_w12;
	CStatic m_w13;
	CStatic m_w14;
	CStatic m_w15;
	CStatic m_w16;
	CStatic m_w17;
	CStatic m_w18;
	CStatic m_FX;
	CStatic m_Time;
	CStatic m_eww;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
