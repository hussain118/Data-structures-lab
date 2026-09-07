#include"iostream"
using namespace std;
int main(){
    int arr[8]={65,92,48,92, 75, 81, 65, 88};
    for (int gap = 8/2; gap > 0; gap/=2)
    {
      for (int i = gap; i < 8; i++)
      {
        int temp=arr[i];
        int j=i;
        while (j>=gap && arr[j-gap]>temp)
        {
              arr[j] = arr[j - gap];
                j -= gap;

        }
        arr[j]=temp;
      }
      
      
      
    }
    int max1;
    int max2;
        for (int i = 0; i <8; i++)
    {
      if (arr[i]>max1)
      {
        max1=arr[i];
      }

      
    }
    for (int i = 0; i <8; i++)
    {
     if (arr[i] < max1 && arr[i] > max2) { 
        max2 = arr[i]; }
    }
    int diff=max1-max2;

  int low = 0;
    int high = 8 - 1;

    while (low <= high) {
         int mid = low + (high - low) / 2;

        // Check if target is present at mid
        if (arr[mid] == diff) {
            return mid;
        }
        
        // If target is greater, ignore the left half
        if (arr[mid] < diff) {
            low = mid + 1;
        } 
        // If target is smaller, ignore the right half
        else {
            high = mid - 1;
        }
    }
}