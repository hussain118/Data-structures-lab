#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int number;
int players = 3;

void directGuess(int player)
{
    int guess;
    cout << "Player " << player << ", enter guess: ";
    cin >> guess;

    if (guess == number)
    {
        cout << "Player " << player << " wins!\n";
        return;
    }

    if (guess < number)
        cout << "Too low\n";
    else
        cout << "Too high\n";

    directGuess(player % players + 1);
}

void playerTwo(int player);

void playerOne(int player)
{
    int guess;
    cout << "Player " << player << ", enter guess: ";
    cin >> guess;

    if (guess == number)
    {
        cout << "Player " << player << " wins!\n";
        return;
    }

    if (guess < number)
        cout << "Too low\n";
    else
        cout << "Too high\n";

    playerTwo(player % players + 1);
}

void playerTwo(int player)
{
    int guess;
    cout << "Player " << player << ", enter guess: ";
    cin >> guess;

    if (guess == number)
    {
        cout << "Player " << player << " wins!\n";
        return;
    }

    if (guess < number)
        cout << "Too low\n";
    else
        cout << "Too high\n";

    playerOne(player % players + 1);
}

int recursiveArraySum(int* arr[], int sizes[], int dim)
{
    if (dim == 0)
        return 0;

    int sum = 0;

    for (int i = 0; i < sizes[dim - 1]; i++)
        sum += arr[dim - 1][i];

    return sum + recursiveArraySum(arr, sizes, dim - 1);
}

int maze[5][5] = {
    {1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0},
    {1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0},
    {1, 0, 0, 1, 1}
};

int solution[5][5] = {0};

bool solveMaze(int r, int c)
{
    if (r < 0 || c < 0 || r >= 5 || c >= 5)
        return false;

    if (maze[r][c] == 0 || solution[r][c] == 1)
        return false;

    solution[r][c] = 1;

    if (r == 4 && c == 4)
        return true;

    if (solveMaze(r + 1, c) || solveMaze(r, c + 1) ||
        solveMaze(r - 1, c) || solveMaze(r, c - 1))
        return true;

    solution[r][c] = 0;
    return false;
}

bool safeFlag(int board[16][16], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
            return false;

        if (col - (row - i) >= 0 &&
            board[i][col - (row - i)] == 1)
            return false;

        if (col + (row - i) < 16 &&
            board[i][col + (row - i)] == 1)
            return false;
    }

    return true;
}

bool placeFlags(int board[16][16], int row)
{
    if (row == 16)
        return true;

    for (int col = 0; col < 16; col++)
    {
        if (safeFlag(board, row, col))
        {
            board[row][col] = 1;

            if (placeFlags(board, row + 1))
                return true;

            board[row][col] = 0;
        }
    }

    return false;
}

char terrain[6][6] = {
    {'D', 'S', 'S', 'F', 'S', 'S'},
    {'F', 'F', 'S', 'F', 'S', 'F'},
    {'S', 'S', 'S', 'S', 'S', 'S'},
    {'S', 'F', 'F', 'F', 'F', 'S'},
    {'S', 'S', 'S', 'S', 'S', 'S'},
    {'S', 'F', 'F', 'F', 'F', 'H'}
};

int visited[6][6] = {0};
int bestPath[6][6] = {0};
int currentPath[6][6] = {0};
int minWind = 1000;

void safestPath(int r, int c, int winds)
{
    if (r < 0 || c < 0 || r >= 6 || c >= 6)
        return;

    if (terrain[r][c] == 'F' || visited[r][c] == 1)
        return;

    if (winds >= minWind)
        return;

    visited[r][c] = 1;
    currentPath[r][c] = 1;

    if (terrain[r][c] == 'H')
    {
        minWind = winds;

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                bestPath[i][j] = currentPath[i][j];

        visited[r][c] = 0;
        currentPath[r][c] = 0;
        return;
    }

    int nextWind = winds;

    if (terrain[r][c] == 'D')
        nextWind++;

    safestPath(r + 1, c, nextWind);
    safestPath(r - 1, c, nextWind);
    safestPath(r, c + 1, nextWind);
    safestPath(r, c - 1, nextWind);

    visited[r][c] = 0;
    currentPath[r][c] = 0;
}

char forest[5][5] = {
    {'S', 'A', 'T', 'A', 'A'},
    {'A', 'T', 'A', 'T', 'A'},
    {'A', 'A', 'T', 'A', 'F'},
    {'T', 'A', 'G', 'G', 'G'},
    {'A', 'G', 'G', 'T', 'G'}
};

int squirrelPath[5][5] = {0};
int foxPath[5][5] = {0};

bool collectItems(int r, int c, char item,
                  int path[5][5], int count, int target)
{
    if (r < 0 || c < 0 || r >= 5 || c >= 5)
        return false;

    if (forest[r][c] == 'T' || path[r][c] == 1)
        return false;

    path[r][c] = 1;

    if (forest[r][c] == item)
        count++;

    if (count >= target)
        return true;

    if (collectItems(r + 1, c, item, path, count, target) ||
        collectItems(r, c + 1, item, path, count, target) ||
        collectItems(r - 1, c, item, path, count, target) ||
        collectItems(r, c - 1, item, path, count, target))
        return true;

    path[r][c] = 0;
    return false;
}

int main()
{
    int choice;

    cout << "Question 1: Direct Recursion\n";
    cout << "Question 2: Mutual Recursion\n";
    cout << "Question 3: Jagged Array Sum\n";
    cout << "Question 4: Maze Backtracking\n";
    cout << "Question 5: 16x16 Flag Placement\n";
    cout << "Question 6: Safest Drone Path\n";
    cout << "Question 7: Squirrel and Fox\n";
    cout << "Enter question number: ";
    cin >> choice;

    if (choice == 1)
    {
        srand(time(0));
        number = rand() % 100 + 1;
        directGuess(1);
    }
    else if (choice == 2)
    {
        srand(time(0));
        number = rand() % 100 + 1;
        playerOne(1);
    }
    else if (choice == 3)
    {
        int a[] = {1, 2, 3};
        int b[] = {4, 5};
        int c[] = {6, 7, 8, 9};
        int* arr[] = {a, b, c};
        int sizes[] = {3, 2, 4};

        cout << "Q3 Sum = "
             << recursiveArraySum(arr, sizes, 3) << endl;
    }
    else if (choice == 4)
    {
        if (solveMaze(0, 0))
        {
            cout << "Q4 Solution Array:\n";

            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                    cout << solution[i][j] << " ";
                cout << endl;
            }
        }
        else
            cout << "No path found\n";
    }
    else if (choice == 5)
    {
        int board[16][16] = {0};

        if (placeFlags(board, 0))
        {
            cout << "Q5 Maximum flags = 16\n";

            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < 16; j++)
                    cout << board[i][j] << " ";
                cout << endl;
            }
        }
    }
    else if (choice == 6)
    {
        safestPath(0, 0, 0);

        if (minWind == 1000)
            cout << "Q6 No path found\n";
        else
        {
            cout << "Q6 Minimum high-wind cells = "
                 << minWind << endl;

            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    if (terrain[i][j] == 'F')
                        cout << "F ";
                    else if (bestPath[i][j] == 1)
                        cout << "* ";
                    else
                        cout << ". ";
                }
                cout << endl;
            }
        }
    }
    else if (choice == 7)
    {
        collectItems(0, 0, 'A', squirrelPath, 0, 7);
        collectItems(2, 4, 'G', foxPath, 0, 6);

        cout << "Q7 Squirrel Path:\n";

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
                cout << squirrelPath[i][j] << " ";
            cout << endl;
        }

        cout << "Q7 Fox Path:\n";

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
                cout << foxPath[i][j] << " ";
            cout << endl;
        }
    }

    return 0;
}