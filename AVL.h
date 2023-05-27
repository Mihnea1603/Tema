#include "BST.h"

int nodeHeight(Node *root);
Node *rightRotation(Node *z);
Node *leftRotation(Node *z);
Node *LRRotation(Node *z);
Node *RLRotation(Node *z);
Node *insertNodeAVL(Node *root,NodeTeam *team);
void traverseInorder(Node *rootBST,Node **rootAVL);
void printLevel(Node *root,int level,FILE *h);
