#include "MQTTPublisher.h"

MQTTPublisher::MQTTPublisher(GSMHandler& gsmHandler) : gsmHandler(gsmHandler) {
	this->gsmHandler = gsmHandler;
	this->mqttPubLisherClient = new PubSubClient("broker.hivemq.com", 1883, this->gsmHandler);
}

void MQTTPublisher::publish(const char* jsonData) {
	while (!mqttPubLisherClient->connected()) {
		if (this->mqttPubLisherClient->connect(this->clientId.c_str())) {
			this->mqttPubLisherClient->publish(this->topic.c_str(), jsonData);
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(this->mqttPubLisherClient->state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}
