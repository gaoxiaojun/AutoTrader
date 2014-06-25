/**************************************************************
**			函数封装类 v1.03								 **
** AutoCAD2010 x64											 **
** VS2008													 **
***************************************************************/
#pragma once
#include "StdAfx.h"
#include <vector>
#include <tuple>
#include <array>
#include<cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <math.h>

//#ifndef PI
//#define  PI 3.1415926535897932384626433832795;;
//#endif


using namespace std;
typedef vector<CString> LINEINFO;
//typedef tuple<CString, CString> ERRORUNIT;
//typedef vector<ERRORUNIT> ERRORLIST;
typedef AcDbEntity*  CADEnt;

#ifndef NREADMODE
#define  NREADMODE 1
#define  NWRITEMODE 0
#endif

class Additional_Class
{
public:
	Additional_Class(void);
	~Additional_Class(void);

private:
	//ERRORLIST m_ErrorList;
	//ERRORUNIT m_Error;

protected:
	//void SetError(CString ErrorState, CString FuncName);

public:
/****************************************************************************************************
交互函数
			|
			—选择实体
			|
			—返回实体ID
			|
			—判断实体类型（多段线返回1；）
			|
			—过滤图层
-----------------------------------------------------------------------
创建实体
			|
			—增加表格行
			|
			—绘制直线(起始点，终止点)
			|
			—绘制文字（文字，插入点，字高，角度）
			|
			—绘制圆（插入点，半径）
			|
			—绘制表格
-----------------------------------------------------------------------
实体参数
			|
			—获取扩展数据
			|
			—得到多段线段的数目
*************************************************************************************************/

//******交互函数*****************************************************************

	// 打开正交坐标锁定
	void Open_ORTHOMODE(void);
	// 关闭正交坐标锁定
	void Close_ORTHOMODE(void);
	// 用户选择实体函数,用户提示，返回实体，返回点
	//void Select_Entity_Ent(CString ScreenPrint, ads_name &RtEntity, ads_point &RtPoint);
	bool Select_Entity_Ent(CString ScreenPrint, ads_name &RtEntity, ads_point &RtPoint);
	// 打开实体返回实体ID，输入实体对象， 返回实体ID
	void Get_EntityID(ads_name RtEntity, AcDbObjectId &RtEntityID);
	// 判断对象类型， 输入对象实体
	int Check_Entity(AcDbEntity* InputEntity);
	// 查找图层
	bool FindLayer(CString LaylerName);
	// 打开关闭图层
	void SetLayerIsOff( CString strLayerName);
	// 设置当前图层
	void SetCurLayler(CString LaylerName);
	void SetCurLayler(AcDbObjectId curlayerID);
	// 获得当前图层ID
	AcDbObjectId GetCurLayler();
	// 全模型空间过滤
	AcDbObjectIdArray ObjectXdataFilter(CString XdataName, CString Xdata);
	// 过滤图层, 图层名， 返回符合条件的实体ID数组， 过滤条件函数
	bool LaylerFilter(CString LaylerName, AcDbObjectIdArray &EntityID, bool(*Filter)(AcDbEntity*,	 AcDbObjectId&));
	// 全部图层过滤
	bool LaylerFilter(AcDbObjectIdArray &EntityID, bool(*Filter)(AcDbEntity*,	 AcDbObjectId&));
	// 打开块表
	void Open_BlockTable(AcDbBlockTable* &pBlockTable, int ReadMode);
	// 打开模型空间
	void Open_ModelTableRecord(AcDbBlockTableRecord* &pBlkTblRcd, AcDbBlockTable* &pBlkTbl, int ReadMode);
	// 用户框选实体
	AcDbObjectIdArray Select_Entitys(CString ScreenPrint);
//*******块表记录******************************************************************
	// 遍历块表记录是否含有块
	bool BlkHasRef(CString RefName);
	// 插入扩张数据
	void addXdata(AcDbObjectId entID, CString xdataStr);
	void addXdata(AcDbObjectId entID, CString xdataStr, CString xdataNameStr);
	// 获取扩张数据
	CString Get_Xdata(AcDbObjectId EntID, CString Xdata_Ref);

//*******创建实体******************************************************************
	// 绘制一条直线
	AcDbObjectId Draw_Line(AcGePoint3d stPoint, AcGePoint3d enPoint);
	AcDbObjectId Draw_Line(AcGePoint3d stPoint, AcGePoint3d enPoint, CString LineType, double TypeScale);
	// 绘制文字
	AcDbObjectId Draw_Text(CString InputText, AcGePoint3d InsertPoint, double TextHeight, double TextAngle);
	AcDbObjectId Draw_MText(CString InputText, AcGePoint3d InsertPoint, double TextHeight, double TextAngle);
	// 绘制圆圈 XY平面
	AcDbObjectId Draw_Circle(AcGePoint3d ptCircle, double Radius);
	// 绘制矩形
	AcDbObjectId Draw_Rectangle(AcGePoint2d stPt, double length, double height);
	// 创建表
	AcDbObjectId Creat_Table(AcGePoint3d TablePoint, vector<CString> Title, double ColWidth=100, double RowHeight = 20, double TextHeight =10);
	// 增加表格行
	void Insert_TableRow(AcDbObjectId TableID, vector<CString> StrList);
	// 绘制圆弧
	AcDbObjectId Draw_Arc(AcGePoint3d CenterPt, double RadiusArc, double StartAngle, double EndAngle);
	// 设置模型颜色
	void Set_ObjectColor(AcDbObjectId ObID, int ColorIndex);
	void Set_ObjectColor(AcDbObjectIdArray obIDArray, int ColorIndex);
//********实体参数*****************************************************************
	// 追加线型
	BOOL Add_LineType(CString linetype);
	// 加入线型
	BOOL Get_LineTypeID(CString linetype, AcDbObjectId &linetypeid);
	// 获得实体外框中心
	AcGePoint3d Get_CenterPt(AcDbObjectId ObjID);
	// 改变直线起点终点，直线ID
	void Change_Line(AcDbObjectId LineID, AcGePoint3d ptStart, AcGePoint3d ptEnd);
	void Change_Line(AcDbObjectId LineID, AcGeVector3d deltaVec);
	// 改变文字位置
	void Change_TextPosition(AcDbObjectId TextID, AcGePoint3d ptText);
	// 删除直线实体通过ID
	void Delete_AcDbObject(AcDbObjectId LineID);
	// 判断多段线是否含有曲线
	bool PolyLineHasCruve(AcDbPolyline *PolyLineEntity);
	// 得到多段线夹点数组
	AcGePoint3dArray Get_PolyLinePointArray(AcDbObjectId PolyLineId);
	// 得到多段线段的数目
	int Get_NumPolyLine(AcDbPolyline *PolyLineEntity);
	// 判断多段线是否是矩形
	bool PolyLineIfRectangle(AcDbPolyline *PolyLineEntity);
	// 返回矩形的长和宽
	void Get_RectangleLW(AcDbPolyline *PolyLineEntity, double &Length, double &width);
	// 得到多段线端点坐标数组
	void Get_PolyLine_Point(AcDbObjectId PolyLineId,AcGePoint3dArray &PointArray);
	// 得到多线段每段长度数组
	void Get_PolyLine_Length(AcDbObjectId PolyLineId, AcGeDoubleArray &LengthArray);
	// 得到多线段类型字符串数组
	void Get_PolyLineType(AcDbObjectId PolyLineId,LINEINFO &LineInfo_List);
	// 得到多线段X，Y坐标值
	void Get_PolyLineCoor(AcGePoint3dArray PointArray, LINEINFO &X_Coor_List,LINEINFO &Y_Coor_List);
	// 得到多线段的第一列
	void Get_PolyLineFirst(CString First_P, AcGeDoubleArray LineLengthList, LINEINFO &First_List);
	// 得到指定图层模板的长宽
	bool Get_LayerLW(CString LayerName, double &Length, double &Width);
	// 把double数组变为cstring数组
	void TransFrom(AcGeDoubleArray LineLength, LINEINFO &LengthStr);
	// 改变表格位置
	void Change_TablePoint(AcDbObjectId TableID,AcGePoint3d newPt);
	// 得到圆弧的中点
	void Get_ArcMiddle(AcDbObjectId PolyLineId, AcGePoint3dArray &Middle_List, AcGePoint3dArray &CenterListInput, LINEINFO &ArcInfoRList, LINEINFO &ArcInfoAList);
	// 将实体绕z轴旋转 一定角度
	void RotateEnt(AcDbObjectId EntID, double RotateAng, AcGePoint3d InpPt);
	// 判断实体是不是AcDBCurve类
	bool IsAcDbCurve(AcDbObjectId EntID);

//************************************************************************************************************
	// 计算线型比例
	double CalLineTypeScale(double Len);
	// 获得数字的数量级
	int GetCountOrder(double Num);
	// 得到点数组中某坐标最大值的点index
	int GetMAXPt(int pos, AcGePoint3dArray PtList);
	// 得到点数组中某坐标最小值的点index
	int GetMINPt(int pos, AcGePoint3dArray PtList);
	// 分割字符串
	CString SplitString(CString str, char split, CString& LastStr);
	// 按行读取文件
	bool ReadFileL(CString Dir_ConfigFile, vector<CString> &FileData);
//************************************************************************************************************
	// 错误窗口
	void ErrorBox(CString TextError, HWND MyHandle);
	// 读写注册表
	void ReadReg(LPCTSTR data_Set, CString ValueName, CString & ReadStr);
	void WriteReg(LPCTSTR data_Set, CString ValueName, CString NewValue);
	bool CheckReg(LPCTSTR data_Set, CString ValueName);
	bool CheckReg(LPCTSTR data_Set, CString ValueName, CString &resStr);

	//////////////////////////////////////////////////////////////////////////
	
	inline CString Int2CString(int NeedInt)
	{
		char a[200];
		itoa(NeedInt, a, 10);
		CString ss = a;
		return ss;
	}

	inline char* CString2CharPt( CString InputString )
	{
		CString str = InputString;
		//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
		int n = str.GetLength();     // n = 14, len = 18
		//获取宽字节字符的大小，大小是按字节计算的
		int len = WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len+1];   //以字节为单位
		//宽字节编码转换成多字节编码
		WideCharToMultiByte(CP_ACP,0,str,str.GetLength() + 1 ,pFileName,len + 1 ,NULL,NULL);
		return pFileName;
	}

	inline CString Double2CString(double NeedInt)
	{
		char a[200];
		itoa(NeedInt, a, 10);
		CString ss = a;
		return ss;
	}
	inline double CString2Double(CString str)
	{
		double res;
		//char c[1024];
		char *c;
		c = CString2CharPt(str);
		//lstrcpyn(c, str , _countof(c));
		res = atof(c);
		//res = _ttof(str);
		return res;
	}
	inline LPBYTE CString2LPBYTE(CString str)
	{
		LPBYTE lpb = (LPBYTE)(LPCTSTR)str;
		return lpb;
	}
	inline TCHAR* CString2TCHAR(CString str)
	{
		int iLen = str.GetLength(); 
		TCHAR* szRs = new TCHAR[iLen]; 
		lstrcpy(szRs, str.GetBuffer(iLen)); 
		str.ReleaseBuffer(); 
		return szRs;
	}
	// 用于测试
	inline void PrintTest(int T_T)
	{
		CString StrName = Int2CString(T_T);
		acutPrintf(_T("测试结果: %s\n"), StrName);
	}
	inline void PrintTest(CString T_T)
	{
		acutPrintf(_T("测试结果: %s\n"), T_T);
	}
	inline void PrintTest(bool T_T)
	{
		if (T_T == true)
		{
			acutPrintf(_T("测试结果: True"));
		}
		acutPrintf(_T("测试结果: False"));
	}
	inline void PrintTest(char *T_T)
	{
		acutPrintf(_T("测试结果:"));
		//acutPrintf(T_T);
	}
	inline void PrintTest(AcGePoint3d T_T)
	{
		acutPrintf(_T("测试结果:"));
		CString temp;
		temp = Double2CString(T_T[0]);
		acutPrintf(_T("X:")+temp);
		temp = Double2CString(T_T[1]);
		acutPrintf(_T("Y") + temp);
		temp = Double2CString(T_T[2]);
		acutPrintf(_T("Z")+temp);
	}
};