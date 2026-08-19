class Numbers
{
private:
 int size;
public:
 int *member;
 Numbers(int num,int mum){
    num=size;
    member=new int(mum);
 }
 ~Numbers(){
    delete member;
 }
 Numbers(Numbers &j){
    size= j.size;
    member= new int(j.*member);
 }
    
 
};

int main(){
    Numbers n(12,43);
    Numbers n1=n;
    Numbers n2(*n);
}