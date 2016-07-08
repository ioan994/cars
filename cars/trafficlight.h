#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "squareobj.h"

class CRoad;

class CTrafficLight
{
public:
    CTrafficLight(CRoad &i_road);
    virtual ~CTrafficLight();

    void Switch();
    void Draw(QPainter& i_paintContext);

private:
    bool m_switched;
    CRoad& m_road;
};

#endif // TRAFFICLIGHT_H
