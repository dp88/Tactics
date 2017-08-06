#include <stdlib.h>
#include <stdbool.h>
#include <search.h>
#include "Map.h"
#include "NodeList.h"

static int CompareTotalCost(const void* a, const void* b);
static int CompareHeuristicCost(const void* a, const void* b);
static int CompareEquality(const void* a, const void* b);

TacticsMapNodeList* Tactics_MapNodeList_Create() {
    TacticsMapNodeList* list = calloc(1, sizeof(TacticsMapNodeList));
    
    list->length = 0;
    list->contents = NULL;
    
    return list;
}

void Tactics_MapNodeList_Destroy(TacticsMapNodeList* list) {
    if (list->contents != NULL) free(list->contents);
    free(list);
}

void Tactics_MapNodeList_Add(TacticsMapNodeList* list, TacticsMapNode* node) {
    list->length++;
    list->contents = realloc(list->contents, list->length * sizeof(TacticsMapNode*));
    list->contents[list->length - 1] = node;
}

TacticsMapNode* Tactics_MapNodeList_Pop(TacticsMapNodeList* list) {
    const int oldSize = list->length;
    const int newSize = oldSize - 1;
    TacticsMapNode** newContents = NULL;
    TacticsMapNode* top = NULL;
    
    if (oldSize > 0) {
        top = list->contents[0];
    }
    
    if (newSize > 0) {
        newContents = calloc(newSize, sizeof(TacticsMapNode*));
    }
    
    if (newSize > 0 && oldSize > 0) {
        for (int i = 0; i < newSize; i++) {
            newContents[i] = list->contents[i + 1];
        }
    }
    
    if (list->contents != NULL) free(list->contents);
    list->contents = newContents;
    list->length = newSize;
    
    return top;
}

void Tactics_MapNodeList_Remove(TacticsMapNodeList* list, TacticsMapNode* node) {
    const int oldSize = list->length;
    const int newSize = oldSize - 1;
    TacticsMapNode** newContents = NULL;
    bool found = false;
    
    if (oldSize == 0) return;
    
    for (int i = 0; i < oldSize; i++) {
        if (list->contents[i] == node) {
            found = true;
            break;
        }
    }
    
    if (!found) return;
    
    newContents = calloc(newSize, sizeof(TacticsMapNode*));
    
    for (int i = 0, j = 0; i < oldSize; i++) {
        if (list->contents[i] == node) continue;
        newContents[j] = list->contents[i];
        j++;
    }
    
    free(list->contents);
    list->contents = newContents;
    list->length = newSize;
}

bool Tactics_MapNodeList_Contains(TacticsMapNodeList* list, TacticsMapNode* node) {
    for (int i = list->length - 1; i >= 0; i--) {
        if (list->contents[i] == node) return true;
    }
    
    return false;
}

void Tactics_MapNodeList_SortByTotalCost(TacticsMapNodeList* list) {
    qsort(list->contents, list->length, sizeof(TacticsMapNode*), CompareTotalCost);
}

void Tactics_MapNodeList_SortByHeuristicCost(TacticsMapNodeList* list) {
    qsort(list->contents, list->length, sizeof(TacticsMapNode*), CompareHeuristicCost);
}

static int CompareTotalCost(const void* a, const void* b) {
    TacticsMapNode* aa = *(TacticsMapNode**)a;
    TacticsMapNode* bb = *(TacticsMapNode**)b;
    
    return Tactics_MapNode_TotalPathCost(bb) - Tactics_MapNode_TotalPathCost(aa);
}

static int CompareHeuristicCost(const void* a, const void* b) {
    TacticsMapNode* aa = *(TacticsMapNode**)a;
    TacticsMapNode* bb = *(TacticsMapNode**)b;
    
    return Tactics_MapNode_HeuristicCost(bb) - Tactics_MapNode_HeuristicCost(aa);
}

static int CompareEquality(const void* a, const void* b) {
    return a == b ? 1 : 0;
}

