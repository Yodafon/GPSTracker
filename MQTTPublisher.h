#pragma once
#include <PubSubClient.h>
#include "GSMHandler.h"
#include <string>
class MQTTPublisher {
private:
	GSMHandler& gsmHandler;
	PubSubClient* mqttPubLisherClient;
	std::string clientId{"MotorTracker"};
	std::string topic= "Current GPS Position";
public:
	MQTTPublisher(GSMHandler& gsmHandler);
	void publish(const char* jsonData);

};