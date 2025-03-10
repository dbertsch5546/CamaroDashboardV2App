#include "ChartWidgetController.h"

CustomPlot::CustomPlot(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    m_customPlot = new QCustomPlot();
    // Example setup
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setData(QVector<double>() << 1 << 2 << 3 << 4, QVector<double>() << 1 << 4 << 9 << 16);
    m_customPlot->replot();
}

void CustomPlot::paint(QPainter *painter)
{
    if (m_customPlot)
    {
        QPixmap picture(boundingRect().size().toSize());
        QCPPainter qcpPainter(&picture);
        m_customPlot->toPainter(&qcpPainter);
        painter->drawPixmap(0, 0, picture);
    }
}
