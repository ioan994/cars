#include "road.h"
#include "cassert"

const int CRoad::sc_width = 50;

CRoad::CRoad(bool i_isInvisible, const QPointF &i_position):
    CSquareObj(i_position, sc_width),
    m_isBlocked(0),
    m_isInvisible(i_isInvisible)
{
}

CRoad::~CRoad()
{
}

CRoad* CRoad::AddRoad(EDirection i_roadDir, CRoad* i_road)
{
    return AddRoad(i_roadDir, Utils::getOppositeDirection(i_roadDir), i_road);
}

CRoad* CRoad::AddRoad(EDirection i_roadDir, EDirection i_oppositeDirection, CRoad* i_road)
{
    if(i_road == nullptr)
    {
        assert(false);
        return this;
    }

    if(m_position == GetInvalidPoint() && i_road->GetPosition() != GetInvalidPoint())
    {
        m_position = i_road->GetNextTilePos(i_oppositeDirection);
    }
    doAddOutputRoad(i_roadDir, i_road);
    i_road->onAddedToRoad(i_oppositeDirection, this);
    return i_road;
}

CRoad* CRoad::GetRoad(EDirection i_direction)
{
    const auto& roadItr = findRoadByDirection(m_outputRoads, i_direction);
    return roadItr == m_outputRoads.end() ? nullptr : roadItr->second;
}

EDirection CRoad::GetAvailibleDirection()
{
    if(m_outputRoads.empty())
    {
        assert(false);
        return EDirection::North;
    }
    return m_outputRoads[qrand() % m_outputRoads.size()].first;
}

void CRoad::Block()
{
    m_isBlocked++;
}

void CRoad::Unblock()
{
    m_isBlocked--;
}

bool CRoad::IsBlocked()
{
    return m_isBlocked !=0;
}

void CRoad::Draw(QPainter& i_paintContext)
{
    if(m_isInvisible) return;

    i_paintContext.setPen(QPen(QColor(0,0,0), 2));

    bool skipTopLine = false, skipLeftLine = false, skipBottomLine = false, skipRigthLine = false;
    RoadSet allRoads = m_outputRoads;
    allRoads.insert(allRoads.end(), m_inputRoads.begin(), m_inputRoads.end());
    for(const DirectedRoad& directedRoad : allRoads)
    {
        skipTopLine |= directedRoad.first == EDirection::North;
        skipLeftLine |=  directedRoad.first == EDirection::West;
        skipBottomLine |= directedRoad.first == EDirection::South;
        skipRigthLine |=  directedRoad.first == EDirection::East;
    }

    QRectF roomRect = GetRectangle();
    if(!skipTopLine)
    {
        i_paintContext.drawLine(roomRect.topLeft(), roomRect.topRight());
    }
    if(!skipLeftLine)
    {
        i_paintContext.drawLine(roomRect.topLeft(), roomRect.bottomLeft());
    }
    if(!skipBottomLine)
    {
        i_paintContext.drawLine(roomRect.bottomLeft(), roomRect.bottomRight());
    }
    if(!skipRigthLine)
    {
        i_paintContext.drawLine(roomRect.topRight(), roomRect.bottomRight());
    }

    if(m_outputRoads.size() != 1)
    {
        return;
    }
    Utils::drawArrow(GetPosition(), m_outputRoads.front().first, GetWidth()/4, i_paintContext);
}

void CRoad::onAddedToRoad(EDirection i_roadDir, CRoad* i_road)
{
    doAddInputRoad(i_roadDir, i_road);
    if(m_position == GetInvalidPoint())
    {
        m_position = i_road->GetNextTilePos(Utils::getOppositeDirection(i_roadDir));
    }
}

void CRoad::doAddOutputRoad(EDirection i_roadDir, CRoad* i_road)
{
    if(findRoadByDirection(m_outputRoads, i_roadDir) != m_outputRoads.end())
    {
        assert(false);
        return;
    }
    m_outputRoads.push_back(DirectedRoad(i_roadDir, i_road));
}

void CRoad::doAddInputRoad(EDirection i_roadDir, CRoad* i_road)
{
    if(findRoadByDirection(m_inputRoads, i_roadDir) != m_inputRoads.end())
    {
        assert(false);
        return;
    }
    m_inputRoads.push_back(DirectedRoad(i_roadDir, i_road));
}

CRoad::RoadSet::const_iterator CRoad::findRoadByDirection(const RoadSet& i_roads, EDirection i_direction)
{
    return std::find_if(i_roads.begin(), i_roads.end(),
                        [i_direction](const DirectedRoad& i_directedRoad) {return i_directedRoad.first == i_direction;});
}

QPointF CRoad::GetNextTilePos(EDirection i_direction)
{
    if(GetPosition() == GetInvalidPoint()) return GetInvalidPoint();
    return Utils::addDistance(GetPosition(), i_direction, m_width);
}

/*
COneDirectionRoad::COneDirectionRoad(const QPoint& i_position):
    CRoad(i_position)
{
}

COneDirectionRoad::~COneDirectionRoad()
{
}

void COneDirectionRoad::doAddOutputRoad(EDirection i_roadDir, CRoad* i_road)
{
    if(!m_outputRoads.empty())
    {
        assert(false);
        return;
    }
    m_outputRoads.push_back(DirectedRoad(i_roadDir, i_road));
}

void COneDirectionRoad::doAddInputRoad(EDirection i_roadDir, CRoad* i_road)
{
    if(!m_inputRoads.empty())
    {
        assert(false);
        return;
    }
    m_inputRoads.push_back(DirectedRoad(i_roadDir, i_road));
}
*/
