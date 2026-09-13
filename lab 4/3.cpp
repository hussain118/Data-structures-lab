#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    string cnic;
    int seatNo;

    Node* next;
    Node* prev;

    Node(string n, string c, int s)
    {
        name = n;
        cnic = c;
        seatNo = s;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList
{
private:
    Node* head;
    Node* tail;

public:

    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Check whether list is empty
    bool isEmpty()
    {
        return head == nullptr;
    }

    // Create a node
    Node* createNode(string name, string cnic, int seat)
    {
        Node* newNode = new Node(name, cnic, seat);
        return newNode;
    }

    // Check if passenger already exists using CNIC/ID
    bool passengerExists(string cnic)
    {
        Node* temp = head;

        while (temp != nullptr)
        {
            if (temp->cnic == cnic)
                return true;

            temp = temp->next;
        }

        return false;
    }

    // Sorted insertion
    void insertSorted(string name, string cnic, int seat)
    {
        if (passengerExists(cnic))
        {
            cout << "\nReservation already exists for this passenger.\n";
            return;
        }

        Node* newNode = createNode(name, cnic, seat);

        // Empty list
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;

            cout << "\nReservation added successfully.\n";
            return;
        }

        // Insert before head
        if (name < head->name)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;

            cout << "\nReservation added successfully.\n";
            return;
        }

        // Find correct position
        Node* temp = head;

        while (temp->next != nullptr && temp->next->name <= name)
        {
            temp = temp->next;
        }

        // Insert at end
        if (temp->next == nullptr)
        {
            temp->next = newNode;
            newNode->prev = temp;
            tail = newNode;
        }
        else
        {
            // Insert in middle
            newNode->next = temp->next;
            newNode->prev = temp;

            temp->next->prev = newNode;
            temp->next = newNode;
        }

        cout << "\nReservation added successfully.\n";
    }

    // Display forward
    void displayForward()
    {
        if (head == nullptr)
        {
            cout << "\nReservation list is empty.\n";
            return;
        }

        Node* temp = head;

        cout << "\n--- Passengers (Alphabetical Order) ---\n";

        while (temp != nullptr)
        {
            cout << "Name  : " << temp->name << endl;
            cout << "CNIC  : " << temp->cnic << endl;
            cout << "Seat  : " << temp->seatNo << endl;
            cout << "-------------------------\n";

            temp = temp->next;
        }
    }

    // Display reverse
    void displayReverse()
    {
        if (tail == nullptr)
        {
            cout << "\nReservation list is empty.\n";
            return;
        }

        Node* temp = tail;

        cout << "\n--- Passengers (Reverse Alphabetical Order) ---\n";

        while (temp != nullptr)
        {
            cout << "Name  : " << temp->name << endl;
            cout << "CNIC  : " << temp->cnic << endl;
            cout << "Seat  : " << temp->seatNo << endl;
            cout << "-------------------------\n";

            temp = temp->prev;
        }
    }

    // Search passenger by name
    void searchPassenger(string name)
    {
        if (head == nullptr)
        {
            cout << "\nReservation list is empty.\n";
            return;
        }

        Node* temp = head;
        bool found = false;

        cout << "\nSearch Results:\n";

        while (temp != nullptr)
        {
            if (temp->name == name)
            {
                found = true;

                cout << "Name : " << temp->name << endl;
                cout << "CNIC : " << temp->cnic << endl;
                cout << "Seat : " << temp->seatNo << endl;
                cout << "-------------------------\n";
            }

            temp = temp->next;
        }

        if (!found)
        {
            cout << "Passenger does not exist.\n";
        }
    }

    // Delete one particular node
    void deleteNode(Node* temp)
    {
        if (temp == nullptr)
            return;

        // Only node
        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
            delete temp;
            return;
        }

        // First node
        if (temp == head)
        {
            head = head->next;
            head->prev = nullptr;

            delete temp;
            return;
        }

        // Last node
        if (temp == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;

            delete temp;
            return;
        }

        // Middle node
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
    }

    // Cancel reservation
    void cancelReservation()
    {
        if (head == nullptr)
        {
            cout << "\nReservation list is empty.\n";
            return;
        }

        string name;

        cout << "\nEnter passenger name: ";
        cin.ignore();
        getline(cin, name);

        Node* temp = head;

        int count = 0;

        // Count passengers with same name
        while (temp != nullptr)
        {
            if (temp->name == name)
                count++;

            temp = temp->next;
        }

        if (count == 0)
        {
            cout << "\nPassenger does not exist.\n";
            return;
        }

        // Only one passenger with this name
        if (count == 1)
        {
            temp = head;

            while (temp != nullptr)
            {
                if (temp->name == name)
                    break;

                temp = temp->next;
            }

            cout << "\nPassenger found:\n";
            cout << "Name : " << temp->name << endl;
            cout << "CNIC : " << temp->cnic << endl;
            cout << "Seat : " << temp->seatNo << endl;

            char confirm;

            cout << "Cancel this reservation? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {
                deleteNode(temp);
                cout << "Reservation cancelled successfully.\n";
            }
            else
            {
                cout << "Cancellation cancelled.\n";
            }

            return;
        }

        // Multiple passengers with same name
        cout << "\nMultiple passengers found with this name:\n";

        temp = head;
        int number = 1;

        while (temp != nullptr)
        {
            if (temp->name == name)
            {
                cout << number << ". ";
                cout << "CNIC: " << temp->cnic;
                cout << ", Seat: " << temp->seatNo << endl;

                number++;
            }

            temp = temp->next;
        }

        string selectedCNIC;

        cout << "\nEnter CNIC/ID of passenger to cancel: ";
        cin >> selectedCNIC;

        temp = head;

        while (temp != nullptr)
        {
            if (temp->name == name && temp->cnic == selectedCNIC)
                break;

            temp = temp->next;
        }

        if (temp == nullptr)
        {
            cout << "Passenger with this name and CNIC does not exist.\n";
            return;
        }

        char confirm;

        cout << "\nSelected passenger:\n";
        cout << "Name : " << temp->name << endl;
        cout << "CNIC : " << temp->cnic << endl;
        cout << "Seat : " << temp->seatNo << endl;

        cout << "\nCancel this reservation? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y')
        {
            deleteNode(temp);
            cout << "Reservation cancelled successfully.\n";
        }
        else
        {
            cout << "Cancellation cancelled.\n";
        }

        // Optional duplicate removal
        cout << "\nAre the remaining records with the same CNIC"
             << " duplicate reservations for the same passenger? (Y/N): ";

        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y')
        {
            Node* current = head;

            while (current != nullptr)
            {
                Node* nextNode = current->next;

                if (current->cnic == selectedCNIC)
                {
                    deleteNode(current);
                }

                current = nextNode;
            }

            cout << "Duplicate records removed.\n";
        }
    }
};

int main()
{
    DoublyLinkedList reservations;

    int choice;

    do
    {
        cout << "\n========== PIA TICKET RESERVATION ==========\n";
        cout << "1. Reserve Ticket\n";
        cout << "2. Cancel Reservation\n";
        cout << "3. Search Passenger\n";
        cout << "4. Display All Passengers\n";
        cout << "5. Display Reverse Order\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name;
            string cnic;
            int seat;

            cin.ignore();

            cout << "Enter passenger name: ";
            getline(cin, name);

            cout << "Enter CNIC/ID: ";
            getline(cin, cnic);

            cout << "Enter seat number: ";
            cin >> seat;

            reservations.insertSorted(name, cnic, seat);
        }

        else if (choice == 2)
        {
            reservations.cancelReservation();
        }

        else if (choice == 3)
        {
            string name;

            cin.ignore();

            cout << "Enter passenger name to search: ";
            getline(cin, name);

            reservations.searchPassenger(name);
        }

        else if (choice == 4)
        {
            reservations.displayForward();
        }

        else if (choice == 5)
        {
            reservations.displayReverse();
        }

        else if (choice == 6)
        {
            cout << "\nProgram ended.\n";
        }

        else
        {
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}