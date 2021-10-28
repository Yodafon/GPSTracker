#pragma once
#define TINY_GSM_MODEM_SIM800
#include "GPSPosition.h"
#include <vector>
#include <c++/5.2.0/bits/unique_ptr.h>
#include <TinyGSM.h>
#include <string>

class GSMHandler{
private: 
	GPSPosition getCellInformations();
	GPSPosition calculateTriangulation(std::vector<double> cells);
	void reconnect(void);

public:
  GSMHandler();
  ~GSMHandler();
  std::unique_ptr<GPSPosition> getPosition();
  void send(GPSPosition position);
  

  
};
