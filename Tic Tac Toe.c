#include <stdio.h>
#include <ctype.h>
#include <string.h>
char a[3][3];
int fun(int n, char ch)
{
    int p=1;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
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
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(j!=2)
            printf("%c | ",a[i][j]);
            else
            printf("%c",a[i][j]);
        }
        printf("\n");
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
    char n1[20], n2[20],f;
    int i,j,k=1,c,r;
    printf("Player 1 name: ");
    scanf("%s",n1);
    printf("Player 2 name: ");
    scanf("%s",n2);
    memset(a,' ',sizeof(a)); //allocates space to every index in array a 
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
    return 0;
}
