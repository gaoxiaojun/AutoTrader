#include "StdAfx.h"
#include "RegeditIO.h"
#include <string.h>
#include <atlbase.h>

using namespace std;

CRegeditIO::CRegeditIO(void)
{
}


CRegeditIO::~CRegeditIO(void)
{
}

BOOL CRegeditIO::ReadRegSZ( HKEY root,CString path,CString name,CString& value )
{
	HKEY hAppKey;
	char szDataFile[MAX_PATH] = {""};

	if (ERROR_SUCCESS == RegOpenKeyEx(
		root,
		path,
		0,
		KEY_READ,
		&hAppKey))
	{
		ULONG cbSize = MAX_PATH*sizeof(TCHAR);
		DWORD dwFlag = RegQueryValueEx(
			hAppKey,
			name,
			NULL,
			NULL,
			(LPBYTE)szDataFile,&cbSize);
		RegCloseKey (hAppKey);
		if (ERROR_SUCCESS == dwFlag)
		{
			CString str;//(szDataFile); 
			str = szDataFile;
			//str.Format(_T("%s"), szDataFile);
			//theString = p;
			value = str;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CRegeditIO::WriteRegSZ( HKEY root,CString path,CString name,CString value )
{
	//打印设置
	LPBYTE pValue = CString_To_LPBYTE(value);
	DWORD cbData_1 = value.GetLength() + 1;

	int return_value = 0;
	HKEY  hkey;
	DWORD dwDisposition;
	long result=RegCreateKeyEx(
		root,          
		path,         
		0,             
		NULL,             
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,           
		&hkey,          
		&dwDisposition 
		);
	if(result==ERROR_SUCCESS)
	{
		result=RegSetValueEx(
			hkey,             
			name,    
			0,         
			REG_SZ,          
			pValue, 
			cbData_1);

		return_value = 1;
		RegCloseKey(hkey);
	}else
	{
		RegCloseKey(hkey);
	}
	if(!return_value)
	{
		return FALSE;
	}
	return return_value;
}

BOOL CRegeditIO::ReadRegDWORD( HKEY root,CString path,CString name, DWORD& value )
{
	HKEY hKey; 
	//打开注册表，不存在则创建。 
	long lRet= RegOpenKeyEx(root,path,NULL,KEY_READ,&hKey);
	if(lRet != ERROR_SUCCESS) 
	{
		return FALSE;
	}
	DWORD dwBufLen = sizeof(DWORD);

	long ret1=::RegQueryValueEx(
		hKey,
		name,
		NULL,
		NULL,
		(BYTE*)&value,
		&dwBufLen);
	if(ret1!=ERROR_SUCCESS)
	{
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}

BOOL CRegeditIO::WriteRegDWORD( HKEY root,CString path,CString name,DWORD value )
{
	HKEY hKey; 
	//打开注册表，不存在则创建。 
	long lRet = RegCreateKeyEx(root,path,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL); 
	if(lRet != ERROR_SUCCESS) 
	{
		return FALSE;
	}
	DWORD dwSize = sizeof(DWORD); 
	//修改键值，不存在则创建。 
	lRet = RegSetValueEx(hKey,name,0,REG_DWORD,(BYTE*)&value,dwSize); 
	if(lRet != ERROR_SUCCESS) 
	{ 
		return FALSE;
	}
	RegCloseKey(hKey); 
	return TRUE;
}

LPBYTE CRegeditIO::CString_To_LPBYTE( CString str )
{
	LPBYTE lpb=new BYTE[str.GetLength()+1];
	for(int i=0;i<str.GetLength();i++)
		lpb[i]=str[i];
	lpb[str.GetLength()] = '\0';

	return lpb;	
}

void CRegeditIO::WriteNetworkCardName( CString networkName )
{
	WriteRegSZ(HKEY_CURRENT_USER,_T("Software\\TradeMaster"),_T("NetworkAddress"),networkName);
}

void CRegeditIO::WriteNetworkCardDesc( CString networkdes )
{
	WriteRegSZ(HKEY_CURRENT_USER,_T("Software\\TradeMaster"),_T("NetworkAddressDes"),networkdes);
}

CString CRegeditIO::ReadNetworkCardName()
{
	CString* res = new CString();
	ReadRegSZ(HKEY_CURRENT_USER,_T("Software\\TradeMaster"),_T("NetworkAddress"),*res);
	return *res;
}
