#ifndef TacticsPathfinding_h
#define TacticsPathfinding_h

#include "Types.h"
#include "Map.h"
#include "NodeList.h"

TacticsMapNodeList* Tactics_Pathfind(TacticsMap* map, int x1, int y1, int x2, int y2, float range);
TacticsMapNodeList* Tactics_GetNeighborsOfNode(TacticsMap* map, TacticsMapNode* node);

#endif
