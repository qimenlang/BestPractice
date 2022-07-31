#include "StateDesignPattern.h"

Machine stateMachine;

int main()
{
    stateMachine.setCurrent(new Idle());
    std::cout << "State Design Pattern" << std::endl;
    return 0;
}