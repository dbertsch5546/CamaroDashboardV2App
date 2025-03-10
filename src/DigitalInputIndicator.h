#ifndef DIGITALINPUTINDICATOR_H
#define DIGITALINPUTINDICATOR_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QMouseEvent>
#include <functional>

class DigitalInputIndicator : public QQuickPaintedItem {
Q_OBJECT
    Q_PROPERTY(bool isOn READ isOn WRITE setIsOn NOTIFY isOnChanged)
    Q_PROPERTY(QString inputName READ inputName WRITE setInputName)

public:
    DigitalInputIndicator(QQuickItem *parent = nullptr);

    bool isOn() const { return m_isOn; }
    void setIsOn(bool isOn);

    QString inputName() const { return m_inputName; }
    void setInputName(const QString &inputName);

    void setOnClickListener(std::function<void()> onClickListener);

protected:
    void paint(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void isOnChanged(bool newIsOn);

private:
    bool m_isOn = false;
    QString m_inputName = "InputName";
    bool m_isClicked = false; // Flag to indicate if the widget is clicked

    void drawDebugRectangle(QPainter *painter);
    std::function<void()> m_onClickListener; // Lambda function for click handling
};

#endif // DIGITALINPUTINDICATOR_H
