#include <cmath>
#include <iostream>
#include <memory>
#include "Common.h"
#include "AnimaStateMachine.h"
int main(){
    log("Animation State Machine Test");

    std::shared_ptr<State> idle = std::make_shared<State>("idle",0.0);
    std::shared_ptr<State> walk = std::make_shared<State>("walk",2.0);
    std::shared_ptr<State> run = std::make_shared<State>("run",5.0);
    std::shared_ptr<State> jump = std::make_shared<State>("jump",0.0);

    std::shared_ptr<Transition> idle_walk = std::make_shared<Transition>(idle,walk,500);
    std::shared_ptr<Transition> walk_idle = std::make_shared<Transition>(walk,idle,500);
    std::shared_ptr<Transition> idle_jump = std::make_shared<Transition>(idle,jump,500);
    std::shared_ptr<Transition> jump_idle = std::make_shared<Transition>(jump,idle,500);

    std::shared_ptr<AnimaStateMachine> state_machine = std::make_shared<AnimaStateMachine>(idle);
    state_machine->SetStates({idle,walk,run,jump});
    state_machine->SetTranstions({idle_walk,walk_idle,idle_jump,jump_idle});
    
    state_machine->Run();
}