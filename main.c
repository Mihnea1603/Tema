#include "stacks.h"

void createPlayer(NodePlayer **top,FILE *g)
{
    Player player;
    char s[20];
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
    pushPlayer(top,player);
}

void createTeam(NodeTeam **top,FILE *g)
{
    int m;
    char *team;
    char s[25];
    fscanf(g,"%d",&m);
    fseek(g,1,1);
    fgets(s,25,g);
    team=(char *)malloc((strlen(s)+1)*sizeof(char));
    if(team==NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }
    strcpy(team,s);
    pushTeam(top,team);
    for(int i=0; i<m; i++)
    {
        createPlayer(&(*top)->top,g);
    }
}

int main()
{
    FILE *f,*g,*h;
    NodeTeam *top=NULL;
    int v[5];
    if((f=fopen("c.txt","r"))==NULL || (h=fopen("r.txt","w"))==NULL)
    {
        printf("File open error\n");
        exit(1);
    }
    for(int i=0; i<5; i++)
    {
        fscanf(f,"%d",&v[i]);
    }
    fclose(f);
    if(v[0]==1)
    {
        int n;
        if((g=fopen("d.txt","r"))==NULL)
        {
            printf("File open error\n");
            exit(1);
        }
        fscanf(g,"%d",&n);
        for(int i=0; i<n; i++)
        {
            createTeam(&top,g);
        }
        fclose(g);
        for(NodeTeam *p=top; p!=NULL; p=p->next)
        {
            fprintf(h,"%s",p->team);
        }
    }
    deleteStackTeam(&top);
    fclose(h);
    return 0;
}
