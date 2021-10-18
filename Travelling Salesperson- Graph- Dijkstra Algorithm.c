#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    char city[20];
    int x;
}s[10];
void path(int n, int a[n][n], int start, int end)
{
    int cost[n][n], dist[n], visited[n], pred[n], i, j, min, next,count;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]==0)
            cost[i][j]=999;
            else
            cost[i][j]=a[i][j];
        }
    }
    for(i=0;i<n;i++)
    {
        dist[i]=cost[start][i];
        pred[i]=start;
        visited[i]=0;
    }
    dist[start]=0;
    visited[start]=1;
    count=1;
    while(count<n-1)
    {
        min=999;
        for(i=0;i<n;i++)
        {
            if(dist[i]<min&& !visited[i])
            {
                min=dist[i];
                next=i;
            }
        }
        visited[next]=1;
        for(i=0;i<n;i++)
        {
            if(!visited[i])
            {
                if((min+cost[next][i])<dist[i])
                {
                    dist[i]=min+cost[next][i];
                    pred[i]=next;
                }
            }
        }
        count++;
    }
    for(i=0;i<n;i++)
    {
        if(i==end)
        {
            printf("The distance from %s to %s is %d\n",s[start].city,s[end].city,dist[i]);
            printf("The path is: %s",s[i].city);
            j=i;
            do
            {
                j=pred[j];
                printf(" <- %s",s[j].city);
            }while(j!=start);
        }
        printf("\n");
    }
}
int main()
{
    int i,j,n,start,end,f=0;
    char source[20], destination[20];
    printf("Enter the number of cities: ");
    scanf("%d",&n);
    int a[n][n];
    printf("Enter the cities:\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",s[i].city);
        s[i].x=i;
    }
    printf("Enter the adjacency matrix:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    printf("Enter the source city: ");
    scanf("%s",source);
    printf("Enter the destination city: ");
    scanf("%s",destination);
    for(i=0;i<n;i++)
    {
        if(strcmp(source,s[i].city)==0)
        {
           start=i;
           f++;
        }
        if(strcmp(destination,s[i].city)==0)
        {
            end=i;
            f++;
        }
        if(f==2)
        break;
    }
    path(n,a,start,end);
    return 0;
}
