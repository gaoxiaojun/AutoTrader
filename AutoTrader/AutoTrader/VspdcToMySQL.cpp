#include "StdAfx.h"
#include "VspdcToMySQL.h"


VspdcToMySQL::VspdcToMySQL(void)
{
}


VspdcToMySQL::~VspdcToMySQL(void)
{
}

int VspdcToMySQL::ConnMySQL( char *host,char * port,char * Db,char * user,char* passwd,char * charset,char * Msg )
{
	if( mysql_init(&mysql) == NULL )
	{
		Msg = "inital mysql handle error";
		return 1;
	}
	
	if (mysql_real_connect(&mysql,host,user,passwd,Db,0,NULL,0) == NULL)
	{
		Msg = "Failed to connect to database: Error";
		return 1;
	}
	if(mysql_set_character_set(&mysql,"GBK") != 0)
	{
		Msg = "mysql_set_character_set Error";
		return 1;
	}
	return 0;
}

string VspdcToMySQL::SelectData( char * SQL,int Cnum ,int Row,char * Msg )
{
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf(sql,SQL);
	int rnum = 0;
	char rg = 0x06;//行隔开
	char cg = {0x05};//字段隔开
	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "select ps_info Error";
		return "";
	}
	m_res = mysql_store_result(&mysql);
	if(m_res==NULL)
	{
		Msg = "select username Error";
		return "";
	}
	string str("");
	while(m_row = mysql_fetch_row(m_res))
	{
		for (int j = 0; j < Row; j++)
		{
			for(int i = 0;i < Cnum;i++)
			{
				str = str + m_row[i] + ",";
			}
		}
	}
	str += rg;
	str += rg;             
	rnum++;
	mysql_free_result(m_res);
	return str;
}

int VspdcToMySQL::InsertData( char * SQL,char * Msg )
{
	char sql[2048];
	sprintf(sql,SQL);
	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "Insert Data Error";
		return 1;
	}
	return 0;
}

int VspdcToMySQL::UpdateData( char * SQL,char * Msg )
{
	char sql[2048];
	sprintf(sql,SQL);
	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "Update Data Error";
		return 1;
	}
	return 0;
}

int VspdcToMySQL::DeleteData( char * SQL,char * Msg )
{
	char sql[2048];
	sprintf(sql,SQL);
	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "Delete Data error";
		return 1;
	}
	return 0;
}

void VspdcToMySQL::CloseMySQLConn()
{
	mysql_close(&mysql);	
}

vector<CString> VspdcToMySQL::GetDataVec( char * SQL,int Cnum ,int Row,char * Msg )
{
	vector<CString> res;

	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf(sql,SQL);
	int rnum = 0;
	char rg = 0x06;//行隔开
	char cg = {0x05};//字段隔开
	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "select ps_info Error";
		return res;
	}
	m_res = mysql_use_result(&mysql);
	if(m_res==NULL)
	{
		Msg = "select username Error";
		return res;
	}
	string str("");
	CString tempStr;
	//mysql_fetch_array
	//mysql_use_result()
	int ssres = mysql_num_rows(m_res);//返回结果集中的行数。
	int m_field_num = mysql_num_fields(m_res);
	MYSQL_FIELD *field; 
	unsigned int num_fields;
	unsigned int i;
	//Field m_field;
	//vector<Record> m_s;
	num_fields = mysql_num_fields(m_res);
	while(m_row = mysql_fetch_row(m_res))
	//for(int i=0; i<ssres;i++)
	{
		//Record temp(&m_field);
		str = "";
		for(int i = 0;i < num_fields-1;i++)
		{
			if (m_row[i] != NULL)
			{
				str = str + m_row[i]+',';
			}
 			else
 			{
 				str = str + 'N';str = str + 'U';str = str + 'L';str = str + 'L';str = str + ',';
 			}
			//temp.SetData(m_row[i]);
		}
		//m_s.push_back(temp);
		tempStr = str.c_str();
		res.push_back(tempStr);
	}         
	rnum++;
	mysql_free_result(m_res);
	return res;
}

int VspdcToMySQL::GetTableNum( CString tableName )
{
	int res = 0;
	char * Msg;

	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	CString SQL_Head = _T("select count(*) from ");
	CString SQL_Value = tableName;
	CString SQL_Tail = _T(";");
	CString SQL = SQL_Head + SQL_Value + SQL_Tail;
	char *sql = CString2CharPt(SQL);

	int rnum = 0;
	char rg = 0x06;//行隔开
	char cg = {0x05};//字段隔开
	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "select ps_info Error";
		return res;
	}

	m_res = mysql_use_result(&mysql);
	if(m_res==NULL)
	{
		Msg = "select username Error";
		return res;
	}

	string str("");
	CString tempStr;
	int ssres = mysql_num_rows(m_res);//返回结果集中的行数。
	int m_field_num = mysql_num_fields(m_res);
	MYSQL_FIELD *field; 
	unsigned int num_fields;
	unsigned int i;

	num_fields = mysql_num_fields(m_res);
	m_row = mysql_fetch_row(m_res);
	tempStr = m_row[0];
	mysql_free_result(m_res);
	//CString str("1234");
	res = _ttoi(tempStr);
	return res;
}

char* VspdcToMySQL::CString2CharPt( CString inputData )
{

	CString str = inputData;
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = str.GetLength();     // n = 14, len = 18
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len+1];   //以字节为单位
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP,0,str,str.GetLength() + 1 ,pFileName,len + 1 ,NULL,NULL);
	return pFileName;

}

void VspdcToMySQL::CleanTable( CString tableName )
{
	//delete from TableName
	char sql[2048];
	//sprintf(sql,SQL);
	CString SQL = _T("delete from ");
	SQL = SQL + tableName;
	if(mysql_query(&mysql,CString2CharPt(SQL)) != 0)
	{
		//Msg = "Delete Data error";
		return;
	}
	return;
}

