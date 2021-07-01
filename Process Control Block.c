/* A multitasking operating system would manage multiple processes in the memory at a time. To manage the processes, it uses the Process Control Block (PCB).
PCB has following attributes:
Name of process, Process-id, Process-priority, link to next process. It manages PCB in the dynamic environment.
It allocates and de-allocates memory dynamically to processes and perform following operation as per users need:
1. Creation
2. Insertion
3. Deletion
4. Traversing
5. Searching
Write the program for process management for as operating system which perform above mentionedoperations. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct PCB *start=NULL;
struct PCB *ptr; //created to check for deletion conditions in main function
struct PCB
{
    char processname[20];
    int id;
    int priority;
    struct PCB *next;
};
void insertbeginning(char *n, int i, int p)
{
    struct PCB *new;
    new=(struct PCB *)malloc(sizeof(struct PCB));
    strcpy(new->processname,n);
    new->id=i;
    new->priority=p;
    new->next=start;
    start=new;
}
void insertmiddle(char *n, int i, int p)
{
    struct PCB *new;
    struct PCB *temp=start;
    new=(struct PCB *)malloc(sizeof(struct PCB));
    strcpy(new->processname,n);
    new->id=i;
    new->priority=p;
    for(int i=1;i<(p-1);i++)
    {
        if(temp->next!=NULL)
        {
            temp=temp->next;
        }
    }
    new->next=temp->next;
    temp->next=new;
    
}
void insertend(char *n, int i, int p)
{
    struct PCB *new;
    new=(struct PCB *)malloc(sizeof(struct PCB));
    struct PCB *temp=start;
    strcpy(new->processname,n);
    new->id=i;
    new->priority=p;
    new->next=NULL;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=new;
}
void deletebeginning()
{
    struct PCB *temp=start;
    start=start->next;
    free(temp);
}
void deletemiddle(int p) //receiving position of node to be deleted
{
    struct PCB *temp=start;
    for(int i=1;i<(p-1);i++)
    {
        if(temp->next!=NULL)
        {
            temp=temp->next;
        }
    }
    temp->next=temp->next->next;
    free(temp);
}
void deleteend()
{
    struct PCB *temp=start;
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=NULL;
    free(temp);
}
void search(char *s)
{
    int f=0;
    struct PCB *temp=start;
    printf("Search results are: \n");
    while(temp!=NULL)
    {
        if(strcmp(s,temp->processname)==0) //displaying all processes with the same name 
        {
            printf("Name: %s\n",temp->processname);
            printf("ID: %d\n",temp->id); 
            printf("Priority: %d\n",temp->priority);
            f=1;
        }
        temp=temp->next;
    }
    if(f==0)
    printf("No records found\n");
}
void print()
{ 
    struct PCB *temp=start;
    printf("The PCB data is as follows:\n");
    while(temp!=NULL)
    {
        printf("Name: %s\n",temp->processname);
        printf("ID: %d\n",temp->id);
        printf("Priority: %d\n",temp->priority);
        temp=temp->next;
    }
}
int main()
{
    int y=1,i=0,j=0,f=0,c,id,priority; //i is used in insertion, j&f are used in deletion
    char processname[20], s[20]; //s is used for searching process name
    while(y==1)
    {
        printf("***MENU***\n");
        printf("Enter 1 to insert\n");
        printf("Enter 2 to delete\n");
        printf("Enter 3 to search\n");
        printf("Enter 4 to traverse/print\n");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
            printf("Enter Process Name: ");
            scanf("%s",processname);
            printf("Enter Process ID: ");
            scanf("%d",&id);
            printf("Enter Priority: "); //Highest priority of a process can be 1
            scanf("%d",&priority);
            if(priority==1)
            insertbeginning(processname,id,priority);
            else if(priority>1&&priority<i&&i>=2)
            insertmiddle(processname,id,priority);
            else
            insertend(processname,id,priority);
            i++; //i increaments when 1 process is complete
            break;
            case 2:
            j=0;
            printf("Enter Process ID to be deleted: ");
            scanf("%d",&id); //deleting by ID as every process has unique ID
            ptr=start;
            while(ptr!=NULL)
            {
                if(id==ptr->id)
                {
                    if(j==0)
                    deletebeginning();
                    else if(j>0&&j<i)
                    deletemiddle(j+1); //sending the position of the node to be deleted
                    else
                    deleteend();
                    i--; //i decrements as 1 node is deleted
                    f=1;
                    break;
                }
                j++; //j is incremented to check for next index
                ptr=ptr->next;
            }
            if(f==0)
            printf("Process Name entered is wrong\n");
            break;
            case 3:
            printf("Enter the Process Name to be searched: ");
            scanf("%s",s); 
            search(s);
            break;
            case 4:
            print();
            break;
            default:
            printf("Wrong choice\n");
            break;
        }
        printf("Do you wish to continue? Enter 1 for yes, 0 for no\n");
        scanf("%d",&y);
    }
    return 0;
}
