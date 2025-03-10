//
// Created by dbertsch on 04/05/24.
//
#include <net/if.h>
#include <sys/ioctl.h>
#include "canThread.h"
#include "globals.h"
#include "linux/can.h"
#include "SettingsHandler.h"
#include <fcntl.h>    // For fcntl
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>   // For close()
#include <cstring>    // For memset
#include <iostream>   // For std::cerr
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <fstream>
#include "globals.h"
#include "utils.h"

std::vector<can_frame> incomingCANFrames;
std::vector<can_frame> outgoingCANFrames;
// Protect vectors with a mutex
std::mutex incomingCANFramesMutex;
std::mutex outgoingCANFramesMutex;
std::atomic<int> frameCount(0);  // Atomic counter for received CAN frames

void printStatistics() {
    std::ofstream logFile("/tmp/can_stats.log", std::ios::app);  // Open log file in append mode

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: /tmp/can_stats.log" << std::endl;
        return;
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        int count = frameCount.exchange(0);  // Reset the counter and get the previous value
        logFile << "Received " << count << " CAN frames in the last 5 seconds." << std::endl;

        // Ensure the output is flushed to the file
        logFile.flush();
    }

    logFile.close();
}

int writeCANFrame(struct can_frame &frame){
    //Add the frame to the outgoingCANFrames vector, check for errors
    {
        std::unique_lock<std::mutex> lock(outgoingCANFramesMutex);
        outgoingCANFrames.push_back(frame);
    }
    return 1;
}
void canListenerThread(SettingsHandler *settingsHandler) {
    int canSocket; // Socket descriptor
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

    // Open CAN Interface
    if ((canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("CAN Socket Error");
        return;
    }

    // Set the interface name
    std::string canInterfaceName = "";
    if (settingsHandler != nullptr) {
        canInterfaceName = "can0";
    }
    strcpy(ifr.ifr_name, canInterfaceName.c_str());
    std::cout << "Listening on CAN interface: " << canInterfaceName << std::endl;
    if (ioctl(canSocket, SIOCGIFINDEX, &ifr) < 0) {
        perror("ioctl");
        close(canSocket);
        return;
    }

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(canSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Can Bind Error");
        close(canSocket);
        return;
    }

    // Set socket to non-blocking mode
    int flags = fcntl(canSocket, F_GETFL, 0);
    if (flags < 0) {
        perror("Error getting flags");
        close(canSocket);
        return;
    }

    flags |= O_NONBLOCK;
    if (fcntl(canSocket, F_SETFL, flags) < 0) {
        perror("Error setting non-blocking flag");
        close(canSocket);
        return;
    }
    //Start the can statistics thread
    std::thread statisticsThread(printStatistics);
    // CAN frame reading loop
    while (true) {
        int nbytes = read(canSocket, &frame, sizeof(struct can_frame));

        if (nbytes < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                // No data available right now, wait a bit before trying again
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            } else {
                perror("read");
                break;  // Exit on read error
            }
        } else if (nbytes == sizeof(struct can_frame)) {
            // Place can frame on the incoming queue
            {
                std::unique_lock<std::mutex> lock(incomingCANFramesMutex);
                incomingCANFrames.push_back(frame);
            }
            // Increment the frame count
            frameCount++;
        } else {
            std::cerr << "Incomplete CAN frame read" << std::endl;
        }

        //Check if there are any can frames to send
        std::unique_lock<std::mutex> lock(outgoingCANFramesMutex);
        if (!outgoingCANFrames.empty()) {
            // Send the first frame in the queue
            struct can_frame &outgoingFrame = outgoingCANFrames.front();
            int bytes_written = write(canSocket, &outgoingFrame, sizeof(struct can_frame));
            if (bytes_written < 0) {
                perror("Error writing can frame");
            } else if (bytes_written != sizeof(struct can_frame)) {
                std::cerr << "Incomplete CAN frame write" << std::endl;
            } else {
                // Remove the frame from the queue
                outgoingCANFrames.erase(outgoingCANFrames.begin());
            }
        }
    }

    close(canSocket);
}