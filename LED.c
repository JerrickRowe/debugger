#include "LED.h"
#include "Global.h"
#include "stm32f10x.h"
#include "debug.h"
#include <stdbool.h>
#include "GPIO_Operate.h"
#include <assert.h>

#define LED_R_BITADDR	BITBANDADDR_GPIO(D)(LED_R_GPIO_PIN)
#define LED_R_GPIO_PORT	GPIOD
#define LED_R_GPIO_PIN	2


#define LED_G_BITADDR	BITBANDADDR_GPIO(C)(LED_G_GPIO_PIN)
#define LED_G_GPIO_PORT	GPIOC
#define LED_G_GPIO_PIN	15

#define ON_VALUE 1
#define OFF_VALUE 0

typedef struct{
	_t_LED_Enum	EnumID;
	_t_LED_Sta sta;
	uint8_t CountFlag;
	uint8_t PWM_TrigValue;		
	uint32_t *BitAddr;
	GPIO_TypeDef *GPIO_Port;
	uint16_t GPIO_Pin;
	uint32_t GPIO_APB2EN;
}_t_LED_Struct;

static _t_LED_Struct LED_List[LED_Butt] = {
	{LED_1,	LED_Sta_Off, 0, 5, LED_R_BITADDR, LED_R_GPIO_PORT, GPIO_PIN(LED_R_GPIO_PIN), RCC_APB2ENR_IOPDEN},
	{LED_0,	LED_Sta_Off, 0, 6, LED_G_BITADDR, LED_G_GPIO_PORT, GPIO_PIN(LED_G_GPIO_PIN), RCC_APB2ENR_IOPCEN},
};
bool Ready = false;


static inline void LED_SetAll( uint32_t set ){
	uint16_t scanCnt;
	for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
		*LED_List[scanCnt].BitAddr = set;
	}
}


#define POLLING_PERIOD_ms	(2)
static inline void LED_Blink_Poll( void ){
	int scanCnt;
	static bool blinkFlag;
	static unsigned int msCnt = 0;
	if( ++msCnt < POLLING_PERIOD_ms ){
		return;
	}
	msCnt = 0;
	if( blinkFlag == true ){
		blinkFlag = false;
	}else{
		blinkFlag = true;
	}
	for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
		if( LED_List[scanCnt].sta != LED_Sta_Blink ){
			continue;
		}
		*LED_List[scanCnt].BitAddr = blinkFlag;
	}
}

//static inline bool NoOneIsCountingN( uint8_t N ){
//	int scanCnt;
//	if( N==0 || N>8 ){ // Cannot count zero and numbers greater than 8
//		return true; 
//	}
//	for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
//		if( LED_List[scanCnt].CountFlag & (0x01<<(N-1)) ){
//			return false;
//		}
//	}
//	return true;
//}


#define COUNTING_POLLING_PERIOD	(1)
#define COUNTING_HEAD_DELAY		(1)
#define COUNTING_ON_DELAY		(1)
#define COUNTING_TAIL_DELAY		(0)
static bool CountOnce( _t_LED_Struct *pLED ){
	static uint8_t BitSta;
	static uint16_t dlyCnt;
	uint8_t scanCnt;
	switch( BitSta ){
		case 0: // Turn off LED
			for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
				if( LED_List[scanCnt].sta == LED_Sta_Count ){
					*LED_List[scanCnt].BitAddr = OFF_VALUE;
				}
			}
			BitSta = 1;
			dlyCnt = 0;
		case 1: // 1st delay
			if( dlyCnt++ < COUNTING_HEAD_DELAY ){
				break;
			}
			BitSta = 2;
		case 2: // Turn on LED
			for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
				if( LED_List[scanCnt].sta == LED_Sta_Count ){
					*LED_List[scanCnt].BitAddr = ON_VALUE;
				}
			}
			BitSta = 3;
			dlyCnt = 0;
		case 3: // 2nd delay
			if( dlyCnt++ < COUNTING_ON_DELAY ){
				break;
			}
			BitSta = 4;
		case 4: // Turn off LED
			for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
				if( LED_List[scanCnt].sta == LED_Sta_Count ){
					*LED_List[scanCnt].BitAddr = OFF_VALUE;
				}
			}
			BitSta = 5;
			dlyCnt = 0;
		case 5: // 3rd delay
			if( dlyCnt++ < COUNTING_TAIL_DELAY ){
				break;
			}
			BitSta = 0;
			return true; // Count finished.
	}
	return false; // Still in counting.
}


static inline void LED_Counting_Poll( void ){
	static unsigned int msCnt = 0;
	if( ++msCnt < COUNTING_POLLING_PERIOD ){
		return;
	}
	int scanCnt;
	
	static enum{
		Check = 0,
		Count1,
		Count2,
		Count3,
		Count4,
		Count5,
		Count6,
		Count7,
		Count8,
		Gap,
	}CountingSta = Check;
	
	static uint8_t BitSta;
	
	bool NoneCounting = true;
	static uint8_t CountingFlag;
	static uint8_t CurrentCount;
	static bool OnFlag;
	switch( CountingSta ){
		case Check:
			for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
				if( LED_List[scanCnt].sta != LED_Sta_Count ){
					continue;
				}
				uint8_t N;
				NoneCounting = false;
				CountingFlag |= LED_List[scanCnt].CountFlag;
			}
			if( NoneCounting ){
				NoneCounting = 0;
				return;
			}
			CurrentCount = 0;
			CountingSta = Count1;
			BitSta = 0;
		case Count1:
			if( CountingFlag & LED_COUNT_1 ){
				// Counting 1
//				if( !CountOnce() ){
//					
//					break;
//				}
			}
			CountingSta = Count2;
		case Count2:
			break;
		case Count3:
			break;
		case Count4:
			break;
		case Count5:
			break;
		case Count6:
			break;
		case Count7:
			break;
		case Count8:
			break;
		case Gap:
			break;
	}
	
	// Skip if none of the LEDs is counting or counting N.
	
	// Gap
	
}


#define PWM_PERIOD_ms		(10)
#define FADE_TIME_ms		(1000)
#define FADE_STEP_MAX		(10)
#define FADE_STEP_PERIOD_ms	(FADE_TIME_ms / FADE_STEP_MAX)
//static int PWM_GammaTable[FADE_STEP_MAX] = {0};
//static bool GammaTable_Available;

static inline void LED_Breath_Poll( void ){
//	int scanCnt;
//	bool fadeTrig = false;
//	static volatile int PWM_Cnt;
//	bool bitVal;
//	static int fadeStep = 0;
//	static int fadeTimer = 0;
//	if( ++PWM_Cnt >= PWM_PERIOD_ms ){
//		PWM_Cnt = 0;
//	}
//	if( ++fadeTimer > FADE_STEP_PERIOD_ms ){
//		fadeTimer = 0;
//		fadeTrig = true;
//	}
//	
//	for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){ //PWM generator
//		switch( LED_List[scanCnt].sta ){
//			case LED_Sta_Fadein:
//			case LED_Sta_Fadeout:
//			case LED_Sta_Breath:
//			case LED_Sta_Grey:
//				if( PWM_Cnt < LED_List[scanCnt].PWM_TrigValue ){
//					*LED_List[scanCnt].BitAddr = 1; //Light up the LED
//				}else{
//					*LED_List[scanCnt].BitAddr = 0; //Put out the LED
//				}
//				break;
//			default:
//				break;
//		}
//	}
//	
//	for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){ //Fader
//		switch( LED_List[scanCnt].sta ){
//			case LED_Sta_Fadein:
//			case LED_Sta_Fadeout:
//			case LED_Sta_Breath:
//			case LED_Sta_Grey:
//			default:
//				break;
//		}
//	}
	
}

//static void PWM_GammaTable_Gen( void ){
//	int i;
//	for( i=0; i<FADE_STEP_MAX; i++ ){
//		PWM_GammaTable[i] = ;
//	}
//	GammaTable_Available = true;
//}


//****************** CMSIS specified code ******************
#include "cmsis_os2.h"
osTimerId_t	osTimer_ID;
static void osTimer(void *arg)
{
	LED_Blink_Poll();
//	LED_Breath_Poll();
}

//****************************************************************
//	Initialize LED hardware configuration 
//	This function should not be called before CMSIS is started
//****************************************************************
void LED_Init( void ){
	int scanCnt;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit( &GPIO_InitStruct );
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	for( scanCnt=0; scanCnt<LED_Butt; scanCnt++ ){
		assert_param( IS_RCC_APB2_PERIPH_GPIO( LED_List[scanCnt].GPIO_APB2EN ) );
		RCC_APB2PeriphClockCmd( LED_List[scanCnt].GPIO_APB2EN, ENABLE );
		GPIO_InitStruct.GPIO_Pin = LED_List[scanCnt].GPIO_Pin;
		GPIO_Init( LED_List[scanCnt].GPIO_Port, &GPIO_InitStruct );
	}
	Ready = true;
	DBG7(printInf("","LED initialized."));
	
	LED_Set( LED_0, LED_Sta_Off );
	LED_Set( LED_1, LED_Sta_Off ); 
	
//	LED_Set( LED_0, LED_Sta_Grey );
//	LED_Set( LED_1, LED_Sta_Grey );
	//-------------- start OS timer --------------
	if( !SystemIsOnline ){
		DBG0(printErr( "", "Blinking LED unavailable because the system is not started." ));
	}
	
	
	const osTimerAttr_t LED_TimerAttr = {
		.name = "LED timer"
	};
	osTimer_ID = osTimerNew( &osTimer, osTimerPeriodic, NULL, &LED_TimerAttr );
	assert( osTimerStart( osTimer_ID, 100 ) == osOK );
	DBG7(printInf( "", "Blinking LED started. osTimerID=0x%08X Period=%dms", (int)osTimer_ID, POLLING_PERIOD_ms ));
}
//**********************************************************



void LED_Set(_t_LED_Enum LED, _t_LED_Sta sta){
	if( Ready != true ){
		DBG1(printErr("","LED not initialized."));
		return;
	}
	switch(sta){
		case LED_Sta_On:
			*LED_List[LED].BitAddr = ON_VALUE;
			break;
		case LED_Sta_Off:
			*LED_List[LED].BitAddr = OFF_VALUE;
			break;
		case LED_Sta_Blink:
			*LED_List[LED].BitAddr = OFF_VALUE;
			break;
		case LED_Sta_Fadein:
			break;
		case LED_Sta_Fadeout:
			break;
		case LED_Sta_Breath:
			break;
		case LED_Sta_Grey:
			break;
		default:
			DBG1(printErr("","Invalid LED operation."));
			return;
	}
	LED_List[LED].sta = sta;
}



void LED_SetCount(_t_LED_Enum LED, uint8_t CountFlag){
	if( Ready != true ){
		DBG1(printErr("","LED not initialized."));
		return;
	}
	LED_List[LED].sta = LED_Sta_Count;
	LED_List[LED].CountFlag = CountFlag;
}



