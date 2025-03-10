#ifndef XMLSETTINGS_HANDLER_H
#define XMLSETTINGS_HANDLER_H

#include <string>
#include <map>
#include "tinyxml2.h"

class XMLSettingsHandler {
public:
    XMLSettingsHandler(const std::string &filePath);
    ~XMLSettingsHandler() = default;

    bool loadSettings();
    bool saveSettings() const;

    void setSetting(const std::string &key, const std::string &value);
    std::string getSetting(const std::string &key) const;
    void printSettings() const;

private:
    std::string filePath;
    std::map<std::string, std::string> settingsMap;
};

#endif // XMLSETTINGS_HANDLER_H
