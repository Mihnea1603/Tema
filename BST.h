#include "stacks.h"

typedef struct Node
{
    NodeTeam *team;
    struct Node *left,*right;
} Node;

float pointsTeam(NodeTeam *team);
Node* newNode(NodeTeam *team);
Node* insertNode(Node *node,NodeTeam *team);
void inorder(Node *root,int *i,FILE *h);
