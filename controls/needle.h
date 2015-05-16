#ifndef NEEDLE_H
#define NEEDLE_H

#include <QDeclarativeItem>
#include <QPainter>
#include <qmath.h>

class Needle : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(float penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)
    Q_PROPERTY(int ringRadius READ ringRadius WRITE setRingRadius NOTIFY ringRadiusChanged)
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(float cutRadius READ cutRadius WRITE setCutRaduis NOTIFY cutRaduisChanged)

public:
    explicit Needle(QDeclarativeItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor color() const { return m_color; }
    float penWidth() const { return m_penWidth; }
    float angle() const { return m_angle; }
    int ringRadius() const { return m_ringRadius; }
    QColor fillColor() const { return m_fillColor; }
    float cutRadius() const { return m_cutRaduis; }

signals:

    void colorChanged(QColor arg);
    void penWidthChanged(float arg);
    float angleChanged(int arg);
    void ringRadiusChanged(int arg);
    void fillColorChanged(QColor arg);
    void cutRaduisChanged(float arg);

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
    void setAngle(float arg)
    {
        if (m_angle != arg) {
            m_angle = arg;
            emit angleChanged(arg);
            update();
        }
    }

    void setRingRadius(int arg)
    {
        if (m_ringRadius != arg) {
            m_ringRadius = arg;
            emit ringRadiusChanged(arg);
            update();
        }
    }

    void setFillColor(QColor arg)
    {
        if (m_fillColor != arg) {
            m_fillColor = arg;
            emit fillColorChanged(arg);
        }
    }

    void setCutRaduis(float arg)
    {
        if (m_cutRaduis != arg) {
            m_cutRaduis = arg;
            emit cutRaduisChanged(arg);
        }
    }

private:
    float rad(float grad) { return grad * M_PI / 180.0; }
    float grad(float rad) { return rad * 180.0 / M_PI; }

    QColor m_color;
    QColor m_fillColor;
    float m_penWidth;
    float m_angle;
    int m_ringRadius;
    float m_cutRaduis;
};

QML_DECLARE_TYPE(Needle)

#endif // NEEDLE_H
