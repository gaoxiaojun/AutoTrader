#include "StdAfx.h"
#include "RunningData15.h"


//int BOLLDAY = 20;

// CRunningData15::CRunningData15(void)
// {
// 	//BOOLDAY = 20;
// 	//M3_Std = 3;
// }


CRunningData15::~CRunningData15(void)
{
}

void CRunningData15::_init_( vector<CMinuteData> inputData )
{
	m_Data_Vec = inputData;
	vector<CMinuteData> tempVec;
	vector<CMinuteData>::iterator xIter;
	//////////////////////////////////////////////////////////////////////////
	// 除掉干扰项
	for (xIter = m_Data_Vec.begin(); xIter!=m_Data_Vec.end();xIter++)
	{
		if(xIter->m_Data.size()<5)
		{
			//m_Data_Vec.erase(xIter);
		}
		else
		{
			tempVec.push_back(*xIter);
		}
	}
	m_Data_Vec = tempVec;
	calculateIdx();
}

void CRunningData15::calculateIdx( void )
{
	//int BOLLDAY = 20;
	//int M3_Std = 3;

	int len = m_Data_Vec.size();
	int roo = len - BOLLDAY;
	vector<float> tempBollMid,tempBollUp,tempBollDown,tempMaxPrice,tempMinPrice,
		tempStdDev,tempCloseValue;
	vector<float> tempM3;

	if (roo < 0)
	{
		printf("超出长度！");
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// 计算n日平均线
	for (int i=0; i<roo; i++)
	{
		float tempMid = 0;
		float tempMax = 0;
		tempCloseValue.push_back(m_Data_Vec.at(i).GetClosePrice());
		for (int j=i; j<i+M3_Std; j++)
		{
			float testFloat = m_Data_Vec.at(j).GetClosePrice();
			tempMid = tempMid + m_Data_Vec.at(j).GetClosePrice();

		}
		float avarage = tempMid/M3_Std;
		tempM3.push_back(avarage);
	}
	m_M3 = tempM3;


	//////////////////////////////////////////////////////////////////////////
	// 计算布林线

	for (int i=0; i<roo; i++)
	{

		float tempMid = 0;
		float tempMax = 0;
		tempCloseValue.push_back(m_Data_Vec.at(i).GetClosePrice());
		for (int j=i; j<i+BOLLDAY; j++)
		{
			tempMid = tempMid + m_Data_Vec.at(j).GetClosePrice();

		}

		float avarage = tempMid/BOLLDAY;
		float Sum = 0;
		for (int k=i; k<i+BOLLDAY; k++)
		{
			Sum = Sum + pow((m_Data_Vec.at(k).GetClosePrice() - avarage),2);
		}

		tempStdDev.push_back(sqrt(Sum/BOLLDAY));

		tempBollMid.push_back(tempMid/BOLLDAY);
		tempMaxPrice.push_back(m_Data_Vec.at(i).GetMaxPrice());
		tempMinPrice.push_back(m_Data_Vec.at(i).GetMinPrice());

		tempBollUp.push_back( (tempMid/BOLLDAY) + 2*(sqrt(Sum/BOLLDAY) ) );
		tempBollDown.push_back( (tempMid/BOLLDAY) - 2*(sqrt(Sum/BOLLDAY) ) );
	}

	m_Close_Price_Idx = tempCloseValue;
	m_StdDev = tempStdDev;
	m_Max_Price = tempMaxPrice;
	m_Min_Price=tempMinPrice;
	m_Boll_mid=tempBollMid;
	m_Boll_up = tempBollUp;
	m_Boll_Down = tempBollDown;
}

void CRunningData15::AddNewStrategyData( StrategyData inputData )
{

}

void CRunningData15::RefreshIndex()
{
	calculateIdx();
}

void CRunningData15::PopData()
{
	m_Boll_mid.pop_back();
	m_Boll_up.pop_back();
	m_Boll_Down.pop_back();
	for (int i = 0; i<BOLLDAY; i++)
	{
		m_Close_Price_Idx.pop_back();
		m_Data_Vec.pop_back();
	}
	for (int i = 0; i<BOLLDAY/3-1; i++)
	{
		m_M3.pop_back();
	}
}
