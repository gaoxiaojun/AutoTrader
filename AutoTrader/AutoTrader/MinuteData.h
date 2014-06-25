#pragma once
#include "AutoInfo.h"
#include <vector>



using namespace std;

class CMinuteData
{
public:
	CMinuteData(void);
	CMinuteData(StrategyData inputData);
	~CMinuteData(void);

	StrategyData m_FirstData;

	HSTimer m_ID_Timer;

	void Add(StrategyData inputData);
	void init(StrategyData inputData);
	void clearData();
	bool IsInner(StrategyData inputData);
	float GetClosePrice(void);
	float GetMaxPrice(void);
	float GetMinPrice(void);

	vector<StrategyData> m_Data;
	//
	float m_Hight_Price;
	float m_Low_Price;
	float m_Close_Price;
	float m_Open_Price;
	float m_Average_Price;

	int m_Buy_Volume;
	int m_Sell_Volume;
	int m_Hold_Volume;
	int m_Trade_Volume;


	// boll line
// 	vector<float> m_Boll_Line_Mid;
// 	vector<float> m_Boll_Line_Up;
// 	vector<float> m_Boll_Line_Down;
	// 
	//void init_BollMid(void);

};

