#include "binary_tree.h"
#include "vector.h"
#include <stdlib.h>

struct BinaryTree {
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

KeyValPair *key_val_pair_construct(void *key, void *val) {
    KeyValPair *kvp = malloc(sizeof(KeyValPair));

    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp) {
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));

    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

void node_destroy(Node *node) {
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    BinaryTree *tree = malloc(sizeof(BinaryTree));

    tree->root = NULL;
    tree->cmp_fn = cmp_fn;
    tree->key_destroy_fn = key_destroy_fn;
    tree->val_destroy_fn = val_destroy_fn;

    return tree;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value) {
    if(bt->root == NULL) {
        Node *n = node_construct(key, value, NULL, NULL);
        bt->root = n;
        return;
    }
    
    Node *current = bt->root;
    Node *prev = NULL;

    int cmp = 0;
    while(current != NULL) {
        cmp = bt->cmp_fn(key, current->key);
        if(cmp == 0) {
            bt->val_destroy_fn(current->value);
            bt->key_destroy_fn(current->key);
            current->key = key;
            current->value = value;
            return;
        }
        else if(cmp > 0) {
            prev = current;
            current = current->right;
        }
        else {
            prev = current;
            current = current->left;
        }
    }
    
    Node *n = node_construct(key, value, NULL, NULL);

    if(cmp > 0)
        prev->right = n;
    else
        prev->left = n;
    
    current = n;
}

void *binary_tree_get(BinaryTree *bt, void *key) {
    Node *current = bt->root;

    while(current != NULL) {
        int cmp = bt->cmp_fn(key, current->key);
        if(cmp == 0)
            return current->value;

        if(cmp > 0)
            current = current->right;
        else
            current = current->left;
    }

    return NULL;
}

void _binary_tree_destroy_recursive(Node *n, KeyDestroyFn key_destroy, ValDestroyFn val_destroy) {
    if(n == NULL) return;

    _binary_tree_destroy_recursive(n->left, key_destroy, val_destroy);
    _binary_tree_destroy_recursive(n->right, key_destroy, val_destroy);
    
    key_destroy(n->key);
    val_destroy(n->value);
    node_destroy(n);
}

void binary_tree_destroy(BinaryTree *bt) {
    _binary_tree_destroy_recursive(bt->root, bt->key_destroy_fn, bt->val_destroy_fn);

    free(bt);
}

void _binary_tree_transplant(BinaryTree *bt, Node *current, Node *parent, Node *new) {
    if(parent == NULL) 
        bt->root = new;
    else if(current == parent->left)
        parent->left = new;
    else
        parent->right = new;
}

void binary_tree_remove(BinaryTree *bt, void *key) {
    Node *current = bt->root;
    Node *prev = NULL;

    int cmp = 0;
    while(current != NULL) {
        cmp = bt->cmp_fn(key, current->key);
        if(cmp == 0) {
            break;
        }
        
        if(cmp > 0) {
            prev = current;
            current = current->right;
        }
        else {
            prev = current;
            current = current->left;
        }
    }

    if(current->left == NULL) {
        _binary_tree_transplant(bt, current, prev, current->right);
        bt->key_destroy_fn(current->key);
        bt->val_destroy_fn(current->value);
        node_destroy(current);
    }
    else if(current->right == NULL) {
        _binary_tree_transplant(bt, current, prev, current->left);
        bt->key_destroy_fn(current->key);
        bt->val_destroy_fn(current->value);
        node_destroy(current);
    }
    else {
        Node *succ = current->right;
        Node *succ_parent = current;

        while(succ->left != NULL) {
            succ_parent = succ;
            succ = succ->left;
        }

        if(succ_parent != current) {
            _binary_tree_transplant(bt, succ, succ_parent, succ->right);
            succ->right = current->right;
        }

        _binary_tree_transplant(bt, current, prev, succ);
        succ->left = current->left;

        bt->key_destroy_fn(current->key);
        bt->val_destroy_fn(current->value);
        node_destroy(current);
    }
}

KeyValPair *binary_tree_min(BinaryTree *bt) {
    Node *current = bt->root;

    while(current->left != NULL) {
        current = current->left;
    }

    KeyValPair *kvp = key_val_pair_construct(current->key, current->value);

    return kvp;
}

KeyValPair *binary_tree_max(BinaryTree *bt) {
    Node *current = bt->root;

    while(current->right != NULL) {
        current = current->right;
    }

    KeyValPair *kvp = key_val_pair_construct(current->key, current->value);
    
    return kvp;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt) {
    Node *current = bt->root;
    Node *prev = NULL;
    
    while(current->left != NULL) {
        prev = current;
        current = current->left;
    }
 
    KeyValPair *kvp = key_val_pair_construct(current->key, current->value);

    if(current->left == NULL) {
        _binary_tree_transplant(bt, current, prev, current->right);
        node_destroy(current);
    }
    else if(current->right == NULL) {
        _binary_tree_transplant(bt, current, prev, current->left);
        node_destroy(current);
    }

    return kvp;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt) {
    Node *current = bt->root;
    Node *prev = NULL;
    
    while(current->right != NULL) {
        prev = current;
        current = current->right;
    }
 
    KeyValPair *kvp = key_val_pair_construct(current->key, current->value);

    if(current->left == NULL) {
        _binary_tree_transplant(bt, current, prev, current->right);
        node_destroy(current);
    }
    else if(current->right == NULL) {
        _binary_tree_transplant(bt, current, prev, current->left);
        node_destroy(current);
    }

    return kvp;
}

int binary_tree_empty(BinaryTree *bt) {
    return (bt->root == NULL);
}

Vector *binary_tree_inorder_traversal(BinaryTree *bt) {
    if(bt->root == NULL) return NULL;
    
    Node *current = bt->root;

    Vector *stack = vector_construct();
    Vector *inorder = vector_construct();

    while(1) {
        if(current != NULL) {
            vector_push_back(stack, current);
            current = current->left;
        }
        else {
            if(vector_size(stack)   ) {
                current = vector_pop_back(stack);
                KeyValPair *kvp = key_val_pair_construct(current->key, current->value);
                vector_push_back(inorder, kvp);
                current = current->right;
            }
            else
                break;
        }
    }

    vector_destroy(stack);

    return inorder;
}

Vector *binary_tree_preorder_traversal(BinaryTree *bt) {
    if(bt->root == NULL) return NULL;

    Node *current = NULL;

    Vector *stack = vector_construct();
    Vector *preorder = vector_construct();

    vector_push_back(stack, bt->root);

    while(vector_size(stack)) {
        current = vector_pop_back(stack);
        
        KeyValPair *kvp = key_val_pair_construct(current->key, current->value);
        vector_push_back(preorder, kvp);
        
        if(current->right != NULL)
            vector_push_back(stack, current->right);
        if(current->left != NULL)
            vector_push_back(stack, current->left);
    }
    
    vector_destroy(stack);

    return preorder;
}

Vector *binary_tree_postorder_traversal(BinaryTree *bt) {
    if(bt->root == NULL) return NULL;

    Vector *stack1 = vector_construct();
    Vector *stack2 = vector_construct();
    
    vector_push_back(stack1, bt->root);

    Node *current = NULL;

    while(vector_size(stack1)) {
        current = vector_pop_back(stack1);
        vector_push_back(stack2, current);
        
        if(current->left != NULL)
            vector_push_back(stack1, current->left);
        if(current->right != NULL)
            vector_push_back(stack1, current->right);
    }

    Vector *postorder = vector_construct();

    while(vector_size(stack2)) {
        current = vector_pop_back(stack2);
        KeyValPair *kvp = key_val_pair_construct(current->key, current->value);
        vector_push_back(postorder, kvp);
    }

    vector_destroy(stack1);
    vector_destroy(stack2);

    return postorder;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt) {
    Vector *queue = vector_construct();
    Vector *levelorder = vector_construct();
    
    vector_push_back(queue, bt->root);

    Node *current = NULL;

    while(vector_size(queue)) {
        current = vector_pop_front(queue);

        if(current != NULL) {
            KeyValPair *kvp = key_val_pair_construct(current->key, current->value);
            vector_push_back(levelorder, kvp);

            if(current->left != NULL)
                vector_push_back(queue, current->left);
            if(current->right != NULL)
                vector_push_back(queue, current->right);
        }
    }
    
    vector_destroy(queue);

    return levelorder;
}

Vector *_inorder_recursive(Node *node, Vector *inorder) {
    if(node == NULL) return inorder;

    _inorder_recursive(node->left, inorder);
    
    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
    vector_push_back(inorder, kvp);

    _inorder_recursive(node->right, inorder);

    return inorder;
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt) {
    Vector *inorder = vector_construct();

    _inorder_recursive(bt->root, inorder);
    
    return inorder;
}

Vector *_preorder_recursive(Node *node, Vector *preorder) {
    if(node == NULL) return preorder;

    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
    vector_push_back(preorder, kvp);
    
    _preorder_recursive(node->left, preorder);
    _preorder_recursive(node->right, preorder);
    
    return preorder;
} 

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt) {
    Vector *preorder = vector_construct();

    _preorder_recursive(bt->root, preorder);
    
    return preorder;
}

Vector *_postorder_recursive(Node *node, Vector *postorder) {
    if(node == NULL) return postorder;

    _postorder_recursive(node->left, postorder);
    _postorder_recursive(node->right, postorder);

    KeyValPair *kvp = key_val_pair_construct(node->key, node->value);
    vector_push_back(postorder, kvp);
    
    return postorder;
}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt) {
    Vector *postorder = vector_construct();

    _postorder_recursive(bt->root, postorder);
    
    return postorder;
}

