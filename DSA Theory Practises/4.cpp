#include"iostream"
using namespace std;
int main(){
    int gap=n;
    int shrink=1.4;
    bool swampped;
    int n;
    while (gap!=1 || swampped)
    {
        if (gap<1)
        {
            gap=1;
        }
        
        gap= gap/1.4;
        for (int i = 0; i+gap < n; i++)
        {
            if (arr[gap+i]<arr[i])
            {
                int temp=arr[i];
                arr[i]=arr[gap+1];
                arr[i+gap]=temp;
                swampped=true;
            }
            
        }
        swampped=false;
    }
    
}