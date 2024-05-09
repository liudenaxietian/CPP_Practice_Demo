#include <iostream>

class TimeKeeper
{
public:
    TimeKeeper(){};
    virtual ~TimeKeeper()
    {
        std::cout << "TimeKeeper desconstructor" << std::endl;
    };
};

class AtomicClock : public TimeKeeper
{
    public:
        AtomicClock(){};
        ~AtomicClock(){
            std::cout<<"AtomicClock desconstructor"<<std::endl;
        }
};
class WaterClock : public TimeKeeper
{
};
class WristClock : public TimeKeeper
{
};

TimeKeeper *getTimeKeeper()
{
    return new AtomicClock();
}

int main()
{
    TimeKeeper *tk = getTimeKeeper();

    delete tk;

    return 0;
}


