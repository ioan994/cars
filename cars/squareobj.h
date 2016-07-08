#ifndef CSQUAREOBJ_H
#define CSQUAREOBJ_H

#include "QPoint"
#include "QRect"
#include "QPainter"

enum class EDirection
{
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

class CSquareObj
{
public:
    CSquareObj(const QPointF& i_position, int i_width);
    virtual ~CSquareObj();

    const QPointF& GetPosition();
    QRectF GetRectangle();
    int GetWidth();

    virtual void Draw(QPainter& i_paintContext) = 0;

    static const QPointF& GetInvalidPoint();

protected:
    QPointF m_position;
    int m_width;

    static const QPointF sc_invalidPoint;
};

namespace Utils
{
    EDirection getOppositeDirection(EDirection i_direction);
    bool isVertical(EDirection i_direction);
    bool isHorisontal(EDirection i_direction);
    QPointF addDistance(const QPointF& i_point, EDirection i_direction, int i_distance);
    QPointF getClosestPoint(const QPointF& i_startPoint, const QPointF& i_firstPoint, const QPointF& i_secondPoint);
    void drawArrow(const QPointF& i_position, EDirection i_direction, int i_size, QPainter &i_paintContext);
    QRectF getRect(const QPointF& i_point, int i_width);
}

#endif // CSQUAREOBJ_H
