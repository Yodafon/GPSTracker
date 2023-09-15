#pragma once
#include "GPSPosition.h"
#include <vector>
#include <c++/5.2.0/bits/unique_ptr.h>
#include <string>

#include <SoftwareSerial.h>
#include <Client.h>
class GSMHandler : public Client{
private: 
    SoftwareSerial* SerialAT;
	GPSPosition getCellInformations();
	GPSPosition calculateTriangulation(std::vector<double> cells);
	void getResponse(unsigned long& now, const int responseTimeInSeconds);
	void sendATCommand(String command, String expected);
	void connect(void);
	void sendTCPRequest(String data);
	void sendHTTPRequest();
	String domain = "broker.hivemq.com";
	String port = "1883";

public:

  GSMHandler();
  ~GSMHandler();
  std::unique_ptr<GPSPosition> getPosition();
  
  
  
  // Inherited via Client
  virtual int connect(IPAddress ip, uint16_t port) override;

  virtual int connect(const char* host, uint16_t port) override;

  virtual size_t write(uint8_t) override;

  virtual size_t write(const uint8_t* buf, size_t size) override;

  virtual int available() override;

  virtual int read() override;

  virtual int read(uint8_t* buf, size_t size) override;

  virtual int peek() override;

  virtual void flush() override;

  virtual void stop() override;

  virtual uint8_t connected() override;

  virtual operator bool() override;

};


