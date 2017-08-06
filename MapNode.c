#include <stdlib.h>
#include <math.h>
#include "MapNode.h"

struct TacticsMapNode {
    int x;
    int y;
    bool impassable;
    float movementCost;
    float heuristicCost;
    float pathCost;
    TacticsMapNode* parent;
    TacticsMapNode* searchTarget;
};

TacticsMapNode* Tactics_CreateMapNode(int x, int y) {
    TacticsMapNode* node = calloc(1, sizeof(TacticsMapNode));
    
    node->x = x;
    node->y = y;
    node->impassable = false;
    node->movementCost = 1.0;
    node->heuristicCost = 0.0;
    node->pathCost = 0.0;
    node->parent = NULL;
    node->searchTarget = NULL;
    
    return node;
}

// Getters
int Tactics_MapNode_X(TacticsMapNode* node) {
    return node->x;
}

int Tactics_MapNode_Y(TacticsMapNode* node) {
    return node->y;
}

float Tactics_MapNode_HeuristicCost(TacticsMapNode* node) {
    return node->heuristicCost;
}

bool Tactics_MapNode_Impassable(TacticsMapNode* node) {
    return node->impassable;
}

TacticsMapNode* Tactics_MapNode_Parent(TacticsMapNode* node) {
    return node->parent;
}
// END Getters

float Tactics_MapNode_TotalLocalCost(TacticsMapNode* node) {
    return node->heuristicCost + node->pathCost;
}

float Tactics_MapNode_TotalPathCost(TacticsMapNode* node) {
    float total = 0.0;
    TacticsMapNode* current = node;
    
    while (current != NULL) {
        total += current->pathCost;
        current = current->parent;
    }
    
    return total;
}

float Tactics_MapNode_PotentialTotalPathCost(TacticsMapNode* node, TacticsMapNode* newParent) {
    float total = 0.0;
    TacticsMapNode* current = node;
    
    total+= current->pathCost;
    current = newParent;
    
    while (current != NULL) {
        total += current->pathCost;
        current = current->parent;
    }
    
    return total;
}

void Tactics_MapNode_SetOrigin(TacticsMapNode* node, TacticsMapNode* target) {
    node->searchTarget = target;
    
    {
        float x = node->x - target->x;
        float y = node->y - target->y;
        node->heuristicCost = sqrtf((x * x) + (y * y));
    }
    
    node->pathCost = 0.0;
    node->parent = NULL;
}

void Tactics_MapNode_RefreshFromNeighbor(TacticsMapNode* node, TacticsMapNode* target, TacticsMapNode* neighbor) {
    node->searchTarget = target;
    
    {
        float x = node->x - target->x;
        float y = node->y - target->y;
        node->heuristicCost = sqrtf((x * x) + (y * y));
    }
    
    {
        float x = node->x - neighbor->x;
        float y = node->y - neighbor->y;
        node->pathCost = sqrtf((x * x) + (y * y)) + node->movementCost - 1.0;
    }
    
    node->parent = neighbor;
}
