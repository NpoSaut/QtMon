#include "needle.h"

#include <math.h>

Needle::Needle(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_color(Qt::red), m_fillColor(Qt::transparent), m_penWidth(1.2), m_angle(0), m_ringRadius(10), m_cutRaduis(0)
{
    // Important, otherwise the paint method is never called
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void Needle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (option);
    Q_UNUSED (widget);

    QPen pen(color(), penWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush brush(fillColor());

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    double r = ringRadius();

    double phi = rad(angle());
    double alpha = atan2(height() * sin(phi), width() * cos(phi));

    QPointF o(0.5 * width(), 0.5 * height());
    QPointF c = o + QPointF  (0.5 * width()  * cos(phi), - 0.5 * height() * sin(phi));

    double gamma = acos(r/QLineF(o, c).length());

    QPainterPath path(c);
    QRectF centerRect(o - QPointF(r, r), 2*QSizeF(r, r));
    path.arcTo(centerRect, grad(alpha + gamma), grad(2 * M_PI - 2 * gamma));
    path.lineTo(c);

    float q = cutRadius();
    QPainterPath cutter;
    cutter.addEllipse(QRectF(o - 0.5 * QPointF(width() * q, height() * q),
                             QSizeF(width() * q, height() * q)));

    path = path.subtracted(cutter);
    painter->drawPath(path);
}
