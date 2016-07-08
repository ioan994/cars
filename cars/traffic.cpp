#include "QDateTime"

#include "traffic.h"
#include "car.h"
#include "road.h"
#include "trafficlight.h"

namespace
{
    class CBackwardRoadAdder
    {
    public:
        CBackwardRoadAdder(CRoad* i_road) : m_currentRoad(i_road)
        {
        }

        // Adds stored road to input road. Stores input road.
        // Returns himself.
        CBackwardRoadAdder& BackwardAddRoad(EDirection i_dir, CRoad* i_road)
        {
            i_road->AddRoad(i_dir, m_currentRoad);
            m_currentRoad = i_road;
            return *this;
        }

        CRoad* GetRoad()
        {
            return m_currentRoad;
        }

    private:
        CRoad* m_currentRoad;
    };
}

CTraffic::CTraffic() :
    m_initialized(false),
    m_tick(0),
    m_cyclesPerSecond(0)
{
}

CTraffic::~CTraffic()
{
}

void CTraffic::Initialize(int i_cyclesPerSecond)
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    const int seriesLength = 4;
    CRoad* startRoad = registerRoad(new CRoad(false, QPointF(150,150)));
    CRoad* crossRoad2 = buildRoadSeries(startRoad, EDirection::East, seriesLength);
    CRoad* crossRoad3 = buildRoadSeries(crossRoad2, EDirection::South, seriesLength);
    CRoad* crossRoad4 = buildRoadSeries(crossRoad3, EDirection::West, seriesLength);
    buildRoadSeries(crossRoad4, EDirection::North, seriesLength-1)->AddRoad(EDirection::North, startRoad);


    CBackwardRoadAdder crossRoad4Appendix(crossRoad4);
    crossRoad4Appendix.BackwardAddRoad(EDirection::North, registerRoad(new CRoad()))
                      .BackwardAddRoad(EDirection::North, registerRoad(new CRoad()))
                      .BackwardAddRoad(EDirection::North, registerRoad(new CRoad(true)));
    buildRoadSeries(crossRoad2, EDirection::East, seriesLength/2)
            ->AddRoad(EDirection::East, EDirection::South, crossRoad4Appendix.GetRoad());


    CBackwardRoadAdder crossRoad3Appendix(crossRoad3);
    crossRoad3Appendix.BackwardAddRoad(EDirection::West, registerRoad(new CRoad()))
                      .BackwardAddRoad(EDirection::West, registerRoad(new CRoad()))
                      .BackwardAddRoad(EDirection::West, registerRoad(new CRoad(true)));
    buildRoadSeries(startRoad, EDirection::North, seriesLength/2)
            ->AddRoad(EDirection::North, EDirection::East, crossRoad3Appendix.GetRoad());

    QColor red(255,0,0);
    QColor blue(0,255,0);
    registerCar(new CCar(280.0/i_cyclesPerSecond, startRoad, EDirection::East, red));
    registerCar(new CCar(120.0/i_cyclesPerSecond, crossRoad3, EDirection::West, blue));

    registerTrafficLight(new CTrafficLight(*startRoad));
    registerTrafficLight(new CTrafficLight(*crossRoad2));
    registerTrafficLight(new CTrafficLight(*crossRoad3));
    registerTrafficLight(new CTrafficLight(*crossRoad4));

    m_cyclesPerSecond = i_cyclesPerSecond;
    m_initialized = true;
}

void CTraffic::OnTimer()
{
    m_tick++;
    if(!m_initialized) return;
    for(auto& car : m_cars)
    {
        car->Move();
    }

    const int trafficLightPeriod = 3;
    if(m_tick % (trafficLightPeriod * m_cyclesPerSecond) == 0)
    {
        for(auto& trafficLight : m_trafficLights)
        {
            trafficLight->Switch();
        }
    }
}

void CTraffic::Draw(QPainter& i_paintContext)
{
    if(!m_initialized) return;
    for(auto& road : m_roads)
    {
        road->Draw(i_paintContext);
    }
    for(auto& car : m_cars)
    {
        car->Draw(i_paintContext);
    }
    for(auto& trafficLight : m_trafficLights)
    {
        trafficLight->Draw(i_paintContext);
    }
}

std::vector<CTraffic::Stat> CTraffic::GetStats()
{
    std::vector<CTraffic::Stat> statVector;
    for(auto& car : m_cars)
    {
        statVector.push_back(Stat(car->GetIdleCycles(), car->GetColor(), car->GetSpeed()));
    }
    return statVector;
}

CRoad* CTraffic::registerRoad(CRoad* i_road)
{
    m_roads.push_back(RoadPtr(i_road));
    return m_roads.back().get();
}

CCar* CTraffic::registerCar(CCar* i_car)
{
    m_cars.push_back(CarPtr(i_car));
    return m_cars.back().get();
}

CTrafficLight* CTraffic::registerTrafficLight(CTrafficLight *i_trafficLight)
{
    m_trafficLights.push_back(TRafficLightPtr(i_trafficLight));
    return m_trafficLights.back().get();
}

CRoad* CTraffic::buildRoadSeries(CRoad* i_start, EDirection i_direction, int i_count)
{
    while(i_count--)
    {
        i_start = i_start->AddRoad(i_direction, registerRoad(new CRoad()));
    }
    return i_start;
}
