/*  
 *		SCOPE.H
 *
 *		Apr 10, 2013
 *
 */


typedef enum _state { AVG_COMPUTING, AVG_COMPUTED, FALLING_EDGE, RISING_EDGE, TRIGGERED } ScopeState_t;
typedef enum _channel { CH1, CH2, BOTH_CH } ScopeChannel_t;

void Begin_Scope(ScopeChannel_t);