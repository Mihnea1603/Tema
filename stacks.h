#ifndef STACKS_H
#define STACKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
    char *firstName;
    char *secondName;
    int points;
} Player;
typedef struct NodePlayer
{
    Player player;
    struct NodePlayer *next;
} NodePlayer;

typedef struct NodeTeam
{
    char *name;
    float points;
    NodePlayer *topPlayers;
    struct NodeTeam *next;
} NodeTeam;

void pushPlayer(NodePlayer **topPlayers,char firstName[],char secondName[],int points);
void freePlayer(NodePlayer *player);
void popPlayer(NodePlayer **topPlayers);
void deleteStackPlayers(NodePlayer **topPlayers);

void pushTeam(NodeTeam **topTeams,char name[]);
void freeTeam(NodeTeam *team);
void popTeam(NodeTeam **topTeams);
void deleteStackTeams(NodeTeam **topTeams);

#endif
