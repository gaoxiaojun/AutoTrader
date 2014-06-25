#include "StdAfx.h"
#include "RunningData.h"


//int BOLLDAY = 20;

CRunningData::CRunningData(void)
{
	BOLLDAY = 20;
	M3_Std = 3;
}


CRunningData::~CRunningData(void)
{
}

void CRunningData::_init_( vector<CMinuteData> inputData )
{
	
}

void CRunningData::calculateIdx( void )
{
	
}


void CRunningData::AddNewStrategyData( StrategyData inputData )
{
	// first check the new strategy data
	// wether in the head of m_data

}

void CRunningData::RefreshIndex()
{
	//calculateIdx();
}

void CRunningData::PopData()
{

}
