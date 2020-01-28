#include "pch.h"
#include "TUIO2/UdpReceiver.h"


using namespace TUIO2;

#pragma once
class ObjectDetector
{
public:
	ObjectDetector();
	void connect();
	void disconnect();
	UdpReceiver *receiver;
private:
};
