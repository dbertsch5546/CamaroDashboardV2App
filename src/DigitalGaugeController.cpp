// DigitalGaugeController.cpp
#include "DigitalGaugeController.h"

DigitalGaugeController::DigitalGaugeController(QQuickItem *parent)
        : QQuickPaintedItem(parent) {
    // You can initialize your item here
}

void DigitalGaugeController::paint(QPainter *painter) {
    // Set the pen for your lines
    QPen pen(Qt::red, 2); // Black color, 2 pixels thick
    // Add more lines as needed
    // Set up the font for the text
    QFont font("Roboto", 8); // Specify font name and size
    painter->setFont(font);
    painter->setPen(pen);
    //Draw the gauge name
    QRectF textRect = painter->boundingRect(QRectF(0, 0, 0, 0), Qt::AlignCenter, this->gaugeName());
    qreal x = (100 - textRect.width()) / 2; // Adjust 100 to your item's width
    qreal y = 8; // Adjust as needed
    painter->drawText(x, y, this->gaugeName());

    // Draw lines for the top of the widget
    painter->drawLine(0, 10, 0, 0); // Example line
    painter->drawLine(0, 0, x - 10, 0);
    painter->drawLine(x + textRect.width() + 10, 0, 100, 0);
    painter->drawLine(100, 0, 100, 10);
    //Draw the value
    QFont fontValue("Roboto", 16); // Specify font name and size
    painter->setFont(fontValue);
    textRect = painter->boundingRect(QRectF(0, 0, 0, 0), Qt::AlignLeft, QString::number(this->value(), 'f', 2));
    x = (100 - textRect.width()) / 3; // Adjust 100 to your item's width
    y = 40; // Adjust as needed
    painter->drawText(x, y, QString::number(this->value(), 'f', 2));
    //Draw the units
    QFont fontUnits("Roboto", 8); // Specify font name and size
    painter->setFont(fontUnits);
    textRect = painter->boundingRect(QRectF(0, 0, 0, 0), Qt::AlignLeft, this->unit());
    x = 100 - 25; // Adjust 100 to your item's width
    y = 39; // Adjust as needed
    painter->drawText(x, y, this->unit());
}

void DigitalGaugeController::setUnit(const QString &unit) {
    if (m_unit == unit) return;
    m_unit = unit;
    emit unitChanged(unit);
    update(); // Trigger repaint
}

void DigitalGaugeController::setValue(float value) {
    if (m_value == value) return;
    m_value = value;
    emit valueChanged(value);
    update(); // Trigger repaint
}

void DigitalGaugeController::setGaugeName(const QString &gaugeName) {
    if (m_gaugeName == gaugeName) return;
    m_gaugeName = gaugeName;
    update(); // Trigger repaint
}