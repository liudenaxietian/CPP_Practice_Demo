#include <iostream>
#include "Singleton.h"

int main(int argc, char *argv[])
{
    Singleton *s1 = Singleton::GetInstance();
    Singleton *s2 = Singleton::GetInstance();

    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;

    return 0;
}