#include "TCPServer.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
CTCPServer::CTCPServer()
{
	m_IsInit = false;
	m_IsStart = false;
	m_IsConnect = false;
	m_IsClose = false;
	m_RecvData = "";
	m_SendData = "";
}

CTCPServer::~CTCPServer()
{
	if (!m_IsClose) {
		Close();
	}
}

bool CTCPServer::Init(string ip, int port)
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		m_ErrData = "Failed to WSA Start up!";
		return false;
	}
	m_ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ListenSocket == INVALID_SOCKET) {
		m_ErrData = "Failed to build socket!";
		return false;
	}
	struct sockaddr_in sin;
	sin.sin_family = AF_INET; 
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = inet_addr(ip.c_str()); 

	if ((::bind(m_ListenSocket, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR))
	{
		m_ErrData = "Failed to bind socket! ";
		return false;
	}
	if (listen(m_ListenSocket, 20) == SOCKET_ERROR){
		m_ErrData = "Failed to set listen socket! ";
		closesocket(m_ListenSocket); 
		WSACleanup(); 
		return false;
	}
	m_IsInit = true;
	return true;
}

bool CTCPServer::Accept()
{
	struct sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr); 
	m_ClientSocket = accept(m_ListenSocket, (SOCKADDR*)&remoteAddr, &nAddrlen);
	if (m_ClientSocket == INVALID_SOCKET)
	{
		m_ErrData = "Failed to accept Client connect!";
		return false;
	}
	m_IsConnect = true;
	return true;
}

void CTCPServer::StartThread(string ip, int port)
{
	while (!m_IsClose) {
		if (!m_IsInit) {
			if (!Init(ip, port)) {
				continue;
			}
			m_IsStart = true;
		}
		if (!m_IsConnect) {
			if (!Accept()) {
				continue;
			}
		}
		break;
	}
}

bool CTCPServer::RecvThread()
{
	while (!IsConnect()) {
	}
	char revData[1025];
	int ret = 0;
	ret = recv(m_ClientSocket, revData, 1024, 0);
	if (ret <= 0) {
		m_ErrData = "Failed to receive data!";
		return false;
	}
	revData[ret] = '\0';
	m_RecvData = revData;
	return true;
}

thread CTCPServer::Start(string ip /*= DEFAULT_IP*/, int port /*= DEFAULT_PORT*/)
{
	thread t(mem_fn(&CTCPServer::StartThread), this, ip, port);
	return t;
}

bool CTCPServer::IsStart()
{
	return m_IsStart;
}

bool CTCPServer::IsConnect()
{
	return m_IsStart;
}

bool CTCPServer::IsClose()
{
	return m_IsClose;
}

bool CTCPServer::Close()
{
	m_IsInit = false;
	m_IsStart = false;
	m_IsConnect = false;
	m_IsClose = true;
	m_RecvData = "";
	m_SendData = "";
	if (m_ListenSocket != INVALID_SOCKET) {
		int ret = closesocket(m_ListenSocket); 
		if (ret != 0) {
			m_ErrData = "Failed to close listen socket!";
			return false;
		}
	}
	if (m_ClientSocket != INVALID_SOCKET) {
		int ret = closesocket(m_ClientSocket); 
		if (ret != 0) {
			m_ErrData = "Failed to close client socket!";
			return false;
		}
	}
	int ret = WSACleanup();
	if (ret != 0) {
		m_ErrData = "Failed to clean WSA!";
		return false;
	}
	return true;
}

bool CTCPServer::SendData(string data)
{
	int ret = send(m_ClientSocket, data.c_str(), strlen(data.c_str()), 0);
	if (ret != 0) {
		m_ErrData = "Failed to send data";
		return false;
	}
	return true;
}

string CTCPServer::GetRecvData(int timeOut)
{
	string data;
	int time = GetTickCount64();
	do 
	{
		if (!m_RecvData.empty()) {
			string temp = m_RecvData;
			m_RecvData = "";
			return temp;
		}
	} while (GetTickCount64() - time < timeOut);
	return "time out";
}

thread CTCPServer::RecvData()
{
	thread t(mem_fn(&CTCPServer::RecvThread), this);
	return t;

}
