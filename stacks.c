#include "stacks.h"

void pushPlayer(NodePlayer **top, Player player)
{
    NodePlayer *p=(NodePlayer*)malloc(sizeof(NodePlayer));
    if(p==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    p->player=player;
    p->next=*top;
    *top=p;
}
void popPlayer(NodePlayer **top)
{
    NodePlayer *p=*top;
    *top=(*top)->next;
    free(p->player.firstName);
    free(p->player.secondName);
    free(p);
}
void deleteStackPlayer(NodePlayer **top)
{
    while (*top!=NULL)
    {
        popPlayer(top);
    }
}

void pushTeam(NodeTeam **top, char *team)
{
    NodeTeam *p=(NodeTeam*)malloc(sizeof(NodeTeam));
    if(p==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    p->team=team;
    p->top=NULL;
    p->next=*top;
    *top=p;
}
void popTeam(NodeTeam **top)
{
    NodeTeam *p=*top;
    *top=(*top)->next;
    free(p->team);
    deleteStackPlayer(&p->top);
    free(p);
}
void deleteStackTeam(NodeTeam **top)
{
    NodeTeam *p;
    while (*top!=NULL)
    {
        popTeam(top);
    }
}
