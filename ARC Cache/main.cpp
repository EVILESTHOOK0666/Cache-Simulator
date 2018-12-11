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
}*head=NULL,*head2=NULL,*head3=NULL,*head4=NULL;

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
    prev=head;
    if(head==NULL)
        return head;
    else if(head->next==NULL)
    {
        head=NULL;
         free(temp);
        return head;
    }
    else
    {
    while(temp->next!=NULL)
    {
        prev=temp;
        temp=temp->next;
    }
    prev->next=NULL;
    free(temp);
    return head;
    }
}
struct node* getlast(struct node* head)
{
    struct node *temp;
    temp=head;
    if(head==NULL)
        return head;
    else if(head->next==NULL)
    {
        return head;
    }
    else
    {
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    return temp;
    }
}
struct node* del(struct node* head,long n)
{
    struct node *temp,*prev;
    if(head==NULL)
        return head;
    else if(head->data==n)
    {
        temp=head;
        head=head->next;
        free(temp);
        return head;
    }
    else
    {
    temp=head;
    while(temp->data!=n)
    {
        prev=temp;
        temp=temp->next;
    }
    prev->next=temp->next;
    free(temp);
    return head;
    }
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
int contain(struct node *head,long n)
{
    struct node *temp;
    int p=0;
    temp=head;
        while(temp!=NULL)
        {
            if(temp->data==n)
            {
                p=1;
                break;
            }
            temp=temp->next;
        }
    return p;
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
    cout<<"\n";
}

int main()
{
    ifstream infile("P7.lis");
    char line[100];long c=0,i,j,n;
    long  hit=0,miss=0,mem_acc=0;
    double hit_ratio;
    int p;
    cout<<"Compiling ARC.....\n";
    cout<<"Enter the cache size\n";
    cin>>n;
    p=n/2;
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
            //case 1:
            struct node *temp;
                if(contain(head,i)==1)
                {
                    hit++;
                    head=del(head,i);
                    if(length(head2)>n-p && head2!=NULL)
                    {
                    temp=getlast(head2);
                        if(length(head4)<p)
                        head4=addfirst(head4,temp->data);
                        else
                        {
                            head4=removelast(head4);
                            head4=addfirst(head4,temp->data);
                        }
                        head2=removelast(head2);
                    }
                    head2=addfirst(head2,i);
                }
                //Case 2:
            else if(contain(head2,i)==1)
            {
                    hit++;
                    head2=del(head2,i);
                    head2=addfirst(head2,i);
            }
            else if(contain(head3,i)==1)
            {
                miss++;
                int x;
                x=length(head2);
                p++;
                if(p>n)
                    p=n;
                if(x>n-p)
                {
                    temp=getlast(head2);
                        if(length(head4)<p)
                        head4=addfirst(head4,temp->data);
                        else
                        {
                            head4=removelast(head4);
                            head4=addfirst(head4,temp->data);
                        }
                        head2=removelast(head2);
                }
                head3=del(head3,i);
                if(length(head2)>=n-p && head2!=NULL)
                {
                    temp=getlast(head2);
                        if(length(head4)<p)
                        head4=addfirst(head4,temp->data);
                        else
                        {
                            head4=removelast(head4);
                            head4=addfirst(head4,temp->data);
                        }
                        head2=removelast(head2);
                        head2=addfirst(head2,i);
                }
            }
            //case 4:
            else if(contain(head4,i)==1)
            {
                miss++;
                int x;
                x=length(head);
                p--;
                if(p<0)
                    p=0;
                if(x>p)
                {
                    temp=getlast(head);
                        if(length(head3)<n-p && temp!=NULL)
                        head3=addfirst(head3,temp->data);
                        else
                        {
                            head3=removelast(head3);
                            head3=addfirst(head3,temp->data);
                        }
                        head=removelast(head);
                }
                head4=del(head4,i);
                if(length(head2)>=n-p)
                {
                    temp=getlast(head2);
                        if(length(head4)<p && temp!=NULL)
                        head4=addfirst(head4,temp->data);
                        else
                        {
                            head4=removelast(head4);
                            head4=addfirst(head4,temp->data);
                        }
                        head2=removelast(head2);
                        head2=addfirst(head2,i);
                }
            }
            //case 5:
            else
            {
                    miss++;
                    if(length(head)>=p)
                    {
                    temp=getlast(head);
                        if(length(head3)<p)
                        head3=addfirst(head3,temp->data);
                        else
                        {
                            head3=removelast(head3);
                            head3=addfirst(head3,temp->data);
                        }
                        head=removelast(head);
                        head=addfirst(head,i);
                    }
                    else
                    {
                        head=addfirst(head,i);
                    }
            }
        }

        }
    infile.close();
    mem_acc=hit+miss;
    hit_ratio=((float)hit/mem_acc)*100;
    cout<<"Hits:"<<hit<<"\n";
    cout<<"Miss:"<<miss<"\n";
    cout<<"\nMemory Accesses:"<<mem_acc<<"\n";
    cout<<"Hit Ratio:"<<hit_ratio<<"\n";
    return 0;
}
