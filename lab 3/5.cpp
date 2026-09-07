#include"iostream"
using namespace std;
 
int main()
{
    int arr[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    int id;
    cout << "Enter employee ID: ";
    cin >> id;

    int low = 0;
    int high = 8;

    while (low <= high && id >= arr[low] && id <= arr[high])
    {
        // Interpolation formula
        int pos = low + ((id - arr[low]) * (high - low))
                        / (arr[high] - arr[low]);

        if (arr[pos] == id)
        {
            cout << "ID found at position: " << pos << endl;
            return 0;
        }

        if (arr[pos] < id)
        {
            low = pos + 1;
        }
        else
        {
            high = pos - 1;
        }
    }

    cout << "ID not found" << endl;

    return 0;
}