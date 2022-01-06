#include "pch.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "TUIO/LibExport.h"
#include "TUIO/TuioListener.h"
#include "TUIO/TuioClient.h"
#include "TUIO/UdpReceiver.h"

#pragma comment(lib, "libTUIO.lib")

using namespace TUIO;

typedef struct _CCVObject {
	int s_id;
	int ptx;
	int pty;
} CCVObject, *LPCCVObject;

#pragma once
class ObjectDetector : public TuioListener
{
public:
	void addTuioObject(TuioObject* tobj);
	void updateTuioObject(TuioObject* tobj);
	void removeTuioObject(TuioObject* tobj);

	void addTuioCursor(TuioCursor* tcur);
	void updateTuioCursor(TuioCursor* tcur);
	void removeTuioCursor(TuioCursor* tcur);

	void addTuioBlob(TuioBlob* tblb);
	void updateTuioBlob(TuioBlob* tblb);
	void removeTuioBlob(TuioBlob* tblb);

	void refresh(TuioTime frameTime);

	BOOL dontprocess[768];

	std::list<CCVObject> ToProcess;
	std::map<int, CCVObject> Objects;

	//std::vector<CCVObject> UnProcessedObjects;
	//std::vector<CCVObject> ProcessedObjects;


private:
};
