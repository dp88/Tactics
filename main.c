#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Tactics.h"

TacticsMap* map;
const int numMaps = 100;
const int mapSize = 25;

int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    
    printf("Generating & Destroying Maps:\n");
    for (int i = numMaps; i > 0; i--) {
        int width  = rand() % 1000,
            height = rand() % 1000;
        
        printf("%i) %i x %i map\n", numMaps - i + 1, width, height);
        
        map = Tactics_CreateMap(width, height);
        Tactics_DestroyMap(map);
    }
    
    printf("Pathfinding:\n");
    map = Tactics_CreateMap(mapSize, mapSize);
    for (int i = numMaps; i > 0; i--) {
        int x1, y1, x2, y2;
        
        do {
            x1 = rand() % mapSize,
            y1 = rand() % mapSize,
            x2 = rand() % mapSize,
            y2 = rand() % mapSize;
        } while (x1 == x2 && y1 == y2);
        
        printf("Search %i of %i\n", numMaps - i + 1, numMaps);
        
        Tactics_Pathfind(map, x1, y1, x2, y2, mapSize * mapSize);
    }
    Tactics_DestroyMap(map);
    
    return 0;
}
