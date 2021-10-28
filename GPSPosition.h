#pragma once
#include <TinyGPS++.h>
#include <string>
#include <ArduinoJson-v6.18.3.h>

struct GPSPosition {
TinyGPSLocation location;
TinyGPSTime time;
TinyGPSDate date;
TinyGPSSpeed speed;
TinyGPSInteger satellites;
TinyGPSHDOP hdop;
GPSPosition(TinyGPSLocation location, TinyGPSDate gpsDate, TinyGPSTime gpsTime,
TinyGPSSpeed speed, TinyGPSInteger satellites, TinyGPSHDOP hdop): location(location), time(gpsTime), date(gpsDate),  speed(speed), satellites(satellites), hdop(hdop) {};
double getLatitude() { return location.lat(); }
double getLongitude() { return location.lng(); }
StaticJsonDocument<500> toJSON() {
	StaticJsonDocument<500> doc;
	auto location = doc.createNestedObject("location");
	location["latitude"] = this->getLatitude();
	location["longitude"] = this->getLongitude();
	
	auto time = doc.createNestedObject("time");
	time["value"] = this->time.value();
	
	auto date = doc.createNestedObject("date");
	date["value"] = this->date.value();

	auto speed = doc.createNestedObject("speed");
	speed["kmph"] = this->speed.kmph();
	
	auto satellites = doc.createNestedObject("satellites");
	satellites["value"] = this->satellites.value();
		
	auto hdop = doc.createNestedObject("hdop");
	hdop["value"] = this->hdop.value();

	return doc;
}
};
