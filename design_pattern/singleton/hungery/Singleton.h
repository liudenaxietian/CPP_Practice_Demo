#ifndef SINGLETON_H_
#define SINGLETON_H_

#include<iostream>


class Singleton{
    public:
    static Singleton* GetInstance(){
        return instance_;
    }
    private:
    Singleton(){};
    static Singleton* instance_;
};


#endif