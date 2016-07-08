#include "cassert"

#include "car.h"
#include "road.h"

const int CCar::sc_width = (int)(CRoad::sc_width * 0.6);

CCar::CCar(float i_speed, CRoad* i_road, EDirection i_dir, QColor i_color):
    CSquareObj(i_road->GetPosition(), sc_width),
    m_speed(i_speed),
    m_isMovingToNextRoad(false),
    m_currentRoad(i_road),
    m_movementDirection(i_dir),
    m_color(i_color),
    m_idleCycles(0)
{
    m_currentRoad->Block();
}

CCar::~CCar()
{
}

void CCar::Move()
{
    if(!isMoving())
    {
        startMove();
    }
    if(!isMoving())
    {
        return;
    }

    QPointF nextTilePos = m_currentRoad->GetNextTilePos(m_movementDirection);
    QPointF nextCarPos = Utils::addDistance(m_position, m_movementDirection, m_speed);
    m_position = Utils::getClosestPoint(m_position, nextCarPos, nextTilePos);

    if(m_position == nextTilePos)
    {
        endMove();
    }
}

void CCar::Draw(QPainter& i_paintContext)
{
    QPen carPen(m_color, 1);
    QBrush fillBrush(m_color, Qt::SolidPattern);
    i_paintContext.setPen(carPen);
    i_paintContext.setBrush(fillBrush);
    i_paintContext.drawRect(GetRectangle());
}

void CCar::startMove()
{
    CRoad* nextRoad = m_currentRoad->GetRoad(m_movementDirection);
    if(nextRoad->IsBlocked())
    {
        m_idleCycles++;
        return;
    }
    nextRoad->Block();
    m_isMovingToNextRoad = true;
}

void CCar::endMove()
{
    CRoad* nextRoad = m_currentRoad->GetRoad(m_movementDirection);
    QPointF nextRoadPos = nextRoad->GetPosition();
    m_position = nextRoadPos;
    m_isMovingToNextRoad = false;
    m_currentRoad->Unblock();
    m_currentRoad = m_currentRoad->GetRoad(m_movementDirection);
    m_movementDirection = m_currentRoad->GetAvailibleDirection();
}

bool CCar::isMoving()
{
    return m_isMovingToNextRoad;
}
