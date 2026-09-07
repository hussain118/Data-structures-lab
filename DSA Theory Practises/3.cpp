#include"iostream"
using namespace std;
struct designation
{
    string designa;
    int priority;

};
int getPriority(string desig) {
    if (desig == "CEO") return 1;
    if (desig == "CTO") return 2;
    if (desig == "CFO") return 3;
    if (desig == "VP")  return 4;
    if (desig == "MGR") return 5;
    if (desig == "EMP") return 6;
    return 7;  
}
void printDesks(designation arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "[" << arr[i].designa << "] ";
    }
    cout << "\n";
}
int main(){
    int size=8;
   string Arr[size]={"EMP", "CFO", "MGR", "EMP", "VP", "CTO", "MGR", "CEO"
    };
    designation d[size];
    for (int i = 0; i < size; i++)
    {
        d[i].designa=Arr[i];
        d[i].priority=getPriority(Arr[i]);
    }
    for (int i = 1; i < size; i++)
    {
        designation key=d[i];
        int j=i-1;
        while (j>=0 && key.priority<d[j].priority)
        {
            d[j]=key;
            j=j-1;
        }
        d[j+1]=key;
    }
    
}
