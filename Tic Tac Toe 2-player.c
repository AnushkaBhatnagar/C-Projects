#include <stdio.h>
#include <ctype.h>
#include <string.h>
char a[3][3];
int i,j;
void instructions()
{
    printf("The board for the game is as follows:\n");
    printf("\t\t1\t|\t2\t|\t3\n");
    printf("\t------------------------------------------------\n");
    printf("\t\t4\t|\t5\t|\t6\n");
    printf("\t------------------------------------------------\n");
    printf("\t\t7\t|\t8\t|\t9\n\n");
    printf("Enter your desired choice of position upon your turn.\n");
}
int fun(int n, char ch)
{
    int p=1;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(p==n)
            {
                if(isspace(a[i][j]))
                {
                    a[i][j]=ch;
                    return 0;
                }
                else
                {
                    printf("Choice entered is already occupied. Enter again.\n");
                    return 1;
                }
            }
            p++;
        }
    }
}
void display()
{
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(j==0)
            printf("\t");
            if(j!=2)
            printf("\t%c\t|",a[i][j]);
            else
            printf("\t%c",a[i][j]);
        }
        printf("\n");
        if(i!=2)
        printf("\t------------------------------------------------\n");
    }
}
char check()
{
    char s=' ';
    if(a[0][0]!=' '&&a[0][0]==a[0][1]&&a[0][0]==a[0][2]) //row 1
    s=a[0][0];
    else if(a[1][0]!=' '&&a[1][0]==a[1][1]&&a[1][0]==a[1][2]) //row 2
    s=a[1][0];
    else if(a[2][0]!=' '&&a[2][0]==a[2][1]&&a[2][0]==a[2][2]) //row 3
    s=a[2][0];
    else if(a[0][0]!=' '&&a[0][0]==a[1][0]&&a[0][0]==a[2][0]) //col 1
    s=a[0][0];
    else if(a[0][1]!=' '&&a[0][1]==a[1][1]&&a[0][1]==a[2][1]) //col 2
    s=a[0][1];
    else if(a[0][2]!=' '&&a[0][2]==a[1][2]&&a[0][2]==a[2][2]) //col 3
    s=a[0][2];
    else if(a[0][0]!=' '&&a[0][0]==a[1][1]&&a[0][0]==a[2][2]) //left diagonal
    s=a[0][0];
    else if(a[0][2]!=' '&&a[0][2]==a[1][1]&&a[0][2]==a[2][0]) //right diagonal
    s=a[0][0];
    return s;
}
int main()
{
    char f;
    int k,c,r,y=1;
    while(y==1)
    {
         char n1[20], n2[20];
         k=1;
         memset(a,' ',sizeof(a)); //allocates space to every index in array a
         instructions();
         printf("Player 1 name: ");
         scanf("%s",n1);
         printf("Player 2 name: ");
         scanf("%s",n2); 
         while(k<=9)
        {
            if(k%2!=0) //player 1
            {
                printf("%s's turn!\nEnter choice: ",n1);
                scanf("%d",&c);
                if(c>=1&&c<=9)
                {
                    r=fun(c,'X');
                    k++;
                }
                else
                {
                    printf("Wrong input! Enter again.\n");
                    continue;
                }
            }
            else //player 2
            {
                printf("%s's turn!\nEnter choice: ",n2);
                scanf("%d",&c);
                if(c>=1&&c<=9)
                {
                    r=fun(c,'O');
                    k++;
                }
                else
                {
                    printf("Wrong input! Enter again.\n");
                    continue;
                }
            }
            if(r==1)
            k--;
            else
            display();
            f=check();
            if(!isspace(f))
            {
                if(f=='X')
                printf("%s wins!!\n",n1);
                else
                printf("%s wins!!\n",n2);
                break;
            }
            if(k==10&&isspace(f))
            printf("It's a tie!\n");
        }
            printf("Do you want to play again? Enter 1 for yes, any other number to exit: ");
            scanf("%d",&y);
    }
    return 0;
}
