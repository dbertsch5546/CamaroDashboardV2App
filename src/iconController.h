// iconController.h
#ifndef iconController_H
#define iconController_H

#include <QObject>
#include <QString>
class iconController : public QObject
{
Q_OBJECT
//Turn signal visibility properties
    Q_PROPERTY(bool isLeftTurnVisible READ isLeftTurnVisible WRITE setLeftTurnVisible NOTIFY leftTurnVisibilityChanged)
    Q_PROPERTY(bool isRightTurnVisible READ isRightTurnVisible WRITE setRightTurnVisible NOTIFY rightTurnVisibilityChanged)
//Headlight visibility properties
    Q_PROPERTY(bool isHeadlightVisible READ isHeadlightVisible WRITE setHeadlightVisible NOTIFY headlightVisibilityChanged)
//High beam visibility properties
    Q_PROPERTY(bool isHighBeamVisible READ isHighBeamVisible WRITE setHighBeamVisible NOTIFY highBeamVisibilityChanged)
public:
    explicit iconController(QObject *parent = nullptr);

    bool isLeftTurnVisible() const;
    void setLeftTurnVisible(bool setLeftTurnVisibility);

    bool isRightTurnVisible() const;
    void setRightTurnVisible(bool setRightTurnVisibility);

    bool isHeadlightVisible() const;
    void setHeadlightVisible(bool setHeadlightVisibility);

    bool isHighBeamVisible() const;
    void setHighBeamVisible(bool setHighBeamVisibility);

signals:
    void leftTurnVisibilityChanged();
    void rightTurnVisibilityChanged();
    void headlightVisibilityChanged();
    void highBeamVisibilityChanged();

private:
    bool m_isLeftTurnVisible = false;
    bool m_isRightTurnVisible = false;
    bool m_isHeadlightVisible = false;
    bool m_isHighBeamVisible = false;
};

#endif // iconController_H
