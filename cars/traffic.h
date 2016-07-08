#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "memory"
#include "list"

#include "QPainter"

class CCar;
class CRoad;
class CTrafficLight;
enum class EDirection;

class CTraffic
{
public:

    struct Stat
    {
        Stat(int i_idleCycles, QColor i_color, float i_speed):
            m_idleCycles(i_idleCycles),
            m_machineColor(i_color),
            m_machineSpeed(i_speed){}

        int m_idleCycles;
        QColor m_machineColor;
        float m_machineSpeed;
    };

    CTraffic();
    ~CTraffic();

    void Initialize(int i_cyclesPerSecond);
    void OnTimer();
    void Draw(QPainter& i_paintContext);
    std::vector<Stat> GetStats();

private:
    typedef std::unique_ptr<CRoad> RoadPtr;
    typedef std::unique_ptr<CCar> CarPtr;
    typedef std::unique_ptr<CTrafficLight> TRafficLightPtr;

    CRoad* registerRoad(CRoad* i_road);
    CCar* registerCar(CCar* i_car);
    CTrafficLight* registerTrafficLight(CTrafficLight* i_trafficLight);
    CRoad* buildRoadSeries(CRoad* i_start, EDirection i_direction, int i_count);

    std::list<CarPtr> m_cars;
    std::list<RoadPtr> m_roads;
    std::list<TRafficLightPtr> m_trafficLights;
    bool m_initialized;
    int m_tick;
    int m_cyclesPerSecond;
};

#endif // TRAFFIC_H
