#include "arc.h"

#include <QDebug>

Arc::Arc(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_color(Qt::red), m_penWidth(1.2), m_startAngle(45), m_endAngle(135)
{
    // Important, otherwise the paint method is never called
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (option);
    Q_UNUSED (widget);

    QPen pen(color(), penWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawArc(this->boundingRect(), m_startAngle * 16, (m_endAngle - m_startAngle) * 16);
}
