#include "pch.h"
#include "Bluetooth.h"

int TestFlag;
BOOL CALLBACK bluetoothAuthCallback(LPVOID param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS params);

DEFINE_GUID(RFCOMM_PROTOCOL_UUID, 0xbc50d0f9, 0xe51e, 0x4d7d, 0x97, 0xf6, 0x49, 0x1a, 0xa5, 0x11, 0x61, 0x05);

void Bluetooth::TestClient()
{
	WSADATA wsa;
	SOCKET s2;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}

	//Create a socket
	SocketsArray[CLIENT_START_INDEX] = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	//s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SocketsArray[CLIENT_START_INDEX] == INVALID_SOCKET)
	{
		return;
	}
	SOCKADDR_BTH s1;
	// Setup the Bluetooth listening socket
	//SerialPortServiceClassID_UUID16
	//s1.serviceClassId = SAMPLE_UUID;
	s1.serviceClassId = RFCOMM_PROTOCOL_UUID;
	s1.addressFamily = AF_BTH;
	s1.btAddr = 0xA402B94A39DA;// 0x00025bc1329e;
	//s1.port = 4;

	//Connect to remote server
	SOCKET testclient = connect(SocketsArray[CLIENT_START_INDEX], (struct sockaddr *)&s1, sizeof(s1));
	if (testclient == SOCKET_ERROR)
	{
		return;
	}

	Make_Non_Blocking(&SocketsArray[CLIENT_START_INDEX]);

	// Register a new Event for the new socket for Read, Write, and Close
	WSAEVENT NewEvent = WSACreateEvent();
	WSAEventSelect(SocketsArray[CLIENT_START_INDEX], NewEvent, FD_READ | FD_WRITE | FD_CLOSE);

	// Add the event to the total
	EventArray[1] = NewEvent;
	EventTotal++;
	SocketsActive[0] = true;
	std::future<void> futureObj = ServerPromise.get_future();
	asynccontrolclient(std::move(futureObj), 0);
	Close_All_Sockets();
	Close_All_Threads();

	return;
}

void Bluetooth::Broadcast_GUID()
{
	wchar_t host_name[100] = { 0 }, comment_name[100] = { 0 };
	char host[100];

	if (SOCKET_ERROR == gethostname(host, 100))
	{            
		dummyworked = false;
		return;
	}

	size_t size = strlen(host) + 1;
	size_t outSize1, outSize2;
	mbstowcs_s(&outSize1, host_name, size, host, size - 1);
	mbstowcs_s(&outSize2, comment_name, size, host, size - 1);

	SOCKADDR_BTH server = { 0 };
	int len = sizeof(SOCKADDR_BTH);
	getsockname(SocketsArray[SERVER_INDEX], (sockaddr *)&server, &len);

	CSADDR_INFO csAddr;
	memset(&csAddr, 0, sizeof(CSADDR_INFO));
	csAddr.LocalAddr.iSockaddrLength = sizeof(SOCKADDR_BTH);
	csAddr.LocalAddr.lpSockaddr = (sockaddr *)&server;
	csAddr.iSocketType = SOCK_STREAM;
	csAddr.iProtocol = BTHPROTO_RFCOMM;

	GUID UUID = RFCOMM_PROTOCOL_UUID;
	WSAQUERYSET service;
	memset(&service, 0, sizeof(WSAQUERYSET));
	service.dwSize = sizeof(WSAQUERYSET);
	service.lpszServiceInstanceName = (LPWSTR)L"TEST SERVICE";
	service.lpServiceClassId = &UUID;
	service.dwNameSpace = NS_BTH;
	service.dwNumberOfCsAddrs = 1;
	service.lpcsaBuffer = &csAddr;
	
	// As long as we use a blocking accept(), we will have a race
	// between advertising the service and actually being ready to
	// accept connections.  If we use non-blocking accept, advertise
	// the service after accept has been called.
	if (WSASetService(&service, RNRSERVICE_REGISTER, 0) == SOCKET_ERROR)
	{
		dummyworked = false;
		return;
	}

	dummyworked = true;
}


Bluetooth::Bluetooth()
{
	// Set Important Variables and flags
	SERVERFLAG = true;
	TOTALCONNECTIONS = 0;
	EventTotal = 0;
	dummyworked = false;

	// Start send as true
	GlobalSendFlag = true;
	GlobalRecvFlag = true;

	// Initialize all flag arrays to false
	for (int i = 0; i < MAX_CONNECTIONS; i++) 
	{
		ReceiveBufferFlag[i] = -1;
		SendBufferFlag[i] = false;
		SocketsActive[i] = false;
		ThreadsActive[i] = false;
		CloseThreads[i] = false;
		EventArray[i] = NULL;
	}

	// Initialize struct to scan for devices
	Initialize_Struct();
	ERRORFLAG = false;
}

// Used to send all threads the promise value and wait for them to close
void Bluetooth::Close_All_Threads()
{
	// Start at the last connect client and close to the server
	for (int i = TOTALCONNECTIONS - 1; i >= 0; i--)
	{
		// If the thread is active set promise
		// Wait for thread to close and continue
		if (ThreadsActive[i])
		{
			PromiseArray[i].set_value();
			ThreadArray[i].join();
		}
	}
}

// Once all threads have closed, make sure resources are freed for sockets
void Bluetooth::Close_All_Sockets()
{
	// Close all connected clients
	for (int i = TOTALCONNECTIONS; i > 0; i--)
	{
		// If the socket is active close it
		if (SocketsActive[i])
		{
			Close_Socket(SocketsArray[CLIENT_START_INDEX + i]);
		}
	}

	// Close Server socket
	Close_Socket(SocketsArray[SERVER_INDEX]);
}

// Should spawn an instance of this in a thread per client connection
// Looks for read, write and close events; asynchronous
void Bluetooth::asynccontrolclient(std::future<void> futureObj, int index)
{
	DWORD Event;
	WSANETWORKEVENTS NetworkEvents;

	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		// Wait for one of the sockets to receive I/O notification and
		if ((Event = WSAWaitForMultipleEvents(1, &EventArray[CLIENT_START_INDEX + index], FALSE, 2, FALSE)) == WSA_WAIT_FAILED)
		{
			return;
		}

		if (WSAEnumNetworkEvents(SocketsArray[CLIENT_START_INDEX + index], EventArray[CLIENT_START_INDEX + index], &NetworkEvents) == SOCKET_ERROR)
		{
			return;
		}

		// Try to read and write data to and from the data buffer if read and write events occur
		if (NetworkEvents.lNetworkEvents & FD_READ)
		{
			if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				GlobalRecvFlag = false;
				break;
			}
			else
			{			
				Receive_Data(SocketsArray[CLIENT_START_INDEX + index], index);
			}
		}

		// Try to read and write data to and from the data buffer if read and write events occur
		if (NetworkEvents.lNetworkEvents & FD_WRITE)
		{
			if (NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				GlobalSendFlag = false;
				break;
			}
			GlobalSendFlag = true;
		}
		if (SendBufferFlag[index] && GlobalSendFlag)
		{
			Send_Data(SocketsArray[CLIENT_START_INDEX + index], index);
		}
		if (NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
			{
				break;
			}

			Close_Socket(SocketsArray[CLIENT_START_INDEX + index]);
			WSACloseEvent(EventArray[CLIENT_START_INDEX + index]);
			SocketsActive[index] = false;
			CloseThreads[index] = true;
		}
	}

	return;
}

// Start winsock
void Bluetooth::Winsock_Startup()
{
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return;
	}

	return;
}

// Create a socket 
void Bluetooth::Create_Socket(SOCKET *NewSocket)
{
	*NewSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	if (*NewSocket == INVALID_SOCKET) {
		WSACleanup();
		return;
	}
	return;
}

// Bind a socket to look for bluetooth connections
void Bluetooth::Bind_Socket(SOCKET *BindSocket)
{
	//SOCKADDR_BTH sa;
	int iResult;

	// Setup the Bluetooth listening socket
	//sa.serviceClassId = RFCOMM_PROTOCOL_UUID;
	sa.addressFamily = AF_BTH;
	sa.btAddr = 0;
	sa.port = BT_PORT_ANY;
	iResult = bind(*BindSocket, (const sockaddr *)&sa, sizeof(SOCKADDR_BTH));
	if (iResult == SOCKET_ERROR) {
		closesocket(*BindSocket);
		WSACleanup();
		return;
	}

	return;
}

// Listen for upto max connections
void Bluetooth::Setup_Listen(SOCKET *ListenSocket)
{
	int iResult;

	WSAEVENT NewEvent = WSACreateEvent();
	WSAEventSelect(*ListenSocket, NewEvent, FD_ACCEPT | FD_CLOSE);

	EventArray[EventTotal] = NewEvent;
	EventTotal++;
	
	iResult = listen(*ListenSocket, MAX_CONNECTIONS);
	if (iResult == SOCKET_ERROR) {
		closesocket(*ListenSocket);
		WSACleanup();
		return;
	}	

	DWORD NonBlock = 1;
	if (ioctlsocket(*ListenSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	{
		return;
	}

	return;
}

// Get the address, port, and other info from a socket
void Bluetooth::Get_Socket_Info(SOCKET SocketInfo, SOCKADDR_BTH* SockAdd)
{
	int iResult;

	int sa_len = sizeof(*SockAdd);
	//iResult = getsockname(SocketInfo, (SOCKADDR *)sa, &sa_len);
	iResult = getpeername(SocketInfo, (SOCKADDR *)SockAdd, &sa_len);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(SocketInfo);
		WSACleanup();
		return;
	}
	
	return;
}

// Make a socket non-blocking
void Bluetooth::Make_Non_Blocking(SOCKET* BSocket)
{
	DWORD NonBlock = 1;
	if (ioctlsocket(*BSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	{
		ExitProcess(2);
	}
}

// Accept a connection
BOOL Bluetooth::Accept_Connections(Player **players, SOCKET* ListenSocket)
{
	SOCKADDR_BTH ca;
	int ca_len = sizeof(ca);
	wchar_t wtext[1024] = { 0 };
	LPWSTR ptr = wtext;

	DWORD buff_len = sizeof(wtext);
	SOCKET NewConnection= accept(*ListenSocket, (LPSOCKADDR)&ca, &ca_len);
	if (SOCKET_ERROR == NewConnection) {
		return -1;
	}
	WSAAddressToString((LPSOCKADDR)&ca, (DWORD)ca_len, NULL, ptr, &buff_len);


	// Check if the device has been connected before in this game	
	int realindex = Get_Index(players, ca);
	SocketsArray[realindex] = NewConnection;

	// Register a new Event for the new socket for Read, Write, and Close
	WSAEVENT NewEvent = WSACreateEvent();
	//EventArray[EventTotal] = WSACreateEvent();
	if (NewEvent == WSA_INVALID_EVENT)
	{
		return -1;
	}
	int result = WSAEventSelect(SocketsArray[realindex], NewEvent, FD_READ | FD_WRITE | FD_CLOSE);
	if (result == SOCKET_ERROR)
	{
		return -1;
	}

	// Add the event to the total
	EventArray[realindex] = NewEvent;
	
	// Create a new promise instance
	PromiseArray[realindex - 1] = std::promise<void>();
	std::future<void> futureObj = PromiseArray[realindex-1].get_future();
	//ThreadArray[TOTALCONNECTIONS] = std::thread(&Bluetooth::nonblocking_checks_client, this, std::move(futureObj), TOTALCONNECTIONS);
	ThreadArray[realindex-1] = std::thread(&Bluetooth::asynccontrolclient, this, std::move(futureObj), realindex-1);
	// Add connection to total
	SocketsActive[realindex-1] = true;

	//*NewSocket = client;
	return realindex;
}

int Bluetooth::Get_Index(Player **players, SOCKADDR_BTH newadd)
{
	int index;
	// Check if we already know the index
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		if (players[i] == nullptr)
			continue;

		SOCKADDR_BTH id = players[i]->get_bth_id();
		if (newadd.btAddr == id.btAddr)
		{
			index = players[i]->get_index();
			return index;
		}
	}
	
	// Otherwise index is the next connection
	TOTALCONNECTIONS++;
	return TOTALCONNECTIONS;
}

// Receive data from a socket
int Bluetooth::Receive_Data(SOCKET ReceiveSocket, int index)
{
	int received = 0, max_data_size = BUFFER_SIZE;
	int attempts = 0, bytes_received = 0;
	char buffer[500] = { 0 };
	char Errorbuffer[500] = { 0 };
	bool flag = false;
	ClearReceiveBuffer(index);

		wchar_t wbuffer[BUFFER_SIZE] = { 0 };
		wchar_t wrec[BUFFER_SIZE] = { 0 };
		size_t outsize;

	bool jsonflag = false;
	auto start = std::chrono::steady_clock::now();
	// Fill correct sockets mailbox with received data
	do
	{
		// Receive a large chunck of data
		received = recv(ReceiveSocket, ReceiveBuffer[index] + bytes_received, max_data_size, 0);
		
		// Recv ran into an error, attempt up to 5 tries and then return
		if (received == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			// No incoming data
			if (error == WSAEWOULDBLOCK)
			{
				//break;
			}
			
			continue;
		}
		// Socket Closed gracefully, No new data received
		if (received == 0)
		{
			if (max_data_size < BUFFER_SIZE)
				ReceiveBufferFlag[index] = true;
			return received;
		}
		// Move the pointer to the length of bytes recieved
		bytes_received += received;

		try
		{
			json message = json::parse(ReceiveBuffer[index]);
			jsonflag = true;
		}
		catch (json::exception e)
		{
			jsonflag = false;
		}

		//length -= received;
	} while (!jsonflag);
	//} while (length > 0);
	
	auto end = std::chrono::steady_clock::now();
	std::ofstream myfile;
	myfile.open("D://Users//theka//S//timing.txt", std::ofstream::app);
	myfile << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << std::endl;
	myfile.close();
	// Signal that the mailbox is full
	if (bytes_received > 0)
		ReceiveBufferFlag[index] = bytes_received;

	return received;
}

// Send blob data
BOOL Bluetooth::Send_Blob_Data(SOCKET SendSocket, void *buff, int bufflen)
{
	int BytesSent;
	char *pbuf = (char *)buff;

	while (bufflen > 0)
	{
		BytesSent = send(SendSocket, pbuf, bufflen, 0);

		if (BytesSent == SOCKET_ERROR)
		{
			// WSAEWOULDBLOCK means that the buffer is full 
			// Continue to try until the buffer empties
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				continue;
			}

			return false;
		}

		pbuf += BytesSent;
		bufflen -= BytesSent;
	}

	return true;
}

void Bluetooth::Send_Data(SOCKET SendSocket, int index)
{
	int iResult;
	int bytes_sent = 0;
	char buffer[500] = { 0 };

	size_t len = strlen(SendBuffer[index]);

	//json sendlength;
	//sendlength["length"] = len;	
	//
	//// If its a json it has an action element, otherwise now a json
	//if (SendBuffer[index][0] == '{')
	//{
	//	json waste = json::parse(SendBuffer[index]);
	//	sendlength["for_action"] = waste["action"].get<std::string>();
	//}
	//strcpy(buffer, sendlength.dump().c_str());
	//myfile << buffer << std::endl;

	
	///*
	//TESTBLOCK
	//*/
	wchar_t wbuffer[BUFFER_SIZE] = { 0 };
	wchar_t wrec[BUFFER_SIZE] = { 0 };
	memset(wbuffer, 0, BUFFER_SIZE);
	memset(wrec, 0, BUFFER_SIZE);

	size_t outsize;
	//mbstowcs_s(&outsize, wbuffer, buffer, BUFFER_SIZE);
	//wcscat_s(wrec, wbuffer);
	//wcscat_s(wrec, L"\r\n");
	//if (ERRORFLAG)
	//{
	//	SetWindowText(*sendfunctiontxt, L"");
	//	SetWindowText(*sendfunctiontxt, wrec);
	//}


	//int bufferlen = strlen(buffer);

	//iResult = send(SendSocket, buffer, bufferlen, 0);
	//std::this_thread::sleep_for(std::chrono::milliseconds(250));
	do 
	{
		iResult = send(SendSocket, SendBuffer[index] + bytes_sent, (int)len, 0);
		if (iResult == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				GlobalSendFlag = false;
				return;
			}

			return;
		}
		bytes_sent += iResult;
		len -= iResult;

	} while (len > 0);

	wcscat_s(wrec, L"Whole Message Sent\r\n");
	if (ERRORFLAG)
	{
		SetWindowText(*sendfunctiontxt, L"");
		SetWindowText(*sendfunctiontxt, wrec);
	}

	ClearSendBuffer(index);
	SendBufferFlag[index] = false;
	return;
}

void Bluetooth::Close_Socket(SOCKET CloseSocket)
{
	int iResult;

	iResult = closesocket(CloseSocket);

	if (SOCKET_ERROR == iResult)
	{
		return;
	}
	return;
}

void Bluetooth::ClearSendBuffer(int index)
{
	memset(SendBuffer[index], 0, BUFFER_SIZE);
	SendBufferFlag[index] = false;
}

void Bluetooth::SetSendBuffer(int index, char* sendstring)
{
	strcpy_s(SendBuffer[index], sendstring);
	SendBufferFlag[index] = true;
}

void Bluetooth::ClearReceiveBuffer(int index)
{
	memset(ReceiveBuffer[index], 0, BUFFER_SIZE);
	ReceiveBufferFlag[index] = -1;
}

char* Bluetooth::GetReceiveBuffer(int index, char* outbuffer)
{
	try
	{
		// Length of received string plus 1 for null character
		int outbufferlen = ReceiveBufferFlag[index] + 1;
		char *output = new char[outbufferlen];
		memset(output, 0, outbufferlen);
		strcpy_s(output, outbufferlen, ReceiveBuffer[index]);
		ClearReceiveBuffer(index);
		return output;
	}
	catch (const std::exception& e)
	{
		return nullptr;
	}
}

void Bluetooth::Initialize_Struct()
{
	// Initialize structs needed for bluetooth
	ZeroMemory(&bdsp, sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS));

	// set options for how we want to load our list of BT devices
	bdsp.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
	bdsp.fReturnAuthenticated = TRUE;
	bdsp.fReturnRemembered = TRUE;
	bdsp.fReturnUnknown = FALSE;
	bdsp.fReturnConnected = TRUE;
	bdsp.fIssueInquiry = TRUE;
	bdsp.cTimeoutMultiplier = 4;
	bdsp.hRadio = NULL;

	bdi.dwSize = sizeof(bdi);
}

void Bluetooth::pop()
{
	this->device_list_dummy.push_back("Gabe");
	this->device_list_dummy.push_back("Daniel");
	this->device_list_dummy.push_back("Erica");
	this->device_list_dummy.push_back("Logan");
}

void Bluetooth::scanDevices()
{
	// Signal scanning has started, clear device list
	scanning_status = SCANNING_STARTED;
	device_list.clear();

	// enumerate our bluetooth devices
	hbf = BluetoothFindFirstDevice(&bdsp, &bdi);

	// Loop until all devices have been touched
	if (hbf)
	{
		do
		{
			// Add the device to the list and continue
			device_list.push_back(bdi);
		} while (BluetoothFindNextDevice(hbf, &bdi));

		// close our device enumerator
		BluetoothFindDeviceClose(hbf);
	}

	// Signal scanning has finished
	scanning_status = SCANNING_ENDED;
}


void Bluetooth::Lookup_Devices()
{
	//scanning_status = SCANNING_STARTED;
	HANDLE hLookup;
	union {
		CHAR buf[5000];
		double __unused; // ensure proper alignment
	};
	LPWSAQUERYSET pwsaResults = (LPWSAQUERYSET)buf;
	DWORD dwSize = sizeof(buf);
	BOOL bHaveName;

	Winsock_Startup();

	// Set up Query Set
	WSAQUERYSET wsaq;
	//GUID UUID = SAMPLE_UUID;
	GUID UUID = RFCOMM_PROTOCOL_UUID;
	ZeroMemory(&wsaq, sizeof(wsaq));
	wsaq.dwSize = sizeof(wsaq);
	wsaq.dwNameSpace = NS_BTH;
	wsaq.lpcsaBuffer = NULL;
	//wsaq.lpServiceClassId = &UUID;

	if (ERROR_SUCCESS != WSALookupServiceBegin(&wsaq, LUP_CONTAINERS, &hLookup))
	{
		//scanning_status = SCANNING_ENDED;
		return;
	}

	ZeroMemory(pwsaResults, sizeof(WSAQUERYSET));
	pwsaResults->dwSize = sizeof(WSAQUERYSET);
	pwsaResults->dwNameSpace = NS_BTH;
	pwsaResults->lpBlob = NULL;

	while (ERROR_SUCCESS == WSALookupServiceNext(hLookup, LUP_RETURN_NAME | LUP_RETURN_ADDR | LUP_RETURN_TYPE,  &dwSize, pwsaResults))
	{
		device_service.push_back(pwsaResults);
		BTH_ADDR b = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
		SOCKADDR_BTH *a = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr);
		bHaveName = pwsaResults->lpszServiceInstanceName && *(pwsaResults->lpszServiceInstanceName);

		wchar_t wtext[1024] = { 0 };
		DWORD wtext_len = sizeof(wtext);
		DWORD a_len = sizeof(a);
		LPWSTR ptr = wtext;

		WSAAddressToString((LPSOCKADDR)a, a_len, NULL, ptr, &wtext_len);
		
	}
	WSALookupServiceEnd(hLookup);
	//scanning_status = SCANNING_ENDED;
	return;
}

// Code to pair, probably will use the windows dialog box instead
std::string Bluetooth::Pair_Device(BLUETOOTH_DEVICE_INFO device)
{
	// File is used for debugging
	std::wstring ws = device.szName;
	// register callback
	HBLUETOOTH_AUTHENTICATION_REGISTRATION hCallbackHandle = 0;
	DWORD result = BluetoothRegisterForAuthenticationEx(&device, &hCallbackHandle, (PFN_AUTHENTICATION_CALLBACK_EX)&bluetoothAuthCallback, NULL);

	if (result != ERROR_SUCCESS)
	{
		return "Failure";
	}

	// authenticate
	result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotRequired);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionRequired);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotRequiredBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionRequiredBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotRequiredGeneralBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionRequiredGeneralBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotDefined);
	switch (result)
	{
	case ERROR_SUCCESS:
		break;

	case ERROR_CANCELLED:
		break;

	case ERROR_INVALID_PARAMETER:
		break;

	case ERROR_NO_MORE_ITEMS:
		break;
	default:
		break;
	}
	return "success";
}

BOOL CALLBACK bluetoothAuthCallback(LPVOID param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS params)
{
	// File used for debugging
	DWORD dwRet;

	BLUETOOTH_AUTHENTICATE_RESPONSE AuthRes;
	AuthRes.authMethod = params->authenticationMethod;

	// Check to make sure we are using numeric comparison (Just Works)
	if (AuthRes.authMethod == BLUETOOTH_AUTHENTICATION_METHOD_NUMERIC_COMPARISON)
	{
	}

	AuthRes.bthAddressRemote = params->deviceInfo.Address;
	AuthRes.negativeResponse = FALSE;

	// Commented out code is used for pairing using the BLUETOOTH_AUTHENTICATION_METHOD_PASSKEY method
	memcpy_s(AuthRes.pinInfo.pin, sizeof(AuthRes.pinInfo.pin), L"1234", 0);
	AuthRes.pinInfo.pinLength = 0;

	// Respond with numerical value for Just Works pairing
	AuthRes.numericCompInfo.NumericValue = 1;

	// Send authentication response to authenticate device
	dwRet = BluetoothSendAuthenticationResponseEx(NULL, &AuthRes);
	if (dwRet != ERROR_SUCCESS)
	{
		if (dwRet == ERROR_CANCELLED)
		{
		}
		else if (dwRet == E_FAIL)
		{
		}
		else if (dwRet == 1244)
		{
		}
	}
	else
	{
	}

	return 1;
}

