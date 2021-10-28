#include "GPSHandler.h"
using namespace std;
GPSHandler::GPSHandler()
{
	this->ss = new SoftwareSerial(RXPin, TXPin);
	this->ss->begin(GPSBaud);
	this->ss->print("$PMTK313,1*2E\r\n");  // Enable to search a SBAS satellite
	this->ss->print("$PMTK301,2*2E\r\n");  // Enable WAAS as DGPS Source
	Serial.println(F("DeviceExample.ino"));
	Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
	Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
	Serial.println(F("by Mikal Hart"));
	Serial.println();
}

void GPSHandler::displayInfo()
{
	TinyGPSPlus gps = this->gps;
	Serial.print(F("Location: "));
	if (gps.location.isValid())
	{
		Serial.print(gps.location.lat(), 6);
		Serial.print(F(","));
		Serial.print(gps.location.lng(), 6);
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.print(F("  Date/Time: "));
	if (gps.date.isValid())
	{
		Serial.print(gps.date.month());
		Serial.print(F("/"));
		Serial.print(gps.date.day());
		Serial.print(F("/"));
		Serial.print(gps.date.year());
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.print(F(" "));
	if (gps.time.isValid())
	{
		if (gps.time.hour() < 10) Serial.print(F("0"));
		Serial.print(gps.time.hour());
		Serial.print(F(":"));
		if (gps.time.minute() < 10) Serial.print(F("0"));
		Serial.print(gps.time.minute());
		Serial.print(F(":"));
		if (gps.time.second() < 10) Serial.print(F("0"));
		Serial.print(gps.time.second());
		Serial.print(F("."));
		if (gps.time.centisecond() < 10) Serial.print(F("0"));
		Serial.print(gps.time.centisecond());
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.println();
}

unique_ptr<GPSPosition> GPSHandler::getPosition()
{

	// This sketch displays information every time a new sentence is correctly encoded.
	if (
		this->ss->available() > 0  && 
		gps.encode(this->ss->read()) &&
		gps.location.isValid())
		{


      	  //this->displayInfo();
			return unique_ptr<GPSPosition>(new GPSPosition(gps.location, gps.date, gps.time, gps.speed, gps.satellites, gps.hdop));
	}
	

	if (gps.charsProcessed() < 10)
	{
		Serial.println(F("No GPS detected: check wiring."));
	}
	return nullptr;

}