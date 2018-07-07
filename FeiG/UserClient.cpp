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


	return TRUE;
}


// �㲥
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

	sendto(m_ClientSocket, (char*)&user ,sizeof(user),0, (struct sockaddr*)&addr, sizeof(addr));

	return TRUE;
}


//BOOL CUserClient::sendData(void)
//{
//}


BOOL CUserClient::sendData(CHAR* pszData, UINT nlen, LPCSTR pszIP)
{
	return TRUE;
}
