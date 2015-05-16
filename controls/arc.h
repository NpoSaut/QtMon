#ifndef ARC_H
#define ARC_H

#include <QDeclarativeItem>
#include <QPainter>

class Arc : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged);
    Q_PROPERTY(float penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged);
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged);
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle NOTIFY endAngleChanged);

    QColor m_color;
    float m_penWidth;
    int m_startAngle;
    int m_endAngle;

public:
    explicit Arc(QDeclarativeItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor color() const { return m_color; }
    float penWidth() const { return m_penWidth; }
    int startAngle() const { return m_startAngle; }
    int endAngle() const { return m_endAngle; }

signals:
    void colorChanged(QColor arg);
    void penWidthChanged(float arg);
    void startAngleChanged(int arg);
    void endAngleChanged(int arg);

public slots:

void setColor(QColor arg)
{
    if (m_color != arg) {
        m_color = arg;
        emit colorChanged(arg);
        update();
    }
}
void setPenWidth(float arg)
{
    if (m_penWidth != arg) {
        m_penWidth = arg;
        emit penWidthChanged(arg);
        update();
    }
}
void setStartAngle(int arg)
{
    if (m_startAngle != arg) {
        m_startAngle = arg;
        emit startAngleChanged(arg);
        update();
    }
}
void setEndAngle(int arg)
{
    if (m_endAngle != arg) {
        m_endAngle = arg;
        emit endAngleChanged(arg);
        update();
    }
}
};

QML_DECLARE_TYPE(Arc)

#endif // ARC_H
