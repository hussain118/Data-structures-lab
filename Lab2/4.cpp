#include <iostream>
#include <iomanip>
using namespace std;

void displaySeating(bool** cinema, const int* rowSizes, int numRows) {
    int totalSeats = 0;
    int availableSeats = 0;

    cout << "\n--- SEATING MAP ---\n";

    for (int i = 0; i < numRows; ++i) {
        cout << "Row " << setw(2) << (i + 1) << ": ";

        for (int j = 0; j < rowSizes[i]; ++j) {
            totalSeats++;

            if (!cinema[i][j]) {
                availableSeats++;
                cout << "[O] "; // O = Available
            } else {
                cout << "[X] "; // X = Reserved
            }
        }

        cout << "\n";
    }

    if (totalSeats > 0) {
        double percentage =
            (static_cast<double>(availableSeats) / totalSeats) * 100.0;

        cout << "\nTotal Seats: " << totalSeats << "\n";
        cout << "Available Seats: " << availableSeats << "\n";

        cout << fixed << setprecision(2);
        cout << "Availability Percentage: " << percentage << "%\n";
    } else {
        cout << "No seats allocated in the cinema.\n";
    }
}

int main() {
    int numRows;

    cout << "Enter the number of rows: ";

    if (!(cin >> numRows) || numRows <= 0) {
        cout << "Invalid number of rows.\n";
        return 1;
    }

    // Allocate array of pointers (rows)
    // and array to store each row's size
    bool** cinema = new bool*[numRows];
    int* rowSizes = new int[numRows];

    for (int i = 0; i < numRows; ++i) {
        cout << "Enter number of seats for row "
             << (i + 1) << ": ";

        cin >> rowSizes[i];

        if (rowSizes[i] <= 0) {
            cout << "Invalid seat count. Setting row size to 0.\n";

            rowSizes[i] = 0;
            cinema[i] = nullptr;

            continue;
        }

        // Allocate seats for this row,
        // default to false (available)
        cinema[i] = new bool[rowSizes[i]]{false};
    }

    int choice;

    do {
        cout << "\n--- CINEMA SYSTEM ---\n";
        cout << "1. Reserve a seat\n";
        cout << "2. Cancel reservation\n";
        cout << "3. Display seating & availability\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (choice == 1 || choice == 2) {
            int r, s;

            cout << "Enter row number (1-" << numRows << "): ";
            cin >> r;

            cout << "Enter seat number: ";
            cin >> s;

            int rowIdx = r - 1;
            int seatIdx = s - 1;

            // Bounds checking before memory access
            if (rowIdx < 0 || rowIdx >= numRows) {
                cout << "Error: Invalid row number!\n";
            }
            else if (seatIdx < 0 || seatIdx >= rowSizes[rowIdx]) {
                cout << "Error: Invalid seat number for row "
                     << r << "!\n";
            }
            else {
                if (choice == 1) {
                    // Reserve
                    if (cinema[rowIdx][seatIdx]) {
                        cout << "Seat is already reserved.\n";
                    }
                    else {
                        cinema[rowIdx][seatIdx] = true;
                        cout << "Seat successfully reserved.\n";
                    }
                }
                else {
                    // Cancel
                    if (!cinema[rowIdx][seatIdx]) {
                        cout << "Seat is already available.\n";
                    }
                    else {
                        cinema[rowIdx][seatIdx] = false;
                        cout << "Reservation canceled.\n";
                    }
                }
            }
        }
        else if (choice == 3) {
            displaySeating(cinema, rowSizes, numRows);
        }

    } while (choice != 4);

    // Free all dynamically allocated memory
    for (int i = 0; i < numRows; ++i) {
        delete[] cinema[i];
    }

    delete[] cinema;
    delete[] rowSizes;

    cout << "Exiting system. Dynamic memory freed.\n";

    return 0;
}
