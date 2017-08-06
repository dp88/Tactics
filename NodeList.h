#ifndef TacticsNodeList_h
#define TacticsNodeList_h

#include "Map.h"

typedef struct TacticsMapNodeList {
    int length;
    TacticsMapNode** contents;
} TacticsMapNodeList;

TacticsMapNodeList* Tactics_MapNodeList_Create();
void Tactics_MapNodeList_Destroy(TacticsMapNodeList* list);
void Tactics_MapNodeList_Add(TacticsMapNodeList* list, TacticsMapNode* node);
TacticsMapNode* Tactics_MapNodeList_Pop(TacticsMapNodeList* list);
void Tactics_MapNodeList_Remove(TacticsMapNodeList* list, TacticsMapNode* node);
bool Tactics_MapNodeList_Contains(TacticsMapNodeList* list, TacticsMapNode* node);
void Tactics_MapNodeList_SortByTotalCost(TacticsMapNodeList* list);
void Tactics_MapNodeList_SortByHeuristicCost(TacticsMapNodeList* list);

#endif
