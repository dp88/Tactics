#include <stdlib.h>
#include <stdio.h>
#include "Map.h"
#include "NodeList.h"
#include "Pathfinding.h"

TacticsMapNodeList* Tactics_Pathfind(TacticsMap* map, int x1, int y1, int x2, int y2, float range) {
    TacticsMapNodeList* path = Tactics_MapNodeList_Create();
    TacticsMapNodeList* open = Tactics_MapNodeList_Create();
    TacticsMapNodeList* closed = Tactics_MapNodeList_Create();
    
    TacticsMapNode* origin = Tactics_Map_GetNodeAt(map, x1, y1);
    TacticsMapNode* destination = Tactics_Map_GetNodeAt(map, x2, y2);
    if (origin == NULL || destination == NULL) return NULL;
    
    Tactics_MapNode_SetOrigin(origin, destination);
    Tactics_MapNodeList_Add(open, origin);
    
    do {
        TacticsMapNode* current;

        // Sort the resulting array by total cost.
        Tactics_MapNodeList_SortByHeuristicCost(open);
        current = Tactics_MapNodeList_Pop(open);
        Tactics_MapNodeList_Add(closed, current);
        
        if (current == destination) { // We're done
            while (current != NULL) {
                Tactics_MapNodeList_Add(path, current);
                current = Tactics_MapNode_Parent(current);
            }
            
            // Cleanup Lists
            Tactics_MapNodeList_Destroy(open);
            Tactics_MapNodeList_Destroy(closed);
            
            printf("(%i, %i) to (%i, %i) in %i steps.\n", x1, y1, x2, y2, path->length);
            return path;
        }
        
        TacticsMapNodeList* neighbors = Tactics_GetNeighborsOfNode(map, current);
        for (int i = 0; i < neighbors->length; i++) {
            bool alreadyOnOpen = false;
            
            // Check if this neighbor has already been checked.
            if (Tactics_MapNodeList_Contains(closed, neighbors->contents[i])) continue;
            
            // Check if the current node would be a faster parent than the existing parent before continuing
            if (Tactics_MapNodeList_Contains(open, neighbors->contents[i])) {
                alreadyOnOpen = true;
                float heuristic = Tactics_MapNode_HeuristicCost(neighbors->contents[i]),
                      potentialTotalCost = Tactics_MapNode_PotentialTotalPathCost(neighbors->contents[i], current) + heuristic,
                      currentTotalCost   = Tactics_MapNode_TotalPathCost(neighbors->contents[i]) + heuristic;
                // This node is already the open list and reparenting would not help.
                if (potentialTotalCost >= currentTotalCost) continue;
            }
            
            Tactics_MapNode_RefreshFromNeighbor(neighbors->contents[i], destination, current);
            if (Tactics_MapNode_TotalPathCost(neighbors->contents[i]) > range) continue;
            if (!alreadyOnOpen) Tactics_MapNodeList_Add(open, neighbors->contents[i]);
        }
        
    } while (open->length > 0);
    
    printf("Never found path from (%i, %i) to (%i, %i)...\n", x1, y1, x2, y2);
    return path;
}

TacticsMapNodeList* Tactics_GetNeighborsOfNode(TacticsMap* map, TacticsMapNode* node) {
    TacticsMapNodeList* neighbors = Tactics_MapNodeList_Create();
    
    int x = Tactics_MapNode_X(node);
    int y = Tactics_MapNode_Y(node);
    
    for (int xx = -1; xx <= 1; xx++) {
        for (int yy = -1; yy <= 1; yy++) {
            if (xx == 0 && yy == 0) continue;
            
            int nx = x + xx;
            int ny = y + yy;
            
            if (!Tactics_PointInBounds(map, nx, ny)) continue;
            TacticsMapNode* neighbor = Tactics_Map_GetNodeAt(map, nx, ny);
            if (Tactics_MapNode_Impassable(neighbor)) continue;
            
            Tactics_MapNodeList_Add(neighbors, neighbor);
        }
    }
    
    return neighbors;
}
