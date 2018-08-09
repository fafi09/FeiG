#include "StdAfx.h"
#include "UserServer.h"


CUserServer::CUserServer(void)
{
}


CUserServer::~CUserServer(void)
{
}


BOOL CUserServer::InitServer(void)
{
	m_SvrSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == m_SvrSocket)
	{
		switch(WSAGetLastError())
		{
		case WSANOTINITIALISED:
			//MessageBox(hwnd,TEXT("WSANOTINITIALISED"),TEXT("INITIAL Server ERROR"),MB_OK);
			break;
		case WSAENETDOWN:
			break;
		case WSAEAFNOSUPPORT:
			break;
		case WSAEINPROGRESS:
			break;
		case WSAEMFILE:
			break;
		case WSAENOBUFS:
			break;
		case WSAEPROTONOSUPPORT:
			break;
		case WSAEPROTOTYPE:
			break;
		case WSAESOCKTNOSUPPORT:
			break;
		}
		return FALSE;
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(USERSERVER_PORT);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//绑定端口
	bind(m_SvrSocket, (struct sockaddr*)&addr, sizeof(addr));

	//开启线程接收消息
	AfxBeginThread(UserThread, this);
}


UINT CUserServer::UserThread(LPVOID pParam)
{
	CUserServer* pthis = (CUserServer*)pParam;

	unsigned   long   maxsize = 0;
	int size = sizeof(maxsize);
	getsockopt(pthis->m_SvrSocket,SOL_SOCKET,SO_MAX_MSG_SIZE,(char*)&maxsize,&size);

	int nRecvBuf = 0;
	int nRecvBufSize = sizeof(nRecvBuf);
	getsockopt(pthis->m_SvrSocket,SOL_SOCKET,SO_RCVBUF,(char*)&nRecvBuf,&nRecvBufSize);

	// 接收缓冲区
	// 必须发送缓冲，接收缓冲同时设置
	//The WSARecvFrom function does not work when a buffer counter greater than one is specified and the receiving datagram size exceeds 1,470 bytes.
	int nRecvBufSet=32*1024;//设置为32K
	setsockopt(pthis->m_SvrSocket,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBufSet,sizeof(int));

	getsockopt(pthis->m_SvrSocket,SOL_SOCKET,SO_RCVBUF,(char*)&nRecvBuf,&nRecvBufSize);
	//循环接收消息
	while(1)
	{
		UDPPACKET packet = {0};
		struct sockaddr_in addr={0};
		int nformLen = sizeof(addr);
		int ret = recvfrom(pthis->m_SvrSocket, (char*)&packet, sizeof(packet),0, (sockaddr*)&addr, &nformLen);

		if(ret == SOCKET_ERROR ) {
			int _i_err = WSAGetLastError();
			switch(_i_err)
			{
			case WSANOTINITIALISED:
				//MessageBox(hwnd,TEXT("WSANOTINITIALISED"),TEXT("INITIAL Server ERROR"),MB_OK);
				break;
			case WSAENETDOWN:
				break;
			case WSAEFAULT:
				break;
			case WSAEINTR:
				break;
			case WSAEINPROGRESS:
				break;
			case WSAEINVAL:
				break;
			case WSAEISCONN:
				break;
			case WSAENETRESET:
				break;
			case WSAENOTSOCK:
				break;
			case WSAEOPNOTSUPP:
				break;
			case WSAESHUTDOWN:
				break;
			case WSAEWOULDBLOCK:
				break;
			case WSAEMSGSIZE:
				break;
			case WSAETIMEDOUT:
				break;
			case WSAECONNRESET:
				break;
			}
			return FALSE;
		}

		CHAR* pszIP = inet_ntoa(addr.sin_addr);
		wchar_t wszFromIp[64] = {0};  
		MultiByteToWideChar(CP_ACP, 0, pszIP, strlen(pszIP), wszFromIp, 64<<1); // 将其转换为宽字符的就可以了

		switch(packet.header.nCmdID)
		{
		case NETCMDID_USERBROADCAST:
			pthis->OnUserBroadcast((LPUSERBROADCAST)&packet, wszFromIp);
			break;
		case NETCMDID_USERCHAT:
			pthis->OnUserChat((LPUSERCHAT)&packet,wszFromIp);
			break;
		case NETCMDID_USERQUIT:
			pthis->OnUserQuit((LPUSERQUIT)&packet,wszFromIp);
			break;
		}


	}


	return 0;
}


BOOL CUserServer::OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, TCHAR * pszIP)
{
	m_pUserView->AddUser(pUserBroadcast->szName, pszIP, pUserBroadcast->szSign);
	return TRUE;
}


BOOL CUserServer::OnUserChat(LPUSERCHAT pUserChat, TCHAR* pszIP)
{
	if(m_pChatView != NULL)
	{
		m_pChatView->AddChat(pUserChat->szChat, pszIP);
	}
	return TRUE;
}


BOOL CUserServer::OnUserQuit(LPUSERQUIT pUserQuit, TCHAR * pszIP)
{
	if(m_pUserView != NULL)
	{
		m_pUserView->DelUser(pszIP);
	}
	//关闭服务器端的socket
	//closesocket(m_SvrSocket);
	return TRUE;
}
