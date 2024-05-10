#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <iostream>
#include<mutex>

class Singleton
{
public:
    static Singleton* GetInstance(){
        if(instance_ == nullptr){
            m_mutex_.lock();
            if(instance_ == nullptr){
                instance_ = new Singleton();
            }
            m_mutex_.unlock();
        }
    }
private:
    Singleton(){};
    static Singleton *instance_;
    static std::mutex m_mutex_;
};

#endif