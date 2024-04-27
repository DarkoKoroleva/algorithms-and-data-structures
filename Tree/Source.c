#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    int order;
    struct tree_t* left;
    struct tree_t* parent;
    struct tree_t* right;
    int subtree_wigth;
} tree_t;

typedef enum {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}variant_t;

void orderUpdate(tree_t* tree, int* order) {
    if (tree) {
        if (tree->left)
            orderUpdate(tree->left, order);

        tree->order = *order;
        (*order)++;

        if (tree->right)
            orderUpdate(tree->right, order);
    }
}

void addition(tree_t** tree, int num) {
    tree_t* temp = (*tree), * newnode, * ptr = (*tree);
    int order = 1;
    newnode = (tree_t*)malloc(sizeof(tree_t));
    if (!newnode)
        return;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    newnode->num = num;

    if (!(*tree)) {
        (*tree) = newnode;
        orderUpdate((*tree), &order);
        return;
    }

    while (ptr) {
        if (num < ptr->num) {
            if (ptr->left)
                ptr = ptr->left;
            else
                break;
        }

        else if (num > ptr->num) {
            if (ptr->right)
                ptr = ptr->right;
            else
                break;
        }

        else { 
            free(newnode);
            return;
        }
    }
    if (num < ptr->num)
        ptr->left = newnode;
    else
        ptr->right = newnode;

    newnode->parent = ptr;

    orderUpdate((*tree), &order);
}

void destroyTree(tree_t* tree) {
    if (tree) {
        destroyTree(tree->left);
        destroyTree(tree->right);
        free(tree);
    }
}

tree_t* KlowerFind(tree_t* tree, int k) {
    if (tree) {

        if (tree->order == k)
            return tree;

        if (KlowerFind(tree->left, k))
            return tree->left;

        if (KlowerFind(tree->right, k))
            return tree->right;
    }
    return NULL;
}

void PrintTree(tree_t* tree, int k) {
    if (tree) {
        PrintTree(tree->left, k);
        if (tree->order < k) {
            printf("%d ", tree->num);
        }
        PrintTree(tree->right, k);
    }
}


int main(void) {
    const int k = 3;
    tree_t* tree = NULL, * find = NULL;

    addition(&tree, 5);
    addition(&tree, 2);
    addition(&tree, -1);
    addition(&tree, -6);
    addition(&tree, 10);
    addition(&tree, 3);
    find = KlowerFind(tree, k);
    printf("The smallest number: %d\n", find->num);

    if (find && (find->num) % 2 == 0)
        PrintTree(tree, k);
    else printf("odd number");

    destroyTree(tree);
    return 0;
}