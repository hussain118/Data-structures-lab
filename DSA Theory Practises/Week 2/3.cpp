#include <iostream>
#include <string>

using namespace std;

class node
{
private:

public:
    string name;
    node *next;

    node(string data) : name(data), next(nullptr) {}
};

class LinkList
{
public:
    node *head;

    LinkList()
    {
        head = nullptr;
    }

    void insertMiddle(int position, string value)
    {
        node *temp = head;
        int index = 0;

        
        while (temp != nullptr && index < position)
        {
            temp = temp->next;
            index++;
        }

         
        node *newnode = new node(value);

        newnode->next = temp->next;
        temp->next = newnode;
    }

    void insertEnd(string namw)
    {
         
        if (head == nullptr)
        {
            node *newnode = new node(namw);
            head = newnode;
            newnode->next = head;
            return;
        }

        node *temp = head;

        while (temp->next != head)
        {
            temp = temp->next;
        }

        // Corrected: create one node
        node *newnode = new node(namw);

        temp->next = newnode;
        newnode->next = head;
    }

    void deleteInMiddle(int position)
    {
        node *temp = head;
        int index = 0;

        // Corrected == instead of =
        if (head == nullptr)
        {
            return;
        }

        while (temp->next != head && index < position)
        {
            temp = temp->next;
            index++;
        }

        if (temp != nullptr && temp->next != head)
        {
            node *nodetodelete = temp->next;
            temp->next = nodetodelete->next;
            delete nodetodelete;
        }
    }

    void removePlayer()
    {
        node *temp = head;

        while (temp->next != temp)
        {
            /*
               temp moves to the next player.
               The player after temp is the 3rd player,
               so newnode points to that player and removes it.
               After deletion, temp moves to the next remaining
               player so counting continues from there.
            */

            node *newnode;

            temp = temp->next;
            newnode = temp->next;

            temp->next = newnode->next;
            delete newnode;

            temp = temp->next;
        }

        cout << "last player standing: " << temp->name;
    }
};