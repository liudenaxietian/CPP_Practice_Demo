#ifndef SINGLETON_H_
#define SINGLETON_H_


class Singleton{
    public:
    Singleton(const Singleton& singleton) = delete;
    Singleton* operator=(const Singleton&) = delete;

    static Singleton& GetInstance(){
        static Singleton instance;
        return instance;
    }

    private:
        Singleton(){};
};


#endif