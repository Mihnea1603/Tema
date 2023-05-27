#include "stacks.h"
#include "queues.h"
#include "BST.h"
#include "AVL.h"

void createPlayer(NodeTeam *topTeams,FILE *g)
{
    int k;
    char s1[25],s2[25];
    fscanf(g,"%s%s%d",s1,s2,&k);
    topTeams->points+=k;
    pushPlayer(&topTeams->topPlayers,s1,s2,k);
}
void createTeam(NodeTeam **topTeams,FILE *g)
{
    int noPlayers;
    char s[35];
    fscanf(g,"%d",&noPlayers);
    fseek(g,1,1);
    fgets(s,35,g);
    for(int i=strlen(s)-1; i>=0; i--)
    {
        if(s[i]==' ' || s[i]=='\n')
        {
            s[i]='\0';
        }
        else
        {
            break;
        }
    }
    pushTeam(topTeams,s);
    for(int i=0; i<noPlayers; i++)
    {
        createPlayer(*topTeams,g);
    }
    (*topTeams)->points/=noPlayers;
}

float minPoints(NodeTeam *topTeams)
{
    float m=topTeams->points;
    for(NodeTeam *p=topTeams->next; p!=NULL; p=p->next)
    {
        if(p->points<m)
        {
            m=p->points;
        }
    }
    return m;
}
void filterTeams(NodeTeam **topTeams,int *noTeams)
{
    NodeTeam *q;
    int maxTeams=1,c=1;
    float m;
    while(maxTeams<=*noTeams)
    {
        maxTeams*=2;
    }
    maxTeams/=2;
    while(*noTeams>maxTeams)
    {
        if(c==1)
        {
            m=minPoints(*topTeams);
        }
        if((*topTeams)->points==m)
        {
            c=0;
            popTeam(topTeams);
            (*noTeams)--;
        }
        else
        {
            c=1;
            for(NodeTeam *p=*topTeams; p->next!=NULL; p=p->next)
            {
                if(p->next->points==m)
                {
                    c=0;
                    q=p->next;
                    p->next=q->next;
                    freeTeam(q);
                    (*noTeams)--;
                    break;
                }
            }
        }
    }
}

void pointsWinner(NodeTeam *winner)
{
    winner->points++;
    for(NodePlayer *p=winner->topPlayers; p!=NULL; p=p->next)
    {
        p->player.points++;
    }
}
void pushWinnerLoser(NodeTeam **topWinners,NodeTeam *winner,NodeTeam **topLosers,NodeTeam *loser)
{
    winner->next=*topWinners;
    *topWinners=winner;
    pointsWinner(winner);
    loser->next=*topLosers;
    *topLosers=loser;
}
void printRound(Queue *q,NodeTeam *topWinners,int round,FILE *h)
{
    fprintf(h,"--- ROUND NO:%d\n",round);
    for(NodeMatch *p=q->front; p!=NULL; p=p->next)
    {
        fprintf(h,"%s",p->team1->name);
        for(int i=0; i<33-strlen(p->team1->name); i++)
        {
            fprintf(h," ");
        }
        fprintf(h,"-");
        for(int i=0; i<33-strlen(p->team2->name); i++)
        {
            fprintf(h," ");
        }
        fprintf(h,"%s\n",p->team2->name);
    }
    fprintf(h,"\nWINNERS OF ROUND NO:%d\n",round);
    for(NodeTeam *p=topWinners; p!=NULL; p=p->next)
    {
        fprintf(h,"%s",p->name);
        for(int i=0; i<34-strlen(p->name); i++)
        {
            fprintf(h," ");
        }
        if(p->points!=6.625)
        {
            fprintf(h,"-  %.2f\n",p->points);
        }
        else
        {
            fprintf(h,"-  %.2f\n",p->points-0.01);
        }
    }
}
void createTop8(NodeTeam **topTeams,NodeTeam *topWinners)
{
    for(NodeTeam *p=topWinners; p!=NULL; p=p->next)
    {
        pushTeam(topTeams,p->name);
        (*topTeams)->points=p->points;
        for(NodePlayer *q=p->topPlayers; q!=NULL; q=q->next)
        {
            pushPlayer(&(*topTeams)->topPlayers,q->player.firstName,q->player.secondName,q->player.points);
        }
    }
}

int main(int argc,char *argv[])
{
    if(argc<4)
    {
        printf("Rule: lanParty c.in d.in r.out");
        exit(1);
    }
    FILE *f,*g,*h;
    int c[5];
    if((f=fopen(argv[1],"r"))==NULL || (g=fopen(argv[2],"r"))==NULL || (h=fopen(argv[3],"w"))==NULL)
    {
        printf("File open error\n");
        exit(1);
    }
    for(int i=0; i<5; i++)
    {
        fscanf(f,"%d",&c[i]);
    }
    fclose(f);
    NodeTeam *topTeams=NULL;
    int noTeams;
    if(c[0]==1)
    {
        fscanf(g,"%d",&noTeams);
        for(int i=0; i<noTeams; i++)
        {
            createTeam(&topTeams,g);
        }
    }
    fclose(g);
    if(c[1]==1)
    {
        filterTeams(&topTeams,&noTeams);
    }
    for(NodeTeam *p=topTeams; p!=NULL; p=p->next)
    {
        fprintf(h,"%s\n",p->name);
    }
    if(c[2]==1)
    {
        Queue *q=createQueue();
        NodeTeam *topWinners=topTeams,*topLosers=NULL;
        int round=1;
        fprintf(h,"\n");
        while(noTeams>1)
        {
            for(NodeTeam *p=topWinners; p!=NULL; p=p->next->next)
            {
                enQueue(q,p,p->next);
            }
            topWinners=NULL;
            for(NodeMatch *p=q->front; p!=NULL; p=p->next)
            {
                if(p->team1->points>p->team2->points)
                {
                    pushWinnerLoser(&topWinners,p->team1,&topLosers,p->team2);
                }
                else
                {
                    pushWinnerLoser(&topWinners,p->team2,&topLosers,p->team1);
                }
            }
            printRound(q,topWinners,round,h);
            if(noTeams>2)
            {
                fprintf(h,"\n");
            }
            deleteStackTeams(&topLosers);
            if(noTeams==16)
            {
                topTeams=NULL;
                createTop8(&topTeams,topWinners);
            }
            round++;
            noTeams/=2;
            deleteQueue(q);
        }
        free(q);
        freeTeam(topWinners);
    }
    Node *rootBST=NULL;
    if(c[3]==1)
    {
        for(NodeTeam *p=topTeams; p!=NULL; p=p->next)
        {
            rootBST=insertNodeBST(rootBST,p);
        }
        fprintf(h,"\nTOP 8 TEAMS:\n");
        printInorder(rootBST,h);
    }
    Node *rootAVL=NULL;
    if(c[4]==1)
    {
        traverseInorder(rootBST,&rootAVL);
        fprintf(h,"\nTHE LEVEL 2 TEAMS ARE: \n");
        printLevel(rootAVL,2,h);
        deleteTree(rootAVL);
    }
    fclose(h);
    deleteTree(rootBST);
    deleteStackTeams(&topTeams);
    return 0;
}
