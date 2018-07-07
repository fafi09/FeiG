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

	//循环接收消息
	while(1)
	{
		UDPPACKET packet = {0};
		struct sockaddr_in addr={0};
		int nformLen = sizeof(addr);
		recvfrom(pthis->m_SvrSocket, (char*)&packet, sizeof(packet),0, (sockaddr*)&addr, &nformLen);

		CHAR* pszIP = inet_ntoa(addr.sin_addr);
		wchar_t wszFromIp[64] = {0};  
		MultiByteToWideChar(CP_ACP, 0, pszIP, strlen(pszIP), wszFromIp, 64<<1); // 将其转换为宽字符的就可以了

		switch(packet.header.nCmdID)
		{
		case NETCMDID_USERBROADCAST:
			pthis->OnUserBroadcast((LPUSERBROADCAST)&packet, wszFromIp);
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
