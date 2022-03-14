#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int id,bt,ct,rbt,finish;
    float tat,wt;
    struct node *lptr,*rptr;
}NODE;

void display(NODE*);
NODE *insert(NODE*);
void test(NODE*);

int flag = 0;

NODE *insert(NODE *first)
{
    NODE *newnode,*temp;
    newnode = (NODE*)malloc(sizeof(NODE));

    printf("\nEnter the process id : ");
    scanf("%d",&newnode->id);

    printf("\nEnter the process burst time : ");
    scanf("%d",&newnode->bt);
    newnode->finish = 0;
    newnode->wt = 0;
    newnode->tat = 0;
    newnode->ct = 0;
    newnode->rbt = newnode->bt;
    newnode->rptr=NULL;

    if(first == NULL)
    {
        newnode->lptr = NULL;
        first = newnode;
    }
    else
    {
        temp = first;
        while(temp->rptr != NULL)
            temp = temp->rptr;
            temp->rptr = newnode;
            newnode->lptr = temp;
    }
    return(first);
}

void test(NODE *first)
{
    while(first != NULL)
    {
        if(first->finish == 0)
           { flag = 1;
              return;
           }
        first = first->rptr;
    }
    flag = 0;
}

void display(NODE *first)
{   printf("\nid\tbt\twt\ttat\n\n");
    while(first != NULL)
    {
        printf("p%d\t%d\t%.0f\t%.0f\n",first->id,first->bt,first->wt,first->tat);
        first = first->rptr;
    }
}

int main()
{
    NODE *first = NULL,*temp;
    int n,i,curtime=0,tq,arr[100]={0},a=0;
    float awt=0,atat=0;

    printf("\nEnter the number of processes : ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        first = insert(first);

    printf("\nEnter the time quantum : ");
    scanf("%d",&tq);

    do
    {
        temp = first;
        while(temp != NULL)
        {
            if(temp->rbt >= tq)
            {
                curtime = curtime + tq;
                temp->rbt = temp->rbt - tq;
                arr[a++] = temp->id;
                if(temp->rbt == 0)
                {
                    temp->ct = curtime;
                    temp->finish = 1;
                }
            }
            else
            {   if(temp->finish != 1)
                {
                    curtime = curtime + temp->rbt;
                    temp->ct = curtime;
                    arr[a++] = temp->id;
                    temp->finish = 1;
                }
            }
        temp = temp->rptr;
        }
        test(first);
    }while(flag == 1);

    arr[a] = '\0';

    temp = first;
    while(temp != NULL)
    {
        temp->tat = temp->ct;
        temp->wt = temp->tat - temp->bt;
        temp = temp->rptr;
    }

    temp = first;
    while(temp != NULL)
    {
        atat = atat + temp->tat/n;
        awt = awt + temp->wt/n;
        temp = temp->rptr;
    }

    display(first);

    printf("\nAverage waiting time = %.2f\nAverage turn around time = %.2f\n",awt,atat);

    printf("\nGantt chart : \n\n");

    for(i=0;i<a-1;i++)
    printf("p%d->",arr[i]);
    printf("p%d\n",arr[a-1]);

    return 0;
}
