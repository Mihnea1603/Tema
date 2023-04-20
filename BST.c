#include "BST.h"

float pointsTeam(NodeTeam *team)
{
    int n=0;
    float k=0;
    for(NodePlayer *p=team->topPlayers; p!=NULL; p=p->next)
    {
        k+=p->player.points;
        n++;
    }
    return k/n;
}
Node *newNode(NodeTeam *team)
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->team=team;
    p->left=p->right=NULL;
    return p;
}
Node *insertNode(Node *root,NodeTeam *team)
{
    if (root==NULL)
    {
        return newNode(team);
    }
    float k=pointsTeam(team);
    if (k<pointsTeam(root->team))
    {
        root->left=insertNode(root->left,team);
    }
    else if (k==pointsTeam(root->team))
    {
        if(strcmp(root->team->name,team->name)==1)
        {
            root->left=insertNode(root->left,team);
        }
        else
        {
            root->right=insertNode(root->right,team);
        }
    }
    else
    {
        root->right=insertNode(root->right,team);
    }
    return root;
}
void inorder(Node *root,int *i,FILE *h)
{
    if (root!=NULL)
    {
        inorder(root->right,i,h);
        fprintf(h,"%s",root->team->name);
        for(int i=0; i<34-strlen(root->team->name); i++)
        {
            fprintf(h," ");
        }
        fprintf(h,"-  %.2f",pointsTeam(root->team));
        (*i)++;
        if(*i!=8)
        {
            fprintf(h,"\n");
        }
        inorder(root->left,i,h);
    }
}
