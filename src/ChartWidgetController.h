#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QQuickPaintedItem>
#include "qcustomplot.h"

class CustomPlot : public QQuickPaintedItem
{
Q_OBJECT

public:
    CustomPlot(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

private:
    QCustomPlot *m_customPlot;
};

#endif // CUSTOMPLOT_H
