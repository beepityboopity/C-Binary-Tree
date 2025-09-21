#include <stdio.h>
#include "BinTree.h"

int main() {
    int vals[10] = {10, 20, 30, 15, 5, 9, 8, 23, 27, 16};
    struct BinTree t1;

    for(int i = 0; i < (sizeof(vals)/sizeof(int)); i++) {
        struct BinNode *newNode = malloc(sizeof(struct BinNode));
        newNode->data = vals[i];
        insertNode(&t1, newNode);
    }
    inorder(&t1);
    deleteNodeV(&t1, 20);
    inorder(&t1);
    deleteNodeV(&t1, 5);
    inorder(&t1);
    return 0;
}
