#include "StdAfx.h"
#include "resource.h"
#include "Additional_Class.h"

Additional_Class::Additional_Class(void)
{
	//this->SetError("","");
}

Additional_Class::~Additional_Class(void)
{
}

//void Additional_Class::Select_Entity_Ent(CString ScreenPrint, ads_name &RtEntity, ads_point &RtPoint)
//{
//	if (acedEntSel(ScreenPrint, RtEntity, RtPoint)!= RTNORM)
//	{
//		acutPrintf(_T("\n返回实体失败！"));
//		this->SetError("用户选择实体失败!", "Select_Entity_Ent");
//		m_ErrorList.push_back(m_Error);
//		return;
//	}
//	return;
//}

bool Additional_Class::Select_Entity_Ent( CString ScreenPrint, ads_name &RtEntity, ads_point &RtPoint )
{
	if (acedEntSel(ScreenPrint, RtEntity, RtPoint)!= RTNORM)
	{
		//acutPrintf(_T(ZYUtils::LoadString(IDS_INPUTFACTOR)));
// 		this->SetError("USER SELECT ENTITY ERROR!", "Select_Entity_Ent");
// 		m_ErrorList.push_back(m_Error);
		return false;
	}
	return true;
}

void Additional_Class::Get_EntityID( ads_name RtEntity, AcDbObjectId &RtEntityID )
{
	AcDbObjectId PolyLineId;
	Acad::ErrorStatus es = acdbGetObjectId(RtEntityID, RtEntity);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nGET ENTITY ID ERROR！"));
// 		this->SetError("GET ENTITY ID ERROR!\n", "Get_EntityID");
// 		m_ErrorList.push_back(m_Error);
		return;
	}
	return;
}

int Additional_Class::Check_Entity(AcDbEntity* InputEntity)
{
	unsigned int counter;
	if (InputEntity->isKindOf(AcDbEntity::desc()))
	{
		counter = 100;
		if (InputEntity->isKindOf(AcDbCurve::desc()))
		{
			if (InputEntity->isKindOf(AcDbPolyline::desc()))
			{
				// 如果是多段线返回1；
				//InputEntity->cast();
				/*AcDbPolyline pLineChange = AcDbPolyline::cast(InputEntity);
				if (pLineChange.isClosed() == true)
				{
				return 101;
				}
				else
				{
				return 103;
				}*/
				return 101;
			}
			if (InputEntity->isKindOf(AcDbLine::desc()))
			{
				// 如果是线段返回2；
				return 102;
			}
			
		}
		if (InputEntity->isKindOf(AcDbText::desc()))
		{
			// 如果是文字返回 110；
			return 110;
		}
		if (InputEntity->isKindOf(AcDbMText::desc()))
		{
			// 如果是文字返回 111；
			return 111;
		}
		if (InputEntity->isKindOf(AcDbDimension::desc()))
		{
			return 120;
		}
		return 100;
	}
	
// 	this->SetError("THERE IS NOT THIS CLASS!\n", "Check_Entity");
// 	m_ErrorList.push_back(m_Error);
	return 0;
}

AcDbObjectId Additional_Class::Draw_Line(AcGePoint3d stPoint, AcGePoint3d enPoint)
{
	AcDbLine *pLineTemp = new AcDbLine();
	pLineTemp->setStartPoint(stPoint);
	pLineTemp->setEndPoint(enPoint);
	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_BlockTable(pBlockTable, NREADMODE);
	AcDbBlockTableRecord *pBlockTableRecord = NULL;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	//acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_ModelTableRecord(pBlockTableRecord, pBlockTable, NWRITEMODE);
	AcDbObjectId TempLineID;
	pBlockTableRecord->appendAcDbEntity(TempLineID, pLineTemp);
	pLineTemp->close();
	pBlockTable->close();
	pBlockTableRecord->close();
	return TempLineID;
}

AcDbObjectId Additional_Class::Draw_Line( AcGePoint3d stPoint, AcGePoint3d enPoint, CString LineType, double TypeScale )
{
	AcDbObjectId tempID, LtCenter, LtByLayer;
	Add_LineType(LineType);

	AcDbLine *pLineTemp = new AcDbLine();
	pLineTemp->setLinetype(LineType);
	pLineTemp->setStartPoint(stPoint);
	pLineTemp->setEndPoint(enPoint);
	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_BlockTable(pBlockTable, NREADMODE);
	AcDbBlockTableRecord *pBlockTableRecord = NULL;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	//acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_ModelTableRecord(pBlockTableRecord, pBlockTable, NWRITEMODE);
	AcDbObjectId TempLineID;
	pBlockTableRecord->appendAcDbEntity(TempLineID, pLineTemp);
	pLineTemp->close();
	pBlockTable->close();
	pBlockTableRecord->close();
	return TempLineID;
}

AcDbObjectId Additional_Class::Draw_Text( CString InputText, AcGePoint3d InsertPoint, double TextHeight, double TextAngle )
{
	AcDbBlockTable *pBlockTable;
	AcDbBlockTableRecord *pBlockTableRecord;
	AcDbText *text_Up = new AcDbText(InsertPoint, InputText, AcDbObjectId::kNull, TextHeight, TextAngle);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_BlockTable(pBlockTable, NREADMODE);
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	//this->Open_ModelTableRecord(pBlockTableRecord, pBlockTable, NWRITEMODE);
	AcDbObjectId TextID;
	pBlockTableRecord->appendAcDbEntity(TextID, text_Up);
	text_Up->close();
	pBlockTable->close();
	pBlockTableRecord->close();
	return TextID;
}

AcDbObjectId Additional_Class::Draw_MText( CString InputText, AcGePoint3d InsertPoint, double TextHeight, double TextAngle )
{
	AcDbBlockTable *pBlockTable;
	AcDbBlockTableRecord *pBlockTableRecord;
	//AcDbMText *text_Up = new AcDbMText(InsertPoint, InputText, AcDbObjectId::kNull, TextHeight, TextAngle);
	AcDbMText *text_Up = new AcDbMText;
	text_Up->setContents(InputText);
	text_Up->setHeight(TextHeight);
	text_Up->setLocation(InsertPoint);

	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_BlockTable(pBlockTable, NREADMODE);
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	//this->Open_ModelTableRecord(pBlockTableRecord, pBlockTable, NWRITEMODE);
	AcDbObjectId TextID;
	pBlockTableRecord->appendAcDbEntity(TextID, text_Up);
	text_Up->close();
	pBlockTable->close();
	pBlockTableRecord->close();
	return TextID;
}

AcDbObjectId Additional_Class::Draw_Circle( AcGePoint3d ptCircle, double Radius )
{
	AcGeVector3d norm(0,0,1);
	AcDbCircle *pCircle = new AcDbCircle(ptCircle, norm, Radius);
	AcDbBlockTable *pBlockTable;
	AcDbBlockTableRecord *pBlockTableRecord;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//Open_BlockTable(pBlockTable, NREADMODE);
	//Open_ModelTableRecord(pBlockTableRecord, pBlockTable, NWRITEMODE);
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	AcDbObjectId CircleId;
	pBlockTableRecord->appendAcDbEntity(CircleId, pCircle);
	pCircle->close();
	pBlockTable->close();
	pBlockTableRecord->close();
	return CircleId;
}

void Additional_Class::Change_Line(AcDbObjectId LineID, AcGePoint3d ptStart, AcGePoint3d ptEnd )
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, LineID, AcDb::kForWrite)!= Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ENETITY ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbLine::desc()))
	{
		acutPrintf(_T("\nENTITY IS NOT LINE"));
		return;
	}
	AcDbLine *pLineChange;
	pLineChange = AcDbLine::cast(pEnt_Temp);
	AcGePoint3d pLineE;
	pLineChange->setStartPoint(ptStart);
	pLineChange->setEndPoint(ptEnd);
	pEnt_Temp->close();
	pLineChange->close();
	return;
}

void Additional_Class::Change_Line( AcDbObjectId LineID, AcGeVector3d deltaVec )
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, LineID, AcDb::kForWrite)!= Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ENTITY ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbLine::desc()))
	{
		acutPrintf(_T("\nENTITY IS NOT LINE"));
		return;
	}
	AcDbLine *pLineChange;
	pLineChange = AcDbLine::cast(pEnt_Temp);
	AcGePoint3d ptLineS, ptLineE;
	Acad::ErrorStatus es = pLineChange->getStartPoint(ptLineS);
	es = pLineChange->getStartPoint(ptLineE);
	pLineChange->setStartPoint(ptLineS+deltaVec);
	pLineChange->setEndPoint(ptLineE + deltaVec);
	pEnt_Temp->close();
	pLineChange->close();
	return;
}

void Additional_Class::Change_TextPosition(AcDbObjectId TextID, AcGePoint3d ptText )
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, TextID, AcDb::kForWrite) != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN TEXT ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbText::desc()))
	{
		acutPrintf(_T("\nENTITY IS NOT TEXT"));
		return;
	}
	AcDbText *pTextUpChange;
	pTextUpChange = AcDbText::cast(pEnt_Temp);
	pTextUpChange->setPosition(ptText);
	pEnt_Temp->close();
	pTextUpChange->close();
	return;
}

void Additional_Class::Delete_AcDbObject( AcDbObjectId LineID )
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, LineID, AcDb::kForWrite) != Acad::eOk	)
	{
		acutPrintf(_T("\nOPEN ENTITY ERROR"));
		return;
	}
	pEnt_Temp->erase();
	pEnt_Temp->close();
	return;
}

AcGePoint3dArray Additional_Class::Get_PolyLinePointArray( AcDbObjectId PolyLineId )
{
	AcGePoint3dArray LineCorner_List;
	AcDbIntArray Osnap_List, GeomID_List;
	AcDbEntity *pEnt_Temp = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt_Temp, PolyLineId, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ENTITY ERROR "));
		return LineCorner_List;
	}
	if (!pEnt_Temp->isKindOf(AcDbPolyline::desc()))
	{
		acutPrintf(_T("\nENETITY IS NOT POLYLINE"));
		return LineCorner_List;
	}
	AcDbPolyline *pPolyLine = AcDbPolyline::cast(pEnt_Temp);
	if (pPolyLine->getGripPoints(LineCorner_List, Osnap_List, GeomID_List) != Acad::eOk)
	{
		acutPrintf(_T("\nGET GRIP POINT ERROR！"));
		pPolyLine->close();
		return LineCorner_List;
	}
	pPolyLine->close();
	return LineCorner_List;
}

AcDbObjectId Additional_Class::Creat_Table(AcGePoint3d TablePoint, vector<CString> Title, double ColWidth, double RowHeight, double TextHeight)
{
	AcDbTable *pTable = new AcDbTable();
	AcDbObjectId TableID;
	pTable->setNumColumns(Title.size());
	pTable->setNumRows(1);
	pTable->setColumnWidth(ColWidth);
	pTable->setRowHeight(RowHeight);
	pTable->setDirection(AcGeVector3d(1,0,0));
	pTable->setNormal(AcGeVector3d(0,0,1));
	
	pTable->setPosition(TablePoint);
	AcDbBlockTable *pBlockTable;
	AcDbBlockTableRecord *pBlockTableRecord;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	pBlockTable->getAt(ACDB_MODEL_SPACE,pBlockTableRecord,AcDb::kForWrite);
	pBlockTableRecord->appendAcDbEntity(TableID, pTable);
	//pBlockTable->close();
	pBlockTableRecord->close();
	//pTable->setTextString(0,0, "桩 号");
	//pTable->setTextHeight(0,0,10);
	//pTable->setTextString(0,1, "X坐标值");
	//pTable->setTextHeight(0,1,10);
	//pTable->setTextString(0,2, "Y坐标值");
	//pTable->setTextHeight(0,2,10);
	//pTable->setTextString(0,3, "特性值");
	//pTable->setTextHeight(0,3,10);
	//pTable->setTextString(0,4, "长 度");
	//pTable->setTextHeight(0,4,10);
	pTable->close();
	return TableID;
}

void Additional_Class::Insert_TableRow( AcDbObjectId TableID, vector<CString> StrList)
{
	AcDbEntity *pEnt_Temp = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt_Temp, TableID, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN TABLE ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbTable::desc()))
	{
		acutPrintf(_T("\nENTITY NOT TABLE"));
		return;
	}
	AcDbTable *pTable = AcDbTable::cast(pEnt_Temp);
	int Row = pTable->numRows();
	int Col = pTable->numColumns();
	if (Col < StrList.size())
	{
		acutPrintf(_T("\nTABLE ERROR"));
		pTable->close();
		return;
	}
	double RowHeight = pTable->rowHeight(0);
	double TextHeight = pTable->textHeight(0, 0);
	pTable->insertRows(Row, RowHeight,1);
	for (int i=0; i<StrList.size(); i++)
	{
		pTable->setTextString(Row, i, StrList.at(i));
		pTable->setTextHeight(Row, i,TextHeight);
	}
	pTable->close();
	pEnt_Temp->close();
}

void Additional_Class::Get_PolyLine_Point( AcDbObjectId PolyLineId,AcGePoint3dArray &PointArray )
{
	AcDbEntity *pEnt_Temp = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt_Temp, PolyLineId, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN POLYLINE ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbPolyline::desc()))
	{
		acutPrintf(_T("\nENTITY IS NOT POLYLINE"));
		return;
	}
	AcDbPolyline *pPolyLine = AcDbPolyline::cast(pEnt_Temp);
	int num = pPolyLine->numVerts();
	AcGePoint3d Start_temp_PT,End_temp_PT;
	for (int index=0; index<num; index++)
	{
		if (pPolyLine->segType(index) == AcDbPolyline::kLine)
		{
			AcGeLineSeg3d tempLine;
			pPolyLine->getLineSegAt(index,tempLine);
			Start_temp_PT = tempLine.startPoint();
			End_temp_PT = tempLine.endPoint();
			PointArray.append(Start_temp_PT);
			PointArray.append(End_temp_PT);
		}
		else if (pPolyLine->segType(index) == AcDbPolyline::kArc)
		{
			AcGeCircArc2d tempArc;
			pPolyLine->getArcSegAt(index,tempArc);
			Start_temp_PT.set(tempArc.startPoint().x,tempArc.startPoint().y,0);
			End_temp_PT.set(tempArc.endPoint().x,tempArc.endPoint().y,0);
			PointArray.append(Start_temp_PT);
			PointArray.append(End_temp_PT);
		}
	}
	pEnt_Temp->close();
	AcGeIntArray IndexArray;
	for (int i=1; i<PointArray.length();i++)
	{
		if (PointArray[i] == PointArray[i-1])
		{
			IndexArray.append(i);
			PointArray.remove(PointArray[i]);
		}
	}
}

void Additional_Class::Get_PolyLine_Length( AcDbObjectId PolyLineId, AcGeDoubleArray &LengthArray )
{
	double PI=3.1415926535897932384626433832795;
	AcDbEntity *pEnt_Temp = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt_Temp, PolyLineId, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN POLYLINE ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbPolyline::desc()))
	{
		acutPrintf(_T("\nENTITY NOT POLYLINE"));
		return;
	}
	AcDbPolyline *pPolyLine = AcDbPolyline::cast(pEnt_Temp);
	int num = pPolyLine->numVerts();
	for (int index=0; index<num; index++)
	{
		if (pPolyLine->segType(index) == AcDbPolyline::kLine)
		{
			AcGeLineSeg3d tempLine;
			pPolyLine->getLineSegAt(index,tempLine);
			double LineLength = tempLine.length();
			LengthArray.append(LineLength);
		}
		else if (pPolyLine->segType(index) == AcDbPolyline::kArc)
		{
			AcGeCircArc2d tempArc;
			pPolyLine->getArcSegAt(index,tempArc);
			double StartAngle = tempArc.startAng();
			double EndAngle = tempArc.endAng();
			double Angle = EndAngle-StartAngle;
			//Angle = (180/PI)*Angle;
			double Radius = tempArc.radius();
			double ArcLength = Radius*Angle;
			LengthArray.append(ArcLength);
		}
	}
	LengthArray.insertAt(0,0);
}

void Additional_Class::Get_PolyLineType( AcDbObjectId PolyLineId,LINEINFO &LineInfo_List )
{
	double PI=3.1415926535897932384626433832795;
	AcDbEntity *pEnt_Temp = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt_Temp, PolyLineId, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN POLYLINE ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbPolyline::desc()))
	{
		acutPrintf(_T("\nENTITY NOT POLYLINE"));
		return;
	}
	AcDbPolyline *pPolyLine = AcDbPolyline::cast(pEnt_Temp);
	int num = pPolyLine->numVerts();
	LineInfo_List.push_back("");
	for (int index=0; index<num; index++)
	{
		if (pPolyLine->segType(index) == AcDbPolyline::kLine)
		{
			CString tempStr_Line;
			tempStr_Line = "直线段";
			LineInfo_List.push_back(tempStr_Line);
		}
		else if (pPolyLine->segType(index) == AcDbPolyline::kArc)
		{
			AcGeCircArc2d tempArc;
			pPolyLine->getArcSegAt(index,tempArc);
			double StartAngle = tempArc.startAng();
			double EndAngle = tempArc.endAng();
			double Angle = abs(EndAngle-StartAngle);
			Angle = (180/PI)*Angle;
			double Radius = tempArc.radius();
			CString tempStr_Angle,tempStr_Radius,sita,du,banjing;
			sita = "θ=";
			du = "°";
			banjing = "R=";
			tempStr_Angle.Format(_T("%.1f"),Angle);
			tempStr_Angle = sita+tempStr_Angle+du;
			tempStr_Radius.Format(_T("%.1f"),Radius);
			tempStr_Radius = banjing + tempStr_Radius;
			tempStr_Radius = tempStr_Angle+" "+tempStr_Radius;
			LineInfo_List.push_back(tempStr_Radius);
		}
	}
}

void Additional_Class::Get_PolyLineCoor( AcGePoint3dArray PointArray, LINEINFO &X_Coor_List,LINEINFO &Y_Coor_List )
{
	for (int index=0; index<PointArray.length(); index++)
	{
		CString tempStr;
		tempStr.Format(_T("%.2f"),PointArray[index].x);
		X_Coor_List.push_back(tempStr);
		tempStr.Format(_T("%.2f"),PointArray[index].y);
		Y_Coor_List.push_back(tempStr);
	}
}

void Additional_Class::Get_PolyLineFirst( CString First_P, AcGeDoubleArray LineLengthList, LINEINFO &First_List )
{
	AcGeDoubleArray Total_Length;
	int num = LineLengthList.length();
	for (int index=0; index<num; index++)
	{
		double total_temp = 0;
		for (int i =0; i<=index; i++)
		{
			total_temp = total_temp + LineLengthList[i];
		}
		Total_Length.append(total_temp);
	}
	//////////////////////////////////////////////////////////////////////////
	num = Total_Length.length();
	for (int index=0; index<num; index++)
	{
		double temp_Double;
		temp_Double = Total_Length[index];
		CString temp_CStr;
		temp_CStr.Format(_T("%.2f"),temp_Double);
		int temp_CStr_len = temp_CStr.GetLength();
		if (temp_CStr_len > 6)
		{
			CString temp_String;
			int Num_P = temp_CStr_len-6;
			for (int ro=0; ro<Num_P; ro++)
			{
				CString tt = temp_CStr.GetAt(ro);
				temp_String.Append(tt);
				//temp_String.Insert(0,temp_CStr.GetAt(ro));
			}

			CString Last_String;
			for (int ro = Num_P; ro<temp_CStr_len; ro++)
			{
				CString tt = temp_CStr.GetAt(ro);
				Last_String.Append(tt);
			}
			Last_String.Insert(0,_T("+"));
			int temp_len = temp_String.GetLength();
			CString result_String;
			int x = 0;
			for (int index=0;index<temp_len;index++)
			{
				int roo = x/3;
				if (roo == 1)
				{
					CString tempt = temp_String.GetAt(temp_len-index-1);
					result_String.Insert(0,_T("+"));
					result_String.Insert(0,tempt);
					x=0;
				}
				CString temptt = temp_String.GetAt(temp_len-index-1);
				result_String.Insert(0,temptt);
				x = x+1;
			}

			result_String.Insert(0,First_P);
			result_String.Append(Last_String);
			First_List.push_back(result_String);
		}//////////////////////////////////////////////////////////////////////////
		else
		{
			int Num_S = 5 - temp_CStr_len;
			CString Zero;
			Zero.Append(First_P);
			Zero.Append(_T("0+"));
			for (int num_roo=0; num_roo<=Num_S; num_roo++)
			{
				Zero.Append(_T("0"));
			}
			Zero.Append(temp_CStr);
			First_List.push_back(Zero);
		}
	}
}

void Additional_Class::TransFrom( AcGeDoubleArray LineLength, LINEINFO &LengthStr)
{
	for (int index=0; index<LineLength.length(); index++)
	{
		double tempDouble;
		tempDouble = LineLength[index];
		CString tempStr;
		tempStr.Format(_T("%.2f"),tempDouble);
		LengthStr.push_back(tempStr);
	}	
}

void Additional_Class::Change_TablePoint( AcDbObjectId TableID,AcGePoint3d newPt )
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, TableID, AcDb::kForWrite)!= Acad::eOk)
	{
		acutPrintf(_T("\nOPEN TABLE ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbTable::desc()))
	{
		acutPrintf(_T("\nENTITY NOT TABLE"));
		return;
	}
	AcDbTable *pTableChange;
	pTableChange = AcDbTable::cast(pEnt_Temp);
	pTableChange->setPosition(newPt);
	pEnt_Temp->close();
	pTableChange->close();
	return;
}

void Additional_Class::Get_ArcMiddle( AcDbObjectId PolyLineId, AcGePoint3dArray &Middle_List,AcGePoint3dArray &CenterListInput, LINEINFO &ArcInfoRList, LINEINFO &ArcInfoAList )
{
	double PI=3.1415926535897932384626433832795;
	AcDbEntity *pEnt_Temp = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt_Temp, PolyLineId, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ENTITY ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbPolyline::desc()))
	{
		acutPrintf(_T("\nENTITY NOT POLYLINE"));
		return;
	}
	AcDbPolyline *pPolyLine = AcDbPolyline::cast(pEnt_Temp);
	int num = pPolyLine->numVerts();
	AcGePoint3d Start_temp_PT,End_temp_PT;
	AcGePoint3dArray Center_List;
	for (int index=0; index<num; index++)
	{
		if (pPolyLine->segType(index) == AcDbPolyline::kArc)
		{
			AcGeCircArc2d tempArc;
			pPolyLine->getArcSegAt(index,tempArc);
			AcGePoint2d CenterPoint;
			CenterPoint = tempArc.center();
			AcGePoint3d CenterPoint3d;
			CenterPoint3d.set(CenterPoint.x, CenterPoint.y, 0);
			Center_List.append(CenterPoint3d);
			AcGePoint3d Start_temp_PT, End_temp_PT;
			Start_temp_PT.set(tempArc.startPoint().x,tempArc.startPoint().y,0);
			End_temp_PT.set(tempArc.endPoint().x,tempArc.endPoint().y,0);
			AcGeVector3d tempVec;
			tempVec = End_temp_PT - Start_temp_PT;
			double tempVec_Len = tempVec.length();
			tempVec.normalize();
			tempVec = tempVec*(tempVec_Len/2);
			AcGeVector3d CenterVec;
			CenterVec = Start_temp_PT - CenterPoint3d;
			CenterVec = CenterVec + tempVec;
			AcGeLine2d CenterLine2d;
			AcGePoint3d Middle_Pt_OnLine;
			Middle_Pt_OnLine = CenterPoint3d+CenterVec;
			AcGePoint2d middle2d;
			middle2d.set(Middle_Pt_OnLine.x, Middle_Pt_OnLine.y);
			CenterLine2d.set(CenterPoint, middle2d);

			int s;
			AcGePoint2d MiddlePT, pt2;
			tempArc.intersectWith(CenterLine2d, s,  MiddlePT, pt2);
			AcGePoint3d MiddlePoint;
			MiddlePoint.set(MiddlePT.x,MiddlePT.y,0);
			Middle_List.append(MiddlePoint);

			double StartAngle = tempArc.startAng();
			double EndAngle = tempArc.endAng();
			double Angle = EndAngle-StartAngle;
			Angle = (180/PI)*Angle;
			double Radius = tempArc.radius();
			CString tempStr_Angle,tempStr_Radius,sita,du,banjing;
			sita = "θ=";
			du = "°";
			banjing = "R=";
			tempStr_Angle.Format(_T("%.1f"),Angle);
			tempStr_Angle = sita+tempStr_Angle+du;
			tempStr_Radius.Format(_T("%.1f"),Radius);
			tempStr_Radius = banjing + tempStr_Radius;
			ArcInfoRList.push_back(tempStr_Radius);
			ArcInfoAList.push_back(tempStr_Angle);
		}
	}
	CenterListInput = Center_List;
}

bool Additional_Class::LaylerFilter( CString LaylerName, AcDbObjectIdArray &EntityID_Array, bool(*Filter)(AcDbEntity*, AcDbObjectId&) )
{
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTbl,AcDb::kForWrite);
	if (false == (pLayerTbl->has(LaylerName)))
	{
		//acutPrintf("\n木有%s层！", LaylerName);
		//SetError("THERE ISTN`T"+LaylerName+"LAYER！", "LaylerFilter");
		pLayerTbl->close();
		return false;
	}
	AcDbObjectId layerId;
	pLayerTbl->getAt(LaylerName,layerId);

	AcDbBlockTable *pBlkTbl;
	//获得当前数据库块表
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl,AcDb::kForWrite);
	
	//获得模型空间块表记录
	AcDbBlockTableRecord *pBlkTblRcd;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);

	//创建块表记录遍历器
	AcDbBlockTableRecordIterator *pltr;
	pBlkTblRcd->newIterator(pltr);

	AcDbEntity *pEnt;
	AcDbObjectId temp_layerId;
	AcDbObjectId entityID;
	//pBlkTblRcd->close();
	//pBlkTbl->close();
	//pLayerTbl->close();
	for (pltr->start(); !pltr->done(); pltr->step())
	{
		if(Acad::eOk ==pltr->getEntity(pEnt, AcDb::kForRead, false))
		{
			//if (200>Check_Entity(pEnt)>=100)
			//{
			temp_layerId = pEnt->layerId();
			if (temp_layerId == layerId)		// 在当前图层中
			{
				entityID = pEnt->objectId();
				if (Filter(pEnt, entityID) == true)  // 符合过滤条件
				{
					EntityID_Array.append(entityID);
				}
			}
			//}
			pEnt->close();
		}
	}
	int Len = EntityID_Array.length();
	if (Len == 0)
	{
		pBlkTbl->close();
		pLayerTbl->close();
		pBlkTblRcd->close();
		return false;
	}
	pBlkTbl->close();
	pLayerTbl->close();
	pBlkTblRcd->close();
	return true;
}

bool Additional_Class::LaylerFilter( AcDbObjectIdArray &EntityID, bool(*Filter)(AcDbEntity*, AcDbObjectId&) )
{
	// 遍历所有图层符合规则的实体返回ID列表
	bool RunState = false;
	AcDbObjectIdArray LayerID_Array;
	vector<CString> LayerName_Array;
	AcDbObjectIdArray tempIDList;
	AcDbLayerTable *pLayerTbl;
	AcDbLayerTableRecord *pLayerTblRcd;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTbl,AcDb::kForWrite);
	AcDbLayerTableIterator *pltr;
	pLayerTbl->newIterator(pltr);	// 图层遍历器
	ACHAR *layerName;
	
	for (pltr->start(); !pltr->done(); pltr->step())
	{
		pltr->getRecord(pLayerTblRcd,AcDb::kForRead);
		pLayerTblRcd->getName(layerName);	// 得到图层名称
		LayerName_Array.push_back(layerName);
		//pLayerTbl->getAt(layerName,layerId); // 得到图层ID
		//LayerID_Array.append(layerId);	// 得到所有图层的ID列表
	}
	pLayerTbl->close();
	pLayerTblRcd->close();
	// 对每层实体进行遍历
	for (int i=0; i<LayerName_Array.size(); i++)
	{
		RunState = LaylerFilter(LayerName_Array.at(i), EntityID, Filter);
	}
	//for (pltr->start(); !pltr->done(); pltr->step())
	//{
	//	// 遍历所有图层开始
	//	pltr->getRecord(pLayerTblRcd,AcDb::kForRead);
	//	pLayerTblRcd->getName(layerName);	// 得到图层名称
	//	pLayerTbl->getAt(layerName,layerId);
	//	for (pltrX->start(); !pltrX->done(); pltrX->step())
	//	{
	//		if(Acad::eOk ==pltrX->getEntity(pEnt, AcDb::kForRead, false))
	//		{
	//			if (200>Check_Entity(pEnt)>=100)
	//			{
	//				temp_layerId = pEnt->layerId();
	//				if (temp_layerId == layerId)
	//				{
	//					entityID = pEnt->objectId();
	//					if (Filter(pEnt, entityID) == true)
	//					{
	//						EntityID.append(entityID);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	
	//	//RunState = LaylerFilter(layerName, tempIDList, Filter);
	//	//if (RunState == true)
	//	//{
	//	//	for (int j = 0; j<tempIDList.length(); j++)
	//	//	{
	//	//		EntityID.append(tempIDList[j]);
	//	//	}
	//	//}
	//}
	//pLayerTblRcd->close();
	//pLayerTbl->close();
	//pBlkTbl->close();
	//pBlkTblRcd->close();
	delete pltr;
	return false;
}

int Additional_Class::Get_NumPolyLine(AcDbPolyline *PolyLineEntity )
{
	return PolyLineEntity->numVerts();
}

bool Additional_Class::PolyLineIfRectangle( AcDbPolyline *PolyLineEntity )
{
	AcGePoint3dArray tempPt_List;
	AcGePoint3d Start_temp_PT,End_temp_PT;
	if (PolyLineEntity->isClosed())
	{
		int Num = Get_NumPolyLine(PolyLineEntity);
		if (Num == 4)
		{
			for (int i = 0; i<Num; i++)
			{
				if (PolyLineEntity->segType(i) == AcDbPolyline::kLine);
				{
					AcGeLineSeg3d tempLine;
					PolyLineEntity->getLineSegAt(i,tempLine);
					Start_temp_PT = tempLine.startPoint();
					End_temp_PT = tempLine.endPoint();
					tempPt_List.append(Start_temp_PT);
					tempPt_List.append(End_temp_PT);
				}
				if (PolyLineEntity->segType(i) == AcDbPolyline::kArc)
				{
					return false;
				}
			}
			for (int i=2; i<8; i=i+2)
			{
				AcGeVector3d v1,v2;
				v1 = tempPt_List[i-1] - tempPt_List[i-2];
				v2 = tempPt_List[i+1] - tempPt_List[i];
				if (v1.isPerpendicularTo(v2)==Adesk::kFalse )
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	return false;
}

void Additional_Class::Get_RectangleLW( AcDbPolyline *PolyLineEntity, double &Length, double &Width )
{
	double temp[2];
	if (PolyLineIfRectangle(PolyLineEntity) == false)
	{
		acutPrintf(_T("Bom Error 1001\n"));// 不是矩形
		return;
	}
	int Num = Get_NumPolyLine(PolyLineEntity);
	for (int i = 0; i<2; i++)
	{
		AcGeLineSeg3d tempLine;
		PolyLineEntity->getLineSegAt(i,tempLine);
		temp[i] = tempLine.length();
	}
	Length = temp[0];
	Width = temp[1];
}

bool Additional_Class::Get_LayerLW( CString LayerName, double &Length, double &Width )
{
	AcDbLayerTable *pLayerTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pLayerTbl,AcDb::kForRead);
	if (!pLayerTbl->has(LayerName))
	{
		//acutPrintf("\n木有%s层！", LayerName);
		//SetError("THERE ISN`T"+LayerName+"LATYER！",  "Get_LayerLW");
		pLayerTbl->close();
		return false;
	}
	AcDbObjectId layerId;
	pLayerTbl->getAt(LayerName, layerId);
	pLayerTbl->close();
	AcDbBlockTable *pBlkTbl = NULL;
	////获得当前数据库块表
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl,AcDb::kForWrite);
	////获得模型空间块表记录
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();

	////创建块表记录遍历器

	AcDbBlockTableRecordIterator *pltr;
	pBlkTblRcd->newIterator(pltr);

	AcDbEntity *pEnt;
	//AcDbEntityPointer pEnt_Ptr;
	////AcDbObjectPointer<AcDbPolyline> pPolyLine_Ptr;
	AcDbPolyline *pPolyLine = NULL;
	AcDbObjectIdArray PolyLineID_List;
	for (pltr->start(); !pltr->done(); pltr->step())
	{
		pltr->getEntity(pEnt, AcDb::kForRead);
	//	//pEnt_Ptr.acquire(pEnt);
		if (pEnt->layerId()==layerId)
		{
			if (pEnt->isKindOf(AcDbPolyline::desc()))
			{
				pPolyLine = AcDbPolyline::cast(pEnt);
				if (pPolyLine != NULL)
				{
					if (PolyLineIfRectangle(pPolyLine)==true)
					{
						PolyLineID_List.append(pPolyLine->objectId());
					}
				}
			}
		}
	}

	if (PolyLineID_List.length() >1)
	{
		acutPrintf(_T("Bom Error 1002\n"));// 有很多矩形
		delete pltr;
		pEnt->close();
		pPolyLine->close();
		pBlkTblRcd->close();
		return false;
	}
	////pPolyLine.open(PolyLineID_List[0], AcDb::kForRead);
	acdbOpenAcDbEntity(pEnt,PolyLineID_List[0], AcDb::kForRead);	//error!
	pPolyLine =  AcDbPolyline::cast(pEnt);
	Get_RectangleLW(pPolyLine, Length, Width);
	pBlkTblRcd->close();
	pPolyLine->close();
	pEnt->close();
	delete pltr;
	return true;
}



// void Additional_Class::SetError( CString ErrorState, CString FuncName )
// {
// 	m_Error = make_tuple(ErrorState,FuncName);
// }

void Additional_Class::Open_BlockTable( AcDbBlockTable* &pBlockTable, int ReadMode )
{
	if(ReadMode == NREADMODE)
	{
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	}
	else
	{
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForWrite);
	}
}

void Additional_Class::Open_ModelTableRecord(AcDbBlockTableRecord* &pBlkTblRcd, AcDbBlockTable* &pBlkTbl, int ReadMode)
{
	if(ReadMode == NREADMODE)
	{
		pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	}
	else
	{
		pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);
		//acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForWrite);
	}
}

CString Additional_Class::SplitString( CString str, char split, CString& LastStr )
{
	int iSubStrs;
	int iPos = 0;
	int iNums = 0;
	CString strTemp = str;
	CString strRight;
	while(iPos != -1)
	{
		iPos = strTemp.Find(split);
		if (iPos == -1)
		{
			break;
		}
		strRight = strTemp.Mid(iPos+1, str.GetLength());
		strTemp = strRight;
		iNums++;
	}

	if (iNums == 0)
	{
		iSubStrs = 1;
		return "";
	}
	iSubStrs = iNums + 1;
	CString* pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = str;
	CString strLeft;
	for (int i = 0; i<iNums; i++)
	{
		iPos = strTemp.Find(split);
		strLeft = strTemp.Left(iPos);
		strRight = strTemp.Mid(iPos+1, strTemp.GetLength());
		strTemp = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNums] = strTemp;
	LastStr = strRight;
//	ResArray.Append(strLeft);
	return *pStrSplit;
}

AcDbObjectIdArray Additional_Class::Select_Entitys( CString ScreenPrint )
{
	AcDbObjectIdArray resArray;
	//ads_name &RtEntity = NULL;
	AcDbEntity *pEnt;
	AcDbPoint RtPoint;
	ads_name ss;
	ads_point ff;
	//acedGetPoint(NULL,"ss",ff);
	//ff = asPnt3d(RtPoint.x, RtPoint.y, RtPoint.z);
	acedEntSel(ScreenPrint, ss, ff);
	//Select_Entity_Ent("ss",pEnt,RtPoint);
	return resArray;
}

bool Additional_Class::ReadFileL(CString Dir_ConfigFile, vector<CString> &FileData)
{
	CStdioFile FileHandle;
	bool RunState;
	RunState = FileHandle.Open(Dir_ConfigFile, CFile::modeRead|CFile::typeText);
	if (RunState == true)
	{
		CString TextContent;
		while(FileHandle.ReadString(TextContent))
		{
			FileData.push_back(TextContent);
		}
		return true;
	}
	return false;
}

void Additional_Class::Open_ORTHOMODE( void )
{
	resbuf var;
	if(RTNORM == acedGetVar(_T("ORTHOMODE"), &var))
	{
		if( var.resval.rint == 1)
		{
			return;
		}
		else
		{
			var.resval.rint = 1;
			acedSetVar(_T("ORTHOMODE"), &var);
			return;
		}
	}
	return;
}

void Additional_Class::Close_ORTHOMODE( void )
{
	resbuf var;
	if(RTNORM == acedGetVar(_T("ORTHOMODE"), &var))
	{
		if( var.resval.rint == 1)
		{
			var.resval.rint = 0;
			acedSetVar(_T("ORTHOMODE"), &var);
			return;
		}
		else
		{
			return;
		}
	}
	return;
}

int Additional_Class::GetMAXPt( int pos, AcGePoint3dArray PtList )
{
	AcGePoint3d tempPT;
	if (PtList.length() == 0)
	{
		return 0;
	}
	tempPT = PtList[0];
	int res;
	for (int i = 0; i<PtList.length(); i++)
	{
		if(PtList[i][pos] > tempPT[pos])
		{
			tempPT = PtList[i];
			res = i;
		}
	}
	return res;
}

int Additional_Class::GetMINPt( int pos, AcGePoint3dArray PtList )
{
	AcGePoint3d tempPT;
	if (PtList.length() == 0)
	{
		return 0;
	}
	tempPT = PtList[0];
	int res;
	for (int i = 0; i<PtList.length(); i++)
	{
		if(PtList[i][pos] < tempPT[pos])
		{
			tempPT = PtList[i];
			res = i;
		}
	}
	return res;
}

AcGePoint3d Additional_Class::Get_CenterPt( AcDbObjectId ObjID )
{
	AcDbEntity *pEnt = NULL;
	AcGePoint3d ptMax, ptMin, ptRes;
	ptRes.set(0,0,0);
	if	(Acad::eOk == acdbOpenAcDbEntity(pEnt, ObjID, AcDb::kForWrite))
	{
		AcDbExtents pEntExtent;
		pEnt->getGeomExtents(pEntExtent);
		ptMax = pEntExtent.maxPoint();
		ptMin = pEntExtent.minPoint();
		ptRes.x = (ptMax.x + ptMin.x)/2;
		ptRes.y = (ptMax.y + ptMin.y)/2;
		ptRes.z = (ptMax.z + ptMin.z)/2;
	}
	pEnt->close();
	return ptRes;
}

AcDbObjectId Additional_Class::Draw_Rectangle( AcGePoint2d stPt, double length, double height )
{
	AcDbPolyline *pPolyline = new AcDbPolyline(4);
	AcGePoint2d stPt1, stPt2, stPt3, stPt4;
	stPt1 = stPt;
	pPolyline->addVertexAt(0, stPt1, 0, 0, 0);
	stPt2.x = stPt.x +length;
	stPt2.y = stPt.y;
	pPolyline->addVertexAt(1, stPt2, 0, 0, 0);
	stPt3.x = stPt2.x;
	stPt3.y = stPt2.y + height;
	pPolyline->addVertexAt(2, stPt3, 0, 0, 0);
	stPt4.x = stPt3.x - length;
	stPt4.y = stPt3.y;
	pPolyline->addVertexAt(3, stPt4, 0, 0, 0);
	pPolyline->setClosed(Adesk::kTrue);
	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_BlockTable(pBlockTable, NREADMODE);
	AcDbBlockTableRecord *pBlockTableRecord = NULL;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	//acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_ModelTableRecord(pBlockTableRecord, pBlockTable, NWRITEMODE);
	AcDbObjectId TempLineID;
	pBlockTableRecord->appendAcDbEntity(TempLineID, pPolyline);
	pPolyline->close();
	pBlockTable->close();
	pBlockTableRecord->close();
	return TempLineID;
}

BOOL Additional_Class::Get_LineTypeID( CString linetype, AcDbObjectId &linetypeid )
{
	AcDbLinetypeTable *pLtpTbl;
	acdbHostApplicationServices()->workingDatabase()->getLinetypeTable(pLtpTbl,AcDb::kForRead);
	if (!pLtpTbl->has((linetype	)))
	{
		pLtpTbl->close();
		return FALSE;
	}
	pLtpTbl->getAt(linetype, linetypeid);
	pLtpTbl->close();
	return TRUE;
}

BOOL Additional_Class::Add_LineType( CString linetype )
{
	AcDbLinetypeTable *pLtpTbl;
	acdbHostApplicationServices()->workingDatabase()->getLinetypeTable(pLtpTbl,AcDb::kForRead);
	if (pLtpTbl->has((linetype	)))
	{
		pLtpTbl->close();
		return TRUE;
	}
	pLtpTbl->close();
	Acad::ErrorStatus es;
	es	= acdbHostApplicationServices()->workingDatabase()->loadLineTypeFile(linetype, _T("ZWCADiso.lin"));
	return TRUE;
}

int Additional_Class::GetCountOrder( double Num )
{
	double tempNum = Num;
	if (Num == 0)
	{
		return 1;
	}
	if (Num<0)
	{
		tempNum = -tempNum;
	}
	if(0 < tempNum && tempNum < 1)
	{
		return 1;
	}
	int ord = 1;
	int roo = tempNum/10;
	while(roo > 1)
	{
		tempNum = tempNum/10;
		roo = tempNum;
		ord = ord + 1;
	}
	return ord;
}

double Additional_Class::CalLineTypeScale( double Len )
{
	double a = Len;
	int b = GetCountOrder(Len);
	double res;
	res = a*pow(10., -2);
	return res;
}

bool Additional_Class::PolyLineHasCruve( AcDbPolyline *PolyLineEntity )
{
	//AcDbObjectIterator *PolyIter;
	int PolyNum = Get_NumPolyLine(PolyLineEntity);
	for (int i=0; i<PolyNum; i++)
	{
		 if(PolyLineEntity->segType(i) == AcDbPolyline::kArc)
		 {
			 return true;
		 }
	}
	return false;
}

AcDbObjectId Additional_Class::Draw_Arc( AcGePoint3d CenterPt, double RadiusArc, double StartAngle, double EndAngle )
{
	AcDbArc *pArcTemp = new AcDbArc();
	pArcTemp->setCenter(CenterPt);
	pArcTemp->setRadius(RadiusArc);
	pArcTemp->setStartAngle(StartAngle);
	pArcTemp->setEndAngle(EndAngle);
	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_BlockTable(pBlockTable, NREADMODE);
	AcDbBlockTableRecord *pBlockTableRecord = NULL;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	//acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	//this->Open_ModelTableRecord(pBlockTableRecord, pBlockTable, NWRITEMODE);
	AcDbObjectId TempArcID;
	pBlockTableRecord->appendAcDbEntity(TempArcID, pArcTemp);
	pArcTemp->close();
	pBlockTable->close();
	pBlockTableRecord->close();
	return TempArcID;
}

bool Additional_Class::BlkHasRef( CString RefName )
{
	// 判断该名称的块定义是否存在
	AcDbBlockTable *pBlkTbl;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);
	CString strBlkDef;
	strBlkDef.Format(_T("%s"), RefName);
	if (pBlkTbl->has(strBlkDef) == true)
	{
		pBlkTbl->close();
		return true;
	}
	pBlkTbl->close();
	return false;
}

void Additional_Class::SetCurLayler( CString LaylerName )
{
	AcDbDatabase *pCurDb = NULL;
	pCurDb = acdbHostApplicationServices()->workingDatabase();
	/*pCurDb->setClayer()*/

	int n = 0;//判断是否找到图层
	//////////////////////////////////////////////////////////////////////////
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pLayerTbl, AcDb::kForWrite);

	// 建立图层遍历器
	AcDbLayerTableIterator *pLayerIterator;
	pLayerTbl->newIterator(pLayerIterator);
	//
	AcDbLayerTableRecord *pLayerTableRcd;
	
	ACHAR *pLtName;
	ACHAR *pLtNameTT;
	CString pLtNameStr;
	for (; !pLayerIterator->done(); pLayerIterator->step()) 
	{
		pLayerIterator->getRecord(pLayerTableRcd, AcDb::kForWrite);
		pLayerTableRcd->getName(pLtName);
		pLayerTableRcd->close();
		pLtNameStr = pLtName;
		if (pLtNameStr == LaylerName)
		{
			pCurDb->setClayer(pLayerTableRcd->id());
			free(pLtName);
			n = 1;//如果图层找到，则将n赋值为1
			delete pLayerIterator;
			pLayerTbl->close();
			return;
		}
		else
		{
			free(pLtName);
		}
	}

	if (n == 0)
	{
		// 新建图层
		AcDbLayerTableRecord *pLayerTableRecordTT = new AcDbLayerTableRecord;
		pLayerTableRecordTT->setName(LaylerName);
		AcDbObjectId pLayerId;
		pLayerTbl->add(pLayerId, pLayerTableRecordTT);
		pLayerTableRecordTT->getName(pLtNameTT);
		pLayerTableRecordTT->close();
		//struct resbuf pResult;
		//::acedGetVar(_T("CLAYER"),&pResult);//取得当前图层
		//char *p = (LPSTR)(LPCTSTR)LaylerName;
		//pResult.resval.rstring = pLtNameTT;
		//int s=acedSetVar(_T("CLAYER"), &pResult);//将输入的图层设为当前层
		//相当于命令 CLAYER LAYERNAME
		//acutPrintf(_T("\nLinetype name is:  %s"), pResult.resval.rstring);
		//acutPrintf(_T("\nLinetype name is:  %d"), s);
		
		n = 1;//如果图层找到，则将n赋值为1
		delete pLayerIterator;
		pLayerTbl->close();
		struct resbuf pResults;
		::acedGetVar(_T("CLAYER"),&pResults);//取得当前图层
		//pLtNameTT = "0";
		pResults.resval.rstring = pLtNameTT;
		::acedSetVar(_T("CLAYER"), &pResults);//将输入的图层设为当前层
		free(pLtNameTT);
	}
	
	// acutPrintf(_T("\nLinetype name"));
	// acutPrintf(_T("\nLinetype name is:  %s"), pResult.resval.rstring);
}

void Additional_Class::SetCurLayler( AcDbObjectId curlayerID)
{
	AcDbDatabase *pCurDb = NULL;
	pCurDb = acdbHostApplicationServices()->workingDatabase();
	pCurDb->setClayer(curlayerID);
	return;
}

void Additional_Class::Set_ObjectColor( AcDbObjectId ObID, int ColorIndex )
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, ObID, AcDb::kForWrite) != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ERROR"));
		return;
	}
// 	ZcGeMatrix3d tt;
// 	tt.setToRotation(PI)
// 	pEnt_Temp->transformBy()
	//if (!pEnt_Temp->isKindOf(AcDbText::desc()))
	//{
	//	acutPrintf(_T("\nENTITY IS NOT TEXT"));
	//	return;
	//}
	pEnt_Temp->setColorIndex(ColorIndex);

	pEnt_Temp->close();
	return;
}

void Additional_Class::Set_ObjectColor( AcDbObjectIdArray obIDArray, int ColorIndex )
{
	AcDbObjectId tempID;
	for (int i=0; i<obIDArray.length(); i++)
	{
		 tempID = obIDArray.at(i);
		 Set_ObjectColor(tempID, ColorIndex);
	}
	//
	//AcDbEntity *pEnt_Temp;
	//if (acdbOpenAcDbEntity(pEnt_Temp, ObID, AcDb::kForWrite) != Acad::eOk)
	//{
	//	acutPrintf(_T("\nOPEN ERROR"));
	//	return;
	//}
	//pEnt_Temp->setColorIndex(ColorIndex);

	//pEnt_Temp->close();
	return;
}

void Additional_Class::RotateEnt( AcDbObjectId EntID, double RotateAng, AcGePoint3d InpPt)
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, EntID, AcDb::kForWrite) != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ERROR"));
		return;
	}
	 AcGeMatrix3d tt;
	 AcGeVector3d zAxis;
	 zAxis.set(0,0,1);
	tt.setToRotation(RotateAng, zAxis, InpPt);
	pEnt_Temp->transformBy(tt);
	pEnt_Temp->close();
}

bool Additional_Class::FindLayer( CString LaylerName )
{
	int n = 0;//判断是否找到图层
	//////////////////////////////////////////////////////////////////////////
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pLayerTbl, AcDb::kForWrite);

	// 建立图层遍历器
	AcDbLayerTableIterator *pLayerIterator;
	pLayerTbl->newIterator(pLayerIterator);
	//
	AcDbLayerTableRecord *pLayerTableRcd;
	ACHAR *pLtName;
	ACHAR *pLtNameTT;
	CString pLtNameStr;
	for (; !pLayerIterator->done(); pLayerIterator->step()) 
	{
		pLayerIterator->getRecord(pLayerTableRcd, AcDb::kForWrite);
		pLayerTableRcd->getName(pLtName);
		pLayerTableRcd->close();
		pLtNameStr = pLtName;
		if (pLtNameStr == LaylerName)
		{
			return true;
		}
		else
		{
			free(pLtName);
		}
	}
	return false;
}

void Additional_Class::ErrorBox( CString TextError, HWND MyHandle)
{
	MessageBox(MyHandle, TextError, _T("ERROR!"), 0);
}

void Additional_Class::WriteReg(LPCTSTR data_Set, CString ValueName, CString NewValue)
{
	HKEY hKey;
	LPSTR tempKey;
	LPBYTE tempLPB;
	DWORD type_1 = REG_SZ;//定义字符串数据类型
	LPBYTE owner_Get = new BYTE[80];
	DWORD cbData_1 = 80;

	//long ret0 = (::RegOpenKeyExA(HKEY_CURRENT_USER,data_Set,0,KEY_READ,&hKey));
	long ret0 = (::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_READ,&hKey));
	//
	ret0 = ::RegQueryValueEx(hKey, ValueName, NULL, &type_1, owner_Get, &cbData_1);
	
	if (ret0 != ERROR_SUCCESS)
	{
		long ret1 = ::RegCreateKey(HKEY_CURRENT_USER, data_Set,  &hKey);
		if (ret1 != ERROR_SUCCESS)
		{
			acutPrintf(_T("\n创建路径失败！"));
			return;
		}
		CString m_strOwner;m_strOwner=NewValue;
		tempLPB= CString2LPBYTE(m_strOwner);//定义值
		
		DWORD cbData_1= m_strOwner.GetLength()+1;//定义数据长度
		//ret1=::RegSetValueEx(hKey, ValueName,NULL,1,tempLPB,cbData_1);
		//RegSetValueEx()
		ret1 = ::RegSetValueEx(hKey, ValueName, NULL, 1, tempLPB, cbData_1);
		::RegCloseKey(hKey);
		return;
	}
	::RegCloseKey(hKey);
	
	// 再次打开路径
	ret0 = ::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_WRITE,&hKey);
	if (ret0 != ERROR_SUCCESS)
	{
		acutPrintf(_T("\n打开注册表失败！"));
		return;
	}
	//
	
	tempLPB= CString2LPBYTE(NewValue);//定义用户姓名 owner_Set
	DWORD NewValueLen = NewValue.GetLength()+1;//定义数据长度
	// 
	//RegSetKeyValue(HKEY_CURRENT_USER, data_Set, ValueName, type_1, tempLPB, NewValueLen);
	//long ret1= ::RegSetValue(HKEY_CURRENT_USER, data_Set, ValueName, type_1, tempLPB, NewValueLen);
	//::RegSetKeyValueA();

	//long ret1= ::RegSetValueA(HKEY_CURRENT_USER, data_Set, type_1, NewValue, NewValueLen);
	long ret3=::RegSetValueEx(hKey, ValueName,NULL,1,tempLPB,NewValueLen);
	//::RegSetKeyValueW(HKEY_CURRENT_USER, data_Set, ValueName, type_1, tempLPB, NewValueLen);
	if(ret3 != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("错误：无法设置有关的注册表信息"));
	}

	::RegCloseKey(hKey);
	//ret1=::RegSetValueEx(hKey,"RegisteredOwner",NULL,type_1,owner_Set,cbData_1);
	/*if(ret1!=ERROR_SUCCESS)
	{
		AfxMessageBox("错误：无法设置有关的注册表信息");
		return;
	}*/
	
}

void Additional_Class::ReadReg( LPCTSTR data_Set, CString ValueName, CString & ReadStr )
{
	HKEY hKey;   
	LONG rc;   
	DWORD dwType;   
	DWORD dwLogFile   =  10;

	rc   =   RegOpenKeyEx(HKEY_CURRENT_USER,   data_Set, REG_OPTION_NON_VOLATILE, KEY_WRITE, &hKey);
	//RegOpenKey()
	//rc = RegOpenKeyEx(HKEY_CURRENT_USER, data_Set, 0, 0, hKey);
	if (rc != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("错误：无法打开有关的注册表信息"));
		return;
	}
	LPBYTE owner_Get = new BYTE[80];
	DWORD type_1 = REG_SZ;
	DWORD cbData_1 = 10;
	
	LONG ret1 = ::RegQueryValueEx(hKey, ValueName, NULL, &type_1, owner_Get, &cbData_1);
	
	//::RegGetValueA(hKey, data_Set, )
	if (ret1 != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("错误：无法读取有关的注册表信息"));
		return;
	}

	ReadStr = owner_Get;
	::RegCloseKey(hKey);
	return;
}

AcDbObjectId Additional_Class::GetCurLayler()
{
	AcDbDatabase *pCurDb = NULL;
	pCurDb = acdbHostApplicationServices()->workingDatabase();
	return pCurDb->clayer();
}

bool Additional_Class::CheckReg( LPCTSTR data_Set, CString ValueName)
{
	HKEY hKey;
	LPSTR tempKey;
	LPBYTE tempLPB;
	DWORD type_1 = REG_SZ;//定义字符串数据类型
	LPBYTE owner_Get = new BYTE[80];
	DWORD cbData_1 = 80;

	long ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_READ,&hKey));
	ret0 = ::RegQueryValueEx(hKey, ValueName, NULL, &type_1, owner_Get, &cbData_1);
	if (ret0 != ERROR_SUCCESS)
	{
		//::RegCloseKey(hKey);
		return false;
	}
	::RegCloseKey(hKey);
	return true;
}

bool Additional_Class::CheckReg( LPCTSTR data_Set, CString ValueName, CString &resStr )
{
	HKEY hKey;
	LPSTR tempKey;
	LPBYTE tempLPB;
	DWORD type_1 = REG_SZ;//定义字符串数据类型
	LPBYTE owner_Get = new BYTE[80];
	DWORD cbData_1 = 80;
	resStr = "";

	long ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_READ,&hKey));
	ret0 = ::RegQueryValueEx(hKey, ValueName, NULL, &type_1, owner_Get, &cbData_1);
	if (ret0 != ERROR_SUCCESS)
	{
		//::RegCloseKey(hKey);
		return false;
	}
	::RegCloseKey(hKey);
	resStr = owner_Get;
	return true;
}

CString Additional_Class::Get_Xdata(AcDbObjectId EntID, CString Xdata_Ref )
{
	AcDbEntity *pEnt;
	acdbOpenAcDbEntity(pEnt, EntID, AcDb::kForRead);
	struct resbuf *pRb;
	pRb = pEnt->xData(Xdata_Ref);
	if (pRb != NULL)
	{
		struct resbuf *pTemp;
		pTemp = pRb;
		pTemp = pTemp->rbnext;
		pEnt->close();
		return pTemp->resval.rstring;
	}
	acutRelRb(pRb);
	pEnt->close();
	return "";
}

void Additional_Class::addXdata( AcDbObjectId entID, CString xdataStr )
{
	AcDbEntity * pEnt;
	struct resbuf * pRb;

	if(Acad::eOk != acdbOpenAcDbEntity(pEnt, entID, AcDb::kForWrite))
	{
		pEnt->close();
		return;
	}
	

	TCHAR strAppName[] = _T("JMBraring");
	acdbRegApp(strAppName);
	
	TCHAR  * typeName = CString2TCHAR(xdataStr);

	struct resbuf * pTemp;
	pTemp = pEnt->xData(strAppName);
	

	pRb = acutBuildList(AcDb::kDxfRegAppName, strAppName,
		AcDb::kDxfXdAsciiString, typeName, 
		RTNONE);
	
	pEnt->setXData(pRb);
	
	acutRelRb(pRb);
	acutRelRb(pTemp);
	pEnt->close();
	
	return;
}

void Additional_Class::addXdata( AcDbObjectId entID, CString xdataStr, CString xdataNameStr )
{
	AcDbEntity * pEnt;
	struct resbuf * pRb;

	if(Acad::eOk != acdbOpenAcDbEntity(pEnt, entID, AcDb::kForWrite))
	{
		pEnt->close();
		return;
	}
	TCHAR * tempTchar = CString2TCHAR(xdataNameStr);
	//TCHAR strAppName[] = tempTchar;
	acdbRegApp(tempTchar);
	TCHAR  * typeName = CString2TCHAR(xdataStr);

	struct resbuf * pTemp;
	pTemp = pEnt->xData(tempTchar);

	pRb = acutBuildList(AcDb::kDxfRegAppName, tempTchar,
		AcDb::kDxfXdAsciiString, typeName, 
		RTNONE);
	pEnt->setXData(pRb);

	acutRelRb(pRb);
	pEnt->close();
	return;
}



AcDbObjectIdArray Additional_Class::ObjectXdataFilter( CString XdataName, CString Xdata )
{
	//// 遍历所有图层符合规则的实体返回ID列表
	AcDbObjectIdArray resID;

	//AcDbObjectIdArray tempIDList;

	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	////this->Open_BlockTable(pBlockTable, NREADMODE);
	AcDbBlockTableRecord *pBlockTableRecord = NULL;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

	//AcDbObjectIterator pltr;
	AcDbBlockTableRecordIterator * pltr2;
	pBlockTableRecord->newIterator(pltr2);
	////pBlockTable->newIterator(pltr);
	AcDbEntity * pEnt;
	CString tempStrEnt;
	for (pltr2->start(); !pltr2->done(); pltr2->step())
	{
		//pltr2.getEntity()
		if(Acad::eOk == pltr2->getEntity(pEnt, AcDb::kForRead, false))
		{
			pEnt->close();
			tempStrEnt = Get_Xdata(pEnt->id(), XdataName);
			if (tempStrEnt == Xdata)
			{
				resID.append(pEnt->id());
			}
		}
		//pEnt->close();
	}
	pEnt->close();
	pBlockTable->close();
	pBlockTableRecord->close();


	delete pltr2;
	return resID;
}

void Additional_Class::SetLayerIsOff( CString strLayerName)
{
	AcDbLayerTable *pLayTbl = NULL; 
	acdbCurDwg()->getLayerTable(pLayTbl, AcDb::kForWrite); 
	if(!pLayTbl->has(strLayerName)) 
	{ 
		pLayTbl->close(); //该图层不存在 
		return; 
	} 

	AcDbLayerTableRecord *pLayTblRec = NULL; 
	AcDbObjectId objId; 
	pLayTbl->getAt(strLayerName, pLayTblRec, AcDb::kForWrite); 
	pLayTbl->close(); 

	//pLayTblRec->isInUse();
	
	if (pLayTblRec==NULL) 
	{ 
		return; 
	} 
	bool tempBool = pLayTblRec->isOff();
	if (tempBool == false)
	{
		pLayTblRec->setIsOff(true); 
	}
	else
	{
		pLayTblRec->setIsOff(false);
	}
	pLayTblRec->close(); 
	return; 
}

bool Additional_Class::IsAcDbCurve( AcDbObjectId EntID )
{
	AcDbEntity *pEnt_Temp;
	if (acdbOpenAcDbEntity(pEnt_Temp, EntID, AcDb::kForWrite)!= Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ENETITY ERROR"));
		//pEnt_Temp->close();
		return false;
	}
	if (pEnt_Temp->isKindOf(AcDbLine::desc()))
	{
		acutPrintf(_T("\nENTITY IS Line"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbArc::desc()))
	{
		acutPrintf(_T("\nENTITY IS Arc"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbCircle::desc()))
	{
		acutPrintf(_T("\nENTITY IS Circle"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbPolyline::desc()))
	{
		acutPrintf(_T("\nENTITY IS Polyline"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbRay::desc()))
	{
		acutPrintf(_T("\nENTITY IS Ray"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbSpline::desc()))
	{
		acutPrintf(_T("\nENTITY IS Spline"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbXline::desc()))
	{
		acutPrintf(_T("\nENTITY IS xline"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbEllipse::desc()))
	{
		acutPrintf(_T("\nENTITY IS Ellipse"));
		pEnt_Temp->close();
		return true;
	}
	if (pEnt_Temp->isKindOf(AcDbLeader::desc()))
	{
		acutPrintf(_T("\nENTITY IS Leader"));
		pEnt_Temp->close();
		return true;
	}
	pEnt_Temp->close();
	acutPrintf(_T("\nENTITY IS NOT Curve"));
	return false;
}


