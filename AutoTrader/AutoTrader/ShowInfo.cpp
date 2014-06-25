// ShowInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ShowInfo.h"
#include "afxdialogex.h"


// CShowInfo 对话框

IMPLEMENT_DYNAMIC(CShowInfo, CDialogEx)

CShowInfo::CShowInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowInfo::IDD, pParent)
{

}

CShowInfo::~CShowInfo()
{
}

void CShowInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_S_DM, m_ID);
	DDX_Control(pDX, IDC_S_ZJS, m_ZJS_Value);
	DDX_Control(pDX, IDC_S_KP, m_Open);
	DDX_Control(pDX, IDC_S_SellValue, m_Sell_Value);
	DDX_Control(pDX, IDC_S_BuyValue, m_Buy_Value);
	DDX_Control(pDX, IDC_S_Split, m_S_Split);
	DDX_Control(pDX, IDC_S_BuyVolume, m_Buy_Volume);
	DDX_Control(pDX, IDC_S_NewValue, m_New_Value);
	DDX_Control(pDX, IDC_S_SellVolume, m_Sell_Volume);
	DDX_Control(pDX, IDC_S_Split2, m_S_Split2);
	DDX_Control(pDX, IDC_S_HeightValue, m_height_value);
	DDX_Control(pDX, IDC_S_LowValue, m_low_value);
	DDX_Control(pDX, IDC_S_JunValue, m_Jun_Value);
	DDX_Control(pDX, IDC_S_ZDPoint, m_ZD_Point);
	DDX_Control(pDX, IDC_S_CJVolume, m_CJ_Volume);
	DDX_Control(pDX, IDC_S_CCVolume, m_CC_Volume);
	DDX_Control(pDX, IDC_S_UnKnow, m_Unknow);
	DDX_Control(pDX, IDC_S_ZTValue, m_ZT_Value);
	DDX_Control(pDX, IDC_S_DTValue, m_DT_Value);
	DDX_Control(pDX, IDC_S_UnKonw2, m_UnKnow2);
	DDX_Control(pDX, IDC_S_UnKonw3, m_UnKnow3);
	DDX_Control(pDX, IDC_S_UnKonw4, m_UnKnow4);
	DDX_Control(pDX, IDC_S_UnKonw5, m_UnKnow5);
	DDX_Control(pDX, IDC_S_UnKonw6, m_UnKnow6);
	DDX_Control(pDX, IDC_S_ZSValue, m_ZS_Value);
	DDX_Control(pDX, IDC_S_UnKonw7, m_Unknow7);
	DDX_Control(pDX, IDC_S_UnKnowZX, m_UnknowZX);
	DDX_Control(pDX, IDC_S_UnKnowJS, m_Unknow_JS);
	DDX_Control(pDX, IDC_S_W1, m_w1);
	DDX_Control(pDX, IDC_S_W2, m_w2);
	DDX_Control(pDX, IDC_S_W3, m_w3);
	DDX_Control(pDX, IDC_S_W4, m_w4);
	DDX_Control(pDX, IDC_S_W5, m_w5);
	DDX_Control(pDX, IDC_S_W6, m_w6);
	DDX_Control(pDX, IDC_S_W7, m_w7);
	DDX_Control(pDX, IDC_S_W8, m_w8);
	DDX_Control(pDX, IDC_S_W9, m_w9);
	DDX_Control(pDX, IDC_S_W10, m_w10);
	DDX_Control(pDX, IDC_S_W11, m_w11);
	DDX_Control(pDX, IDC_S_W12, m_w12);
	DDX_Control(pDX, IDC_S_W13, m_w13);
	DDX_Control(pDX, IDC_S_W14, m_w14);
	DDX_Control(pDX, IDC_S_W15, m_w15);
	DDX_Control(pDX, IDC_S_W16, m_w16);
	DDX_Control(pDX, IDC_S_W17, m_w17);
	DDX_Control(pDX, IDC_S_W18, m_w18);
	DDX_Control(pDX, IDC_S_F, m_FX);
	DDX_Control(pDX, IDC_S_Time, m_Time);
	DDX_Control(pDX, IDC_S_EWW, m_eww);
}


BEGIN_MESSAGE_MAP(CShowInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CShowInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CShowInfo::OnBnClickedCancel)
END_MESSAGE_MAP()

void CShowInfo::UpdateShowData( vector<CString> input )
{
	if (input.size() == 49)
	{
		//if (input.at(0).Right(6) == AG)
		//{
		m_ID.SetWindowTextW(input.at(0).Right(6));
		m_ZJS_Value.SetWindowTextW(input.at(1));
		m_Open.SetWindowTextW(input.at(2));
		m_Sell_Value.SetWindowTextW(input.at(7));
		m_Buy_Value.SetWindowTextW(input.at(4));
		m_S_Split.SetWindowTextW(input.at(6));
		m_Buy_Volume.SetWindowTextW(input.at(5));
		m_New_Value.SetWindowTextW(input.at(3));
		m_Sell_Volume.SetWindowTextW(input.at(8));
		m_S_Split2.SetWindowTextW(input.at(9));
		m_height_value.SetWindowTextW(input.at(10));
		m_low_value.SetWindowTextW(input.at(11));
		m_Jun_Value.SetWindowTextW(input.at(12));
		m_ZD_Point.SetWindowTextW(input.at(13));
		m_CJ_Volume.SetWindowTextW(input.at(14));
		m_CC_Volume.SetWindowTextW(input.at(15));
		m_Unknow.SetWindowTextW(input.at(16));
		m_ZT_Value.SetWindowTextW(input.at(17));
		m_DT_Value.SetWindowTextW(input.at(18));
		m_UnKnow2.SetWindowTextW(input.at(19));
		m_UnKnow3.SetWindowTextW(input.at(20));
		m_UnKnow4.SetWindowTextW(input.at(21));
		m_UnKnow5.SetWindowTextW(input.at(22));
		m_UnKnow6.SetWindowTextW(input.at(23));
		m_ZS_Value.SetWindowTextW(input.at(24));
		m_Unknow7.SetWindowTextW(input.at(25));
		m_UnknowZX.SetWindowTextW(input.at(26));
		m_Unknow_JS.SetWindowTextW(input.at(27));
		m_w1.SetWindowTextW(input.at(28));
		m_w2.SetWindowTextW(input.at(29));
		m_w3.SetWindowTextW(input.at(30));
		m_w4.SetWindowTextW(input.at(31));
		m_w5.SetWindowTextW(input.at(32));
		m_w6.SetWindowTextW(input.at(33));
		m_w7.SetWindowTextW(input.at(34));
		m_w8.SetWindowTextW(input.at(35));
		m_w9.SetWindowTextW(input.at(36));
		m_w1.SetWindowTextW(input.at(37));
		m_w11.SetWindowTextW(input.at(38));
		m_w12.SetWindowTextW(input.at(39));
		m_w13.SetWindowTextW(input.at(40));
		m_w14.SetWindowTextW(input.at(41));
		m_w15.SetWindowTextW(input.at(42));
		m_w16.SetWindowTextW(input.at(43));
		m_w17.SetWindowTextW(input.at(44));
		m_w18.SetWindowTextW(input.at(45));
		m_FX.SetWindowTextW(input.at(46));
		m_Time.SetWindowTextW(input.at(47));
		m_eww.SetWindowTextW(input.at(48));
		//}
		
	}
}


// CShowInfo 消息处理程序


void CShowInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//this->ShowWindow(SW_HIDE);
	CDialogEx::OnOK();
}


void CShowInfo::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//this->DestroyWindow();
	CDialogEx::OnCancel();
	//this->ShowWindow(SW_HIDE);
}
