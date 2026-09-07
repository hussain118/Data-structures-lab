#include <iostream>

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
  


   void evenodd(){
    node *temp=head;
    bool flag=false;
    int index;
    while (temp!=nullptr)
    {
        temp=temp->next;
        index++;
    }
   temp=head;
int count=0;
int countodd;
  while (temp!=nullptr)
  {
      if (temp->data%2==0)
      {
        
        count++;
        
      }
      
      else{
          
          countodd++;
        }
        temp=temp->next;
    }
  if (count==index)
  {
      cout<<"whole list even";
}
  else if (countodd==index)
  {
    cout<<"whole list odd";
  }
  else{
    flag=true;
  }
 
  if (flag=true)
  {
    temp = head;
    
    while (temp!=nullptr)
    {
        if (temp->next->data %2==0)
        {
            node *newnode=temp;
        }
        
    }
    
  }
  
   
        
    
     
}  
};


