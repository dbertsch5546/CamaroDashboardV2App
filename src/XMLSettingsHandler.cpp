#include "XMLSettingsHandler.h"
#include <iostream>

XMLSettingsHandler::XMLSettingsHandler(const std::string &filePath) : filePath(filePath) {
    loadSettings();
}

bool XMLSettingsHandler::loadSettings() {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError loadResult = doc.LoadFile(filePath.c_str());
    if (loadResult != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load settings file: " << filePath << std::endl;
        return false;
    }
    tinyxml2::XMLElement *root = doc.FirstChildElement("settings");
    if (!root) {
        std::cerr << "Failed to find root element 'settings' in settings file: " << filePath << std::endl;
        return false;
    }
    for (tinyxml2::XMLElement *element = root->FirstChildElement(); element; element = element->NextSiblingElement()) {
        settingsMap[element->Name()] = element->GetText();
    }
    return true;
}

bool XMLSettingsHandler::saveSettings() const {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *root = doc.NewElement("settings");
    doc.InsertFirstChild(root);
    for (const auto &setting : settingsMap) {
        tinyxml2::XMLElement *element = doc.NewElement(setting.first.c_str());
        element->SetText(setting.second.c_str());
        root->InsertEndChild(element);
    }
    tinyxml2::XMLError saveResult = doc.SaveFile(filePath.c_str());
    if (saveResult != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to save settings file: " << filePath << std::endl;
        return false;
    }
    return true;
}

void XMLSettingsHandler::setSetting(const std::string &key, const std::string &value) {
    settingsMap[key] = value;
}

std::string XMLSettingsHandler::getSetting(const std::string &key) const {
    auto it = settingsMap.find(key);
    if (it != settingsMap.end()) {
        return it->second;
    }
    return "";
}

void XMLSettingsHandler::printSettings() const {
    for (const auto &setting : settingsMap) {
        std::cout << setting.first << ": " << setting.second << std::endl;
    }
}
