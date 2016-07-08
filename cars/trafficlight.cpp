#include "road.h"
#include "trafficlight.h"

CTrafficLight::CTrafficLight(CRoad& i_road) :
    m_switched(false),
    m_road(i_road)
{
}

CTrafficLight::~CTrafficLight()
{
}

void CTrafficLight::Switch()
{
    if(m_switched)
    {
        m_road.Unblock();
    }
    else
    {
        m_road.Block();
    }
    m_switched = !m_switched;
}

void CTrafficLight::Draw(QPainter& i_paintContext)
{
    int eightsWidth = m_road.GetWidth()/8;
    QPointF lightPosition = m_road.GetPosition();
    lightPosition = Utils::addDistance(lightPosition, EDirection::North, 3 * eightsWidth);
    lightPosition = Utils::addDistance(lightPosition, EDirection::East, 3 * eightsWidth);

    QColor trafficLightColor = m_switched ? QColor(255,0,0) : QColor(0,255,0);
    QPen redPen(QColor(0,0,0), 1);
    QBrush fillBrush(trafficLightColor, Qt::SolidPattern);
    i_paintContext.setPen(redPen);
    i_paintContext.setBrush(fillBrush);
    i_paintContext.drawEllipse(Utils::getRect(lightPosition, eightsWidth));
}
