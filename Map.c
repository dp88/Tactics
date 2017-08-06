#include <stdlib.h>
#include "Map.h"

static int IndexToX  (TacticsMap* map, int index);
static int IndexToY  (TacticsMap* map, int index);
static int XYToIndex (TacticsMap* map, int x, int y);


struct TacticsMap {
    int width;
    int height;
    TacticsMapNode** nodes;
};

TacticsMap* Tactics_CreateMap(int width, int height) {
    TacticsMap* map = calloc(1, sizeof(TacticsMap));
    int dimensions = width * height;
    
    map->width = width;
    map->height = height;
    map->nodes = calloc(dimensions, sizeof(TacticsMapNode*));
    
    for (int i = 0; i < dimensions; i++) {
        int x = IndexToX(map, i);
        int y = IndexToY(map, i);
        map->nodes[i] = Tactics_CreateMapNode(x, y);
    }
    
    return map;
}

void Tactics_DestroyMap(TacticsMap* map) {
    int dimensions = map->width * map->height;
    for (int i = 0; i < dimensions; i++) {
        free(map->nodes[i]);
    }
    free(map->nodes);
    free(map);
}

bool Tactics_PointInBounds(TacticsMap* map, int x, int y) {
    if (x < 0 || y < 0) return false;
    if (x >= map->width || y >= map->height) return false;
    return true;
}

int Tactics_Map_Width(TacticsMap* map) {
    return map->width;
}

int Tactics_Map_Height(TacticsMap* map) {
    return map->height;
}

TacticsMapNode* Tactics_Map_GetNodeAt(TacticsMap* map, int x, int y) {
    if (!Tactics_PointInBounds(map, x, y)) return NULL;
    
    int index = XYToIndex(map, x, y);
    return map->nodes[index];
}



// Local Utilities
static int IndexToX(TacticsMap* map, int index) {
    return index % map->width;
}

static int IndexToY(TacticsMap* map, int index) {
    return index / map->width;
}

static int XYToIndex(TacticsMap* map, int x, int y) {
    return (y * map->width) + x;
}
