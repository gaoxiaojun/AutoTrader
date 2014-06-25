#pragma once
#include <stdio.h>
#include <string>
#include <afxsock.h>
#include "mysql.h"
#include <vector>

using   namespace   std;

// class Field
// {
// public:
// 	Field();
// 	~Field();
// 
// 	vector<string> m_name;
// 	vector<enum_field_types> m_type;
// 
// private:
// 
// };
// 
// 
// 
// class Record
// {
// public:
// 	Record();
// 	~Record();
// 	Record(Field *m_f);
// 
// 	vector<string> m_rs;
// 	Field *m_field;
// 
// 	void SetData(string value);
// 
// 
// };




class VspdcToMySQL
{
public:
	MYSQL mysql;
	VspdcToMySQL(void);
	~VspdcToMySQL(void);

	// 	主要的功能：
	// 		初始化数据库
	// 		连接数据库
	// 		设置字符集
	// 		入口参数：
	// 		host ：MYSQL服务器IP
	// port:数据库端口
	// 	 Db：数据库名称
	// 	 user：数据库用户
	// 	 passwd：数据库用户的密码
	// 	 charset：希望使用的字符集
	// Msg:返回的消息，包括错误消息
	// 	出口参数：
	// 	int ：0表示成功；1表示失败
	int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,char * Msg);
	// 	主要的功能：
	// 		入口参数：
	// 		SQL：查询的SQL语句
	// Cnum:查询的列数
	// Msg:返回的消息，包括错误消息
	// 	出口参数：
	// 	string 准备放置返回的数据，多条记录则用0x06隔开,多个栏位用0x05隔开
	// 	如果 返回的长度＝ 0，责表示舞结果
	string SelectData(char * SQL,int Cnum ,int Row,char * Msg);
	// 	主要功能：
	// 		SQL：查询的SQL语句
	/*Msg:返回的消息，包括错误消息*/
	/*	出口参数：*/
	/*	int ：0表示成功；1表示失败*/
	int InsertData(char * SQL,char * Msg);
	// 	主要功能：
	// 		SQL：查询的SQL语句
	// Msg:返回的消息，包括错误消息
	// 	出口参数：
	// 	int ：0表示成功；1表示失败
	int UpdateData(char * SQL,char * Msg);
	// 	主要功能：
	// 		SQL：查询的SQL语句
	// Msg:返回的消息，包括错误消息
	// 	出口参数：
	// 	int ：0表示成功；1表示失败
	int DeleteData(char * SQL,char * Msg);

	void CleanTable(CString tableName);
	// 	主要功能：
	// 		关闭数据库连接
	void CloseMySQLConn();
	//*************************************
	// 函数名:  	SelectData
	// 目的:	获取批量的数据
	// 时间：   2014/03/27
	//*************************************
	vector<CString> GetDataVec(char * SQL,int Cnum ,int Row,char * Msg);
	//*************************************
	// 函数名:  	GetTableNum
	// 目的:	获取表格行数
	// 时间：   2014/03/27
	//*************************************
	int GetTableNum(CString tableName);

	char* CString2CharPt(CString inputData);

};

