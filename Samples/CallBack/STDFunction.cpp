#include <functional>
#include <iostream>
#include <vector>

void foo(int a, int b)
{
    std::cout << "foo(" << a << ", " << b << ")" << std::endl;
}

class ADD
{
public:
    int foo(int x, int y)
    {
        return x + y;
    }
};

int addMulity(int a, int b, int c)
{
    return a + b * c;
}

class Base
{
public:
    virtual int foo(int x, int y) {
        return x+y;
    }
};

class Derived : public Base
{
public:
    int foo(int x, int y) override
    {
        return x * y;
    }
};


void do_twice(std::function<void()> f)
{
    f();
    f();
}

std::function<int(int)> make_incrementor(int delta)
{
    return [=](int x) { return x + delta; };
}


class EventListener {
public:
    void addListener(const std::function<void()>& listener) {
        listeners.push_back(listener);
    }

    void trigger() {
        for (auto& listener : listeners) {
            listener();
        }
    }

private:
    std::vector<std::function<void()>> listeners;
};

int main()
{
    //包装普通函数
    std::function<void(int,int)> f = foo;
    f(1, 2);

    //包装lamada表达式
    std::function<void(int,int)> f2 = [](int a,int b){    
        std::cout << "foo2(" << a << ", " << b << ")" << std::endl;
    };
    f2(1,2);

    // 包装成员函数
    ADD a;
    std::function<int(ADD*,int,int)> f3 = &ADD::foo;
    std::cout<< f3(&a,1,2)<<std::endl;

    //绑定函数参数
    auto AM1 = std::bind(addMulity,1,2,3);
    std::cout<< "AM1:"<< AM1()<<std::endl;
    auto AM2 = std::bind(addMulity, std::placeholders::_2, std::placeholders::_1, 3);
    std::cout << "AM2:"<<AM2(2,1) << std::endl;

    //存储多态对象
    Base b;
    Derived d;
    std::function<int(Base*,int,int)> f4 = &Base::foo;
    std::cout<<"f4 :"<< f4(&d,1,2)<<","<<f4(&b,1,2)<<std::endl;

    //std::function 可以作为函数参数和返回值，以实现回调函数等功能

    do_twice([]() { std::cout << "Hello, world!" << std::endl; });
    auto inc = make_incrementor(3);
    std::cout << inc(5) << std::endl;

    //实现回调 example 1
    EventListener event;
    auto listener1 = []() {
        std::cout << "Listener 1 called" << std::endl;
    };

    auto listener2 = []() {
        std::cout << "Listener 2 called" << std::endl;
    };

    event.addListener(listener1);
    event.addListener(listener2);

    event.trigger(); // 输出：Listener 1 called、Listener 2 called

    return 0;
}
