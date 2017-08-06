#ifndef MapNode_h
#define MapNode_h

#include <stdbool.h>
#include "Types.h"

TacticsMapNode* Tactics_CreateMapNode(int x, int y);
float Tactics_MapNode_TotalLocalCost(TacticsMapNode* node);
float Tactics_MapNode_TotalPathCost(TacticsMapNode* node);
float Tactics_MapNode_PotentialTotalPathCost(TacticsMapNode* node, TacticsMapNode* newParent);
void Tactics_MapNode_SetOrigin(TacticsMapNode* node, TacticsMapNode* target);
void Tactics_MapNode_RefreshFromNeighbor(TacticsMapNode* node, TacticsMapNode* target, TacticsMapNode* neighbor);
int Tactics_MapNode_X(TacticsMapNode* node);
int Tactics_MapNode_Y(TacticsMapNode* node);
float Tactics_MapNode_HeuristicCost(TacticsMapNode* node);
bool Tactics_MapNode_Impassable(TacticsMapNode* node);
TacticsMapNode* Tactics_MapNode_Parent(TacticsMapNode* node);

#endif
