#include "stacks.h"

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
    int nrPlayers;
    char *team;
    char s[35];
    fscanf(g,"%d",&nrPlayers);
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
    team=(char *)malloc((strlen(s)+1)*sizeof(char));
    if(team==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    strcpy(team,s);
    pushTeam(topTeams,team);
    for(int i=0; i<nrPlayers; i++)
    {
        createPlayer(&(*topTeams)->topPlayers,g);
    }
}

int maxTeams(int nrTeams)
{
    int p=1;
    while(p<nrTeams)
    {
        p*=2;
    }
    return p/2;
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
    float m=pointsTeam(topTeams);
    for(NodeTeam *p=topTeams->next; p!=NULL; p=p->next)
    {
        if(pointsTeam(p)<m)
        {
            m=pointsTeam(p);
        }
    }
    return m;
}
void filterTeams(NodeTeam **topTeams,int *nrTeams)
{
    NodeTeam *q;
    int n=maxTeams(*nrTeams);
    float m;
    while(*nrTeams>n)
    {
        m=minPoints(*topTeams);
        if(pointsTeam(*topTeams)==m)
        {
            popTeam(topTeams);
        }
        else
        {
            for(NodeTeam *p=*topTeams; p->next!=NULL; p=p->next)
            {
                if(pointsTeam(p->next)==m)
                {
                    q=p->next;
                    p->next=q->next;
                    freeTeam(q);
                    break;
                }
            }
        }
        (*nrTeams)--;
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
    int nrTeams;
    if(c[0]==1)
    {
        if((g=fopen("d.txt","r"))==NULL)
        {
            printf("File open error\n");
            exit(1);
        }
        fscanf(g,"%d",&nrTeams);
        for(int i=0; i<nrTeams; i++)
        {
            createTeam(&topTeams,g);
        }
        fclose(g);
    }
    if(c[1]==1)
    {
        filterTeams(&topTeams,&nrTeams);
    }
    for(NodeTeam *p=topTeams; p!=NULL; p=p->next)
    {
        fprintf(h,"%s",p->team);
        if(p->next!=NULL)
        {
            fprintf(h,"\n");
        }
    }
    fclose(h);
    deleteStackTeams(&topTeams);
    return 0;
}
