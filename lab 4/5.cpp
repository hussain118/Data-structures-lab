#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string teamName;
    int points;

    Node* next;
    Node* prev;

    Node(string name, int p)
    {
        teamName = name;
        points = p;

        next = nullptr;
        prev = nullptr;
    }
};

class DoublyCircularList
{
private:
    Node* head;

public:

    DoublyCircularList()
    {
        head = nullptr;
    }

    // Check empty
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

    // Count teams
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

    // Add team
    void addTeam(string name, int points)
    {
        if (searchTeam(name) != nullptr)
        {
            cout << "\nDuplicate team names are not allowed.\n";
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
            newNode->prev = head;

            cout << "Team added successfully.\n";
            return;
        }

        // Insert at end
        Node* last = head->prev;

        newNode->next = head;
        newNode->prev = last;

        last->next = newNode;
        head->prev = newNode;

        cout << "Team added successfully.\n";
    }

    // Remove specific team
    void removeTeam(string name)
    {
        if (head == nullptr)
        {
            cout << "\nList is empty.\n";
            return;
        }

        Node* temp = searchTeam(name);

        if (temp == nullptr)
        {
            cout << "\nTeam does not exist.\n";
            return;
        }

        // Only node
        if (temp->next == temp)
        {
            delete temp;
            head = nullptr;

            cout << "Team removed successfully.\n";
            return;
        }

        // Removing head
        if (temp == head)
        {
            head = head->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;

        cout << "Team removed successfully.\n";
    }

    // Display forward
    void displayForward()
    {
        if (head == nullptr)
        {
            cout << "\nList is empty.\n";
            return;
        }

        Node* temp = head;
        int position = 1;

        cout << "\n========== FORWARD ORDER ==========\n";

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

    // Display reverse
    void displayReverse()
    {
        if (head == nullptr)
        {
            cout << "\nList is empty.\n";
            return;
        }

        Node* temp = head->prev;
        int position = 1;

        cout << "\n========== REVERSE ORDER ==========\n";

        do
        {
            cout << position << ". "
                 << temp->teamName
                 << " | Points: "
                 << temp->points << endl;

            temp = temp->prev;
            position++;

        } while (temp != head->prev);
    }

    // Display both directions
    void displayTeams()
    {
        if (head == nullptr)
        {
            cout << "\nNo teams available.\n";
            return;
        }

        displayForward();
    }

    // Get highest points
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

    // Find lowest team according to current direction
    Node* findLowest(Node* start, Node* protectedTeam, bool forward)
    {
        Node* temp = start;
        Node* lowest = nullptr;

        do
        {
            // Do not eliminate protected team
            if (temp != protectedTeam)
            {
                if (lowest == nullptr ||
                    temp->points < lowest->points)
                {
                    lowest = temp;
                }
            }

            if (forward)
                temp = temp->next;
            else
                temp = temp->prev;

        } while (temp != start);

        return lowest;
    }

    // Delete node
    void deleteNode(Node* nodeToDelete)
    {
        if (nodeToDelete == nullptr)
            return;

        // Only node
        if (nodeToDelete->next == nodeToDelete)
        {
            delete nodeToDelete;
            head = nullptr;
            return;
        }

        if (nodeToDelete == head)
        {
            head = head->next;
        }

        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;

        delete nodeToDelete;
    }

    // Update points
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

    // Knockout challenge
    void knockoutChallenge(string startingTeam, int count)
    {
        if (head == nullptr)
        {
            cout << "\nERROR: No teams are available.\n";
            return;
        }

        if (head->next == head)
        {
            cout << "\nOnly one team is present.\n";
            cout << "Champion: " << head->teamName << endl;
            return;
        }

        if (count <= 0)
        {
            cout << "\nERROR: Counting number must be greater than 0.\n";
            return;
        }

        Node* current = searchTeam(startingTeam);

        if (current == nullptr)
        {
            cout << "\nERROR: Starting team does not exist.\n";
            return;
        }

        // true = forward
        // false = reverse
        bool forward = true;

        while (countTeams() > 1)
        {
            int total = countTeams();

            /*
                If count is larger than number of teams,
                it continues circularly.

                Example:
                total = 5
                count = 7

                (7 - 1) % 5 = 1

                So we move one node from starting team.
            */
            int moves = (count - 1) % total;

            Node* selected = current;

            // Counting
            for (int i = 0; i < moves; i++)
            {
                if (forward)
                    selected = selected->next;
                else
                    selected = selected->prev;
            }

            cout << "\n----------------------------------\n";

            cout << "Counting direction: ";

            if (forward)
                cout << "FORWARD\n";
            else
                cout << "REVERSE\n";

            cout << "Selected team: "
                 << selected->teamName << endl;

            Node* eliminated;

            bool protectionTriggered = false;

            // Highest points protection
            if (selected->points == highestPoints())
            {
                protectionTriggered = true;

                cout << "\nERROR: "
                     << selected->teamName
                     << " has the highest points.\n";

                cout << "This team cannot be eliminated.\n";

                // Find lowest team
                eliminated = findLowest(
                    selected,
                    selected,
                    forward
                );

                cout << "Lowest-point team selected instead: "
                     << eliminated->teamName << endl;

                /*
                    TASK 5 RULE:
                    Reverse direction because protection
                    rule was triggered.
                */
                forward = !forward;

                cout << "Counting direction has been reversed.\n";
            }
            else
            {
                eliminated = selected;
            }

            string eliminatedName = eliminated->teamName;

            /*
                Save the node that comes immediately after
                the eliminated team in the CURRENT direction.

                This is important because Task 5 says the
                next round starts after the actually eliminated
                team.
            */
            Node* nextStart;

            if (forward)
                nextStart = eliminated->next;
            else
                nextStart = eliminated->prev;

            // Delete team
            deleteNode(eliminated);

            cout << "\nEliminated team: "
                 << eliminatedName << endl;

            // Only one team remains
            if (countTeams() == 1)
            {
                cout << "\nOnly one team remains.\n";
                break;
            }

            // Update points
            updatePoints();

            cout << "\nUpdated points:\n";
            displayForward();

            cout << "\nCurrent circular order:\n";

            if (forward)
                displayForward();
            else
                displayReverse();

            /*
                Start next round from the node immediately
                following the eliminated team according to
                the current direction.
            */
            current = nextStart;
        }

        if (head != nullptr)
        {
            cout << "\n========================================\n";
            cout << " FIFA KNOCKOUT CHALLENGE CHAMPION\n";
            cout << "========================================\n";
            cout << "Champion: " << head->teamName << endl;
            cout << "Points  : " << head->points << endl;
        }
    }
};

int main()
{
    DoublyCircularList teams;

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

            cout << "Enter team name to remove: ";
            getline(cin, name);

            teams.removeTeam(name);
        }

        else if (choice == 3)
        {
            string name;

            cin.ignore();

            cout << "Enter team name to search: ";
            getline(cin, name);

            if (teams.searchTeam(name) != nullptr)
            {
                cout << "\nTeam exists in the list.\n";
            }
            else
            {
                cout << "\nTeam does not exist.\n";
            }
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