#include"iostream"
using namespace std;
int main(){
    int i=0;
    int k=0;
    int arr[3];
while (k!=5)
{
    cout<<"enter date first day then month then year enter in format X0 ";
    for (int i = 0; i < 3; i++)
    {
        cin>>arr[i];
    }
    for (int i = 0; i < 3; i++)
    {
        int min=i;
        for (int j = 0; j < i+1; i++)
        {
            if (arr[j]<arr[min])
            {
                min=j;
            }
            int temp=arr[min];
            arr[min]=arr[i];
            arr[i]=temp;
        }
    }
    printf("%d/%d/%d",arr[i],arr[i+1],arr[i+2]);
    k++;
}
}