#include "stacks.h"

void pushPlayer(NodePlayer **topPlayers,Player player)
{
    NodePlayer *p=(NodePlayer*)malloc(sizeof(NodePlayer));
    if(p==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    p->player=player;
    p->next=*topPlayers;
    *topPlayers=p;
}
void freePlayer(NodePlayer *player)
{
    free(player->player.firstName);
    free(player->player.secondName);
    free(player);
}
void popPlayer(NodePlayer **topPlayers)
{
    NodePlayer *p=*topPlayers;
    *topPlayers=(*topPlayers)->next;
    freePlayer(p);
}
void deleteStackPlayers(NodePlayer **topPlayers)
{
    while (*topPlayers!=NULL)
    {
        popPlayer(topPlayers);
    }
}

void pushTeam(NodeTeam **topTeams,char *name)
{
    NodeTeam *p=(NodeTeam*)malloc(sizeof(NodeTeam));
    if(p==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    p->name=name;
    p->topPlayers=NULL;
    p->next=*topTeams;
    *topTeams=p;
}
void freeTeam(NodeTeam *team)
{
    free(team->name);
    deleteStackPlayers(&team->topPlayers);
    free(team);
}
void popTeam(NodeTeam **topTeams)
{
    NodeTeam *p=*topTeams;
    *topTeams=(*topTeams)->next;
    freeTeam(p);
}
void deleteStackTeams(NodeTeam **topTeams)
{
    while (*topTeams!=NULL)
    {
        popTeam(topTeams);
    }
}
