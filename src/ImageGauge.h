#ifndef IMAGEGAUGE_H
#define IMAGEGAUGE_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPen>
#include <QFont>

class ImageGauge : public QQuickPaintedItem
{
Q_OBJECT
    Q_PROPERTY(QString imagePrefix READ imagePrefix WRITE setImagePrefix NOTIFY imagePrefixChanged)
    Q_PROPERTY(int numImages READ numImages WRITE setNumImages NOTIFY numImagesChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int xValue READ xValue WRITE setXValue NOTIFY xValueChanged)
    Q_PROPERTY(int yValue READ yValue WRITE setYValue NOTIFY yValueChanged)
    Q_PROPERTY(QString sourceString READ sourceString WRITE setSourceString NOTIFY sourceStringChanged)

public:
    ImageGauge(QQuickItem *parent = nullptr);

    QString imagePrefix() const;
    void setImagePrefix(const QString &prefix);

    int minValue() const;
    void setMinValue(int min, int imageIndex);

    int maxValue() const;
    void setMaxValue(int max, int imageIndex);

    int numImages() const;
    void setNumImages(int num);

    int value() const;
    void setValue(int newValue);

    int xValue() const;
    void setXValue(int newValue);

    int yValue() const;
    void setYValue(int newValue);

    QString sourceString() const;
    void setSourceString(QString newValue);

signals:
    void imagePrefixChanged();
    void minValueChanged();
    void maxValueChanged();
    void numImagesChanged();
    void valueChanged();
    void xValueChanged();
    void yValueChanged();
    void sourceStringChanged();

protected:
    void paint(QPainter *painter) override;

private:
    QString m_imagePrefix;
    QString m_SourceString;
    int m_minValue;
    int m_maxValue;
    int m_numImages;
    int m_value;
    int m_xvalue;
    int m_yvalue;
};

#endif // IMAGEGAUGE_H