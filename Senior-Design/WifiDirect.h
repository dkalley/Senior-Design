#pragma once
using namespace winrt::Windows::Devices::WiFiDirect;
using namespace winrt::Windows::Networking::Sockets;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

class WifiDirect
{
public:
	WifiDirect();
	void startAdvertisement();

private:
	DWORD *negotiatedVersion;
	HANDLE *clientHandle;
	/*
	WiFiDirectDevice device;
	WiFiDirectAdvertisement advertiser;
	WiFiDirectAdvertisementPublisher publisher;
	WiFiDirectConnectionListener listener;
	StreamSocketListener listenerSocket;
	EventRegistrationToken *connectionRequestedToken;
	EventRegistrationToken *statusChangedToken;
	*/
	

};

