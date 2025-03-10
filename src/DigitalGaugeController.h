// DigitalGaugeController.h
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPen>
#include <QFont>

class DigitalGaugeController : public QQuickPaintedItem {
Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString gaugeName READ gaugeName WRITE setGaugeName)

public:
    DigitalGaugeController(QQuickItem *parent = nullptr);

    float value() const { return m_value; }
    void setValue(float value);

    QString unit() const { return m_unit; }
    void setUnit(const QString &unit);

    QString gaugeName() const { return m_gaugeName; }
    void setGaugeName(const QString &gaugeName);

protected:
    void paint(QPainter *painter) override;

signals:
    void valueChanged(float newValue);
    void unitChanged(const QString &newUnit);

private:
    float m_value = 0.0f;
    QString m_unit = "Unit";
    QString m_gaugeName = "GaugeName";
};