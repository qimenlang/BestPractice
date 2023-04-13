#pragma once
#include "State.h"
#include <memory>
class Transition :public Runable {
    public:
        Transition(std::shared_ptr<State> from,std::shared_ptr<State> to,float duration):m_from(from),m_to(to),m_duration(duration){}
        virtual void print(){
            std::cout<<"transition :"<< m_from.lock()->state_name()<<" -> "<<m_to.lock()->state_name()<<std::endl;
        };

    private:
        std::weak_ptr<State> m_from;
        std::weak_ptr<State> m_to;
        float m_duration;
};