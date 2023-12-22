#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include <winsock2.h>
#include <thread>
#include <functional>   // std::mem_fn


#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_IP "192.168.1.42"
#define DEFAULT_PORT 8888
#define DEFAULT_TIME_OUT 3000 // 3 seconds;

using namespace std;

class CTCPServer
{
public:
	CTCPServer();
	~CTCPServer();

private:
	bool Init(string ip, int port);
	bool Accept();
	void StartThread(string ip, int port);
	bool RecvThread();


public:
	bool IsStart();
	bool IsConnect();
	bool IsClose();

	thread Start(string ip = DEFAULT_IP, int port = DEFAULT_PORT);
	thread RecvData();
	bool Close();
	bool SendData(string data);
	string GetRecvData(int timeOut = DEFAULT_TIME_OUT);

private:
	bool m_IsInit;
	bool m_IsStart;
	bool m_IsConnect;
	bool m_IsClose;

	string m_ErrData;
	string m_RecvData;
	string m_SendData;
	SOCKET m_ListenSocket;
	SOCKET m_ClientSocket;

};