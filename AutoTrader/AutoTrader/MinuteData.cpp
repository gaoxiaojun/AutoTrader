#include "StdAfx.h"
#include "MinuteData.h"



/*int BOLLDAY = 20;*/

CMinuteData::CMinuteData(void)
{
	
}

CMinuteData::CMinuteData( StrategyData inputData )
{
	m_FirstData = inputData;
	m_Data.push_back(inputData);

	m_ID_Timer.SetData(inputData.HSTIME,inputData.HSDATE);
}


CMinuteData::~CMinuteData(void)
{
}

void CMinuteData::Add( StrategyData inputData )
{
	m_Data.push_back(inputData);
}

void CMinuteData::init( StrategyData inputData )
{
	m_FirstData = inputData;

	m_ID_Timer.SetData(inputData.HSTIME,inputData.HSDATE);
}

bool CMinuteData::IsInner( StrategyData inputData )
{
	bool res = false;
	res = m_FirstData.timer.isInOneMinute(inputData.timer);
	return res;
}

void CMinuteData::clearData()
{
	m_Data.clear();
	//m_Data.push_back(inputData);
}

float CMinuteData::GetClosePrice( void )
{
	return m_Data.at(0).ClosePrice;
}

float CMinuteData::GetMaxPrice( void )
{
	float res = 0;
	for (int i = 0; i < m_Data.size(); i++)
	{
		if(m_Data.at(i).ClosePrice > res)
		{
			res = m_Data.at(i).ClosePrice;
		}
	}
	return res;

}

float CMinuteData::GetMinPrice( void )
{
	float res = 999999999999;
	for (int i = 0; i < m_Data.size(); i++)
	{
		if(m_Data.at(i).ClosePrice < res)
		{
			res = m_Data.at(i).ClosePrice;
		}
	}
	return res;
}

// void CMinuteData::init_BollMid( void )
// {
// 	for (int i=0; i<m_Data.size(); i++)
// 	{
// 
// 	}
// }
