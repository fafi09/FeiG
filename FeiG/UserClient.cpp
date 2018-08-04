#include "StdAfx.h"
#include "UserClient.h"
#include "feigdef.h"

CUserClient::CUserClient(void)
{
}


CUserClient::~CUserClient(void)
{
}


// ��ʼ���ͻ���
BOOL CUserClient::InitClient(void)
{
	return TRUE;
}


BOOL CUserClient::InitClient(HWND hwnd)
{
	//����socket
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

	//���ù㲥����
	BOOL bBroadcast = TRUE;
	setsockopt(m_ClientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(bBroadcast));

	//ΪclientSocket��һ������
	SOCKADDR_IN	addrClient	= {0};
	addrClient.sin_family	= AF_INET;
	//addrClient.sin_addr.s_addr	= inet_addr("192.168.1.119");
	addrClient.sin_addr.s_addr	= inet_addr("10.1.4.156");
	addrClient.sin_port	= 0;	/// 0 ��ʾ��ϵͳ�Զ�����˿ں�
	if (0 != bind (m_ClientSocket, (sockaddr*)&addrClient, sizeof(addrClient)))
	{
		printf ("bind failed.ip=[%s] errno=[%d]\n", "192.168.1.119", WSAGetLastError());
	}
	return TRUE;
}


// �㲥
BOOL CUserClient::Broadcast(void)
{
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(USERSERVER_PORT);

	addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);

	//255.255.255.255
	//CHAR* pszIP = inet_ntoa(addr.sin_addr);


	USERBROADCAST user = {0};
	user.header.nCmdID = NETCMDID_USERBROADCAST;
	user.header.nVersion = 1;
	user.header.nDataLength = sizeof(user) - sizeof(NETHEADER);

	DWORD nlen = 128;
	GetComputerName(user.szName,&nlen);

	wcscpy(user.szSign, TEXT("hello"));

	// ���뷢�ͻ��壬���ջ���ͬʱ����
	//The WSARecvFrom function does not work when a buffer counter greater than one is specified and the receiving datagram size exceeds 1,470 bytes.
	int nSndBufSet=32*1024;//����Ϊ32K
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
