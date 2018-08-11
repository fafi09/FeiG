#include "StdAfx.h"
#include "FileClient.h"


CFileClient::CFileClient(void)
{
	
}


CFileClient::~CFileClient(void)
{
}


BOOL CFileClient::InitClient(void)
{
	m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_ClientSocket == INVALID_SOCKET )
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CFileClient::ConnectServer(LPCSTR pszSvrIP)
{
	SOCKADDR_IN addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_FILESVR);
	addr.sin_addr.S_un.S_addr = inet_addr(pszSvrIP);

	int retValue = connect(m_ClientSocket, (sockaddr*)&addr, sizeof(addr));

	if(retValue == SOCKET_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CFileClient::SendFile(LPCTSTR pszFilePath, CStatic * pwnStaticSend, CProgressCtrl * pwndProgress)
{
	//发送文件的大小名称等信息

}


BOOL CFileClient::SendData(LPVOID pData, DWORD nLen)
{
	LPSTR pTempData = (LPSTR)pData;
	DWORD nLeft = nLen;

	while(nLeft > 0)
	{
		int nSend = send(m_ClientSocket, pTempData, nLeft, 0);
		if(nSend == SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft = nLeft - nSend;
		pTempData = pTempData + nSend;
	}
}
