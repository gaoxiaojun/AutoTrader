#pragma once
#include <vector>

using namespace std;

class CRegeditIO
{
public:
	CRegeditIO(void);
	~CRegeditIO(void);

	LPBYTE CString_To_LPBYTE(CString str);
	BOOL ReadRegSZ(HKEY root,CString path,CString name,CString& value);
	BOOL WriteRegSZ(HKEY root,CString path,CString name,CString value);
	BOOL ReadRegDWORD(HKEY root,CString path,CString name, DWORD& value);
	BOOL WriteRegDWORD(HKEY root,CString path,CString name,DWORD value);

	void WriteNetworkCardName(CString networkName);
	void WriteNetworkCardDesc(CString networkdes);
	CString ReadNetworkCardName();
};

