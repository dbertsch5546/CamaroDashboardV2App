#include "LogWidgetController.h"
#include <QTimer>
#include <QDateTime>
#include <QPen>
#include <QFont>

LogWidgetController::LogWidgetController(QQuickItem *parent)
        : QQuickPaintedItem(parent),
          m_logText(""),
          m_xValue(0),
          m_yValue(0),
          m_width(200),  // Assuming default width
          m_height(150),  // Assuming default height
          m_fontSize(12),  // Default font size
          m_fontColor("#FFFFFF"),  // Default font color (white)
          m_updatePending(false)
{
    setFlag(QQuickItem::ItemHasContents, true);
    connect(&m_updateTimer, &QTimer::timeout, this, &LogWidgetController::updateTimeout);
    m_updateTimer.start(500); // Throttle updates to once per second
}

QString LogWidgetController::logText() const {
    return m_logText;
}

void LogWidgetController::setLogText(const QString &text) {
    if (m_logText != text) {
        m_logText = text;
        emit logTextChanged();
        m_updatePending = true;
    }
}

int LogWidgetController::xValue() const {
    return m_xValue;
}

void LogWidgetController::setXValue(int newValue) {
    if (m_xValue != newValue) {
        m_xValue = newValue;
        emit xValueChanged();
        m_updatePending = true;
    }
}

int LogWidgetController::yValue() const {
    return m_yValue;
}

void LogWidgetController::setYValue(int newValue) {
    if (m_yValue != newValue) {
        m_yValue = newValue;
        emit yValueChanged();
        m_updatePending = true;
    }
}

int LogWidgetController::width() const {
    return m_width;
}

void LogWidgetController::setWidth(int newValue) {
    if (m_width != newValue) {
        m_width = newValue;
        emit widthChanged();
        m_updatePending = true;
    }
}

int LogWidgetController::height() const {
    return m_height;
}

void LogWidgetController::setHeight(int newValue) {
    if (m_height != newValue) {
        m_height = newValue;
        emit heightChanged();
        m_updatePending = true;
    }
}

int LogWidgetController::fontSize() const {
    return m_fontSize;
}

void LogWidgetController::setFontSize(int newValue) {
    if (m_fontSize != newValue) {
        m_fontSize = newValue;
        emit fontSizeChanged();
        m_updatePending = true;
    }
}

QString LogWidgetController::fontColor() const {
    return m_fontColor;
}

void LogWidgetController::setFontColor(QString newValue) {
    if (m_fontColor != newValue) {
        m_fontColor = newValue;
        emit fontColorChanged();
        m_updatePending = true;
    }
}

void LogWidgetController::addLogEntry(const std::string &entry, QColor color) {
    // Create log entry
    logEntry newEntry;
    newEntry.entry = QString::fromStdString(entry);
    newEntry.color = color;
    newEntry.timestamp = time(nullptr);
    m_logEntries.push_back(newEntry);
    m_updatePending = true;
}

std::string LogWidgetController::printLogEntries() const {
    std::string entries;
    for (const auto &entry : m_logEntries) {
        entries += entry.entry.toStdString() + "\n";
    }
    return entries;
}

void LogWidgetController::clearLogEntries() {
    m_logEntries.clear();
    m_updatePending = true;
}

void LogWidgetController::paint(QPainter *painter) {
    if (!m_updatePending) {
        return;
    }

    // Base coordinates for drawing
    int startX = m_xValue;
    int startY = m_yValue;

    // No background fill to make it transparent

    // Set up the pen and font for the title
    QPen titlePen(Qt::white, 2); // White color, 2 pixels thick for the title
    painter->setPen(titlePen);
    QFont titleFont = painter->font();
    titleFont.setPointSize(m_fontSize + 4); // Slightly larger font size for the title
    titleFont.setBold(true); // Make the title bold
    painter->setFont(titleFont);
    // Draw the title
    QString title = "Vehicle Log:";
    QRectF titleRect(startX, startY, m_width, 30); // Assuming 30px is enough for the title height
    painter->drawText(titleRect, Qt::AlignCenter, title);

    // Draw the top line
    painter->drawLine(startX, m_yValue, startX + m_width, m_yValue);

    // Adjust startY for the log entries, add space below the title
    startY += 35; // Move start position below the title, with some space

    // Set up the pen and font for log entries
    QFont textFont = painter->font();
    textFont.setPointSize(m_fontSize);
    textFont.setBold(false); // Log entries are not bold
    painter->setFont(textFont);

    // Initialize totalHeight with the space taken up by the title
    int totalHeight = 35; // Height occupied by the title

    // Draw each log entry and calculate total height
    for (const logEntry &entry : m_logEntries) {
        // Set color according to log entry
        QPen textPen(QColor(entry.color), 2); // Set color for the text
        painter->setPen(textPen);

        int entryHeight = 25; // Set spacing between lines
        QRectF rect(startX, startY, m_width, entryHeight);
        painter->drawText(rect, Qt::AlignLeft, entry.entry);
        startY += entryHeight + 1; // Move to the next line
        totalHeight += entryHeight + 1; // Accumulate total height
    }

    // Draw a bounding rectangle around the widget content
    QPen boxPen(Qt::red, 2); // Red color, 2 pixels thick for bounding box
    painter->setPen(boxPen);
    QRectF boundingRect(m_xValue, m_yValue, m_width, totalHeight);
    //painter->drawRect(boundingRect);

    // Draw the bottom line at a fixed position relative to initial startY
    QPen bottomLinePen(Qt::white, 2);
    painter->setPen(bottomLinePen);
    int bottomLineY = m_yValue + m_height + 100; // Fixed position
    painter->drawLine(startX, bottomLineY, startX + m_width, bottomLineY);

    m_updatePending = false;
}

void LogWidgetController::updateTimeout() {
    if (m_updatePending) {
        update();
    }
}
