#ifndef TacticsMap_h
#define TacticsMap_h

#include "Types.h"
#include "MapNode.h"

TacticsMap* Tactics_CreateMap(int width, int height);
void Tactics_DestroyMap(TacticsMap* map);
bool Tactics_PointInBounds(TacticsMap* map, int x, int y);
int Tactics_Map_Width(TacticsMap* map);
int Tactics_Map_Height(TacticsMap* map);
TacticsMapNode* Tactics_Map_GetNodeAt(TacticsMap* map, int x, int y);

#endif
