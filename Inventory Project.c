#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct product
{
    char name[20];
    int code;
    double price;
    int quantity;
    struct product *left;
    struct product *right;
};
struct product *root1=NULL; //tree 1 for code
struct product *root2=NULL; //tree 2 for name
int s1=0, s2=0, d=0; //flag variables for search and delete functions
struct product* newnode(char *n, int c, double p, int q)
{
    struct product* temp;
    temp=(struct product *)malloc(sizeof(struct product));
    strcpy(temp->name,n);
    temp->code=c;
    temp->price=p;
    temp->quantity=q;
    temp->left=NULL;
    temp->right=NULL;
}
struct product* insertnode_code(struct product* root1, char *n, int c, double p, int q)
{
    if(root1==NULL)
    root1=newnode(n,c,p,q);
    else if(c<root1->code)
    root1->left=insertnode_code(root1->left,n,c,p,q);
    else if(c>root1->code)
    root1->right=insertnode_code(root1->right,n,c,p,q);
}
struct product* insertnode_name(struct product* root2, char *n, int c, double p, int q)
{
    if(root2==NULL)
    root2=newnode(n,c,p,q);
    else if(strcmp(n,root2->name)<0) //meaning n comes before name
    root2->left=insertnode_name(root2->left,n,c,p,q);
    else if(strcmp(n,root2->name)>0)
    root2->right=insertnode_name(root2->right,n,c,p,q);
}
struct product* searchbycode(struct product *root1, int scode)
{
    if(root1!=NULL)
    {
        searchbycode(root1->left,scode);
        if(scode==root1->code)
        {
            s1=1;
            printf("Product found!\n");
            printf("Product Name: %s\n",root1->name);
            printf("Product Code: %d\n",root1->code);
            printf("Product Price: %lf\n",root1->price);
            printf("Product Quantity: %d\n",root1->quantity);
        }
        searchbycode(root1->right,scode);
    }
}
struct product* searchbyname(struct product *root2, char *sname)
{
    if(root2!=NULL)
    {
        searchbyname(root2->left,sname);
        if(strcmp(sname,root2->name)==0)
        {
            s2=1;
            printf("Product found!\n");
            printf("Product Name: %s\n",root2->name);
            printf("Product Code: %d\n",root2->code);
            printf("Product Price: %lf\n",root2->price);
            printf("Product Quantity: %d\n",root2->quantity);
        }
        searchbyname(root2->right,sname);
    }
}
struct product* findMinimum(struct product *root)
{
    while(root->left!=NULL)
    {
        root=root->left;
    }
    return root;
}
struct product* deletename(struct product *root2, char *dname)
{
    if(root2==NULL) //tree is empty
    return root1;
    else if(strcmp(dname,root2->name)<0) //meaning dname comes before name
    root2->left=deletename(root2->left,dname); 
    else if(strcmp(dname,root2->name)>0)
    root2->right=deletename(root2->right,dname); 
    else //meaning (strcmp(dname,root2->name)==0)
    {
        if(root2->left==NULL&&root2->right==NULL) 
        {
            free(root2);
            root2=NULL;
            return root2;
        }
        else if(root2->left==NULL) 
        {
            struct product* temp=root2;
            root2=root2->right; 
            free(temp); 
            return root2;
        }
        else if(root2->right==NULL) 
        {
            struct product* temp=root2;
            root2=root2->left; 
            free(temp);
            return root2;
        }
        else
        {
            struct product* temp=findMinimum(root2->right);
            strcpy(root2->name,temp->name);
            root2->right=deletename(root2->right,temp->name);
        }
    }
}
struct product* deletecode(struct product *root1, int dcode)
{
    if(root1==NULL) //tree is empty
    return root1;
    else if(dcode<root1->code)
    root1->left=deletecode(root1->left,dcode); 
    else if(dcode>root1->code)
    root1->right=deletecode(root1->right,dcode); 
    else if(dcode==root1->code)
    {
        deletename(root2,root1->name);
        d=1;
        if(root1->left==NULL&&root1->right==NULL) 
        {
            free(root1);
            root1=NULL;
            return root1;
        }
        else if(root1->left==NULL) 
        {
            struct product* temp=root1;
            root1=root1->right; 
            free(temp); 
            return root1;
        }
        else if(root1->right==NULL) 
        {
            struct product* temp=root1;
            root1=root1->left; 
            free(temp);
            return root1;
        }
        else
        {
            struct product* temp=findMinimum(root1->right);
            root1->code=temp->code;
            root1->right=deletecode(root1->right,temp->code);
        }
        printf("Product deleted!\n");
    }
}
void sorted(struct product *root1) //displaying inorder of code tree
{
    if(root1!=NULL)
    {
        sorted(root1->left);
        printf("Product Name: %s\n",root1->name);
        printf("Product Code: %d\n",root1->code);
        printf("Product Price: %lf\n",root1->price);
        printf("Product Quantity: %d\n\n",root1->quantity);
        sorted(root1->right);
    }
}
int main()
{
    int x,c,q,scode,dcode;  //x for switch, c for code, q for quantity, scode for search by code
    //dcode for deletion
    double p; //for price
    char ch='y',n[20], sname[20]; //n for name, sname for search by name
    while(ch=='y'||ch=='Y')
    {
        printf("           ***MENU***\n");
        printf("Enter 1 to insert product details\n");
        printf("Enter 2 to search a product by code\n");
        printf("Enter 3 to search a product by name\n");
        printf("Enter 4 to delete a product from the list\n");
        printf("Enter 5 to display all the products in list\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
            printf("Enter Product Name: ");
            scanf("%s",n);
            printf("Enter Product Code: ");
            scanf("%d",&c);
            printf("Enter Product Price: ");
            scanf("%lf",&p);
            printf("Enter Product Quantity: ");
            scanf("%d",&q);
            if(root1==NULL||root2==NULL) //checking only one of them is also sufficient
            {
                root1=newnode(n,c,p,q);
                root2=newnode(n,c,p,q);
            }
            else
            {
                insertnode_code(root1,n,c,p,q);
                insertnode_name(root2,n,c,p,q);
            }
            break;
            case 2:
            printf("Enter product code to be searched: ");
            scanf("%d",&scode);
            searchbycode(root1,scode);
            if(s1==0)
            printf("Product not found\n");
            break;
            case 3:
            printf("Enter product name to be searched: ");
            scanf("%s",sname);
            searchbyname(root2,sname);
            if(s2==0)
            printf("Product not found\n");
            break;
            case 4:
            printf("Enter product code to be deleted: ");
            scanf("%d",&dcode);
            deletecode(root1,dcode);
            if(d==0)
            printf("Product code entered is not in the list\n");
            break;
            case 5:
            printf("List of Products in the Inventory:\n");
            sorted(root1);
            break;
            default:
            printf("Invalid choice\n");
            break;
            
        }
        printf("Do you wish to continue? Press y or Y for yes\n");
        scanf("%*c%c",&ch);
    }
}
