#include <iostream>

// look up table state machine drawbacks:
// They are large (space-wise). For every combination of input and state there is a record of the next state.
// They are difficult to maintain by hand.
// No actions can be performed during tansitions without another action table.

/* States. */
#define  IDLE                    0
#define  DIAL                    1
#define  ALERTING                2
#define  CONNECTED               3
#define  BUSY                    4
#define  RINGING         5

/* Possible inputs    */
#define  ON_HOOK_IND             0
#define  OFF_HOOK_IND            1
#define  DIGITS_IND              2
#define  CONNECTED_IND           3
#define  INCOMING_CALL_IND       4
#define  TIMEOUT_IND             5
#define  PICKUP_IND              6

int transtab[7][6] = /* transtab[Input][CurrentState] => NextState      */
{

/* IDLE     DIAL      ALERTING   CONNECTED  BUSY  RINGING    */

{ IDLE,    IDLE,     BUSY,      IDLE,      IDLE, IDLE      }, /* ON_HOOK_IND       */
{ DIAL,    DIAL,     BUSY,      IDLE,      IDLE, IDLE      }, /* OFF_HOOK_IND      */
{ IDLE,    ALERTING, IDLE,      IDLE,      IDLE, IDLE      }, /* DIGITS_IND        */
{ IDLE,    DIAL,     ALERTING,  IDLE,      IDLE, IDLE      }, /* CONNECTED_IND     */
{ RINGING, DIAL,     IDLE,      CONNECTED, BUSY, RINGING   }, /* INCOMING_CALL_IND */
{ IDLE,    DIAL,     BUSY,      IDLE,      IDLE, IDLE      }, /* TIMEOUT_IND       */
{ IDLE,    DIAL,     BUSY,      IDLE,      IDLE, CONNECTED }, /* PICKUP_IND        */
};

static int cur_state = IDLE;

void TransState(int event){
    cur_state = transtab[event][cur_state];
    std::cout<<"state:"<<cur_state<<std::endl;
}

int main(){
    std::cout<<"Look Up Table State Machine"<<std::endl;
    TransState(INCOMING_CALL_IND);
    TransState(PICKUP_IND);
    TransState(TIMEOUT_IND);

    return 0;   
}