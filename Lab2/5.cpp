#include"iostream"

int main() {
    int numRows;

    std::cout << "Enter the number of rows: ";
    if (!(std::cin >> numRows) || numRows <= 0) {
        std::cout << "Invalid number of rows.\n";
        return 1;
    }

    int** jaggedArray = new int*[numRows];
    int* rowSizes = new int[numRows];

    // Input row sizes and populate elements
    for (int i = 0; i < numRows; ++i) {
        std::cout << "\nEnter number of elements for Row " << (i + 1) << ": ";
        std::cin >> rowSizes[i];

        if (rowSizes[i] <= 0) {
            std::cout << "Row size must be greater than 0. Setting size to 0.\n";
            rowSizes[i] = 0;
            jaggedArray[i] = nullptr;
            continue;
        }

        jaggedArray[i] = new int[rowSizes[i]];

        std::cout << "Enter " << rowSizes[i] << " elements for Row " << (i + 1) << ": ";
        for (int j = 0; j < rowSizes[i]; ++j) {
            std::cin >> jaggedArray[i][j];
        }
    }

    // Determine the row with the maximum number of elements
    int maxRowIndex = 0;
    int maxSize = rowSizes[0];

    for (int i = 1; i < numRows; ++i) {
        if (rowSizes[i] > maxSize) {
            maxSize = rowSizes[i];
            maxRowIndex = i;
        }
    }

    // Display results
    std::cout << "\n--- RESULT ---\n";
    if (maxSize == 0) {
        std::cout << "No elements were entered in any row.\n";
    } else {
        std::cout << "1. Row with maximum elements: Row " << (maxRowIndex + 1) << "\n";
        std::cout << "2. Size of that row: " << maxSize << " elements\n";
        std::cout << "3. Elements of Row " << (maxRowIndex + 1) << ": ";
        for (int j = 0; j < maxSize; ++j) {
            std::cout << jaggedArray[maxRowIndex][j] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 0; i < numRows; ++i) {
        delete[] jaggedArray[i];
    }
    delete[] jaggedArray;
    delete[] rowSizes;

    return 0;
}
