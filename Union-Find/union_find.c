#include "union_find.h"
#include <stdlib.h>

struct UnionFind {
    int *array;
    int size;
};

UnionFind *uf_construct(int size) {
    UnionFind *uf = malloc(sizeof(UnionFind));

    uf->size = size;
    uf->array = malloc(size * sizeof(int));
    
    for(int i = 0; i < size; i++) {
        uf->array[i] = i;
    }

    return uf;
}

void uf_destroy(UnionFind *uf) {
    free(uf->array);
    free(uf);
}

int uf_find(UnionFind *uf, int p) {
    return uf->array[p];
}

bool uf_connected(UnionFind *uf, int p, int q) {
    return uf_find(uf, p) == uf_find(uf, q);
}

void uf_union(UnionFind *uf, int p, int q) {
    int p_idx = uf_find(uf, p);
    int q_idx = uf_find(uf, q);

    for(int i = 0; i < uf->size; i++) {
        if(uf->array[i] == p_idx)
            uf->array[i] = q_idx;
    }
}
