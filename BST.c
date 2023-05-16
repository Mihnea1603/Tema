#include "BST.h"

Node *newNode(NodeTeam *team)
{
    Node *p=(Node*)malloc(sizeof(Node));
    if(p==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    p->team=team;
    p->left=p->right=NULL;
    return p;
}
Node *insertNodeBST(Node *root,NodeTeam *team)
{
    if(root==NULL)
    {
        return newNode(team);
    }
    if(team->points<root->team->points)
    {
        root->left=insertNodeBST(root->left,team);
    }
    else if(team->points>root->team->points)
    {
        root->right=insertNodeBST(root->right,team);
    }
    else
    {
        if(strcmp(root->team->name,team->name)==1)
        {
            root->left=insertNodeBST(root->left,team);
        }
        else
        {
            root->right=insertNodeBST(root->right,team);
        }
    }
    return root;
}
void printInorder(Node *root,int *k,FILE *h)
{
    if(root!=NULL)
    {
        printInorder(root->right,k,h);
        fprintf(h,"%s",root->team->name);
        for(int i=0; i<34-strlen(root->team->name); i++)
        {
            fprintf(h," ");
        }
        fprintf(h,"-  %.2f",root->team->points);
        (*k)++;
        if(*k!=8)
        {
            fprintf(h,"\n");
        }
        printInorder(root->left,k,h);
    }
}
void deleteTree(Node *root)
{
    if(root!=NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}
