#pragma once
class CUserClient
{
public:
	CUserClient(void);
	virtual ~CUserClient(void);
	// 初始化客户端
	BOOL InitClient(void);
	SOCKET m_ClientSocket;
	BOOL InitClient(HWND hwnd);
	// 广播
	BOOL Broadcast(void);
//	BOOL sendData(void);
	BOOL sendData(CHAR* pszData, UINT nlen, LPCTSTR pszIP);
	BOOL SendChat(CString strIP, CString strData, BOOL bBroadcast);
	void UserQuit(void);
};

