#ifndef INPUTBUTTON_H
#define INPUTBUTTON_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class InputButton : public QQuickPaintedItem
{
Q_OBJECT
    Q_PROPERTY(int rectX READ rectX WRITE setRectX NOTIFY rectXChanged)
    Q_PROPERTY(int rectY READ rectY WRITE setRectY NOTIFY rectYChanged)

public:
    InputButton(QQuickItem *parent = nullptr)
            : QQuickPaintedItem(parent), m_rectX(0), m_rectY(0) {}

    int rectX() const { return m_rectX; }
    void setRectX(int x) {
        if (m_rectX == x)
            return;
        m_rectX = x;
        emit rectXChanged();
        update();
    }

    int rectY() const { return m_rectY; }
    void setRectY(int y) {
        if (m_rectY == y)
            return;
        m_rectY = y;
        emit rectYChanged();
        update();
    }

    void paint(QPainter *painter) override {
        painter->setBrush(QBrush(Qt::lightGray));
        painter->drawRect(m_rectX, m_rectY, 100, 100);  // Fixed size rectangle
    }

signals:
    void rectXChanged();
    void rectYChanged();
    void rectangleClicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit rectangleClicked(event->x(), event->y());
            handleRectangleClick(event->x(), event->y());
        }
    }

private:
    void handleRectangleClick(int x, int y) {
        qDebug() << "Rectangle clicked at position:" << x << "," << y;
        // Perform additional actions here
    }

    int m_rectX;
    int m_rectY;
};

#endif // INPUTBUTTON_H
