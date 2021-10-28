#pragma once
#include "GPSHandler.h"
#include "GSMHandler.h"
#include "GPSPosition.h"

class PositionQuery {
public:
	PositionQuery(GPSHandler& gpsHandler, GSMHandler& gsmHandler);
	GPSPosition* getPosition();
private:
	GPSHandler& gpsHandler;
	GSMHandler& gsmHandler;
};