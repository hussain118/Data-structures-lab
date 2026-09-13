#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string teamName;
    int points;
    Node* next;

    Node(string name, int p)
    {
        teamName = name;
        points = p;
        next = nullptr;
    }
};

class CircularList
{
private:
    Node* head;

public:

    CircularList()
    {
        head = nullptr;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    // Create node
    Node* createNode(string name, int points)
    {
        return new Node(name, points);
    }

    // Search team
    Node* searchTeam(string name)
    {
        if (head == nullptr)
            return nullptr;

        Node* temp = head;

        do
        {
            if (temp->teamName == name)
                return temp;

            temp = temp->next;

        } while (temp != head);

        return nullptr;
    }

    // Add team
    void addTeam(string name, int points)
    {
        if (searchTeam(name) != nullptr)
        {
            cout << "\nDuplicate team name is not allowed.\n";
            return;
        }

        if (points < 0)
            points = 0;

        if (points > 150)
            points = 150;

        Node* newNode = createNode(name, points);

        // Empty list
        if (head == nullptr)
        {
            head = newNode;
            newNode->next = head;

            cout << "Team added successfully.\n";
            return;
        }

        // Insert at end
        Node* temp = head;

        while (temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = head;

        cout << "Team added successfully.\n";
    }

    // Remove a specific team
    void removeTeam(string name)
    {
        if (head == nullptr)
        {
            cout << "\nList is empty.\n";
            return;
        }

        Node* current = head;
        Node* previous = nullptr;

        // One node
        if (head->next == head)
        {
            if (head->teamName == name)
            {
                delete head;
                head = nullptr;

                cout << "Team removed successfully.\n";
            }
            else
            {
                cout << "Team does not exist.\n";
            }

            return;
        }

        // Find previous node
        while (current->teamName != name)
        {
            previous = current;
            current = current->next;

            if (current == head)
            {
                cout << "Team does not exist.\n";
                return;
            }
        }

        // Removing head
        if (current == head)
        {
            Node* last = head;

            while (last->next != head)
            {
                last = last->next;
            }

            head = head->next;
            last->next = head;

            delete current;
        }
        else
        {
            previous->next = current->next;
            delete current;
        }

        cout << "Team removed successfully.\n";
    }

    // Display teams
    void displayTeams()
    {
        if (head == nullptr)
        {
            cout << "\nNo teams available.\n";
            return;
        }

        Node* temp = head;

        cout << "\n========== CURRENT TEAMS ==========\n";

        int position = 1;

        do
        {
            cout << position << ". "
                 << temp->teamName
                 << " | Points: "
                 << temp->points << endl;

            temp = temp->next;
            position++;

        } while (temp != head);
    }

    // Count nodes
    int countTeams()
    {
        if (head == nullptr)
            return 0;

        int count = 0;

        Node* temp = head;

        do
        {
            count++;
            temp = temp->next;

        } while (temp != head);

        return count;
    }

    // Find highest points
    int highestPoints()
    {
        if (head == nullptr)
            return 0;

        int highest = head->points;

        Node* temp = head->next;

        while (temp != head)
        {
            if (temp->points > highest)
                highest = temp->points;

            temp = temp->next;
        }

        return highest;
    }

    // Find lowest team starting from a particular node
    Node* findLowest(Node* start, Node* protectedTeam)
    {
        Node* temp = start;
        Node* lowest = nullptr;

        do
        {
            if (temp != protectedTeam)
            {
                if (lowest == nullptr ||
                    temp->points < lowest->points)
                {
                    lowest = temp;
                }
            }

            temp = temp->next;

        } while (temp != start);

        return lowest;
    }

    // Delete a node and return the next node
    Node* deleteNode(Node* nodeToDelete)
    {
        if (nodeToDelete == nullptr)
            return nullptr;

        // Only one node
        if (nodeToDelete->next == nodeToDelete)
        {
            delete nodeToDelete;
            head = nullptr;
            return nullptr;
        }

        Node* previous = nodeToDelete;

        while (previous->next != nodeToDelete)
        {
            previous = previous->next;
        }

        Node* nextNode = nodeToDelete->next;

        // If deleting head
        if (nodeToDelete == head)
        {
            head = head->next;
        }

        previous->next = nodeToDelete->next;

        delete nodeToDelete;

        return nextNode;
    }

    // Update points according to positions
    void updatePoints()
    {
        if (head == nullptr)
            return;

        Node* temp = head;
        int position = 1;

        do
        {
            if (position % 2 == 1)
            {
                // Odd position: subtract 20
                temp->points -= 20;

                if (temp->points < 0)
                    temp->points = 0;
            }
            else
            {
                // Even position: add 10
                temp->points += 10;

                if (temp->points > 150)
                    temp->points = 150;
            }

            temp = temp->next;
            position++;

        } while (temp != head);
    }

    // Perform knockout challenge
    void knockoutChallenge(string startingTeam, int count)
    {
        if (head == nullptr)
        {
            cout << "\nNo teams available.\n";
            return;
        }

        if (head->next == head)
        {
            cout << "\nOnly one team exists.\n";
            cout << "Champion: " << head->teamName << endl;
            return;
        }

        Node* current = searchTeam(startingTeam);

        if (current == nullptr)
        {
            cout << "\nStarting team does not exist.\n";
            return;
        }

        if (count <= 0)
        {
            cout << "\nCounting number must be greater than 0.\n";
            return;
        }

        while (countTeams() > 1)
        {
            int total = countTeams();

            // Move count-1 positions
            int moves = (count - 1) % total;

            Node* selected = current;

            for (int i = 0; i < moves; i++)
            {
                selected = selected->next;
            }

            cout << "\nSelected team: "
                 << selected->teamName << endl;

            Node* eliminated;

            // Highest points protection
            if (selected->points == highestPoints())
            {
                cout << "ERROR: "
                     << selected->teamName
                     << " has the highest points and cannot be eliminated.\n";

                // Find lowest excluding protected team
                eliminated = findLowest(selected, selected);

                cout << "Therefore, lowest-point team "
                     << eliminated->teamName
                     << " will be eliminated instead.\n";
            }
            else
            {
                eliminated = selected;
            }

            string eliminatedName = eliminated->teamName;

            // Next round begins after eliminated team
            Node* nextStart = eliminated->next;

            // Delete selected team
            deleteNode(eliminated);

            cout << "\nEliminated team: "
                 << eliminatedName << endl;

            if (countTeams() == 1)
                break;

            // Update points
            updatePoints();

            cout << "\nUpdated points and circular order:\n";
            displayTeams();

            // Start next round from next remaining team
            current = nextStart;
        }

        if (head != nullptr)
        {
            cout << "\n=================================\n";
            cout << "FIFA KNOCKOUT CHALLENGE CHAMPION\n";
            cout << "Champion: " << head->teamName << endl;
            cout << "=================================\n";
        }
    }
};

int main()
{
    CircularList teams;

    int choice;

    do
    {
        cout << "\n========== FIFA KNOCKOUT CHALLENGE ==========\n";
        cout << "1. Add Team\n";
        cout << "2. Remove Team\n";
        cout << "3. Search Team\n";
        cout << "4. Display Teams\n";
        cout << "5. Start Knockout Challenge\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name;
            int points;

            cin.ignore();

            cout << "Enter team name: ";
            getline(cin, name);

            cout << "Enter points (0-150): ";
            cin >> points;

            teams.addTeam(name, points);
        }

        else if (choice == 2)
        {
            string name;

            cin.ignore();

            cout << "Enter team to remove: ";
            getline(cin, name);

            teams.removeTeam(name);
        }

        else if (choice == 3)
        {
            string name;

            cin.ignore();

            cout << "Enter team to search: ";
            getline(cin, name);

            if (teams.searchTeam(name) != nullptr)
                cout << "Team exists in the list.\n";
            else
                cout << "Team does not exist.\n";
        }

        else if (choice == 4)
        {
            teams.displayTeams();
        }

        else if (choice == 5)
        {
            string startingTeam;
            int count;

            cin.ignore();

            cout << "Enter starting team: ";
            getline(cin, startingTeam);

            cout << "Enter counting number: ";
            cin >> count;

            teams.knockoutChallenge(startingTeam, count);
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