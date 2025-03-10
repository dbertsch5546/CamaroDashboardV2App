#include "RPMProvider.h"

RPMProvider::RPMProvider(QObject *parent)
        : QObject(parent), m_displayRpm("000"), m_rpmFrame(0) {}

QString RPMProvider::displayRpm() const {
    return m_displayRpm;
}

void RPMProvider::setDisplayRpm(const QString &value) {
    if (value != m_displayRpm) {
        m_displayRpm = value;
        emit displayRpmChanged();
    }
}

int RPMProvider::rpmFrame() const {
    return m_rpmFrame;
}

void RPMProvider::setRpmFrame(int value) {
    //Set display rpm value to QString
    QString displayValue = QString::number(value);
    this->setDisplayRpm(displayValue);
    int correctedFrameValue = value / 10; //Example: 1000 RPM -> frame count 100
    if (correctedFrameValue != m_rpmFrame) {
        m_rpmFrame = correctedFrameValue;
        emit rpmFrameChanged();
    }
}
