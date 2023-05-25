#include "ICU.h"
static volatile void (*g_callBackPtr)(void) = NULL;
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

void ICU_init(const ICU_CONFIG * CONFIG)
{
	DDRD &=~(1<<PD6);
	TCCR1A |=(1<<FOC1A) | (1<<FOC1B);
	TCCR1B =(TCCR1B & 0xF8) | (CONFIG ->clock);
	TCCR1B = (TCCR1B & 0xBF) | ((CONFIG->edge) << 6);
	TCNT1 = 0 ; 
	ICR1 = 0 ;
	TIMSK |=(1<<TICIE1);
}
void Edge_select(const ICU_EDGE_TYPE select_edge)
{
	TCCR1B = (TCCR1B & 0xBF) | ((select_edge) << 6);
}
uint16_t Get_ICU_VALUE()
{
	return ICR1;
}

void ICU_CLEAR_TIMER()
{
	TCNT1 = 0 ;
}
void ICU_DeInit()
{
	TCCR1B = 0x00;
    TCNT1 = 0 ; 
	ICR1 = 0;
	TIMSK &=~(1<<TICIE1);
}
