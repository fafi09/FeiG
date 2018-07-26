#include "StdAfx.h"
#include "UserClient.h"
#include "feigdef.h"

CUserClient::CUserClient(void)
{
}


CUserClient::~CUserClient(void)
{
}


// 初始化客户端
BOOL CUserClient::InitClient(void)
{
	return TRUE;
}


BOOL CUserClient::InitClient(HWND hwnd)
{
	//建立socket
	m_ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == m_ClientSocket)
	{
		switch(WSAGetLastError())
		{
		case WSANOTINITIALISED:
			MessageBox(hwnd,TEXT("WSANOTINITIALISED"),TEXT("INITIAL CLIENT ERROR"),MB_OK);
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

	//设置广播属性
	BOOL bBroadcast = TRUE;
	setsockopt(m_ClientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(bBroadcast));


	return TRUE;
}


// 广播
BOOL CUserClient::Broadcast(void)
{
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(USERSERVER_PORT);

	addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);

	USERBROADCAST user = {0};
	user.header.nCmdID = NETCMDID_USERBROADCAST;
	user.header.nVersion = 1;
	user.header.nDataLength = sizeof(user) - sizeof(NETHEADER);

	DWORD nlen = 128;
	GetComputerName(user.szName,&nlen);

	wcscpy(user.szSign, TEXT("hello"));

	// 必须发送缓冲，接收缓冲同时设置
	//The WSARecvFrom function does not work when a buffer counter greater than one is specified and the receiving datagram size exceeds 1,470 bytes.
	int nSndBufSet=32*1024;//设置为32K
	setsockopt(m_ClientSocket,SOL_SOCKET,SO_SNDBUF,(const char*)&nSndBufSet,sizeof(int));


	int ret = sendto(m_ClientSocket, (char*)&user ,sizeof(user),0, (struct sockaddr*)&addr, sizeof(addr));
	if(ret == SOCKET_ERROR ) {
		int _i_err = WSAGetLastError();
		switch(WSAGetLastError())
		{
		case WSAENOTSOCK:
			break;
		case WSANOTINITIALISED:
			//MessageBox(hwnd,TEXT("WSANOTINITIALISED"),TEXT("INITIAL Server ERROR"),MB_OK);
			break;
		case WSAENETDOWN:
			break;
		case WSAEACCES:
			break;
		case WSAEINVAL:
			break;
		case WSAEINTR:
			break;
		case WSAEINPROGRESS:
			break;
		case WSAEFAULT:
			break;
		case WSAENETRESET:
			break;
		case WSAENOBUFS:
			break;
		case WSAENOTCONN:
			break;
		case WSAEOPNOTSUPP:
			break;
		case WSAESHUTDOWN:
			break;
		case WSAEWOULDBLOCK:
			break;
		case WSAEMSGSIZE:
			break;
		case WSAEHOSTUNREACH:
			break;
		case WSAECONNABORTED:
			break;
		case WSAECONNRESET:
			break;
		case WSAEADDRNOTAVAIL:
			break;
		case WSAEAFNOSUPPORT:
			break;
		case WSAEDESTADDRREQ:
			break;
		case WSAENETUNREACH:
			break;
		case WSAETIMEDOUT:
			break;
		}
		return FALSE;
	}
	return TRUE;
}


//BOOL CUserClient::sendData(void)
//{
//}


BOOL CUserClient::sendData(CHAR* pszData, UINT nlen, LPCSTR pszIP)
{
	return TRUE;
}
