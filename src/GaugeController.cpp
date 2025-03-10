// GaugeController.cpp
#include "GaugeController.h"
#include <QDir>
#include <QString>
#include <QFileInfoList>

GaugeController::GaugeController(QObject *parent)
    : QObject(parent), m_value(0.0)
{
    this->m_frameName = "TEST";
}

float GaugeController::value() const
{
    return m_value;
}

void GaugeController::setValue(float newValue)
{
    if(this->_50PercentFrameCount == 0){
        if((int)newValue > this->totalNumberOfFrames){
            newValue = (int)this->totalNumberOfFrames;
        }
        if((int)newValue < 0){
            newValue = 0;
        }
        //This is used for gauges that have 1 -> 1 frameValues to value mapping, such as speedGauge.
        // Ensure the frame number is an integer and zero-padded to 4 digits
        QString frameNumber = QString("%1").arg((int)newValue, 3, 10, QChar('0'));

        // Construct the frame path with zero-padded frame number
        QString framePath = this->assetBasePath + "/" + this->assetPrefix + frameNumber + ".png";
        this->m_frameName = framePath;
        this->setFrameName(framePath);
        if (m_value != newValue) {
            m_value = newValue;
            emit valueChanged();
        }
        return;
    }
    //Compute the frame according to a linear equation. (0,0) -> (100, maxFrameCount)
    // y = mx+b; b = y - mx, use 50 percent frame as test point -> (50, 50PercentFrameNumber)
    float slope = ((float)this->totalNumberOfFrames - 0.0f) / (100.0f - 0.0f);
    float b = this->_50PercentFrameCount - slope*50.0f;
    int computedFrame = slope*newValue + b;
    if(computedFrame < 0){
        computedFrame = 0;
    }
    if(computedFrame > this->totalNumberOfFrames){
        computedFrame = this->totalNumberOfFrames;
    }
    // Ensure the frame number is an integer and zero-padded to 4 digits
    QString frameNumber = QString("%1").arg((int)computedFrame, 4, 10, QChar('0'));

    // Construct the frame path with zero-padded frame number
    QString framePath = this->assetBasePath + "/" + this->assetPrefix + frameNumber + ".png";

    this->m_frameName = framePath;
    this->setFrameName(framePath);
    if (m_value != newValue) {
        m_value = newValue;
        emit valueChanged();
    }
}

QString GaugeController::frameName() const
{
    return m_frameName;
}

void GaugeController::setFrameName(QString newValue){
    this->m_frameName = newValue;
    emit frameNameChanged();
}

int GaugeController::setAssetBasePath(QString basePath, QString assetPrefix, int totalFrames){
    this->assetBasePath = basePath;
    this->assetPrefix = assetPrefix;
    this->totalNumberOfFrames = totalFrames;
    return 1;
}

void GaugeController::set50PercentFrame(int frameNumber){
    this->_50PercentFrameCount = frameNumber;
}
