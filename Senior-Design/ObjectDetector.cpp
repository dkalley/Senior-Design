#include "pch.h"
#include "ObjectDetector.h"

void ObjectDetector::addTuioCursor(TuioCursor* tcur)
{
	// Create new object and store it
	CCVObject newobject;
	newobject.s_id = tcur->getCursorID();
	newobject.ptx = (int)(tcur->getX() * 1280); 
	newobject.pty = (int)(tcur->getY() * 720);

	// Store object
	Objects.insert(std::pair<int, CCVObject>(tcur->getCursorID(), newobject));

	//Objects[tcur->getCursorID] = newobject;
	// Add to list to proces
	ToProcess.push_back(newobject);
	return;
}

void ObjectDetector::updateTuioCursor(TuioCursor* tcur)
{
	int processflag = false;

	// Get the object to update and update it
	CCVObject objecttoupdate = Objects[tcur->getCursorID()];

	// Determine if we should process. If movement is more than half a "square" away process that point
	int ptx = (int)(tcur->getX() * 1280), pty = (int)(tcur->getY() * 720);
	if (abs(ptx - objecttoupdate.ptx) > 21 || abs(pty - objecttoupdate.pty) > 16)
		processflag = true;

	objecttoupdate.s_id = tcur->getCursorID();
	objecttoupdate.ptx = (int)(tcur->getX() * 1280);
	objecttoupdate.pty = (int)(tcur->getY() * 720);

	// Store updated object
	Objects[tcur->getCursorID()] = objecttoupdate;

	if (processflag)
	{
		// Add to list to proces movement
		ToProcess.push_back(objecttoupdate);
	}

	return;
}

void ObjectDetector::removeTuioCursor(TuioCursor* tcur)
{
	// Remove the object from map
	Objects.erase(tcur->getCursorID());
	return;
}


/*
*	Functions NOT used in implementation below
*/


void ObjectDetector::addTuioObject(TuioObject* tobj)
{
	return;
}
void ObjectDetector::updateTuioObject(TuioObject* tobj)
{
	return;
}
void ObjectDetector::removeTuioObject(TuioObject* tobj)
{
	return;
}

void ObjectDetector::addTuioBlob(TuioBlob* tblb)
{
	return;
}
void ObjectDetector::updateTuioBlob(TuioBlob* tblb)
{
	return;
}
void ObjectDetector::removeTuioBlob(TuioBlob* tblb)
{
	return;
}

void ObjectDetector::refresh(TuioTime frameTime)
{
	return;
}