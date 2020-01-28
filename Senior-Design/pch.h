#pragma once

#include <windows.h>
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

// winrt headers
#include <winrt/base.h>
#include <winrt/Windows.Devices.WiFiDirect.h>
#include <winrt/Windows.Networking.Sockets.h>
#include <winrt/Windows.Foundation.h>

// Default C/C++ headers
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>