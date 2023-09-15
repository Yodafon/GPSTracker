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
	SerialAT = new SoftwareSerial(26, 27);
	SerialAT->begin(9600);
}

GSMHandler::~GSMHandler() {
}

unique_ptr<GPSPosition> GSMHandler::getPosition()
{
	return nullptr;
}

void GSMHandler::sendATCommand(String command, String expected) {
	String result = "";
	do {
		// Hang up after 2 seconds
		SerialAT->print(command + "\r\n");

		result = SerialAT->readString();
		Serial.print(result);

	} while (strstr(result.c_str(), expected.c_str()) == NULL);

}

void GSMHandler::connect(void)
{

	// Check if modem is ok
	// 65 84 13 13 10 79 75 13 10 13 10 67 97 108 108 32 82 101 97 100 121 13 10 13 10 83 77 83 32 82 101 97 100 121 13 10 134 14 220 216 34 126 160 252 76 50 60 66 175 234

	sendATCommand("AT", "OK");

	//Query network status until netwok is available
	sendATCommand("AT+CREG?", "+CREG: 0,1");

	//ATTACH/DETACH FROM GPRS SERVICE
	sendATCommand("AT+CGATT=1", "OK");

	//Define PDP context (IP, APN)
	sendATCommand("AT+CGDCONT=1,\"IP\",\"internet.telekom\",\"0.0.0.0\",0,0", "OK");

	//Activate PDP context
	sendATCommand("AT+CGACT=1,1", "AT+CGACT=1,1");

	sendATCommand("AT+CSTT=\"internet.telekom\",\"\",\"\"", "OK");
	sendATCommand("AT+CIICR", "OK");

	//Enter Data state
	sendATCommand("AT+CGDATA=\"PPP\",1", "CONNECT");
	//Get PDP address
	sendATCommand("AT+CGPADDR=1", "CGPADDR");


	//Set GPRS class to B (Class B)
	sendATCommand("AT+CGCLASS=\"B\"", "OK");

	//disable unneccessary  error codes
	sendATCommand("AT+CGEREP=0", "OK");

	//get network status, cell id, location code
	sendATCommand("AT+CGREG=2", "OK");
	sendATCommand("AT+CGREG?", "OK");

	sendATCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", "OK");
	sendATCommand("AT+SAPBR=3,1,\"APN\",\"internet.telekom\"", "OK");
	sendATCommand("AT+SAPBR=1,1", "OK");



	//set Packet domain (GPRS) transfer mode
	sendATCommand("AT+CGSMS=0", "OK");
	SerialAT->print("AT+CIFSR\r\n");
	unsigned long now = millis();   // last time a char was available
	getResponse(now, 1);


	sendATCommand("AT+CIPSTART=\"TCP\",\"" + this->domain + "\"," + this->port, "OK");

	sendATCommand("AT+CIPMUX?", "OK");

	//sendHTTPRequest();

}

void GSMHandler::sendTCPRequest(String data)
{
	Serial.println("Data" + data);
	SerialAT->print("AT+CIPSTATUS\r\n");
	unsigned long now = millis();   // last time a char was available
	getResponse(now, 1);
	Serial.println("Send command");

	sendATCommand("AT+CIPSEND="+data.length(), "OK");
	now = millis();   // last time a char was available
	getResponse(now, 1);
	Serial.println("Send Data");

	sendATCommand(data, "SEND OK");


}


void GSMHandler::sendHTTPRequest()
{
	//HTTP init
	sendATCommand("AT+HTTPINIT", "OK");

	sendATCommand("AT+HTTPPARA=\"CID\",1", "OK");
	sendATCommand("AT+HTTPPARA=\"URL\",\"www.allamkincstar.gov.hu\"", "OK");

	sendATCommand("AT+HTTPACTION=\"0\"", "OK");
	unsigned long now = millis();   // last time a char was available
	getResponse(now, 15);
	sendATCommand("AT+HTTPREAD", "OK");
	now = millis();   // last time a char was available
	getResponse(now, 15);
}

void GSMHandler::getResponse(unsigned long& now, const int responseTimeInSeconds)
{
	while (millis() - now < responseTimeInSeconds*1000) {
		while (SerialAT->available()) {
			Serial.write(SerialAT->read());
			now = millis();   // update the lastRead timestamp
		}
	}
}

int GSMHandler::connect(IPAddress ip, uint16_t port)
{
	Serial.println("Connect");
	Serial.print(ip.toString()); Serial.print(":");Serial.println(port);
	connect();
	return true;
}

int GSMHandler::connect(const char* host, uint16_t port)
{
	Serial.println("Connect");
	Serial.print(host);Serial.print(":");Serial.println(port);
	connect();
	return true;
}

size_t GSMHandler::write(uint8_t d)
{
	Serial.println("Write staff");
	Serial.println(d);
	return size_t();
}

size_t GSMHandler::write(const uint8_t* buf, size_t size)
{
	Serial.println("Write staff");
	String data;
	for(int i=0; i<size; i++)
	data+= ((char)buf[i]);
	this->sendTCPRequest(data);
	return size_t();
}

int GSMHandler::available()
{
	Serial.println("Available");
	return true;
}

int GSMHandler::read()
{
	Serial.println("Read staff");
	return true;
}

int GSMHandler::read(uint8_t* buf, size_t size)
{
	Serial.println("Read buffered staff");
	return true;
}

int GSMHandler::peek()
{
	Serial.println("Peek staff");
	return 0;
}

void GSMHandler::flush()
{
	Serial.println("Flush staff");
}

void GSMHandler::stop()
{
}

uint8_t GSMHandler::connected()
{
	String result = "";

	// Hang up after 2 seconds
	SerialAT->print("AT+CIPSTATUS\r\n");

	result = SerialAT->readString();
	Serial.print(result);

	if (strstr(result.c_str(), "OK") == NULL)
	{
		return 0;
	}

	else {
		Serial.println("Connected");
		return 1;
	}
}

GSMHandler::operator bool()
{
	return connected();
}
