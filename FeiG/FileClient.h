#pragma once
class CFileClient
{
public:
	CFileClient(void);
	virtual ~CFileClient(void);
	BOOL InitClient(void);
	BOOL ConnectServer(LPCSTR pszSvrIP);
	BOOL SendFile(LPCTSTR pszFilePath, CStatic * pwnStaticSend, CProgressCtrl * pwndProgress);
	BOOL SendData(LPVOID pData, DWORD nLen);
	SOCKET m_ClientSocket;
};

