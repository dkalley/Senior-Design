#include "pch.h"
#include "Bluetooth.h"

BOOL CALLBACK bluetoothAuthCallback(LPVOID param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS params);

Bluetooth::Bluetooth()
{
	// Initialize structs needed for bluetooth
	ZeroMemory(&bdsp, sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS));

	// set options for how we want to load our list of BT devices
	bdsp.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
	bdsp.fReturnAuthenticated = TRUE;
	bdsp.fReturnRemembered = TRUE;
	bdsp.fReturnUnknown = TRUE;
	bdsp.fReturnConnected = TRUE;
	bdsp.fIssueInquiry = TRUE;
	bdsp.cTimeoutMultiplier = 4;
	bdsp.hRadio = NULL;

	bdi.dwSize = sizeof(bdi);
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

/*
 PAIR =/= CONNECT 
 CONNECT STILL NEEDS TO BE DONE
*/

string Bluetooth::Pair_Device(BLUETOOTH_DEVICE_INFO device)
{
	// File is used for debugging
	ofstream myfile;
	myfile.open("example.txt");
	wstring ws = device.szName;
	cout << "Pairing device " << string(ws.begin(), ws.end()) << endl;

	// register callback
	myfile << "Registering callback" << endl;
	HBLUETOOTH_AUTHENTICATION_REGISTRATION hCallbackHandle = 0;
	DWORD result = BluetoothRegisterForAuthenticationEx(&device, &hCallbackHandle, (PFN_AUTHENTICATION_CALLBACK_EX)&bluetoothAuthCallback, NULL);

	if (result != ERROR_SUCCESS)
	{
		myfile << "Failed to register callback" << endl;
		myfile.close();
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
		myfile << "pair device success" << endl;
		break;

	case ERROR_CANCELLED:
		myfile << "pair device failed, user cancelled" << endl;
		break;

	case ERROR_INVALID_PARAMETER:
		myfile << "pair device failed, invalid parameter" << endl;
		break;

	case ERROR_NO_MORE_ITEMS:
		myfile << "pair device failed, device appears paired already" << endl;
		
		break;

	default:
		myfile << "pair device failed, unknown error, code " << (unsigned int)result << endl;
		break;
	}
	myfile.close();
	return "success";
}



BOOL CALLBACK bluetoothAuthCallback(LPVOID param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS params)
{
	// File used for debugging
	ofstream myfile;
	myfile.open("example.txt");
	DWORD dwRet;

	myfile << "BluetoothAuthCallback " << params->deviceInfo.Address.ullLong << endl;

	BLUETOOTH_AUTHENTICATE_RESPONSE AuthRes;
	AuthRes.authMethod = params->authenticationMethod;

	myfile << "Authmethod " << AuthRes.authMethod << endl;

	// Check to make sure we are using numeric comparison (Just Works)
	if (AuthRes.authMethod == BLUETOOTH_AUTHENTICATION_METHOD_NUMERIC_COMPARISON)
	{
		myfile << "Numeric Comparison supported" << endl;
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
		myfile << "BluetoothSendAuthenticationResponseEx ret " << dwRet << endl;
		if (dwRet == ERROR_CANCELLED)
		{
			myfile << "Bluetooth device denied passkey response or communicatino problem" << endl;
		}
		else if (dwRet == E_FAIL)
		{
			myfile << "Device returned a failure code during authentication" << endl;
		}
		else if (dwRet == 1244)
		{
			myfile << "Not authenticated" << endl;
		}
	}
	else
	{
		myfile << "BluetoothAuthCallback finish" << endl;
	}

	myfile.close();
	return 1;
}


// After device is paired, connect
string Bluetooth::Connect_Device(BLUETOOTH_DEVICE_INFO device)
{
	
}

