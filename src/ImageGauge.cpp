#include "ImageGauge.h"


ImageGauge::ImageGauge(QQuickItem *parent)
        : QQuickPaintedItem(parent) {
    // You can initialize your item here
}
QString ImageGauge::imagePrefix() const {
    return m_imagePrefix;
}

void ImageGauge::setImagePrefix(const QString &prefix) {
    //Check if prefix contains .png, if it does it tells us that this gauge contains only 1 image
    if(prefix.contains(".png")){
        m_numImages = 1;
    }
    if (m_imagePrefix != prefix) {
        m_imagePrefix = prefix;
        emit imagePrefixChanged();
    }
}

int ImageGauge::minValue() const {
    return m_minValue;
}

void ImageGauge::setMinValue(int min, int imageIndex) {
    m_minValue = min;
}

int ImageGauge::maxValue() const {
    return m_maxValue;
}

void ImageGauge::setMaxValue(int max, int imageIndex) {
    m_maxValue = max;
}

int ImageGauge::numImages() const {
    return m_numImages;
}

void ImageGauge::setNumImages(int num) {
    if (m_numImages != num) {
        m_numImages = num;
        emit numImagesChanged();
    }
}

int ImageGauge::value() const {
    return m_value;
}

void ImageGauge::setValue(int newValue) {
    //Check to see if this gauge is a single image
    if(m_numImages == 1){
        //Value of 1 implies show the image else don't show the image.
        if(newValue == 1){
            m_SourceString = m_imagePrefix;
            this->setVisible(true);
        }else{
            this->setVisible(false);
        }
        update();
        return;
    }

    // Scale newValue to an image index
    double range = m_maxValue - m_minValue;
    double scale = (m_numImages - 1) / range;
    int imageIndex = static_cast<int>((newValue - m_minValue) * scale);

    // Form the complete image path
    QString imagePath = m_imagePrefix + QString("%1").arg(imageIndex, 4, 10, QChar('0')) + ".png";

    // Check if the actual value or source string has changed to minimize updates
    if (m_value != newValue || m_SourceString != imagePath) {
        m_value = newValue;
        m_SourceString = imagePath;
        update();  // Request a repaint
        emit valueChanged();
        emit sourceStringChanged();  // Notify about the source string change
    }
}

int ImageGauge::xValue() const{
    return this->m_xvalue;
}

int ImageGauge::yValue() const{
    return this->m_yvalue;
}

void ImageGauge::setXValue(int newValue)
{
    this->m_xvalue = newValue;
}

void ImageGauge::setYValue(int newValue)
{
    this->m_yvalue = newValue;
}

QString ImageGauge::sourceString() const{
    return this->m_SourceString;
}

void ImageGauge::setSourceString(QString newValue){
    this->m_SourceString = newValue;
    update();
}

void ImageGauge::paint(QPainter *painter) {
    QImage image(m_SourceString);
    if (!image.isNull()) {
        painter->drawImage(boundingRect(), image);
    }
}