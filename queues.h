#include "stacks.h"

typedef struct NodeMatch
{
    NodeTeam *team1,*team2;
    struct NodeMatch *next;
} NodeMatch;
typedef struct Queue
{
    NodeMatch *front,*rear;
} Queue;

Queue *createQueue();
void enQueue(Queue *q,NodeTeam *team1,NodeTeam *team2);
void deQueue(Queue *q);
void deleteQueue(Queue *q);
