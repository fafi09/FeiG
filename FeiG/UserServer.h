#pragma once

#include "ChatView.h"
#include "UserView.h"
#include "feigdef.h"
class CUserServer
{
public:
	CUserServer(void);
	virtual ~CUserServer(void);
	SOCKET m_SvrSocket;
	CUserView *m_pUserView;
	CChatView *m_pChatView;
	BOOL InitServer(void);
	static UINT UserThread(LPVOID pParam);
	BOOL OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, TCHAR * pszIP);
	BOOL OnUserChat(LPUSERCHAT pUserChat, TCHAR* pszIP);
	BOOL OnUserQuit(LPUSERQUIT pUserQuit, TCHAR * pszIP);
};

