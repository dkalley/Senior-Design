#include "pch.h"

#include <windows.h>
#include <windef.h>
#include <bthdef.h>
#include <WinSock2.h>
#include <ws2def.h>

#include <ws2bth.h>
#include <bthsdpdef.h>
#include <BluetoothAPIs.h>
#include <cguid.h>
#include <initguid.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <vector>
#include <future>
#include <ctime> 
#include <chrono> 
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include "Player.h"

#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "bthprops.lib")
#pragma comment(lib, "irprops.lib")

#define SCANNING_STARTED 0
#define SCANNING_ENDED 1
#define MAX_CONNECTIONS 5
#define MAX_SOCKETS 6
#define MAX_EVENTS 6
#define SERVER_INDEX 0
#define CLIENT_START_INDEX 1
#define BUFFER_SIZE 16384
#define DEFAULT_PORT 4


#pragma once
class Bluetooth
{
public:
	HWND *sendfunction, *sendfunctiontxt, *recvfunction, *recvfunctiontxt;
	BOOL dummyworked;
	void Broadcast_GUID();
	void TestClient();
	int SDPGetPort(const char *addr, LPGUID guid);
	BOOL ERRORFLAG;

	Bluetooth();
	std::vector<LPWSAQUERYSET> device_service;
	std::vector<std::string> device_list_dummy;
	std::vector<BLUETOOTH_DEVICE_INFO> device_list;
	BLUETOOTH_DEVICE_INFO *devices;
	std::vector<BLUETOOTH_DEVICE_INFO> res;
	BLUETOOTH_DEVICE_SEARCH_PARAMS bdsp;
	BLUETOOTH_DEVICE_INFO bdi;
	HBLUETOOTH_DEVICE_FIND hbf;
	int scanning_status;
	SOCKET s, server_socket;
	SOCKADDR_BTH sab, sa;
	
	/* STUFF IM CURRENTLY USING */
	SOCKET ServerSocket;
	std::vector<SOCKET> ConnectedClients;
	SOCKET ClientSocket;
	SOCKADDR_BTH SocketAddress;
	//char *SendBuffer;
	BOOL SendFlag;
	BOOL SERVERFLAG;
	//int TestFlag;

	std::thread ThreadArray[MAX_SOCKETS];
	std::promise<void> ServerPromise;
	std::promise<void> PromiseArray[MAX_SOCKETS];
	SOCKET SocketsArray[MAX_SOCKETS];
	int TOTALCONNECTIONS, EventTotal;
	WSAEVENT EventArray[MAX_EVENTS];
	BOOL SendBufferFlag[MAX_CONNECTIONS];
	char SendBuffer[MAX_CONNECTIONS][BUFFER_SIZE];
	int ReceiveBufferFlag[MAX_CONNECTIONS];
	// Will be come a queue of 1024 byte buffers, when one fills place it into the vector
	// Create memory for a new buffer and continue to recv
	std::vector<char*> ReceiveQueue;
	
	char ReceiveBuffer[MAX_CONNECTIONS][BUFFER_SIZE];
	BOOL GlobalSendFlag, GlobalRecvFlag;
	BOOL SocketsActive[MAX_CONNECTIONS];
	BOOL ThreadsActive[MAX_CONNECTIONS];
	BOOL CloseThreads[MAX_CONNECTIONS];

	int Get_Index(Player **players, SOCKADDR_BTH newadd);
	void Close_All_Threads();
	void Close_All_Sockets();
	void ClearSendBuffer(int index);
	void SetSendBuffer(int index, char* sendstring);
	void ClearReceiveBuffer(int index);
	char* GetReceiveBuffer(int index, char* outbuffer);
	void temp_server(std::future<void> futureObj);
	void Make_Non_Blocking(SOCKET* BSocket);
	void Bluetooth_Start_Up();
	void Winsock_Startup();
	void Create_Socket(SOCKET *NewSocket);
	void Bind_Socket(SOCKET *BindSocket);
	void Setup_Listen(SOCKET *ListenSocket);
	void Get_Socket_Info(SOCKET SocketInfo, SOCKADDR_BTH* SockAdd);
	BOOL Accept_Connections(Player **players, SOCKET *ListenSocket);
	int Receive_Data(SOCKET ReceiveSocket, int index);
	BOOL Send_Blob_Data(SOCKET SendSocket, void *buff, int bufflen);
	void Send_Data(SOCKET SendSocket, int index);
	void Close_Socket(SOCKET CloseSocket);
	/* END OF STUFF IM CURRENTLY USING */

	void asynccontrolserver(std::future<void> futureObj);
	void asynccontrolclient(std::future<void> futureObj, int index);
	void Lookup_Devices();
	void scanDevices();
	std::string Pair_Device(BLUETOOTH_DEVICE_INFO device);
	void Initialize_Struct();
	void pop();
	int temp();

private:
};

