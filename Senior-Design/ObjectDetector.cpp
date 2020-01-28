#include "pch.h"
#include "ObjectDetector.h"


void temp()
{

}

ObjectDetector::ObjectDetector()
{
	
}

void ObjectDetector::connect()
{
	receiver = new UdpReceiver(3333);
	receiver->~UdpReceiver();
	//unsigned short port = 3333;
	//TuioClient client(port);
	
	/*client.addTuioListener(this);
	client.connect();*/
	
}

void ObjectDetector::disconnect()
{
	
}