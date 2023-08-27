#include "union_find.h"
#include <stdlib.h>

struct UnionFind {
    int *array;
    int size;
    int *sz;
};

UnionFind *uf_construct(int size) {
    UnionFind *uf = malloc(sizeof(UnionFind));

    uf->size = size;
    uf->array = malloc(size * sizeof(int));
    uf->sz = malloc(size * sizeof(int));
    
    for(int i = 0; i < size; i++) {
        uf->array[i] = i;
        uf->sz[i] = 1;
    }

    return uf;
}

void uf_destroy(UnionFind *uf) {
    free(uf->array);
    free(uf->sz);
    free(uf);
}

int uf_find_root(UnionFind *uf, int p) {
    while(uf->array[p] != p)
        p = uf->array[p];

    return p;
}

bool uf_connected(UnionFind *uf, int p, int q) {
    return uf_find_root(uf, p) == uf_find_root(uf, q);
}

void uf_union(UnionFind *uf, int p, int q) {
    int p_root = uf_find_root(uf, p);
    int q_root = uf_find_root(uf, q);

    if(uf->sz[p_root] < uf->sz[q_root]) {
        uf->array[p_root] = q_root;
        uf->sz[q_root] += uf->sz[p_root];
    }
    else {
        uf->array[q_root] = p_root;
        uf->sz[p_root] += uf->sz[q_root];
    }
}
