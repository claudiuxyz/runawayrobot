#ifndef OVERLAPPINGBOARDS_H
#define OVERLAPPINGBOARDS_H
#include "Algorithm.h"
#include "tools.h"

class AvoidDeadEnds : public Algorithm
{
public:
    AvoidDeadEnds();
    virtual bool ApplyAlgorithm();
    virtual ~AvoidDeadEnds();
private:
    void MarkDeadEnds();
    bool IsRoadBlocked(int x, int y);
    bool PostMarkDeadEnds();
    bool IsPositionHidden(int x, int y);
    bool Search(int pathLength);
};

#endif // OVERLAPPINGBOARDS_H
