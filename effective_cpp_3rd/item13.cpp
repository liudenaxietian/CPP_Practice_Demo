/*
 * @Author: zouf zouf@192.168.49.250
 * @Date: 2024-05-10 08:37:03
 * @LastEditors: zouf zouf@192.168.49.250
 * @LastEditTime: 2024-05-10 08:54:18
 * @FilePath: \CPP_Practice_Demo\effective_cpp_3rd\item13.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <memory>

class Investment
{
public:
    Investment()
    {
        std::cout << "Investment Constructor" << std::endl;
    }

    ~Investment()
    {
        std::cout << "Investment Destructor" << std::endl;
    }
};

Investment *CreateInvetment()
{
    return new Investment();
};

void f1()
{
    Investment *pInv = CreateInvetment();

    // return; //模拟内存泄漏

    delete pInv;
};

void f2()
{

    std::shared_ptr<Investment> pInv1(CreateInvetment());
    std::cout << pInv1.use_count() << std::endl;

    std::shared_ptr<Investment> pInv2(pInv1);
    std::cout << pInv1.use_count() << std::endl;
    std::cout << pInv2.use_count() << std::endl;

    std::shared_ptr<Investment> pInv3 = pInv1;
    std::cout << pInv1.use_count() << std::endl;
    
    std::shared_ptr<Investment> pInv4 = std::move(pInv1);
    std::cout << pInv4.use_count() << std::endl;

};

int main()
{

    f1(); //手动删除资源
 
    f2(); //使用资源管理对象RCSP自动管理资源

    return 0;
}