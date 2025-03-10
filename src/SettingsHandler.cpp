#include "SettingsHandler.h"
#include <fstream>
#include <iostream>
#include <string>

SettingsHandler::SettingsHandler(QObject *parent) : QObject(parent), xmlHandler("settings.xml") {
    loadSettings();
    //Populate the QML properties with the values from the settings file
    string canInterfaceName = this->xmlHandler.getSetting("canInterfaceName");
    this->setCanInterfaceName(QString::fromStdString(canInterfaceName));
}

SettingsHandler::~SettingsHandler() {
    saveSettings();
}

void SettingsHandler::setSetting(const std::string &key, const std::string &value) {
    xmlHandler.setSetting(key, value);
}

std::string SettingsHandler::getSetting(const std::string &key) const {
    return xmlHandler.getSetting(key);
}

bool SettingsHandler::saveSettings() const {
    return xmlHandler.saveSettings();
}

bool SettingsHandler::loadSettings() {
    return xmlHandler.loadSettings();
}

QQuickItem* SettingsHandler::findItemById(const QObject *parent, const QString &id) {
    const QList<QQuickItem*> children = parent->findChildren<QQuickItem*>();
    for (QQuickItem *child : children) {
        if (child->objectName() == id) {
            return child;
        }
    }
    return nullptr;
}

void SettingsHandler::handleSaveClicked(const QString &canInterfaceName, const QString &logUpdateFrequency) {
    setSetting("canInterfaceName", canInterfaceName.toStdString());
    setSetting("logUpdateFrequency", logUpdateFrequency.toStdString());
    saveSettings();
}

void SettingsHandler::handleStartCanSimulatorClicked() {
    std::string command = "/root/vcan_control.sh start";
    std::string result = "";
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error executing command: " << command << std::endl;
        return;
    }
    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
    }
    pclose(pipe);
    std::cout << "Command output: " << result << std::endl;

    command = "/root/can_simulation.sh start -f /root/canTestData1.log -i vcan0=can0 -l 20";
    result = "";
    pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error executing command: " << command << std::endl;
        return;
    }
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
    }
    pclose(pipe);
    std::cout << "Command output: " << result << std::endl;
}

void SettingsHandler::handleStopCanSimulatorClicked() {
    std::string command = "/root/can_simulation.sh stop";
    std::string result = "";
    FILE *pipe = popen(command.c_str(), "r");
    char buffer[256] = {0};

    if (!pipe) {
        std::cerr << "Error executing command: " << command << std::endl;
        return;
    }
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
    }
    pclose(pipe);
    std::cout << "Command output: " << result << std::endl;
}
