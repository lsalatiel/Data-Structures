#include "union_find.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;

    scanf("%d", &size);

    UnionFind *uf = uf_construct(size);

    int n;
    scanf("%d", &n);

    int p, q;
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &p, &q);

        if(!uf_connected(uf, p, q)) {
            uf_union(uf, p, q);
            printf("%d %d\n", p, q);
        }
    }

    return 0;
}
