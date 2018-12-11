#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
struct node
{
    long data;
    struct node* next;
}*head=NULL;

struct node* addfirst(struct node* head,long n)
{
    struct node* temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->data=n;
    temp->next=head;
    head=temp;
    return head;
}

struct node* removelast(struct node* head)
{
    struct node *temp,*prev;
    temp=head;
    if(head==NULL)
        return head;
    else if(head->next==NULL)
    {
        head=NULL;
         free(temp);
        return head;
    }
    while(temp->next!=NULL)
    {
        prev=temp;
        temp=temp->next;
    }
    prev->next=NULL;
    free(temp);

    return head;
}

struct node* del(struct node* head,long n)
{
    if(head==NULL)
        return head;

    struct node *temp,*prev;
    temp=head;
    while(temp->next->data!=n)
    {
        prev=temp;
        temp=temp->next;
    }
    prev->next=temp->next;
    free(temp);

    return head;
}
int length(struct node *head)
{
    int c=0;
    struct node *temp;
    temp=head;
    while(temp!=NULL)
    {
        c++;
        temp=temp->next;
    }
    return c;
}

void display(struct node *head)
{
    struct node *temp;
    temp=head;
    if(temp==NULL)
        cout<<"No elements\n";
    else
    {
        while(temp!=NULL)
        {
            cout<<temp->data<<" ";
            temp=temp->next;
        }
    }
}

int main()
{
    ifstream infile("P7.lis");
    char line[100];long c=0,i,j,n;
    long  hit=0,miss=0,mem_acc=0;
    double hit_ratio;
    cout<<"Compiling LRU.....\n";
    cout<<"Enter the cache size in bytes\n";
    cin>>n;
    while(!infile.eof())
    {
        infile.getline(line,100);
        c++;
        char ch[20],ch2[20],ch3,ch4,ch5[20];
        long a,b;
        for(i=0;line[i]!='\0';i++)
        {

            if(line[i]==' ')
            {
                a=atoi(ch);
                ch5[0]=line[i+1];
                if(line[i+2]!=' ')
                {
                ch5[1]=line[i+2];
                }
                b=atoi(ch5);
                break;
            }
            else
            {
                ch[i]=line[i];
            }
        }
        for(i=a;i<(a+b);i++)
        {
            struct node* temp;
            int p=0;
            temp=head;
            if(temp!=NULL)
            {
            while(temp!=NULL)
            {
                if(temp->data==i)
                {
                    hit++;
                    head=del(head,i);
                    head=addfirst(head,i);
                    p=1;
                    break;
                }
                temp=temp->next;
            }
            if(p==0)
            {
                if(length(head)>=n)
                {
                    head=removelast(head);
                    head=addfirst(head,i);
                }
                else
                {
                    head=addfirst(head,i);
                }
                miss++;
            }
            }
            else if(temp==NULL)
            {
                head=addfirst(head,i);
                miss++;
            }

        }
    }
    infile.close();
    mem_acc=hit+miss;
    hit_ratio=((float)hit/mem_acc)*100;
    cout<<"Hits:"<<hit<<"\n";
    cout<<"Miss:"<<miss<"\n";
    cout<<"\nMemory Accesses:"<<mem_acc;
    cout<<"\nHit Ratio:"<<hit_ratio<<"\n";
    return 0;
}
