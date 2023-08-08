#include "hash.h"
#include <stdlib.h>
#include "forward_list.h"

struct HashTable {
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int n_elements;
    int table_size;
};

struct HashTableIterator {
    HashTable *h;
    int bucket_index;
    Node *curr;
    int count;
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn) {
    HashTable *hash = calloc(1, sizeof(HashTable));

    hash->hash_fn = hash_fn;
    hash->cmp_fn = cmp_fn;

    hash->n_elements = 0;
    hash->table_size = table_size;

    hash->buckets = calloc(table_size, sizeof(ForwardList *));

    return hash;
}

HashTableItem *_hash_pair_create(void *key, void *val) {
    HashTableItem *pair = malloc(sizeof(HashTableItem));
    pair->key = key;
    pair->val = val;

    return pair;
}

void _hash_pair_destroy(HashTableItem *pair) {
    free(pair->key);
    free(pair->val);
    free(pair);
}

void hash_table_destroy(HashTable *h) {
    for(int i = 0; i < h->table_size; i++) {
        if (h->buckets[i] != NULL) {
            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

void *hash_table_set(HashTable *h, void *key, void *val) {
    int key_val = h->hash_fn(h, key);
    key_val = key_val % h->table_size;
    
    if(h->buckets[key_val] == NULL) {
        h->buckets[key_val] = forward_list_construct();
    }
    else {
        Node *curr = h->buckets[key_val]->head;
        
        while(curr != NULL) {
            HashTableItem *pair = (HashTableItem *)curr->value;
            
            if(!h->cmp_fn(key, pair->key)) {
                void *to_remove = pair->val;
                pair->val = val;
                return to_remove;
            }
            
            curr = curr->next;
        }
    }
    
    HashTableItem *item = _hash_pair_create(key, val);
    forward_list_push_back(h->buckets[key_val], item);
    h->n_elements++;

    return NULL;
}

int hash_table_size(HashTable *h) {
    return h->table_size;
}

int hash_table_num_elems(HashTable *h) {
    return h->n_elements;
}

void *hash_table_get(HashTable *h, void *key) {
    int key_val = h->hash_fn(h, key);
    key_val = key_val % h->table_size;

    Node *curr = h->buckets[key_val]->head;
        
        while(curr != NULL) {
            HashTableItem *pair = (HashTableItem *)curr->value;
            
            if(!h->cmp_fn(key, pair->key)) {
                return pair->val;
            }
            
            curr = curr->next;
        }
    
    return NULL;
}

void *hash_table_pop(HashTable *h, void *key) {
     int key_val = h->hash_fn(h, key);
    key_val = key_val % h->table_size;

    Node *curr = h->buckets[key_val]->head;
        
        while(curr != NULL) {
            HashTableItem *pair = (HashTableItem *)curr->value;
            
            if(!h->cmp_fn(key, pair->key)) {
                void *to_remove = pair->val;
                _hash_pair_destroy(pair);
                h->n_elements--;
                return to_remove;
            }
            
            curr = curr->next;
        }
    
    return NULL;
}

HashTableIterator *hash_table_iterator(HashTable *h) {
    HashTableIterator *it = malloc(sizeof(HashTableIterator));
    
    it->h = h;
    it->bucket_index = -1;
    it->curr = NULL;
    it->count = 0;

    return it;
}

int hash_table_iterator_is_over(HashTableIterator *it) {
    return (it->count == it->h->n_elements);
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it) {
    if(it->curr != NULL && it->count != 0)
        it->curr = it->curr->next;
    
    while(it->curr == NULL) {
        it->bucket_index++;
        if(it->h->buckets[it->bucket_index] != NULL)
            it->curr = it->h->buckets[it->bucket_index]->head;
    }

    it->count++;

    HashTableItem *pair = it->curr->value;
    return pair;
}

void hash_table_iterator_destroy(HashTableIterator *it) {
    free(it);
}
