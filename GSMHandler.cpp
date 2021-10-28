#include "GSMHandler.h"
using namespace std;
GPSPosition GSMHandler::getCellInformations()
{
	return GPSPosition(TinyGPSLocation(), TinyGPSDate(), TinyGPSTime(), TinyGPSSpeed(), TinyGPSInteger(), TinyGPSHDOP());
}

GPSPosition GSMHandler::calculateTriangulation(std::vector<double> cells)
{
	return GPSPosition(TinyGPSLocation(), TinyGPSDate(), TinyGPSTime(), TinyGPSSpeed(), TinyGPSInteger(), TinyGPSHDOP());
}

GSMHandler::GSMHandler()
{


}

GSMHandler::~GSMHandler() {
}

unique_ptr<GPSPosition> GSMHandler::getPosition()
{
	return nullptr;
}


void GSMHandler::reconnect(void)
{

}

void GSMHandler::send(GPSPosition position)
{

}
