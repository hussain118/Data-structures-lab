#include <iostream>
#include <string>
using namespace std;

class node
{
private:
 
public:
int data;
node *next;
node(int data) : data(data), next(nullptr) {}


};
class LinkList
{
public:
   node *head;

   LinkList(){
    node *head=nullptr;
   }
   
   void insertMiddle(int position,int value){
    node *temp=head;
    int index=0;
    while (temp!=nullptr || index<position )

    {
        temp=temp->next;
        index++;
    }
    node *newnode= new node(value);
    newnode->next=temp->next;
    temp->next=newnode;
   }

   void deleteInMiddle(int position){
    node* temp=head;
    int index=0;
    if (head=nullptr)
    {
        return;
    }
    
    while (temp!=nullptr && position>index)
    {
        temp=temp->next;
        index++;
    }
    if (temp!=nullptr && temp->next!=nullptr)
    {
        node *nodetodelete=temp->next;
        temp->next=nodetodelete->next;
        delete nodetodelete;
    }
    
   }
   void Palindrome(int arr[],int n){
    node* temp=head;
    int index=0;
    while (temp!=nullptr)
    {

        temp=temp->next;
        index++;
    }
    temp=head;
    for (int i = 0; i < index; i++)
    {
        arr[i]=temp->data;
        temp=temp->next;
    }
    for (int i = 0; i < index/2; i++)
    {
        for (int j =index ; j > index-i-1; j--)
        {
            if (arr[i]!=arr[j])
            {
                cout<<"palindrome not true";
                break;
            
            }
            else
            cout<<"palindrome checked for "<<arr[i];


        }
        
    }
    
    
   }
};


 
