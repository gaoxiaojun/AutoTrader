#pragma once
#include "runningdata.h"
#include "MinuteData.h"
#include "AutoInfo.h"

// #ifndef BOOLDAY
// #define BOOLDAY 15;
// #define  M3_Std 3;
// #endif // !BOOLDAY

class CRunningData5 :
	public CRunningData
{
public:
	CRunningData5(void):CRunningData()
		{
			
	};

	~CRunningData5(void);

	void _init_(vector<CMinuteData> inputData);
	void calculateIdx(void);
	void AddNewStrategyData(StrategyData inputData);
	void RefreshIndex();
	void PopData();
};

