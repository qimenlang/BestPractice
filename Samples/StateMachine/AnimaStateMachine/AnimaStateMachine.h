#pragma once
#include "State.h"
#include "Transition.h"
#include <memory>
#include <chrono>
#include <thread>

class AnimaStateMachine{
public:
    //virtual void operator()(EIndication input) override
    AnimaStateMachine(std::shared_ptr<State> begin_state):m_current_state(begin_state){}
    void Run(){
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            m_current_state.lock()->print();
        }
    }
private:
    std::weak_ptr<State> m_current_state;
    // conditions
};