#ifndef SETTINGS_HANDLER_H
#define SETTINGS_HANDLER_H

#include <QObject>
#include <QString>
#include <QQuickItem>
#include <map>
#include <string>
#include "XMLSettingsHandler.h"

using namespace std;
class SettingsHandler : public QObject {
Q_OBJECT
    Q_PROPERTY(QString canInterfaceName READ canInterfaceName WRITE setCanInterfaceName NOTIFY canInterfaceNameChanged)
    Q_PROPERTY(QString logUpdateFrequency READ logUpdateFrequency WRITE setLogUpdateFrequency NOTIFY logUpdateFrequencyChanged)
public:
    explicit SettingsHandler(QObject *parent = nullptr);
    ~SettingsHandler();

    void setSetting(const std::string &key, const std::string &value);
    std::string getSetting(const std::string &key) const;
    QString canInterfaceName() const {
        string canInterfaceName = this->getSetting("canInterfaceName");
        return QString::fromStdString(canInterfaceName);
    }

    void setCanInterfaceName(const QString &name) {
        this->setSetting("canInterfaceName", name.toStdString());
        emit canInterfaceNameChanged();
    }

    QString logUpdateFrequency() const {
        string logUpdateFrequency = this->getSetting("logUpdateFrequency");
        return QString::fromStdString(logUpdateFrequency);
    }
    void setLogUpdateFrequency(const QString &frequency) {
        this->setSetting("logUpdateFrequency", frequency.toStdString());
        emit logUpdateFrequencyChanged();
    }

signals:
    void canInterfaceNameChanged();
    void logUpdateFrequencyChanged();
    void saveClicked(const QString &canInterfaceName, const QString &logUpdateFrequency);
    void startCanSimulatorClicked();
    void stopCanSimulatorClicked();


public slots:
    void handleSaveClicked(const QString &canInterfaceName, const QString &logUpdateFrequency);
    void handleStartCanSimulatorClicked();
    void handleStopCanSimulatorClicked();

private:
    bool loadSettings();
    bool saveSettings() const;
    QQuickItem* findItemById(const QObject *parent, const QString &id);

    XMLSettingsHandler xmlHandler;
};

#endif // SETTINGS_HANDLER_H
