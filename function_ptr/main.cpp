#include<iostream>
#include<vector>

int func1(int a,int b){
    return a+b;
};

int func2(int a,int b){
    return a -b;
}

int func3(int a,int b){
    return a * b;
}

int func4(int a,int b){
    return a /b;
}


void computed(int a,int b,int (*func)(int a,int b)){
    std::cout<<"computed: "<<func(a,b)<<std::endl;
}


int main(int argc,char* argv[]){

    int a = 20;
    int b = 14;

    // std::vector<decltype<func1>*> vf = {func1,func2,func3,func4};

    std::vector<decltype(func1)*> vf =  {func1,func2,func3,func4};

    for(auto fun:vf){
        computed(a,b,fun);
    }
    return 0;
}