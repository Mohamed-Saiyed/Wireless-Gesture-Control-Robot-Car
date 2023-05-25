#ifndef ICU
#define ICU
typedef enum Clock
{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_CLOCK;
typedef enum edge
{
	FALLING,RISING
}ICU_EDGE_TYPE;
typedef struct
{
	ICU_CLOCK clock;
	ICU_EDGE_TYPE edge;
}ICU_CONFIG;
void ICU_CLEAR_TIMER();
void ICU_DeInit();
uint16_t Get_ICU_VALUE();
void Edge_select(const ICU_EDGE_TYPE select_edge);
void ICU_init(const ICU_CONFIG * CONFIG);
void Icu_setCallBack(void(*a_ptr)(void));

#endif