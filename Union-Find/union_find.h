#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_

#include <stdbool.h>

typedef struct UnionFind UnionFind;

UnionFind *uf_construct(int size);

void uf_destroy(UnionFind *uf);

int uf_find_root(UnionFind *uf, int p);

bool uf_connected(UnionFind *uf, int p, int q);

void uf_union(UnionFind *uf, int p, int q);

#endif
