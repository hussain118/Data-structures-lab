#include <iostream>
using namespace std;

void Factors(){
    int num;
    cout<<"add a positive num";

    cin >>num;
    if (num<0 || num==-1)
    {
        cout<<" wrong num";
        return;
    }
    int sum=0;
    for (int i = 1; i <= num; i++)
    {
        if (num%i==0)
        {
            sum=+i;
        }
        else{
            cout<<""<<num;
        }
        
    }

    
    

}

// Q2

#include <iostream>
using namespace std;

void MinMax(int arr[], int size, int *min, int *max)
{
    *min = arr[0];
    *max = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < *min)
        {
            *min = arr[i];
        }

        if (arr[i] > *max)
        {
            *max = arr[i];
        }
    }
}

int main()
{
    int arr[] = {25, 10, 45, 5, 30, 60, 15};

    int min, max;

    MinMax(arr, 7, &min, &max);

    cout << "Smallest = " << min << endl;
    cout << "Largest = " << max << endl;

    return 0;
}

//q3
class Numbers
{
private:
 int size;
public:
 int *member;
 Numbers(int num,int mum){
    size=num;
    member=new int(mum);
 }
 ~Numbers(){
    delete member;
 }
 Numbers(Numbers &j){
    size= j.size;
    member= new int(*j.member);
 }
    
 
};

int main(){
    Numbers n(12,43);
    Numbers n1=n;
    Numbers n2(n);
}
// q4
class mystring 
{

public:
   char *str;
   mystring(char *arr){
    str= new char{strlen(arr)+1};
    strcpy(str,arr);
   }
   mystring(mystring &g){
    str=new char{strlen(g.str)+1};
    strcpy(g.str,str);

   }
   mystring &operator=(mystring &T){
      if (this != &T)
        {
            delete[] str;

            str = new char[strlen(T.str) + 1];
            strcpy(str, T.str);
        }

        return *this;
    }

   ~mystring{
    delete str;
   }
};


//q5
class Product
{
private:
    /* data */
public:
    string name;
    int *quantity;
    Product(string n,int na){
        name=n;
        quantity=new int(na);
    }
    Product(Product &m){
        name=m.name;
        quantity=new int(*m.quantity);
    }
    Product &operator=(Product &p){
        if (this!=&p)
        {
            name=p.name;
            quantity=new int (*p.quantity);
        }
               
    }
};


