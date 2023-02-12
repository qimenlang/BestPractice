#include <cmath>
#include <iostream>
#include <memory>
#include "Common.h"
#include "AnimaStateMachine.h"
int main(){
    log("Animation State Machine Test");
    std::shared_ptr<State> idle = std::make_shared<State>("idle",0.0);
    std::shared_ptr<State> walk = std::make_shared<State>("walk",1.0);
    std::shared_ptr<State> slow_run = std::make_shared<State>("slow_run",3.0);
    std::shared_ptr<State> fast_run = std::make_shared<State>("fast_run",7.0);
    std::shared_ptr<State> jump = std::make_shared<State>("jump",0.0);

    std::shared_ptr<AnimaStateMachine> state_machine = std::make_shared<AnimaStateMachine>(idle);
    state_machine->Run();
}