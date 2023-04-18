#include "queues.h"

void createPlayer(NodePlayer **topPlayers,FILE *g)
{
    Player player;
    char s[25];
    fscanf(g,"%s",s);
    player.firstName=(char *)malloc((strlen(s)+1)*sizeof(char));
    if(player.firstName==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    strcpy(player.firstName,s);
    fscanf(g,"%s",s);
    player.secondName=(char *)malloc((strlen(s)+1)*sizeof(char));
    if(player.secondName==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    strcpy(player.secondName,s);
    fscanf(g,"%d",&player.points);
    pushPlayer(topPlayers,player);
}
void createTeam(NodeTeam **topTeams,FILE *g)
{
    int noPlayers;
    char *name,s[35];
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
    name=(char *)malloc((strlen(s)+1)*sizeof(char));
    if(name==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    strcpy(name,s);
    pushTeam(topTeams,name);
    for(int i=0; i<noPlayers; i++)
    {
        createPlayer(&(*topTeams)->topPlayers,g);
    }
}

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
float minPoints(NodeTeam *topTeams)
{
    float m=pointsTeam(topTeams),k;
    for(NodeTeam *p=topTeams->next; p!=NULL; p=p->next)
    {
        k=pointsTeam(p);
        if(k<m)
        {
            m=k;
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
        if(pointsTeam(*topTeams)==m)
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
                if(pointsTeam(p->next)==m)
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
void printRound(Queue *q,NodeTeam *topWinners,int round,int noTeams,FILE *h)
{
    fprintf(h,"\n--- ROUND NO:%d\n",round);
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
        fprintf(h,"-  %.2f",pointsTeam(p));
        if(noTeams!=2)
        {
            fprintf(h,"\n");
        }
    }
}

int main()
{
    FILE *f,*g,*h;
    int c[5];
    if((f=fopen("c.txt","r"))==NULL || (h=fopen("r.txt","w"))==NULL)
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
        if((g=fopen("d.txt","r"))==NULL)
        {
            printf("File open error\n");
            exit(1);
        }
        fscanf(g,"%d",&noTeams);
        for(int i=0; i<noTeams; i++)
        {
            createTeam(&topTeams,g);
        }
        fclose(g);
    }
    if(c[1]==1)
    {
        filterTeams(&topTeams,&noTeams);
    }
    for(NodeTeam *p=topTeams; p!=NULL; p=p->next)
    {
        fprintf(h,"%s",p->name);
        if(p->next!=NULL)
        {
            fprintf(h,"\n");
        }
    }
    if(c[2]==1)
    {
        Queue *q;
        NodeTeam *topWinners=topTeams,*topLosers=NULL;
        int round=1;
        fprintf(h,"\n");
        while(noTeams>1)
        {
            q=createQueue();
            for(NodeTeam *p=topWinners; p!=NULL; p=p->next->next)
            {
                enQueue(q,p,p->next);
            }
            topWinners=NULL;
            for(NodeMatch *p=q->front; p!=NULL; p=p->next)
            {
                if(pointsTeam(p->team1)>pointsTeam(p->team2))
                {
                    pushWinnerLoser(&topWinners,p->team1,&topLosers,p->team2);
                }
                else
                {
                    pushWinnerLoser(&topWinners,p->team2,&topLosers,p->team1);
                }
            }
            printRound(q,topWinners,round,noTeams,h);
            if(noTeams>8)
            {
                deleteStackTeams(&topLosers);
            }
            round++;
            noTeams/=2;
            deleteQueue(q);
        }
        topTeams=topLosers;
        topWinners->next=topTeams;
        topTeams=topWinners;
    }
    fclose(h);
    deleteStackTeams(&topTeams);
    return 0;
}
