#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int breakingflag=0;
typedef struct bstnames
{
    char firstname[200];
    struct bstnames* right;
    struct bstnames* left;
    struct bstid *id;
    struct bstnames *father;
};
struct bstnames*Name=NULL;
typedef struct bstid
{
    char id[100];
    struct bstid*right;
    struct bstid*left;
    struct bstnames* name;
    struct bstid *father;
};
struct bstid*Id=NULL;
void constructorNames(struct bstnames* p)
{
    p->right=NULL;
    p->left=NULL;
    p->id=NULL;
}
void constructor(struct bstid* p)
{
    p->right=NULL;
    p->left=NULL;
    p->name=NULL;
    p->father=NULL;
}
void load()
{
    int x;
    struct bstnames* tempname;
    struct bstid*tempid;
    int i=0,j=0;
    int word=0;
    char first[25];
    char last[25];
    char number[10];
    FILE * f;
    char line[1000];
    f = fopen("names.txt","r");
    if (f != NULL)
    {
        printf("file exists !\n");
        while(!(feof(f)))
        {
            fgets(line,100,f);
            printf("%s\n",line);
            int n=strlen(line);
            word=0;
            j=0;
            i=0;
            while(word<2)
            {
                if(word==0)
                {
                    while(line[i]!=',')
                    {
                        first[j]=line[i];
                        i++;
                        j++;
                    }
                    first[j]='\0';
                    i++;
                }
                else if(word==1)
                {
                    j=0;
                    while(line[i]!='\n')
                    {
                        number[j]=line[i];
                        j++;
                        i++;
                    }
                    number[j]='\0';
                    i++;
                }
                word++;
            }
            int flag=0;
            struct bstnames*p=(struct bstnames*)malloc(sizeof(struct bstnames));
            constructorNames(p);
            struct bstid*pid=(struct bstid*)malloc(sizeof(struct bstid));
            constructor(pid);
            strcpy(p->firstname,first);
            strcpy(pid->id,number);
            p->id=pid;
            pid->name=p;
            if(Name==NULL)
            {
                Name=p;
                p->father=NULL;
            }
            else
            {
                tempname=Name;
                struct bstnames* runner;
                while(tempname)
                {
                    x=strcmpi(tempname->firstname,first);
                    if(x==0)
                    {
                        flag=1;
                        printf("Equality\n");
                        break;
                    }
                    else if(x>0)
                    {
                        runner=tempname;
                        tempname=tempname->left;
                    }
                    else
                    {
                        runner=tempname;
                        tempname=tempname->right;
                    }
                }
                if(flag==1)
                {
                    struct bstnames*temp;
                    temp=tempname->left;
                    p->father=tempname;
                    tempname->left=p;
                    p->left=temp;
                }
                else
                {
                    x=strcmpi(runner->firstname,first);
                    if(x>0)
                    {
                        runner->left=p;
                        p->father=runner;
                    }
                    if(x<0)
                    {
                        //printf("yemin %s",runner->firstname);
                        runner->right=p;
                        p->father=runner;
                    }
                }
            }
            if(Id==NULL)
            {
                Id=pid;
                pid->father=NULL;
            }
            else
            {
                int f;
                tempid=Id;
                struct bstid*runner2=NULL;
                while(tempid)
                {
                    //printf("tempid:%s\n",tempid->id);
                    f=strcmp(tempid->id,number);
                    printf("%s id\n",tempid->id);
                    if(f>0)
                    {
                        runner2=tempid;
                        tempid=tempid->left;
                    }
                    else if(f<0)
                    {
                        runner2=tempid;
                        tempid=tempid->right;
                    }
                    if(f==0)scanf("%d",&f);
                }
                f=strcmpi(runner2->id,number);
                if(f>0)
                {
                    pid->father=runner2;
                    runner2->left=pid;
                }
                else
                {
                    runner2->right=pid;
                    pid->father=runner2;
                }
            }
        }
        fclose(f);
    }
    else printf("File doesn't exist");
}
void Preorder(struct bstnames *root)
{
    if (root != NULL)
    {
        printf("first name: %s\nID : %s\n", root->firstname,root->id->id);
        Preorder(root->left);
        Preorder(root->right);
    }
}
void SearchName(struct bstnames *root,char student[])
{
    if(root!=NULL)
    {
        if(strcmpi(root->firstname,student)==0)
        {
            printf("First name:%s\nId:%s\n",root->firstname,root->id->id);
        }
        else if(SubString(root->firstname,student)==0)
        {
            printf("First name:%s\nId:%s\n",root->firstname,root->id->id);
        }
        SearchName(root->left,student);
        SearchName(root->right,student);
    }
}
struct bstid *SearchId(struct bstid*root,char number[])
{
    struct bstid *temp;
    if(root!=NULL)
    {
        if(strcmp(number,root->id)==0)
        {
            printf("First name:%s\nId:%s\n",root->name->firstname,root->id);
            temp=root;
        }
        SearchId(root->left,number);
        SearchId(root->right,number);

    }
    return temp;
}

void Preorderid(struct bstid*p)
{
    if(p)
    {
        printf("First name :%s\nId :%s\n",p->name->firstname,p->id);
        Preorderid(p->left);
        Preorderid(p->right);
    }
}
int SubString(char str1[],char str2[])
{
    int n,m,i,z,j;
    n=strlen(str1);
    m=strlen(str2);
    for(i=0; i<=n-m; i++)
    {
        for(j=i; j<i+m; j++)
        {
            z=1;
            if (str1[j]!=str2[j-i])
            {
                z=0;
                break;
            }
        }
        if (z==1)
            break;
    }
    if (z==0)
        return 1;
    else
        return 0;
}
void inorder (struct bstnames *root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    printf("Name : %s\nID : %s\n", root->firstname,root->id->id);
    inorder(root->right);
}
void postorder (struct bstnames *root)
{
    if(root==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("Name : %s\nID : %s\n", root->firstname,root->id->id);
}
struct bstid*pointerId;
struct bstnames* pointerName;
void Insert(struct bstnames* names,struct bstid* id)
{
    char number[20];
    char first[200];
    struct bstnames*p=(struct bstnames*)malloc(sizeof(struct bstnames));
    constructorNames(p);
    struct bstid*pid=(struct bstid*)malloc(sizeof(struct bstid));
    constructor(pid);
    printf("Enter The name\n");
    gets(first);
    while(!isValidName(first))
    {
        //printf("Not a valid name\n");
        printf("Enter the name\n");
        gets(first);
    }
    printf("Enter the ID\n");
    gets(number);
    while(!isdig(number))
    {
        //printf("Not a valid Id\n");
        printf("Enter a valid Id please\n");
        gets(number);
    }
    strcpy(p->firstname,first);
    strcpy(pid->id,number);
    p->id=pid;
    pid->name=p;
    if(Name)
    {
        pointerName=NULL;
        findMePointer(names,first,NULL);
        pointerId=NULL;
        fineMeId(id,number,NULL);
        int x;
        int y;
        int m;
        //printf("pointername %s\n",pointerName->firstname);
        //printf("%d pointerid\n%s\n",pointerId,pointerId->id);
        if(pointerId)
        {
            x=strcmpi(pointerName->firstname,first);
            m=strcmp(pointerId->id,number);
            if(x==0)
            {
                struct bstnames*temp;
                temp=pointerName->left;
                pointerName->left=p;
                p->father=pointerName;
                p->left=temp;
            }
            else if(x>0)
            {
                p->father=pointerName;
                pointerName->left=p;
            }
            else
            {
                p->father=pointerName;
                pointerName->right=p;
            }
            if(m>0)
            {
                pid->father=pointerId;
                pointerId->left=pid;
            }
            else
            {
                pid->father=pointerId;
                pointerId->right=pid;
            }
        }
        else
        {
            free(p);
            free(pid);
            printf("Some student has the same Id,Can't be inserted\n");
        }
    }
    else
    {
        Name=p;
        p->father=NULL;
        Id=pid;
        pid->father=NULL;
    }
}
void findMePointer(struct bstnames* names,char first[],struct bstnames* runner)
{

    if(names!=NULL)
    {
        int x;
        runner=names;
        x=strcmpi(names->firstname,first);
        if(x==0)
        {
            pointerName=names;
            return;
        }
        else if(x>0)
        {
            findMePointer(names->left,first,runner);
        }
        else
        {
            findMePointer(names->right,first,runner);
        }
    }
    else
    {
        pointerName=runner;
        return;
    }
}
void fineMeId(struct bstid*p,char number[],struct bstid*runner)
{
    if(p!=NULL)
    {
        int x=strcmp(p->id,number);
        if(x>0)
        {
            runner=p;
            fineMeId(p->left,number,runner);
        }
        else if(x<0)
        {
            runner=p;
            fineMeId(p->right,number,runner);
        }
        else
        {
            pointerId=NULL;
            return;
        }
    }
    else
    {
        printf("%s runner\n",runner->id);
        pointerId=runner;
        return;
    }
}
//struct bstid *maxID;
//struct bstnames *maxname;

struct bstnames*students[200];
int top=0;
void DeleteSearch(struct bstnames*p,char x[100],char found[30])
{
    if(p)
    {
        if(strcmpi(p->firstname,x)==0)
        {

            students[top]=p;
            top++;
        }
        else if(SubString(p->firstname,x)==0)
        {
            //printf("name:%s\nId:%s",p->firstname,p->id->id);
            students[top]=p;
            top++;
        }
        DeleteSearch(p->left,x,found);
        DeleteSearch(p->right,x,found);
    }
}
struct bstid *getMaxID(struct bstid* root,struct bstid *maxID)
{
    //constructor(&maxID);
    if(root == NULL)
        return NULL;
    if(root->right == NULL)
        return root;
    getMaxID(root->right,maxID);
}

struct bstnames *getMaxName(struct bstnames* root,struct bstnames *maxname)
{
    if(root == NULL)
        return NULL;
    if(root->right == NULL)
        return root;
    getMaxName(root->right,maxname);
}

void deleteid (struct bstid *root,char ID [30],struct bstid *maxID)
{
    struct bstid *temp = root;
    if(temp->left == temp ->right)  //law homma el 2 b NULL
    {
        if(temp->father!=NULL)
            if (strcmp(root->id,root->father->id)<0||strcmp(root->id,root->father->id)==0)
                temp->father->left=NULL;
            else
                temp->father->right = NULL;
        else
            root=NULL;

        free(temp);
    }
    else if (root->left==NULL)  //7aalet el child el yemeen
    {
        if(temp->father == NULL)
        {
            root->father=NULL;
            root=root->right;
        }
    }
    else if (root->right==NULL) //7aalet el child el shemaal
    {
        if(temp->father != NULL)
        {
            if (strcmp(temp->id,temp->father->id)>0)
                temp->father->right = temp->left;
            else
                temp->father->left = temp->left;
        }
        else
        {
            root = root->left;
            root->father = NULL;

        }
    }
    else
    {
        struct bstid *temp2;
        getMaxID(temp->left,maxID);
        strcpy(temp2->id,ID);
        strcpy(temp->id,temp2->id);
        strcpy(temp->name->firstname,temp2->name->firstname);
        deleteid(temp2,Id->id,maxID);
    }
}
void deletename (struct bstnames *root,char student [30],struct bstnames *maxname)
{
    struct bstnames *temp = root;
    if(temp->left == temp ->right)  //law homma el 2 b NULL
    {
        if(temp->father!=NULL)
            if (strcmpi(root->firstname,root->father->firstname)<0||strcmpi(root->firstname,root->father->firstname)==0)
                temp->father->left=NULL;
            else
                temp->father->right = NULL;
        else
            root=NULL;

        free(temp);
    }
    else if (root->left==NULL)  //7aalet el child el yemeen
    {
        if(temp->father == NULL)
        {
            root->father=NULL;
            root=root->right;
        }
    }
    else if (root->right==NULL) //7aalet el child el shemaal
    {
        if(temp->father != NULL)
        {
            if (strcmpi(temp->firstname,temp->father->firstname)>0)
                temp->father->right = temp->left;
            else
                temp->father->left = temp->left;
        }
        else
        {
            root = root->left;
            root->father = NULL;

        }
    }
    else
    {
        struct bstnames* temp2;
        getMaxName(temp->left,maxname);
        strcpy(temp2->firstname,student);
        strcpy(temp->firstname,temp2->firstname);
        strcpy(temp->id->id,temp2->id->id);
        deletename(temp2,Name->firstname,maxname);
    }
}
void deletebyid(struct bstid* root,char ID[10],char rootname[30],char maxID[30],char maxname[30])
{
    struct bstnames *arrayofpointers[50];
    int n=0,i;
    struct bstid* temp;
    char found[30];
    SearchId(root , ID);
    strcpy(rootname,found);
    if (root == NULL)
        printf("yadi el neela\n");
    else
        printf("mesh b NULL\n");
    temp = root;
    printf("el esm : %s\n",rootname);
    if (root == NULL)
    {
        printf("No Matches Found\n");
        return;
    }
    printf("wslt hena\n");
    if (temp == root)
    {
        printf("da5al el if\n");
        deleteid(root,Id->id,maxID);
    }
    else
    {
        printf("da5al el else\n");
        deleteid(temp,Id->id,maxID);
    }
    //SearchName(Name,rootname,found);
    /*for (i =0;i<n;i++)
    {
        if (arrayofpointers[i]->id == Id->id)
        {
             if(arrayofpointers[i] == rootname)
                deletename(Name,rootname);
            else
                deletename(arrayofpointers[i],rootname);
            break;
        }
    }*/
    printf("Deleted\n");

}
void save(FILE *fil,struct bstid *root,char ID [30])
{

    {
        if(root == NULL)
            return;
        fprintf(fil,"%s,%s\n",root->name,root->id);
        save(fil,root->left,ID);
        save(fil,root->right,ID);

    }
    fclose(fil);
}
int isValidName(char str[])
{
    int len;
    int i,j;
    int spaces=0;
    len = strlen(str);
    for(j=0; j<len; j++)
    {
        if(str[j]==' ')
            spaces++;
        else
            spaces=0;
    }
    if (spaces!=0)
    {
        printf("Name can't be empty\nPlease try again\n");
        return 0;
    }
    else if (spaces==0)
    {
        if (len==0)
        {
            printf("Name can't be empty\nPlease try again\n");
            return 0;
        }
        else
        {
            for(i=0; i<len; i++)
            {
                if(str[i]==' ')
                    continue;

                if(!isalpha(str[i]))
                {
                    printf("Error,name can't include numbers\nPlease try again\n");
                    return 0;
                }
                else
                    continue;
            }
        }
    }


}


int isdig(char str[])
{
    int len;
    int i,j;
    int spaces=0;
    len = strlen(str);
    for(j=0; j<len; j++)
    {
        if(str[j]==' ')
            spaces++;
        else
            spaces=0;
    }
    if (spaces!=0)
    {
        printf("ID can't be empty\nPlease try again\n");
        return 0;
    }
    else if (spaces==0)
    {
        if (len==0)
        {
            printf("ID can't be empty\nPlease try again\n");
            return 0;
        }
        else
        {
            for(i=0; i<len; i++)
            {
                if(!isdigit(str[i]))
                {
                    printf("Error,ID can't include charachters or spaces\nPlease try again\n");
                    return 0;
                }
                else
                {
                    continue;
                }

            }
        }
    }
}
/*void main()
{
    load(Name,Id);
    char ID[30];
    char student [30];
    int i;
    struct bstid *found=NULL;
    constructor(&found);
    struct bstid *maxID;
    constructor(&maxID);
    struct bstnames *maxname;
    constructorNames(&maxname);
    getMaxID(Id,&maxID);
    //getMaxID(Name,&maxname);
    if (Id == NULL)
        printf("Lessa b NULL\n");
    else
        printf("da el maxID : %s\n",maxID->id);
        printf("da el maxname : %s\n",maxname->firstname);
        //gets(ID);
    //found = SearchId(Id,ID);
    //printf("2aadi El ID bta3o : %s\n",found->id);
    //printf("wadi esm sa7eb el ID : %s\n",found->name->firstname);
    //deletebyid(Id,ID,found->name->firstname,Id->id,Id->name->firstname);
    printf("\n\n");
    Preorder(Name);
}
*/
void main ()
{
    char choice,cho,cho2;
    char student[30];
    char id[30];
    FILE *f;
    printf("\t\t\tWelcome To Our Project\n");
    printf("Options :-\n\n");
    printf("1 - Load\n2 - Insert\n3 - Search\n4 - Delete\n5 - Display\n6 - Save\n7 - Exit\n\n");
    printf("Please choose the option by entering the corresponding number:\n");
    scanf("%c",&choice);
    constructorNames(&Name);
    constructor(&Id);
    while (choice>='1'&&choice<='6'&&choice!='7')
{
    char ch;
    switch(choice)
    {
    case '1':
        getchar();
        load(Name,Id);
        break;
    case '2':
        getchar();
        Insert(Name,Id);
        break;
    case '3':
        printf("\n1 - Search By Name\n2 - Search By ID\n");
        getchar();
        printf("\nPlease Enter Your Choice:\n");
        scanf("%c",&cho);
        if (cho == '1')
        {
            getchar();
            printf("Enter The Name Of The Student You Want To Find:\n");
            gets(student);
            SearchName(Name,student);
        }
        else if (cho == '2')
        {
            getchar();
            printf("Enter The ID Of The Student You Want To Find\n");
            gets(id);
            SearchId(Id,id);
        }
        else {printf("Invalid Choice\n");
        main();
        }
        break;
    case '4':
        printf("1 - Delete By Name\n2 - Delete By ID\n");
        printf("\nEnter The Method Of Deleting\n");
        getchar();
        scanf("%c",&cho2);
        getchar();
        char ID [30];
        if (cho2 == '1')
            printf("Bati5a");
        else if (cho2 == '2'){
            printf("Enter The Student's ID : \n");
            gets(ID);
            //deletebyid(id,ID,student);
        }
        else
            {printf("Invalid Choice\n\n");main();}
    case '5':

        printf("1 - PreOrder\n2 - InOrder\n3 - PostOrder\n");
        printf("\nEnter The Method Of Displaying\n");
        getchar();
        scanf("%c",&ch);
        getchar();
        if (ch == '1')
            Preorder(Name);
        else if (ch == '2')
            inorder(Name);
        else if (ch == '3')
            postorder(Name);
        else {printf("Invalid Choice\n\n");main();}
        break;
    case '6':
        printf("Enter the path you want to save into\n");
        char savef[200];
        getchar();
        gets(savef);
        f =fopen(savef,"w");
        save(f,Id,Id->id);
        break;
    case '7':
            exit(0);
    default:
        printf("Invalid Choice\n");
        main();
    }
    printf("\n\n");
    printf("Options :-\n\n");
    printf("1 - Load\n2 - Insert\n3 - Search\n4 - Delete\n5 - Display\n6 - Save\n7 - Exit\n\n");
    printf("\nPlease choose the option by entering the corresponding number:\n");
    scanf("%c",&choice);
}
if (choice<'1'||choice>'7')
    {
        printf("Invalid Choice\n\n");
        main();

    }
}

