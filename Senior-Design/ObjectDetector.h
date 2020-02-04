#include "pch.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Networking.h"
#include "winrt/Windows.Networking.Sockets.h"
#include "winrt/Windows.Storage.Streams.h"
//#include <amp.h>


//#include "TUIO/TcpReceiver.h"

//using namespace concurrency;
//using namespace platform;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Networking;
using namespace winrt::Windows::Networking::Sockets;

#pragma once
class ObjectDetector
{
public:
	ObjectDetector();
	void StartClient();
	//void connect();
	//void disconnect();
	

	StreamSocket streamSocket = { 0 };

	//HostName hostname;
	//TuioClient *myclient;
	//TcpReceiver *receiver;

	


private:
};
