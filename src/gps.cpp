#include "gps.h"
#include <cstring>
#include <chrono>
#include <thread>
#include <tuple>
#include <iomanip>

GPS::GPS(const std::string& port, unsigned int baud_rate) {
    serial_fd_ = open(port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd_ < 0) {
        throw std::runtime_error("Failed to open GPS serial port");
    }
    configurePort(baud_rate);
}

GPS::~GPS() {
    close(serial_fd_);
}

void GPS::configurePort(unsigned int baud_rate) {
    memset(&tty_, 0, sizeof tty_);
    if (tcgetattr(serial_fd_, &tty_) != 0) {
        throw std::runtime_error("Failed to get terminal attributes");
    }

    cfsetospeed(&tty_, baud_rate);
    cfsetispeed(&tty_, baud_rate);

    tty_.c_cflag = (tty_.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    tty_.c_iflag &= ~IGNBRK;         // disable break processing
    tty_.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty_.c_oflag = 0;                // no remapping, no delays
    tty_.c_cc[VMIN]  = 1;            // read doesn't block
    tty_.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty_.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty_.c_cflag |= (CLOCAL | CREAD); // ignore modem controls,
    // enable reading
    tty_.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty_.c_cflag |= 0;
    tty_.c_cflag &= ~CSTOPB;
    tty_.c_cflag &= ~CRTSCTS;

    if (tcsetattr(serial_fd_, TCSANOW, &tty_) != 0) {
        throw std::runtime_error("Failed to set terminal attributes");
    }
}

void GPS::sendCommand(const std::string& command) {
    write(serial_fd_, command.c_str(), command.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 100 ms
}

void GPS::changeBaudRate(unsigned int new_baud_rate) {
    std::string command;
    if (new_baud_rate == B4800) {
        command = "$PMTK251,4800*14\r\n";
    } else if (new_baud_rate == B9600) {
        command = "$PMTK251,9600*17\r\n";
    } else if (new_baud_rate == B19200) {
        command = "$PMTK251,19200*22\r\n";
    } else if (new_baud_rate == B38400) {
        command = "$PMTK251,38400*27\r\n";
    } else if (new_baud_rate == B57600) {
        command = "$PMTK251,57600*2C\r\n";
    } else if (new_baud_rate == B115200) {
        command = "$PMTK251,115200*1F\r\n";
    } else {
        throw std::invalid_argument("Unsupported baud rate.");
    }
    sendCommand(command);
    configurePort(new_baud_rate);
}

void GPS::changeUpdateRate(unsigned int rate_hz) {
    std::string command;
    if (rate_hz == 1) {
        command = "$PMTK220,1000*1F\r\n";
    } else if (rate_hz == 2) {
        command = "$PMTK220,500*2B\r\n";
    } else if (rate_hz == 5) {
        command = "$PMTK220,200*2C\r\n";
    } else if (rate_hz == 10) {
        command = "$PMTK220,100*2F\r\n";
    } else {
        throw std::invalid_argument("Unsupported update rate.");
    }
    sendCommand(command);
}

std::string GPS::readLine() {
    char c;
    std::string result;
    while (true) {
        int n = read(serial_fd_, &c, 1);
        if (n > 0) {
            if (c == '\n') break;
            result += c;
        }
    }
    return result;
}

std::vector<std::string> GPS::parseNMEA(const std::string& nmea_sentence) {
    std::vector<std::string> result;
    std::istringstream stream(nmea_sentence);
    std::string token;
    while (std::getline(stream, token, ',')) {
        result.push_back(token);
    }
    return result;
}

GPSManager::GPSManager(GPS& gps) : gps_(gps) {}

void GPSManager::changeBaudRate(unsigned int new_baud_rate) {
    gps_.changeBaudRate(new_baud_rate);
}

void GPSManager::changeUpdateRate(unsigned int rate_hz) {
    gps_.changeUpdateRate(rate_hz);
}

std::tuple<double, double, double> GPSManager::getLatLong() {
    // Clear the read buffer
    tcflush(gps_.serial_fd_, TCIFLUSH);

    while (true) {
        std::string line = gps_.readLine();
        if (line.substr(0, 6) == "$GPGGA") {
            auto data = gps_.parseNMEA(line);
            if (data.size() >= 6) {
                double time_utc = convertTimeToDouble(data[1]);
                double latitude = convertLatLongToDouble(data[2], data[3]);
                double longitude = convertLatLongToDouble(data[4], data[5]);

                return std::make_tuple(time_utc, latitude, longitude);
            }
        }
    }
}

void GPSManager::printLocation() {
    auto [time_utc, latitude, longitude] = getLatLong();
    std::cout << "Time UTC: " << time_utc << ", "
              << "Latitude: " << latitude << ", "
              << "Longitude: " << longitude << std::endl;
}

double GPSManager::convertLatLongToDouble(const std::string& value, const std::string& direction) {
    double degrees = std::stod(value.substr(0, 2));
    double minutes = std::stod(value.substr(2));
    double result = degrees + (minutes / 60.0);
    if (direction == "S" || direction == "W") {
        result = -result;
    }
    return result;
}

double GPSManager::convertTimeToDouble(const std::string& time_str) {
    double hours = std::stod(time_str.substr(0, 2));
    double minutes = std::stod(time_str.substr(2, 2));
    double seconds = std::stod(time_str.substr(4));
    return hours + (minutes / 60.0) + (seconds / 3600.0);
}
