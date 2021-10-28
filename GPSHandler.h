#pragma once
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "GPSPosition.h"
#include <c++/5.2.0/bits/unique_ptr.h>

class GPSHandler {
public:
    GPSHandler();
    std::unique_ptr<GPSPosition> getPosition();

private:
    TinyGPSPlus gps;
    void displayInfo();
    const int RXPin = 23, TXPin = 22;
    const uint32_t GPSBaud = 9600;
    SoftwareSerial* ss;
};

