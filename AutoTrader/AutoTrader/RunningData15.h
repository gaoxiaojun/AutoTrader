#pragma once
#include "runningdata.h"

// #ifndef BOOLDAY
// #define BOOLDAY 15;
// #define  M3_Std 3;
// #endif // !BOOLDAY

class CRunningData15 :
	public CRunningData
{
public:
	CRunningData15(void):CRunningData(){
	
	};
	~CRunningData15(void);

	void _init_(vector<CMinuteData> inputData);
	void calculateIdx(void);
	void AddNewStrategyData(StrategyData inputData);
	void RefreshIndex();
	void PopData();
};

