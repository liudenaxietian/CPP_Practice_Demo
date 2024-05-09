/*
 * @Author: zouf zouf@192.168.49.250
 * @Date: 2024-05-09 08:46:07
 * @LastEditors: zouf zouf@192.168.49.250
 * @LastEditTime: 2024-05-09 09:02:01
 * @FilePath: \CPP_Practice_Demo\lambda\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <memory>

// 正常模式
void test01()
{
    std::cout << "normal test01:" << std::endl;
    auto add = [](int a, int b) -> int
    {
        return a + b;
    };

    std::cout << add(1, 2) << std::endl;
}

// 传值捕获
void test02()
{
    std::cout << "value capture test02:" << std::endl;
    int c = 3;
    int d = 4;
    auto add = [c, d](int a, int b) -> int
    {
        std::cout << "c: " << c << " d: " << d << std::endl;
        return c + a;
    };

    c = 20;
    std::cout << "c: " << c << " d: " << d << std::endl;
    std::cout << add(1, 2) << std::endl;
}

// 传引用捕获
void test03()
{
    std::cout << "reference capture test03:" << std::endl;
    int c = 3;
    int d = 4;
    auto add = [&c, &d](int a, int b) -> int
    {
        d = 15;
        std::cout << "c: " << c << " d: " << d << std::endl;
        return c + a;
    };

    c = 20;
    std::cout << "c: " << c << " d: " << d << std::endl;
    std::cout << add(1, 2) << std::endl;
}

//隐式捕获(传值)
void test04(){
    std::cout << "reference capture test03:" << std::endl;
}

int main(int argc, char *argv[])
{
    test01();
    test02();
    test03();

    return 0;
}