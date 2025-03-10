#ifndef GPS_H
#define GPS_H

#include <string>
#include <vector>
#include <tuple>
#include <termios.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>

class GPS {
public:
    GPS(const std::string& port, unsigned int baud_rate);
    ~GPS();

    void changeBaudRate(unsigned int new_baud_rate);
    void changeUpdateRate(unsigned int rate_hz);

    std::string readLine();
    std::vector<std::string> parseNMEA(const std::string& nmea_sentence);
    int serial_fd_;
    struct termios tty_;

private:
    void configurePort(unsigned int baud_rate);
    void sendCommand(const std::string& command);
};

class GPSManager {
public:
    GPSManager(GPS& gps);

    void changeBaudRate(unsigned int new_baud_rate);
    void changeUpdateRate(unsigned int rate_hz);

    std::tuple<double, double, double> getLatLong();
    void printLocation();

private:
    GPS& gps_;
    double convertLatLongToDouble(const std::string& value, const std::string& direction);
    double convertTimeToDouble(const std::string& time_str);
};

#endif // GPS_H
