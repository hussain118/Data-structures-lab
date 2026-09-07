#include"iostream"
using namespace std;
int main(){
    int count=0;
    cin>>count;
    int **arr;
    int averge[count];
    int sum;
    *arr=new int[count];
    for (int i = 0; i < count; i++)
    {
        cout<<"enter emplyees count for team "<<i+1;
        int num;
        cin>>num;
        averge[i]=num;
        *arr[i]=new int(num);
        for (int  j = 0; j < num; j++)
        {
            cout<<"scores for team "<<i+1;
            int dr;

            arr[i][j]=dr;
             sum=+arr[i][j];
        }
            
         int averagqe=sum/averge[i];
            cout<<"averge:  "<<averagqe;

    }
    
    
}