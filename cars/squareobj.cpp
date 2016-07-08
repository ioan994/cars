#include "cassert"
#include "cmath"

#include "squareobj.h"


namespace
{
    double calcDistance(const QPointF& i_firstPoint, const QPointF& i_secondPoint)
    {
        return sqrt(pow(i_firstPoint.x() - i_secondPoint.x(),2) + pow(i_firstPoint.y() - i_secondPoint.y(), 2));
    }
}

namespace Utils
{
    EDirection getOppositeDirection(EDirection i_direction)
    {
        const int val = static_cast<int>(i_direction);
        return static_cast<EDirection>(val < 2 ? val+2 : val-2);
    }

    bool isVertical(EDirection i_direction)
    {
        return static_cast<int>(i_direction) % 2 == 0;
    }

    bool isHorisontal(EDirection i_direction)
    {
        return !isVertical(i_direction);
    }

    QPointF addDistance(const QPointF& i_point, EDirection i_direction, int i_distance)
    {
        switch(i_direction)
        {
            case EDirection::North:
                return QPointF(i_point.x(), i_point.y()-i_distance);
            case EDirection::South:
                return QPointF(i_point.x(), i_point.y()+i_distance);
            case EDirection::West:
                return QPointF(i_point.x()-i_distance, i_point.y());
            case EDirection::East:
                return QPointF(i_point.x()+i_distance, i_point.y());
        }
        assert(false);
        return i_point;
    }

    QPointF getClosestPoint(const QPointF &i_startPoint, const QPointF &i_firstPoint, const QPointF &i_secondPoint)
    {
        return calcDistance(i_startPoint, i_firstPoint) < calcDistance(i_startPoint, i_secondPoint) ?
                    i_firstPoint : i_secondPoint;
    }

    void drawArrow(const QPointF& i_position, EDirection i_direction, int i_size, QPainter &i_paintContext)
    {
        QColor blackColor(0,0,0);
        QPen blackPen(blackColor, 1);
        i_paintContext.setPen(blackPen);

        const int halfWidth = i_size/2;
        const QPointF middleLeftPoint = addDistance(i_position, EDirection::West, halfWidth);
        const QPointF middleRightPoint = addDistance(i_position, EDirection::East, halfWidth);
        const QPointF centerTopPoint = addDistance(i_position, EDirection::North, halfWidth);
        const QPointF centerBottomPoint = addDistance(i_position, EDirection::South, halfWidth);

        if(isVertical(i_direction))
        {
             i_paintContext.drawLine(centerTopPoint, centerBottomPoint);
        }
        else
        {
            i_paintContext.drawLine(middleLeftPoint, middleRightPoint);
        }

        if(i_direction == EDirection::North || i_direction == EDirection::East)
        {
            i_paintContext.drawLine(centerTopPoint, middleRightPoint);
        }
        if(i_direction == EDirection::East || i_direction == EDirection::South)
        {
            i_paintContext.drawLine(middleRightPoint, centerBottomPoint);
        }
        if(i_direction == EDirection::South || i_direction == EDirection::West)
        {
            i_paintContext.drawLine(centerBottomPoint, middleLeftPoint);
        }
        if(i_direction == EDirection::West || i_direction == EDirection::North)
        {
            i_paintContext.drawLine(middleLeftPoint, centerTopPoint);
        }
    }

    QRectF getRect(const QPointF& i_point, int i_width)
    {
        const int halfWidth = i_width/2;
        const QPointF topLeft(i_point.x()-halfWidth, i_point.y()-halfWidth);
        const QPointF bottomRight(i_point.x()+halfWidth, i_point.y()+halfWidth);
        return QRectF(topLeft, bottomRight);
    }
}

const QPointF CSquareObj::sc_invalidPoint = QPointF(-1,-1);

CSquareObj::CSquareObj(const QPointF& i_position, int i_width):
    m_position(i_position),
    m_width(i_width)
{
}

CSquareObj::~CSquareObj()
{
}

const QPointF& CSquareObj::GetPosition()
{
    return m_position;
}

int CSquareObj::GetWidth()
{
    return m_width;
}

QRectF CSquareObj::GetRectangle()
{
    return Utils::getRect(m_position, m_width);
}

const QPointF &CSquareObj::GetInvalidPoint()
{
    return sc_invalidPoint;
}
