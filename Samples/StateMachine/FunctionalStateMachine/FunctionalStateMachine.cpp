#include <iostream>
/* These are the events that can affect our */
/* StateMachine                             */
typedef enum
{
  ON_HOOK_IND,
  OFF_HOOK_IND,
  DIGITS_IND,
  CALL_PROCEEDING_IND,
  CONNECTED_IND,
  INCOMING_CALL_IND,
  TIMEOUT_IND,
  INVALID_DIGITS_IND,
  BUSY_IND,
  PICKUP_IND
} EIndication;

/* StateMachine is a structure which holds the                 */
/* current state pointer.  This is just a forward              */
/* declaration for the next typedef                            */
typedef struct StateMachine TStateMachine;

/* StateProc is the function pointer type that                 */
/* is used to represent each state of our machine.             */
/* The StateMachine *sm argument holds the current             */
/* information about the machine most importantly the          */
/* current state.  A StateProc function may receive            */
/* input that forces a change in the current state.  This      */
/* is done by setting the curState member of the StateMachine. */
typedef void (*StateProc)(TStateMachine *sm, EIndication input);

/* Now that StateProc is defined, we can define the            */
/* actual layout of StateMachine.  Here we only have the       */
/* current state of the StateMachine.                          */
struct StateMachine
{
  StateProc curState;
};

void NotifyInvalidInput(EIndication input){
    std::cerr<<"invalid input"<<input<<std::endl;
}

/* Here are the prototypes for the different                   */
/* states in our system.  We must prototype                    */
/* these functions to be able to set the                       */
/* curState of the StateMachine.  Our states                   */
/* react to an enumerated type as input.  This                 */
/* can be changed to whatever data type (or                    */
/* types) necessary to report the input stimulus.              */
void Idle(TStateMachine      *sm,  EIndication input);
void Dial(TStateMachine      *sm,  EIndication input);
void Busy(TStateMachine      *sm,  EIndication input);
void Alerting(TStateMachine  *sm,  EIndication input);
void Connected(TStateMachine *sm,  EIndication input);
void Ringing(TStateMachine   *sm,  EIndication input);


void Idle(TStateMachine *sm, EIndication input)
{
  if (input == OFF_HOOK_IND)     /* On OFF_HOOK               */
    sm->curState = Dial;                /*  - shift to Dial state    */
  else if (input == INCOMING_CALL_IND)  /* On INCOMING_CALL    */
    sm->curState = Ringing;             /*  - shift to Ringing state */
                                        /* else stay the same        */
}

void Dial(TStateMachine *sm, EIndication input)
{
  switch (input)
  {
    case DIGITS_IND:             /* On DIGITS_IND               */
      sm->curState = Alerting;          /*   - shift to Alerting state */
      break;
      
    case ON_HOOK_IND:            /* Hang up---go idle.          */
      sm->curState = Idle;
      break;
      
    default:
      NotifyInvalidInput(input);        /* Send output to LBU          */
      sm->curState = Idle;              /* Invalid, go back to idle    */
  }
}

void Busy(TStateMachine *sm, EIndication input)
{
  sm->curState = Idle;    /* shift to Idle state on anything */
}

void Alerting(TStateMachine *sm, EIndication input)
{
  if (input == CONNECTED_IND)      /* On CONNECT                    */
    sm->curState = Connected;             /*   - shift to Connect state    */
  else                           /* else invalid, go back to idle */
    sm->curState = Idle;                /*   - shift to Idle state       */
}

void Connected(TStateMachine *sm, EIndication input)
{
  sm->curState = Idle;  /*   - shift to Idle state on anything */
}

void Ringing(TStateMachine *sm, EIndication input)
{
  if (input == PICKUP_IND)       /* On PICKUP                     */
    sm->curState = Connected;             /*   - shift to Connect state    */
  else                                  /* else invalid, go back to idle */
    sm->curState = Idle;                /*   - shift to Idle state       */
}

TStateMachine EmergencyDevice = { Idle };

int main(){
    std::cout<<"Functional StateMachine"<<std::endl;
    while(true){
        srand((int) time(0));        
        int event = rand()%10;
        std::cout<<"event:"<<event<<std::endl;
        TStateMachine* machine =&EmergencyDevice;
        (machine->curState)(machine, (EIndication)event);
    }
}