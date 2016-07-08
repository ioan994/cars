#ifndef CCAR_H
#define CCAR_H

#include "QPainter"

#include "squareobj.h"

class CRoad;
enum class EDirection;

class CCar : public CSquareObj
{
public:
    CCar(float i_speed, CRoad* i_road, EDirection i_dir, QColor i_color);
    virtual ~CCar();

    void Move();
    int GetIdleCycles() {return m_idleCycles;}
    QColor GetColor() {return m_color;}
    float GetSpeed() {return m_speed;}

    virtual void Draw(QPainter& i_paintContext) override;

    static const int sc_width;

private:

    void startMove();
    void endMove();
    bool isMoving();

    float m_speed;
    bool m_isMovingToNextRoad;
    CRoad* m_currentRoad;
    EDirection m_movementDirection;
    QColor m_color;
    int m_idleCycles;
};

#endif // CCAR_H
