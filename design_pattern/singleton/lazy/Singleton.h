/*
 * @Author: zouf zouf@192.168.49.250
 * @Date: 2024-05-09 19:50:41
 * @LastEditors: zouf zouf@192.168.49.250
 * @LastEditTime: 2024-05-09 20:25:01
 * @FilePath: \CPP_Practice_Demo\design_pattern\singleton\lazy\Singleton.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <iostream>
#include <string>
#include <mutex>

class Singleton
{
public:
    static Singleton *GetInstance()
    {
        if (instance_ == nullptr)
        {
            //加锁保证多个线程并发调用getInstance时只会创建一个实例
            m_mutex_.lock();
            if (instance_ == nullptr)
            {
                instance_ = new Singleton();
            }
            m_mutex_.unlock();
        }
        return instance_;
    }

private:
    Singleton(){};
    static Singleton *instance_;
    static std::mutex m_mutex_;
};

#endif