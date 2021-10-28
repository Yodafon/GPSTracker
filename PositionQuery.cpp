#include "PositionQuery.h"
using namespace std;
PositionQuery::PositionQuery(GPSHandler& gpsHandler, GSMHandler& gsmHandler) : gpsHandler(gpsHandler), gsmHandler(gsmHandler)
{
}

GPSPosition* PositionQuery::getPosition()
{
	unique_ptr<GPSPosition> position = gpsHandler.getPosition(); //primarly query basd on gps position
	if (position == nullptr) {
		position = gsmHandler.getPosition(); //falling back to mobile cell based position query
	}
	if (position != nullptr) {
		return position.get();
	}
	else {
		return nullptr;
	}
}
