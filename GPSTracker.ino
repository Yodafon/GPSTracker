/*
 Name:		GPSTracker.ino
 Created:	6/16/2021 2:39:19 PM
 Author:	Laci
*/	
#include <PubSubClient.h>
#include "PositionQuery.h"
#include "GSMHandler.h"
#include "GPSHandler.h"
#include "MQTTPublisher.h"
#include <string>
#include <c++/5.2.0/bits/unique_ptr.h>


std::unique_ptr<PositionQuery> positionQuery;

GSMHandler* gsmHandler;
GPSHandler* gpsHandler;
MQTTPublisher* mqttPublisher;
void setup() {

	Serial.begin(115200);

	gpsHandler = new GPSHandler();
	gsmHandler = new GSMHandler();
	mqttPublisher = new MQTTPublisher(*gsmHandler);

	positionQuery = std::unique_ptr<PositionQuery>(new PositionQuery(*gpsHandler, *gsmHandler));
}


// the loop function runs over and over again until power down or reset
void loop() {
	//Serial.println(F("Loop"));
	GPSPosition* position = positionQuery.get()->getPosition();
	std::string result;
	if (position != nullptr) {
	size_t bytes = serializeJson(position->toJSON(), result);
	Serial.println(bytes);
	Serial.println(result.c_str());
	mqttPublisher->publish(result.c_str());
	}
  
}
