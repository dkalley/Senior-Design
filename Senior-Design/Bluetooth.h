#include "pch.h"
//#include "winrt/base.h"
//#include "winrt/Windows.Devices.Bluetooth.h"
//#include "winrt/Windows.Devices.Bluetooth.Advertisement.h"
//#include "winrt/Windows.Foundation.h"
//#include "winrt/Windows.Foundation.Collections.h"
//#include "winrt/Windows.Devices.Enumeration.h"
#include <WinSock2.h>
#include <windows.h>
#include "bthdef.h"
#include "BluetoothAPIs.h"
#include <tchar.h>
#include <string>
#include <iostream>
#include <vector>
#pragma comment(lib, "bthprops.lib")


using namespace std;
//using namespace winrt;
//using namespace winrt::Windows::Devices::Enumeration;
//using namespace winrt::Windows::Devices::Bluetooth;
//using namespace winrt::Windows::Devices::Bluetooth::Advertisement;
//using namespace winrt::Windows::Foundation;
//using namespace winrt::Windows::Foundation::Collections;

#pragma once
class Bluetooth
{
#define SCANNING_STARTED 0
#define SCANNING_ENDED 1

public:
	Bluetooth();
	vector<BLUETOOTH_DEVICE_INFO> device_list;
	vector<BLUETOOTH_DEVICE_INFO> res;
	BLUETOOTH_DEVICE_SEARCH_PARAMS bdsp;
	BLUETOOTH_DEVICE_INFO bdi;
	HBLUETOOTH_DEVICE_FIND hbf;
	int scanning_status;


	void scanDevices();
	string Pair_Device(BLUETOOTH_DEVICE_INFO device);
	string Connect_Device(BLUETOOTH_DEVICE_INFO device);

private:

};

