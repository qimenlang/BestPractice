#pragma once
#include "State.h"
#include "Transition.h"
#include <memory>
#include <chrono>
#include <thread>
#include <vector>

class AnimaStateMachine{
public:
    //virtual void operator()(EIndication input) override
    AnimaStateMachine(std::shared_ptr<State> begin_state):m_current_state(begin_state){}
    void AddState(std::shared_ptr<State> state){
        m_states.emplace_back(state);
    }

    void SetStates(const std::vector<std::shared_ptr<State>>& states){
        m_states = states;
    }

    void SetTranstions(const std::vector<std::shared_ptr<Transition>>& transitions){
        m_transitions = transitions;
    }

    void Run(){
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            m_current_state->print();
        }
    }
private:
    std::shared_ptr<State> m_current_state;
    std::vector<std::shared_ptr<State>> m_states;
    std::vector<std::shared_ptr<Transition>> m_transitions;
    // conditions
};