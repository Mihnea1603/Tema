#include "AVL.h"

int nodeHeight(Node *root)
{
    if (root!=NULL)
    {
        int hs=nodeHeight(root->left),hd=nodeHeight(root->right);
        return 1+((hs >hd) ? hs:hd);
    }
    return 0;
}
Node *rightRotation(Node *z)
{
    Node *y=z->left,*T3=y->right;
    y->right=z;
    z->left=T3;
    return y;
}
Node *leftRotation(Node *z)
{
    Node *y=z->right,*T2=y->left;
    y->left=z;
    z->right=T2;
    return y;
}
Node *LRRotation(Node *z)
{
    z->left=leftRotation(z->left);
    return rightRotation(z);
}
Node *RLRotation(Node *z)
{
    z->right = rightRotation(z->right);
    return leftRotation(z);
}
Node *insertNodeAVL(Node *root,NodeTeam *team)
{
    if (root==NULL)
    {
        return newNode(team);
    }
    if (team->points<root->team->points)
    {
        root->left=insertNodeAVL(root->left,team);
    }
    else if(team->points>root->team->points)
    {
        root->right=insertNodeAVL(root->right,team);
    }
    else
    {
        if(strcmp(root->team->name,team->name)==1)
        {
            root->left=insertNodeAVL(root->left,team);
        }
        else
        {
            root->right=insertNodeAVL(root->right,team);
        }
    }
    int h=nodeHeight(root->left)-nodeHeight(root->right);
    if (h>1)
    {
        if(team->points<root->left->team->points)
        {
            return rightRotation(root);
        }
        else if(team->points>root->left->team->points)
        {
            return LRRotation(root);
        }
        else
        {
            if(strcmp(root->left->team->name,team->name)==1)
            {
                return rightRotation(root);
            }
            else
            {
                return LRRotation(root);
            }
        }
    }
    if (h<-1)
    {
        if(team->points<root->right->team->points)
        {
            return RLRotation(root);
        }
        else if(team->points>root->right->team->points)
        {
            return leftRotation(root);
        }
        else
        {
            if(strcmp(root->right->team->name,team->name)==1)
            {
                return RLRotation(root);
            }
            else
            {
                return leftRotation(root);
            }
        }
    }
    return root;
}
void traverseInorder(Node *rootBST,Node **rootAVL)
{
    if(rootBST!=NULL)
    {
        traverseInorder(rootBST->right,rootAVL);
        *rootAVL=insertNodeAVL(*rootAVL,rootBST->team);
        traverseInorder(rootBST->left,rootAVL);
    }
}
void printLevel(Node *root,int level,int *k,FILE *h)
{
    if(root!=NULL)
    {
        if(level==0)
        {
            fprintf(h,"%s",root->team->name);
            (*k)++;
            if(*k!=4)
            {
                fprintf(h,"\n");
            }
        }
        else
        {
            printLevel(root->right,level-1,k,h);
            printLevel(root->left,level-1,k,h);
        }
    }
}
