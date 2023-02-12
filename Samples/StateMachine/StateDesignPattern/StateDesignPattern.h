#pragma once
#include <iostream>

using namespace std;

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


void NotifyInvalidInput(EIndication input)
{
    std::cerr << "invalid input" << input << std::endl;
}

class State;
class Idle;
class Ringing;
class Dial;
class Connected;
class Busy;
class Alerting;
class Machine
{
    class State* curState;

public:
    Machine() {};
    void setCurrent(State* s)
    {
        curState = s;
    }
};

class State
{
protected:
    Machine* sm;

public:
    virtual void operator()(EIndication input) = 0;
};


class Idle : public State
{
public:
    virtual void operator()(EIndication input) override
    {
        if (input == OFF_HOOK_IND)           /* On OFF_HOOK               */
            sm->setCurrent(new Dial());      /*  - shift to Dial state    */
        else if (input == INCOMING_CALL_IND) /* On INCOMING_CALL    */
            sm->setCurrent(new Ringing());   /*  - shift to Ringing state */
                                             /* else stay the same        */
        delete this;
    }
};

class Ringing : public State
{
    virtual void operator()(EIndication input) override
    {
        if (input == PICKUP_IND)             /* On PICKUP                     */
            sm->setCurrent(new Connected()); /*   - shift to Connect state    */
        else                                 /* else invalid, go back to idle */
            sm->setCurrent(new Idle());      /*   - shift to Idle state       */
        delete this;
    }
};

class Dial : public State
{
    virtual void operator()(EIndication input) override
    {
        switch (input)
        {
        case DIGITS_IND:                    /* On DIGITS_IND               */
            sm->setCurrent(new Alerting()); /*   - shift to Alerting state */
            break;

        case ON_HOOK_IND: /* Hang up---go idle.          */
            sm->setCurrent(new Idle());
            break;

        default:
            NotifyInvalidInput(input);  /* Send output to LBU          */
            sm->setCurrent(new Idle()); /* Invalid, go back to idle    */
        }
        delete this;
    }
};

class Connected : public State
{
    virtual void operator()(EIndication input) override
    {
        sm->setCurrent(new Idle()); /* shift to Idle state on anything */
        delete this;
    }
};


class Busy : public State
{
    virtual void operator()(EIndication input) override
    {
        sm->setCurrent(new Idle()); /* shift to Idle state on anything */
        delete this;
    }
};

class Alerting : public State
{
    virtual void operator()(EIndication input) override
    {
        if (input == CONNECTED_IND)          /* On CONNECT                    */
            sm->setCurrent(new Connected()); /*   - shift to Connect state    */
        else                                 /* else invalid, go back to idle */
            sm->setCurrent(new Idle());      /*   - shift to Idle state       */
        delete this;
    }
};