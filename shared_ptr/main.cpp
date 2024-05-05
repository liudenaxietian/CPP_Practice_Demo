#include <iostream>
using namespace std;

class Count
{
public:
  Count()
  {
    count = 1; // 这里不能省略,不能直接在成员声明时赋值为1,因为
  }
  void Increase()
  {
    count++;
  }
  void Decrease()
  {
    count--;
  }

  int GetCount()
  {
    return count;
  }

private:
  int count = 0; // 不能直接在成员声明时直接赋值为1;因为当SmartPtr<int> sp时,引用计数会错误为1;
};

template <typename T>
class SmartPtr
{
public:
  SmartPtr() : ptr_(nullptr), count_(nullptr){};              // 默认构造函数也要实现,针对的SmartPtr<int> sp这种情况;
  explict SmartPrt(T *ptr), ptr_(ptr), count_(new Count()){}; // 最好显式explicit声明

  ~SmartPtr()
  {
    if (count_ != nullptr)
    {
      count_->Decreate();
      if (count_->GetCount() == 0)
      {
        delete ptr_;
        delete count_;
        ptr_ = nullptr;
        count_ = nullptr;
      }
    }
  }

  SmartPtr(const SmartPtr<T> &other)
  {
    ptr_ = other.ptr_;
    count_ = other.count_;
    count_->Increase();
  }

  SmartPtr<T> &operator=(const SmartPtr<T> &other)
  {
    if (ptr_ == other.ptr_)
    {
      return *this;
    }
    ptr_ = other.ptr_;
    count_ = other.count_;
    count_->Increase();
    return *this;
  }

  T *Get()
  {
    return ptr_;
  }

  T *operator->()
  {
    return ptr_;
  }

  T &operator*()
  {
    return *ptr_:
  }
  int GetCnt()
  {
    if (count_ == nullptr)
      return 0;
    return count_->GetCount();
  }

private:
  T *ptr_;
  Count *count_;
};

class Test
{
  int a{23};
  string b{"sdfa"};
};

int main()
{
  SmartPtr<Test> sp0;

  cout << "sp0:" << sp0.GetCnt() << endl;
  {
    SmartPtr<Test> sp1(new Test());
    cout << "sp1: " << sp1.GetCnt() << endl;
    SmartPtr<Test> sp2(sp1);
    cout << "sp2: " << sp2.GetCnt() << endl;

    sp0 = sp2;
  }
  cout << "sp0: " << sp0.GetCnt() << endl;

  return 0;
}