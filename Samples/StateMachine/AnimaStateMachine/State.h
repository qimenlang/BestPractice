#pragma once
#include "Common.h"
#include <iostream>
class State{
    public:
        State(const std::string & name_in,float power = 0.0):m_state_name(name_in),m_power(power){}
        std::string state_name(){return m_state_name;}
        float power(){return m_power;}
        float set_power(float power){m_power = power;}

        void print(){
            std::cout<<"state:"<<m_state_name<<" ,power:"<<m_power<<std::endl;
        }
    private:
        std::string m_state_name;
        float m_power;//量化每个状态，以便于模拟状态之间的插值混合；
};