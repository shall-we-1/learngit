#include<iostream>
#include<string>
#include<fstream>
#include <unistd.h>
using namespace std;
#define M 100
void showmenu(){
    cout<<"**************************************"<<endl;
    cout<<"*********welcome to my system*********"<<endl;
    cout<<"********************0.quit************"<<endl;
    cout<<"********************1.add*************"<<endl;
    cout<<"********************2.show************"<<endl;
    cout<<"********************3.delete**********"<<endl;
    cout<<"*******************4.change***********"<<endl;
    cout<<"********************5.find************"<<endl;
    cout<<"********************6.sort************"<<endl;
    cout<<"******************7.clear all*********"<<endl;
}

class abper{
    public:
    int getnum1(){
        return this->num1;
    }
    string getname(){
        return this->name;
    }
    void showperson(){//完成了单个员工的展示
        cout<<"职工编号："<<this->num1<<"  姓名："<<this->name<<"  职工岗位："<<this->pos<<endl;
        this->perway();
    }
    virtual void perway(){ //不能构建纯虚函数，纯虚函数会让这个对象无法实例化，我在使用数组创建对象的时候会导致无法创建
        //所以要使用虚函数而不是直接等于0形成纯虚，再次编译尝试一下
        int z=0;
    };//定义一个虚函数，这个虚函数会被子类重写，代表每一个员工的职责，可以在函数使用过程中发生多态，

    string getfunc(){
        return "职工编号："+ to_string(this->num1) + "  职工姓名：" + this->name + "  职位：" + this->pos;
    }
    abper(int a,string name,string pos){
        this->num1=a;
        this->name=name;
        this->pos=pos;

    };//使用括号给变量赋予初值，不需要虚构析函数，因为我给出的目标中并没有在类中单独使用
    //堆上内存

    //重载一个赋值拷贝函数，这样才能够完整的将值给整过去
    // abper& operator=(const abper& ab){
    //     this->num1=ab.num1;
    //     this->name=ab.name;
    //     this->pos=ab.pos;
    //     return *this;
    // }//没有重载的必要吗？
    abper& operator()(int a,string name,string pos){
        this->num1= a;
        this->name= name;
        this->pos= pos;
        return *this;
    }
    ~abper(){
        // delete num1;
        // delete name;
        // delete pos;
        cout<<"调用析构函数了，应该会多次出现"<<endl;
    }
    private:
    int num1;
    string name;
    string pos;

};
class zg  : public abper{
    public:
    using abper::abper;
    void perway(){
        cout<<"我是普通职工，我的职责是完成经理交给我的任务"<<endl;

    }
    //     zg& operator()(int a,string name,string pos){
    //     this->num1= a;
    //     this->name= name;
    //     this->pos= pos;
    //     return *this;
    // }
};

class jl : public abper{
    
    public:
    using abper::abper;
    void perway(){
        cout<<"我是经理， 我的职责是完成老板交给的任务，并且下发任务给员工"<<endl;
    }
    //     jl& operator()(int a,string name,string pos){
    //     this->num1= a;
    //     this->name= name;
    //     this->pos= pos;
    //     return *this;
    // }

};
class lb : public abper{
    public:
    using abper::abper;
    void perway(){
        cout<<"我是老板，我的职责是管理公司所有的事务，要累死了"<<endl;
    }

//         lb& operator()(int a,string name,string pos){
//         this->num1= a;
//         this->name= name;
//         this->pos= pos;
//         return *this;
//     }
 };
abper *all[M];

int totalnum=0;


void   filefunc(){  //将文件写入的方法单独独立出来，可以直接让后续 的函数也可以进行调用
        ofstream of1;
    of1.open("./testall.txt",ios::out);
    if(!of1.is_open()){

        cerr<<"错误：文件无法打开"<<endl;
        return;
    }
    for(int i = 0;i<totalnum;++i){
        of1<<all[i]->getfunc()<<endl;

    }
    of1.close();
}
void filefunc1(){
    ifstream ifs;
    ifs.open("./testall.txt",ios::in);
    string buf;
    while(getline(ifs,buf)){

        cout<<buf<<endl;
    }
    ifs.close();
}//从文件中读取内容，输出到屏幕上，这个东西似乎没有返回值，直接调用而不是使用cout输出
//从文件中读取内容的各种方式
// char buf[1024];
// while (ifs>>buf)
// {
//     cout<<buf<<endl;
// }
// while (ifs.getline(buf,sizeof(buf)))
// {
//     cout<<buf<<endl;
// }



//在这个函数中，我想直接使用类指针数组赋予初值，进行单个姓名的初始化，但因为我在类中把数据类型设置成了私有，我
//只能通过成员函数去设置他们的初值，但我又不知道如何调用这个对象的构造函数，我的解决办法是将括号重载，让他变成一个仿函数调用，
//这样直接让我将数组解引用过后直接调用
//第二个问题是在解引用指针的时候将解引用放在括号外边了，导致没有解引用到内部对象无法使用函数调用
void func1(){
    cout<<"这次招了几个全国跑的电器工程师呀？"<<endl;
    int temp=0;
    cin>>temp;
    
    for(int i = totalnum;i<(totalnum+temp);++i){
        cout<<"请输入工程师的编号，int型"<<endl;
        int temp1;
        cin>>temp1;
        cout<<"请输入工程师的名字，随便输"<<endl;
        string temp2;
        cin>>temp2;
        cout<<"请输入工程师的职位，有职工老板和经理三者之分"<<endl;
        string temp3;
        cin>>temp3;
        if(temp3=="老板"){
            all[i]=new lb(temp1,temp2,temp3);

        }else if(temp3=="经理"){
            all[i]=new jl(temp1,temp2,temp3);
        }else if(temp3=="职工"){
            all[i]=new zg(temp1,temp2,temp3);
        }else{
            all[i]=new zg(temp1,temp2,temp3);
        }
    }



    // for(int i =totalnum;i<(totalnum+temp);++i){
    //     all[i] = new abper(1,"sd","asd");

    // }
    // for(int i =totalnum;i<(temp+totalnum);++i){
    //     cout<<"请输入工程师的编号，int型"<<endl;
    //     int temp1;
    //     cin>>temp1;
    //     cout<<"请输入工程师的名字，随便输"<<endl;
    //     string temp2;
    //     cin>>temp2;
    //     cout<<"请输入工程师的职位，有职工老板和经理三者之分"<<endl;
    //     string temp3;
    //     cin>>temp3;
    //     (*all[i])(temp1,temp2,temp3); //似乎数组并不是能够直接使用这个括号符号进行函数调用，因为数组并不是一个指针？那我创建一个针对于这个类的指针数组即可？？
    // }
    totalnum+=temp; //需要一个全局变量去记录当前的数组到达了什么位置方便进行遍历或者处理
    //每次添加新内容的时候就将totalnum之后的n个位置初始化，再通过赋值写入文件
    //
    filefunc();
    // ofstream of1;
    // of1.open("./testall.txt",ios::out);
    // if(!of1.is_open()){

    //     cerr<<"错误：文件无法打开"<<endl;
    //     return;
    // }
    // for(int i = 0;i<totalnum;++i){
    //     of1<<all[i]->getfunc()<<endl;

    // }
    // of1.close();

}
//花了一个上午终于完成了第一个功能，来总结一下这段代码中遇到的问题，首先是定义类的时候将数据成员做了私有化，只能通过成员函数去调用，或许可以考虑
// 友元函数的办法直接调用
// 第二点，我想使用数组进行类成员的保存，这就涉及到最后的释放空间，因为我所产生的对象全部被赋予在堆区
// 同时因为数组产生的对象赋值方法较难，需要先单独将他们进行初始化，我之前一直没有对数组内的成员进行初始化，导致
// 每一次读取数组指针都是野指针，无法读取
// 所以初始化类指针数组的时候要先将他们每一个都初始化赋予一个初始值，再进行修改
// 在修改这一个阶段，因为成员进行了私有化，所以调用的时候不能直接使用变量名进行赋值，需要使用函数进行赋值
// 我将（）重载了过后能够直接使用(*all[i])(temp1,temp2,temp3); 完成数组内部对象的赋值，这叫做仿函数
// 调用起来和函数很相似，但并不是函数，那如果我想直接写一个函数进行调用，调用的方式应该是(*all[i])->func(a,b,v);
// 不过重载整体来说是非常方便的调用，
// 第三点，文件的读写，文件的写入只能写入""内部的所有内容，将函数放在其中并不会执行，不使用该符号能够执行成员函数，
// 如果成员函数有返回值的话能够直接将返回值写入文件中，所以写了一个get成员函数用于返回所有的调用，写入文件这一个操作后续或许还可以复用，可以考虑将这个函数独立
// 这样后续的调用也会非常方便


void func2(){//展示当前所有内容
    if(totalnum==0){
        cout<<"当前公司一个人都没得，别问了"<<endl;
    }else{
    filefunc1();
    }
}
//文件中已经存在职工的姓名，不清空该文件夹的话会导致显示没有员工但是会打印，可以考虑将
// totalnum变为计数制，采用和输出文件内容一样的函数，统计总共有几行，这样可以直接给totalnum赋值
// 变相的解决这个问题
//或者将else这个条件加上，但是这样就不会存储，不过没事，不存储是对的哈哈哈，用一次得了

void func3(){
    cout<<"请输入你想要删除的员工编号"<<endl;
    int k=0;
    cin>>k;
    for(int i = 0;i<totalnum;++i){
        if((all[i]->getnum1())==k){
            delete all[i]; 
            all[i]=nullptr; 
            if(i==(totalnum-1)){}
            else{
                for(int j = i+1;j<totalnum;++j){
                    
                    all[j-1]=all[j];

                    //千万保证数组不会越界， 可恶，还保证数组不越界呢
                    //上来就是越界，因为数组的最后下标是总数-1；
                }

            }
        totalnum=totalnum-1;
        filefunc();
        break;//删除完成后及时跳出循环，不然可能会导致出现错误，
        }

    }
    // totalnum=totalnum-1;
    // filefunc();这样会导致每一次都删除，这样是不正确的
    
}

void func4(){
    //根据编号改变员工的信息，即更新员工信息
    cout<<"输入你想要调动的员工编号"<<endl;
    int k;
    cin>>k;
    for(int i = 0;i<totalnum;++i){
        if(all[i]->getnum1()==k){
            cout<<"请输入工程师的编号，int型"<<endl;
            int temp1;
            cin>>temp1;
            cout<<"请输入工程师的名字，随便输"<<endl;
            string temp2;
            cin>>temp2;
            cout<<"请输入工程师的职位，有职工老板和经理三者之分"<<endl;
            string temp3;
            cin>>temp3;
            (*all[i])(temp1,temp2,temp3);
        }
    }
    filefunc();
}

void func5(){
    //根据名字或者编号查找姓名
    cout<<"你想根据编号还是姓名查找"<<endl;
    cout<<"1.根据编号查找"<<endl;
    cout<<"2.根据名字查找"<<endl;
    int k;
    cin>>k;
    switch (k)
    {
    case 1:{
        cout<<"请输入你想要查找的编号"<<endl;
        int n = 0;
        cin>>n;
        for(int i = 0;i<totalnum;++i){
        if(all[i]->getnum1()==n){
            all[i]->showperson();
                }
            }
        }
        break;
    case 2:cout<<"请输入你想要查找的名字"<<endl;
    {    
        string w="name";
        cin>>w;
        for(int i = 0;i<totalnum;++i){
        if(all[i]->getname()==w){
            all[i]->showperson();
            }
        }
    }
    break;
    default:
        cout<<"你输入了错误的数字，请重新尝试"<<endl;
        break;
    }
}
void func6(){
    //排序怎么排啊，完全忘了，没有使用容器存储，要是使用容器的话能够直接调用排序函数
    //只需要写一个排序和写入文件即可，因为写入文件已经封装，可以直接写排序就完成了
    //尝试冒泡排序，通过不断遍历对比两个编号的大小完成交换
    //排序代码错误，改完后全是垃圾值
    cout<<"请输入你想要的排序方式"<<endl;
    cout<<"1.按升序排列"<<endl;
    cout<<"2.按降序排列"<<endl;
    int k =0;
    cin>>k;
    int flag=1;
    if(k==1){

        for(int i = 0;i<totalnum;++i){
            flag=1;
        if(flag==1){
            flag=0;
            for(int j = 1 ;j<totalnum;++j){
                if(all[j-1]->getnum1()>all[j]->getnum1()){
                    abper *temp1 ;//我明白了，存在一个深拷贝和浅拷贝的问题
                    temp1=all[j-1];
                    all[j-1]=all[j];
                    all[j]=temp1;
                    
                    flag=1;
                
                }
            }
        }else{
            break;
        }

        }
    }else{
        for(int i = 0;i<totalnum;++i){
        if(flag==1){
            flag=0;
            for(int j = 1 ;j<totalnum;++j){
                if(all[j-1]->getnum1()<all[j]->getnum1()){
                    abper *temp1;
                    temp1=all[j-1];
                    all[j-1]=all[j];
                    all[j]=temp1;
                    //使用指针即可完成交换？？
                    flag=1;
                    
            
                }
            }
        }else{
            break;
        }

        }
}

cout<<"已经完成排序！！！"<<endl;
filefunc();
}
void func7(){
cout<<"1.确认清除所有信息"<<endl;
cout<<"2.取消清除所有信息"<<endl;
int k = 0;
cin>>k;
if(k==1){
    for(int i = 0;i<totalnum;++i){
        delete all[i];
        all[i]=nullptr;

    }
   totalnum=0;
ofstream clearFile("testall.txt",ios::trunc);
clearFile.close();//直接清空文件夹内部的所有内容

}else{
    return;
}



}

int main(){
    int select=0;

    while(1){
        showmenu();
        cout<<"input your choose again"<<endl;
        cin>>select;
        switch (select)
        {
        case 0:
            cout<<"you have quit this system aleady"<<endl;
            return 0;
        
        case 1:
            func1();
            cout<<"你想要添加的员工已经添加完毕，感谢使用本系统"<<endl;
            break;
        case 2:
        func2();
        break;
        case 3:func3();
        break;
        case 4:func4();break;
        case 5:func5();break;
        case 6:func6();break;
        case 7:func7();break;
        default:
            break;
        }
    }



    
    return 0; 
}

//运行func7的时候出现内存泄漏了，考虑是不是多次释放同一个内存了