#include"iostream"
using namespace std;
int main(){
    int min;
    int arr[7]={45000, 62000, 38000, 75000, 51000, 68000, 42000};
    for (int i = 0; i < 7; i++)
    {
        min=i;
        for (int j = i+1; j < 7; j++)
        {
            if (arr[j]<arr[min])
            {
                min=j;
            }
            
        }
        swap(arr[i],arr[min]);
    }
    cout<<"lowest:"<<arr[0];
    cout<<"biggest:"<<arr[6];
    cout<<"middle value:"<<arr[3];
    


}