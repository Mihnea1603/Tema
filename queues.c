#include "queues.h"

Queue *createQueue()
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    q->front=q->rear=NULL;
    return q;
}
void enQueue(Queue *q,NodeTeam *team1,NodeTeam *team2)
{
    NodeMatch *p=(NodeMatch*)malloc(sizeof(NodeMatch));
    if(p==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    p->team1=team1;
    p->team2=team2;
    p->next=NULL;
    if (q->rear==NULL)
    {
        q->front=q->rear=p;
    }
    else
    {
        q->rear->next=p;
        q->rear=p;
    }
}
void deQueue(Queue *q)
{
    NodeMatch *p;
    p=q->front;
    q->front=q->front->next;
    free(p);
}
void deleteQueue(Queue *q)
{
    while (q->front!=NULL)
    {
        deQueue(q);
    }
    free(q);
}
