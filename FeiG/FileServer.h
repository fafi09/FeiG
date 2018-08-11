#pragma once
class CFileServer
{
public:
	CFileServer(void);
	virtual ~CFileServer(void);
	BOOL InitServer(void);
	static UINT FileThread(LPVOID pParam);
	void OnConnect(SOCKET clientsock, LPSTR pszID);
	SOCKET m_SvrSocket;
};

