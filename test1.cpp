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
    return 0;
}