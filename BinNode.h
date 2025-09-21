#ifndef BIN_NODE_H
#define BIN_NODE_H

struct BinNode {
    int data;
    struct BinNode *left;
    struct BinNode *right;
    struct BinNode *parent;
};

#endif
