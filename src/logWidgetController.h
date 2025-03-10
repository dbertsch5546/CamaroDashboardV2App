#ifndef LOGWIDGETCONTROLLER_H
#define LOGWIDGETCONTROLLER_H

#include <QObject>

class LogWidgetController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

public:
    explicit LogWidgetController(QObject *parent = nullptr);

    int width() const;
    void setWidth(int newWidth);

    int height() const;
    void setHeight(int newHeight);

    signals:
            void widthChanged(int);
    void heightChanged(int);

private:
    int m_width;
    int m_height;
};

#endif // LOGWIDGETCONTROLLER_H
