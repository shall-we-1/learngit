#include<iostream>
#include<vector>
#include"math.h"
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
    cout<<"learning cmake"<<endl;
    cout<<add(1,2);
    return 0;
}