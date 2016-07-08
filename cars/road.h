#ifndef CROAD_H
#define CROAD_H

#include <utility>

#include "squareobj.h"

class CRoad : public CSquareObj
{
public:
    CRoad(bool i_isInvisible = false, const QPointF& i_position = GetInvalidPoint());
    virtual ~CRoad();

    CRoad* AddRoad(EDirection i_roadDir, CRoad* i_road);
    CRoad* AddRoad(EDirection i_roadDir, EDirection i_oppositeDirection, CRoad* i_road);
    CRoad* GetRoad(EDirection i_direction);
    EDirection GetAvailibleDirection();
    QPointF GetNextTilePos(EDirection i_direction);
    void Block();
    void Unblock();
    bool IsBlocked();

    virtual void Draw(QPainter& i_paintContext) override;

    static const int sc_width;

protected:
    typedef std::pair<EDirection, CRoad*> DirectedRoad;
    typedef std::vector<DirectedRoad> RoadSet;

    void onAddedToRoad(EDirection i_roadDir, CRoad* i_road);
    void doAddOutputRoad(EDirection i_roadDir, CRoad* i_road);
    void doAddInputRoad(EDirection i_roadDir, CRoad* i_road);
    RoadSet::const_iterator findRoadByDirection(const RoadSet& i_roads, EDirection i_direction);

    RoadSet m_outputRoads;
    RoadSet m_inputRoads;
    int m_isBlocked;
    bool m_isInvisible;
};

/*
class COneDirectionRoad : public CRoad
{
public:
    COneDirectionRoad(const QPoint& i_position = GetInvalidPoint());
    virtual ~COneDirectionRoad();

    virtual void doAddOutputRoad(EDirection i_roadDir, CRoad* i_road) override;
    virtual void doAddInputRoad(EDirection i_roadDir, CRoad* i_road) override;
};
*/

#endif // CROAD_H
