#include "DigitalInputIndicator.h"
#include <QDebug>

DigitalInputIndicator::DigitalInputIndicator(QQuickItem *parent)
        : QQuickPaintedItem(parent) {
    // Enable mouse events
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

void DigitalInputIndicator::paint(QPainter *painter) {
    // Set the pen for your lines
    QPen pen(Qt::red, 2); // Red color, 2 pixels thick
    painter->setPen(pen);

    // Set up the font for the text
    QFont font("Roboto", 8); // Specify font name and size
    painter->setFont(font);

    // Draw the input name
    QRectF textRect = painter->boundingRect(QRectF(0, 0, 0, 0), Qt::AlignCenter, this->inputName());
    qreal x = (100 - textRect.width()) / 2; // Adjust 100 to your item's width
    qreal y = 8; // Adjust as needed
    painter->drawText(x, y, this->inputName());

    // Draw the circle for the digital input status
    QColor color = m_isOn ? Qt::green : Qt::red;
    painter->setBrush(color);
    qreal circleX = (100 - 18) / 2; // Adjust 100 to your item's width, 20 is the diameter of the circle
    qreal circleY = 30; // Adjust as needed
    painter->drawEllipse(circleX, circleY, 20, 20); // Draw the circle with a diameter of 20

    // Draw the debug rectangle if clicked
    if (m_isClicked) {
        drawDebugRectangle(painter);
    }
}

void DigitalInputIndicator::setIsOn(bool isOn) {
    if (m_isOn == isOn) return;
    m_isOn = isOn;
    emit isOnChanged(isOn);
    update(); // Trigger repaint
}

void DigitalInputIndicator::setInputName(const QString &inputName) {
    if (m_inputName == inputName) return;
    m_inputName = inputName;
    update(); // Trigger repaint
}

void DigitalInputIndicator::setOnClickListener(std::function<void()> onClickListener) {
    m_onClickListener = onClickListener;
}

void DigitalInputIndicator::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_isClicked = !m_isClicked; // Toggle the flag when clicked
        update(); // Trigger repaint to draw the rectangle

        // Call the onClickListener lambda function if it is set
        if (m_onClickListener) {
            m_onClickListener();
        }
    }
    QQuickPaintedItem::mousePressEvent(event); // Call the base class implementation
}

void DigitalInputIndicator::drawDebugRectangle(QPainter *painter) {
    // Draw a rectangle to visualize the click event
    QPen pen(Qt::blue, 2); // Blue color, 2 pixels thick
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0, 0, width(), height());
}
