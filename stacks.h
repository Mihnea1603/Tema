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
    char *team;
    NodePlayer *top;
    struct NodeTeam *next;
} NodeTeam;

void pushPlayer(NodePlayer **top, Player player);
void popPlayer(NodePlayer **top);
void deleteStackPlayer(NodePlayer **top);

void pushTeam(NodeTeam **top, char *team);
void popPlayer(NodePlayer **top);
void deleteStackPlayer(NodePlayer **top);
