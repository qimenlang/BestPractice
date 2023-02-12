#pragma once
#include "State.h"
#include <memory>
class Transition{
    public:
        Transition(std::shared_ptr<State> from,std::shared_ptr<State> to):m_from(from),m_to(to){}

    private:
        std::weak_ptr<State> m_from;
        std::weak_ptr<State> m_to;
        float m_duration;
};