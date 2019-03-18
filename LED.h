#ifndef _LED_H_
#define _LED_H_
#include <stdint.h>

typedef enum{
	LED_1,
	LED_0,
	LED_Butt,
}_t_LED_Enum;


typedef enum{
	LED_Sta_Off,
	LED_Sta_On,
	LED_Sta_Blink,
	LED_Sta_Fadein,
	LED_Sta_Fadeout,
	LED_Sta_Breath,
	LED_Sta_Count,
	LED_Sta_Grey,	//Keep still on brightness
	LED_Sta_Butt,
}_t_LED_Sta;

#define LED_COUNT_1		(0x01)
#define LED_COUNT_2		(0x02)
#define LED_COUNT_3		(0x04)
#define LED_COUNT_4		(0x08)
#define LED_COUNT_5		(0x10)
#define LED_COUNT_6		(0x20)
#define LED_COUNT_7		(0x40)
#define LED_COUNT_8		(0x80)

void LED_Init( void );
void LED_Set(_t_LED_Enum LED, _t_LED_Sta sta);
void LED_SetCount(_t_LED_Enum LED, uint8_t CountFlag);


#endif
