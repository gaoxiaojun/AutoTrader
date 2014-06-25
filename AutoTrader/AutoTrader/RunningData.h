#pragma once
#include "MinuteData.h"

// #ifndef BOOLDAY
// #define BOOLDAY 15;
// #define  M3_Std 3;
// #endif // !BOOLDAY



class CRunningData
{
public:
	CRunningData(void);
// 	CRunningData(vector<CMinuteData> inputData){
// 		m_Data_Vec = inputData;
// 		//BOOLDAY = 20;
// 		//M3_Std = 3;
// 	};

	~CRunningData(void);
protected:
	int BOLLDAY;
	int M3_Std;
public:
	void _init_(vector<CMinuteData> inputData);
	void calculateIdx(void);
	//void StdDeviation(void);
	// add new StrategyData for in running time
	void AddNewStrategyData(StrategyData inputData);
	void RefreshIndex();
	void PopData();

	vector<float> m_Close_Price_Idx;
	vector<CMinuteData> m_Data_Vec;
	// Boll Ö¸±ê

	float m_StandardDeviation;
	vector<float> m_StdDev;

	vector<float> m_Boll_mid;
	vector<float> m_Boll_up;
	vector<float> m_Boll_Down;
	//
	vector<float> m_Max_Price;
	vector<float> m_Min_Price;
	// buy volume
	vector<int> m_buy_Vol;
	// sell volume
	vector<int> m_sell_Vol;
	//
	vector<float> m_M3;
	vector<float> m_M5;
	vector<float> m_M10;
};

