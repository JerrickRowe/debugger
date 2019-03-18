#ifndef _GPIO_OPERATE_H_
#define _GPIO_OPERATE_H_

#include "stm32f10x.h"

#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define GPIO_PIN(n)	PRIMITIVE_CAT(GPIO_Pin_, n)
#define GPIO(x) PRIMITIVE_CAT(GPIO, x)



#define GPIO_PORT(num) \
 ((num == 0) ? GPIOA : \
  (num == 1) ? GPIOB : \
  (num == 2) ? GPIOC : \
  (num == 3) ? GPIOD : \
  (num == 4) ? GPIOE : \
  (num == 5) ? GPIOF : \
  (num == 6) ? GPIOG : \
  NULL)



#define BITBAND_GPIO(p)		PRIMITIVE_CAT(BITBAND_GPIO, p)
#define BITBAND_GPIOA(n)	(*(uint32_t *)(PERIPH_BB_BASE + 0x210180 + n*4))
#define BITBAND_GPIOB(n)	(*(uint32_t *)(PERIPH_BB_BASE + 0x218180 + n*4))
#define BITBAND_GPIOC(n)	(*(uint32_t *)(PERIPH_BB_BASE + 0x220180 + n*4))
#define BITBAND_GPIOD(n)	(*(uint32_t *)(PERIPH_BB_BASE + 0x228180 + n*4))
#define BITBAND_GPIOE(n)	(*(uint32_t *)(PERIPH_BB_BASE + 0x230180 + n*4))
#define BITBAND_GPIOF(n)	(*(uint32_t *)(PERIPH_BB_BASE + 0x238180 + n*4))
#define BITBAND_GPIOG(n)	(*(uint32_t *)(PERIPH_BB_BASE + 0x240180 + n*4))

#define BITBANDADDR_GPIO(p)		PRIMITIVE_CAT(BITBANDADDR_GPIO, p)
#define BITBANDADDR_GPIOA(n)	((uint32_t *)(PERIPH_BB_BASE + 0x210180 + n*4))
#define BITBANDADDR_GPIOB(n)	((uint32_t *)(PERIPH_BB_BASE + 0x218180 + n*4))
#define BITBANDADDR_GPIOC(n)	((uint32_t *)(PERIPH_BB_BASE + 0x220180 + n*4))
#define BITBANDADDR_GPIOD(n)	((uint32_t *)(PERIPH_BB_BASE + 0x228180 + n*4))
#define BITBANDADDR_GPIOE(n)	((uint32_t *)(PERIPH_BB_BASE + 0x230180 + n*4))
#define BITBANDADDR_GPIOF(n)	((uint32_t *)(PERIPH_BB_BASE + 0x238180 + n*4))
#define BITBANDADDR_GPIOG(n)	((uint32_t *)(PERIPH_BB_BASE + 0x240180 + n*4))

//#define CLOCK_ENABLE_GPIO(p)	PRIMITIVE_CAT(CLOCK_ENABLE_GPIO, p)
#ifdef RCC_APB2ENR_IOPAEN
	#define CLOCK_ENABLE_GPIOA()	RCC_APB2PeriphClockCmd( RCC_APB2ENR_IOPAEN, ENABLE )
#else
	#define CLOCK_ENABLE_GPIOA()	(void)0	//GPIO_A not available
#endif

#ifdef RCC_APB2ENR_IOPBEN
	#define CLOCK_ENABLE_GPIOB()	RCC_APB2PeriphClockCmd( RCC_APB2ENR_IOPBEN, ENABLE )
#else
	#define CLOCK_ENABLE_GPIOB()	(void)0	//GPIO_B not available
#endif

#ifdef RCC_APB2ENR_IOPCEN
	#define CLOCK_ENABLE_GPIOC()	RCC_APB2PeriphClockCmd( RCC_APB2ENR_IOPCEN, ENABLE )
#else
	#define CLOCK_ENABLE_GPIOC()	(void)0	//GPIO_C not available
#endif

#ifdef RCC_APB2ENR_IOPDEN
	#define CLOCK_ENABLE_GPIOD()	RCC_APB2PeriphClockCmd( RCC_APB2ENR_IOPDEN, ENABLE )
#else
	#define CLOCK_ENABLE_GPIOD()	(void)0	//GPIO_D not available
#endif

#ifdef RCC_APB2ENR_IOPEEN
	#define CLOCK_ENABLE_GPIOE()	RCC_APB2PeriphClockCmd( RCC_APB2ENR_IOPEEN, ENABLE )
#else
	#define CLOCK_ENABLE_GPIOE()	(void)0	//GPIO_E not available
#endif

#ifdef RCC_APB2ENR_IOPFEN
	#define CLOCK_ENABLE_GPIOF()	RCC_APB2PeriphClockCmd( RCC_APB2ENR_IOPFEN, ENABLE )
#else
	#define CLOCK_ENABLE_GPIOF()	(void)0	//GPIO_F not available
#endif

#ifdef RCC_APB2ENR_IOPGEN
	#define CLOCK_ENABLE_GPIOG()	RCC_APB2PeriphClockCmd( RCC_APB2ENR_IOPGEN, ENABLE )
#else
	#define CLOCK_ENABLE_GPIOG()	(void)0	//GPIO_G not available
#endif

//#define CLOCK_ENABLE_GPIO(p)	
#define IS_RCC_APB2_PERIPH_GPIO(PERIPH) ((((PERIPH) & 0xFFFFFE03) == 0x00) && ((PERIPH) != 0x00))

#endif
