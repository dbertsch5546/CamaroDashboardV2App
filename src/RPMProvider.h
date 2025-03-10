#ifndef RPM_PROVIDER_H
#define RPM_PROVIDER_H

#include <QObject>

class RPMProvider : public QObject {
Q_OBJECT
    Q_PROPERTY(QString displayRpm READ displayRpm WRITE setDisplayRpm NOTIFY displayRpmChanged)
    Q_PROPERTY(int rpmFrame READ rpmFrame WRITE setRpmFrame NOTIFY rpmFrameChanged)

public:
    explicit RPMProvider(QObject *parent = nullptr);

    QString displayRpm() const;
    void setDisplayRpm(const QString &value);

    int rpmFrame() const;
    void setRpmFrame(int value);

signals:
    void displayRpmChanged();
    void rpmFrameChanged();

private:
    QString m_displayRpm;
    int m_rpmFrame;
};

#endif // RPM_PROVIDER_H
