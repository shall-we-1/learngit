#include<iostream>
#include<vector>
using namespace std;    
int main(){
    vector <char> a={'H','e','l','l','o'};
    for(size_t i =0;i<a.size();++i){
        cout<<a[i]<<' ';
    }
    for(auto ptr = a.begin();ptr!=a.end();++ptr){
        cout<<*ptr<<' ';

    }
    cout<<"Hello,c++"<<endl;
<<<<<<< HEAD
    cout<<"在master分支添加了一行代码，故意找茬引起冲突"<<endl;
=======
    cout<<"add a new way on usebranch";
>>>>>>> usebranch
    return 0;
}
