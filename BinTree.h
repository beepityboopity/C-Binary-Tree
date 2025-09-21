#include "BinNode.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef BIN_TREE_H
#define BIN_TREE_H

struct BinTree {
    struct BinNode *root;
    unsigned int size;
};

bool DEBUG = 0;

// node insertion
void insertNode(struct BinTree *t, struct BinNode *d);
void _insertLeft(struct BinNode *r, struct BinNode *d);
void _insertRight(struct BinNode *r, struct BinNode *d);

// node deletion, allows deletion of particular value or particular node
void deleteNodeN(struct BinTree *t, struct BinNode *n);
void _deleteNodeN(struct BinTree *t, struct BinNode *r, struct BinNode *n);

void deleteNodeV(struct BinTree *t, int d);
void _deleteNodeV(struct BinTree *t, struct BinNode *r, int d);

// tree traversal
void preorder(struct BinTree *t);
void inorder(struct BinTree *t);
void postorder(struct BinTree *t);

void _preorder(struct BinNode *r);
void _inorder(struct BinNode *r);
void _postorder(struct BinNode *r);

/*
 *
 * Insertion
 *
 */
void insertNode(struct BinTree *t, struct BinNode *d) {
    if(t == NULL) {
        if(DEBUG) printf("Tree is null\n");
        return;
    }

    if(t->root == NULL) {
        if(DEBUG) printf("tree root is null\n");
        t->root = d;
        t->size = 1;
        if(DEBUG) printf("inserted %d\n", d->data);
    }
    else if(t->root->data <= d->data) {
        if(DEBUG) printf("inserting right\n");
        if(DEBUG) printf("node: %d, data: %d\n", t->root->data, d->data);
        _insertRight(t->root, d);
        t->size++;
    }
    else {
        if(DEBUG) printf("inserting left\n");
        if(DEBUG) printf("node: %d, data: %d\n", t->root->data, d->data);
        _insertLeft(t->root, d);
        t->size++;
    }
}

void _insertLeft(struct BinNode *r, struct BinNode *d) {
    if(r->left == NULL) {
        if(DEBUG) printf("left is null\n");
        d->parent = r;
        r->left = d;
        if(DEBUG) printf("inserted %d\n", d->data);
    }
    else if(r->left->data <= d->data) {
        if(DEBUG) printf("inserting right from left\n");
        if(DEBUG) printf("node: %d, data: %d\n", r->left->data, d->data);
        _insertRight(r->left, d);
    }
    else {
        if(DEBUG) printf("inserting left from left\n");
        if(DEBUG) printf("node: %d, data: %d\n", r->left->data, d->data);
        _insertLeft(r->left, d);
    }
}

void _insertRight(struct BinNode *r, struct BinNode *d) {
    if(r->right == NULL) {
        if(DEBUG) printf("right is null\n");
        d->parent = r;
        r->right = d;
        if(DEBUG) printf("inserted %d\n", d->data);
    }
    else if(r->right->data <= d->data) {
        if(DEBUG) printf("inserting right from right\n");
        if(DEBUG) printf("node: %d, data: %d\n", r->right->data, d->data);
        _insertRight(r->right, d);
    }
    else {
        if(DEBUG) printf("inserting left from right\n");
        if(DEBUG) printf("node: %d, data: %d\n", r->right->data, d->data);
        _insertLeft(r->right, d);
    }
}

/*
 *
 * Deletion
 *
 */
void deleteNodeN(struct BinTree *t, struct BinNode *n) {
    if(t == NULL || n == NULL) {
        if(DEBUG) printf("Attempted deletion with null tree or node\n");
        return;
    }
    if(t->root == NULL) {
        if(DEBUG) printf("Attempted deletion with null tree root\n");
        return;
    }
    _deleteNodeN(t, t->root, n);
    t->size--;
}

void _deleteNodeN(struct BinTree *t, struct BinNode *r, struct BinNode *n) {
    if(r == NULL) {
        if(DEBUG) printf("Deletion failed\n");
        return;
    }
    else if(r->data < n->data) {
        if(DEBUG) printf("Searching right\n");
        if(DEBUG) printf("root: %d, node: %d\n", r->data, n->data);
        _deleteNodeN(t, r->right, n);
    }
    else if(r->data > n->data) {
        if(DEBUG) printf("Searching left\n");
        if(DEBUG) printf("root: %d, node: %d\n", r->data, n->data);
        _deleteNodeN(t, r->left, n);
    }
    else {
        if(DEBUG) printf("Node to delete found\n");
        if(r != n && DEBUG) printf("Somehow, r and n are different locations in memory\n");

        if(r->left == NULL && r->right == NULL) {
            if(DEBUG) printf("r has no children\n");
            struct BinNode *p = r->parent;
            if(p->left == r) p->left = NULL;
            else p->right = NULL;
            free(r);
        }
        else if(r->left != NULL && r->right != NULL) {
            if(DEBUG) printf("r has two children\n");
            struct BinNode *q = r->left;
            while(q->right != NULL) q = q->right;
            struct BinNode *qp = q->parent;

            r->data = q->data;
            if(qp == r) {
                if(q->left != NULL) r->left = q->left;
                else r->left = NULL;
            }
            else {
                if(q->left != NULL) qp->right = q->left;
                else qp->right = NULL;
            }
            free(q);
        }
        else {
            if(DEBUG) printf("r has one child\n");
            if(r->left == NULL) {
                if(DEBUG) printf("r has right child\n");
                if(t->root == r) {
                    if(DEBUG) printf("r is root\n");
                    t->root = r->right;
                }
                else {
                    struct BinNode *p = r->parent;
                    if(p->right == r) p->right = r->right;
                    else p->left = r->right;
                }
            }
            else {
                if(DEBUG) printf("r has left child\n");
                if(t->root == r) {
                    if(DEBUG) printf("r is root\n");
                    t->root = r->left;
                }
                else {
                    struct BinNode *p = r->parent;
                    if(p->right == r) p->right = r->left;
                    else p->left = r->left;
                }
            }
            free(r);
        }
    }
}

void deleteNodeV(struct BinTree *t, int n) {
    if(t == NULL) {
        if(DEBUG) printf("Attempted deletion with null tree\n");
        return;
    }
    if(t->root == NULL) {
        if(DEBUG) printf("Attempted deletion with null tree root\n");
        return;
    }

    _deleteNodeV(t, t->root, n);
    t->size--;
}

void _deleteNodeV(struct BinTree *t, struct BinNode *r, int n) {
    if(r == NULL) {
        if(DEBUG) printf("Deletion failed\n");
        return;
    }
    else if(r->data < n) {
        if(DEBUG) printf("Searching right\n");
        if(DEBUG) printf("root: %d, node: %d\n", r->data, n);
        _deleteNodeV(t, r->right, n);
    }
    else if(r->data > n) {
        if(DEBUG) printf("Searching left\n");
        if(DEBUG) printf("root: %d, node: %d\n", r->data, n);
        _deleteNodeV(t, r->left, n);
    }
    else {
        if(DEBUG) printf("Node to delete found\n");
        if(r->left == NULL && r->right == NULL) {
            if(DEBUG) printf("r has no children\n");
            struct BinNode *p = r->parent;
            if(p->left == r) p->left = NULL;
            else p->right = NULL;
            free(r);
        }
        else if(r->left != NULL && r->right != NULL) {
            if(DEBUG) printf("r has two children\n");
            struct BinNode *q = r->left;
            while(q->right != NULL) q = q->right;
            struct BinNode *qp = q->parent;

            r->data = q->data;
            if(qp == r) {
                if(q->left != NULL) r->left = q->left;
                else r->left = NULL;
            }
            else {
                if(q->left != NULL) qp->right = q->left;
                else qp->right = NULL;
            }
            free(q);
        }
        else {
            if(DEBUG) printf("r has one child\n");
            if(r->left == NULL) {
                if(DEBUG) printf("r has right child\n");
                if(t->root == r) {
                    if(DEBUG) printf("r is root\n");
                    t->root = r->right;
                }
                else {
                    struct BinNode *p = r->parent;
                    if(p->right == r) p->right = r->right;
                    else p->left = r->right;
                }
            }
            else {
                if(DEBUG) printf("r has left child\n");
                if(t->root == r) {
                    if(DEBUG) printf("r is root\n");
                    t->root = r->left;
                }
                else {
                    struct BinNode *p = r->parent;
                    if(p->right == r) p->right = r->left;
                    else p->left = r->left;
                }
            }
            free(r);
        }
    }
}

/*
 *
 * Traversal
 *
 */
void preorder(struct BinTree *t) {
    if(t->root != NULL) {
        printf("Preorder: ");
        _preorder(t->root);
        printf("\n");
    }
}

void inorder(struct BinTree *t) {
    if(t->root != NULL) {
        printf("Inorder: ");
        _inorder(t->root);
        printf("\n");
    }
}

void postorder(struct BinTree *t) {
    if(t->root != NULL) {
        printf("Postorder: ");
        _postorder(t->root);
        printf("\n");
    }
}

void _preorder(struct BinNode *r) {
    if(r != NULL) {
        printf("%d ", r->data);
        _preorder(r->left);
        _preorder(r->right);
    }
}

void _inorder(struct BinNode *r) {
    if(r != NULL) {
        _inorder(r->left);
        printf("%d ", r->data);
        _inorder(r->right);
    }
}

void _postorder(struct BinNode *r) {
    if(r != NULL) {
        _postorder(r->left);
        _postorder(r->right);
        printf("%d ", r->data);
    }
}

#endif
