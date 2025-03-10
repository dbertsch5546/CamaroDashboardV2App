// GaugeController.h
#ifndef GAUGECONTROLLER_H
#define GAUGECONTROLLER_H

#include <QObject>
#include <QString>
class GaugeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString frameName READ frameName WRITE setFrameName NOTIFY frameNameChanged)

public:
    explicit GaugeController(QObject *parent = nullptr);

    float value() const;
    void setValue(float newValue);

    QString frameName() const;//Getter
    void setFrameName(QString newValue);
    int setAssetBasePath(QString basePath, QString assetPrefix, int totalFrames);
    void set50PercentFrame(int frameNumber);
signals:
    void valueChanged();
    void frameNameChanged();

private:
    float m_value = 0;
    QString m_frameName = "";
    QString assetBasePath = "";//Where the sequence of .png images are stored for the gauge.
    QString assetPrefix = "";
    int _50PercentFrameCount = 0;
    int totalNumberOfFrames = 0;
};

#endif // GAUGECONTROLLER_H
