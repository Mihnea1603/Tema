#ifndef BST_H
#define BST_H

#include "stacks.h"

typedef struct Node
{
    NodeTeam *team;
    struct Node *left,*right;
} Node;

Node *newNode(NodeTeam *team);
Node *insertNodeBST(Node *node,NodeTeam *team);
void printInorder(Node *root,FILE *h);
void deleteTree(Node *root);

#endif
