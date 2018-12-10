#ifndef __STM32F769I_EVAL_GPIO_H
#define __STM32F769I_EVAL_GPIO_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"

/**
 * GPIO Pins declarations 
 * For HAL drivers compatibility
 */
  
#ifndef GPIO_PIN_0
#define GPIO_PIN_0		((uint16_t)0x0001)
#define GPIO_PIN_1		((uint16_t)0x0002)
#define GPIO_PIN_2		((uint16_t)0x0004)
#define GPIO_PIN_3		((uint16_t)0x0008)
#define GPIO_PIN_4		((uint16_t)0x0010)
#define GPIO_PIN_5		((uint16_t)0x0020)
#define GPIO_PIN_6		((uint16_t)0x0040)
#define GPIO_PIN_7		((uint16_t)0x0080)
#define GPIO_PIN_8		((uint16_t)0x0100)
#define GPIO_PIN_9		((uint16_t)0x0200)
#define GPIO_PIN_10		((uint16_t)0x0400)
#define GPIO_PIN_11		((uint16_t)0x0800)
#define GPIO_PIN_12		((uint16_t)0x1000)
#define GPIO_PIN_13		((uint16_t)0x2000)
#define GPIO_PIN_14		((uint16_t)0x4000)
#define GPIO_PIN_15		((uint16_t)0x8000)
#define GPIO_PIN_ALL	((uint16_t)0xFFFF)
#endif

/**
 * GPIO Pins declarations 
 * For STD Periph drivers compatibility
 */

#ifndef GPIO_Pin_0
#define GPIO_Pin_0		((uint16_t)0x0001)
#define GPIO_Pin_1		((uint16_t)0x0002)
#define GPIO_Pin_2		((uint16_t)0x0004)
#define GPIO_Pin_3		((uint16_t)0x0008)
#define GPIO_Pin_4		((uint16_t)0x0010)
#define GPIO_Pin_5		((uint16_t)0x0020)
#define GPIO_Pin_6		((uint16_t)0x0040)
#define GPIO_Pin_7		((uint16_t)0x0080)
#define GPIO_Pin_8		((uint16_t)0x0100)
#define GPIO_Pin_9		((uint16_t)0x0200)
#define GPIO_Pin_10		((uint16_t)0x0400)
#define GPIO_Pin_11		((uint16_t)0x0800)
#define GPIO_Pin_12		((uint16_t)0x1000)
#define GPIO_Pin_13		((uint16_t)0x2000)
#define GPIO_Pin_14		((uint16_t)0x4000)
#define GPIO_Pin_15		((uint16_t)0x8000)
#define GPIO_Pin_All	((uint16_t)0xFFFF)
#endif


/**
 * GPIO Mode enum
 */
typedef enum {
	GPIO_Mode_IN = 0x00,  // General Purpose Input
	GPIO_Mode_OUT = 0x01, // General Purpose Output
	GPIO_Mode_AF = 0x02,  // GPIO Pin as Alternate Function
	GPIO_Mode_AN = 0x03,  // GPIO Pin as Analog input/output
} GPIO_Mode_t;

/**
 * GPIO Output type enum
 */
typedef enum {
	GPIO_OType_PP = 0x00, // GPIO Output Type Push-Pull
	GPIO_OType_OD = 0x01  // GPIO Output Type Open-Drain
} GPIO_OType_t;

/**
 * GPIO Speed enum
 */
typedef enum {
	GPIO_Speed_Low = 0x00,    // GPIO Speed Low
	GPIO_Speed_Medium = 0x01, // GPIO Speed Medium
	GPIO_Speed_Fast = 0x02,   // GPIO Speed Fast 
	GPIO_Speed_High = 0x03    // GPIO Speed High
} GPIO_Speed_t;

/**
 * GPIO pull resistors enum
 */
typedef enum {
	GPIO_PuPd_NOPULL = 0x00, // No pull resistor
	GPIO_PuPd_UP = 0x01,     // Pull up resistor enabled
	GPIO_PuPd_DOWN = 0x02    // Pull down resistor enabled
} GPIO_PuPd_t;

/**
 * GPIO pin numbers within port
 */
typedef enum {
	p3 = GPIO_PIN_8,
	p4 = GPIO_PIN_15,
	p5 = GPIO_PIN_14,
	p6 = GPIO_PIN_12,
	p7 = GPIO_PIN_11,
	p8 = GPIO_PIN_6,
	p9 = GPIO_PIN_7,
	p10 = GPIO_PIN_8,
	p11 = GPIO_PIN_9,
	p12 = GPIO_PIN_10,
	p13 = GPIO_PIN_11,
	p14 = GPIO_PIN_12,
	p15 = GPIO_PIN_0,
	p16 = GPIO_PIN_5,
	p17 = GPIO_PIN_6,
	p18 = GPIO_PIN_7,
	p19 = GPIO_PIN_9,
	p20 = GPIO_PIN_8,
	p25 = GPIO_PIN_6,
	p26 = GPIO_PIN_7,
	p27 = GPIO_PIN_9,
	p28 = GPIO_PIN_8,
	p29 = GPIO_PIN_7,
	p30 = GPIO_PIN_6,
	p31 = GPIO_PIN_0,
	p32 = GPIO_PIN_6,
	p33 = GPIO_PIN_4,
	p34 = GPIO_PIN_10,
	p35 = GPIO_PIN_4,
	p36 = GPIO_PIN_12
} GPIO_Pin_Num;

 
/**
 * Initializes GPIO pins
 * pin: GPIO Pin that is being initialized (refers to board pin)
 * GPIO_Mode: Select GPIO mode. This parameter can be a value of @ref GPIO_Mode_t enumeration
 * GPIO_OType: Select GPIO Output type. This parameter can be a value of @ref GPIO_OType_t enumeration
 * GPIO_PuPd: Select GPIO pull resistor. This parameter can be a value of @ref GPIO_PuPd_t enumeration
 * GPIO_Speed: Select GPIO speed. This parameter can be a value of @ref GPIO_Speed_t enumeration
 */
void GPIO_Init(uint16_t pin, GPIO_Mode_t GPIO_Mode, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed);

/**
 * Initializes GPIO pins(s) as alternate function
 * GPIOx: Pointer to GPIOx port you will use for initialization
 * GPIO_Pin: GPIO pin(s) you will use for initialization
 * GPIO_OType: Select GPIO Output type. This parameter can be a value of @ref GPIO_OType_t enumeration
 * GPIO_PuPd: Select GPIO pull resistor. This parameter can be a value of @ref GPIO_PuPd_t enumeration
 * GPIO_Speed: Select GPIO speed. This parameter can be a value of @ref GPIO_Speed_t enumeration
 * Alternate: Alternate function you will use
 */
void GPIO_InitAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed, uint8_t Alternate);

/**
 * Deinitializes pin
 * GPIOx: GPIOx PORT where you want to set pin as input
 * GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them as input
 */
void GPIO_DeInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * Sets pin(s) as input 
 * GPIOx: GPIOx PORT where you want to set pin as input
 * GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them as input
 */
void GPIO_SetPinAsInput(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * Sets pin(s) as output
 * GPIOx: GPIOx PORT where you want to set pin as output
 * GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them as output
 */
void GPIO_SetPinAsOutput(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * Sets pin(s) as analog
 * GPIOx: GPIOx PORT where you want to set pin as analog
 * GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them as analog
 */
void GPIO_SetPinAsAnalog(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/** 
 * Sets pin(s) as alternate function
 * GPIOx: GPIOx PORT where you want to set pin as alternate
 * GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them as alternate
 */
void GPIO_SetPinAsAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * Sets pull resistor settings to GPIO pin(s)
 * *GPIOx: GPIOx PORT where you want to select pull resistor
 * GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them as output
 * GPIO_PuPd: Pull resistor option. This parameter can be a value of @ref GPIO_PuPd_t enumeration
 */
void GPIO_SetPullResistor(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PuPd_t GPIO_PuPd);

/**
 * Sets pin low
 * pin: GPIO pin being set low
 */
void GPIO_SetPinLow(uint16_t pin);

/**
 * Sets pin(s) high
 * pin: GPIO pin being set high
 */
void GPIO_SetPinHigh(uint16_t pin);

/**
 * Sets pin value
 * pin: GPIO pin that has value set
 * val: If parameter is 0 then pin will be low, otherwise high
 */
void GPIO_SetPinValue(uint16_t pin, uint8_t val);
/**
 * Toggles pin
 * pin: GPIO pin that is toggled
 */
void GPIO_TogglePinValue(uint16_t pin);

/**
 * Gets input data bit
 * pin: GPIO pin used for getting input value
 * @retval 1 in case pin is high, or 0 if low
 */
uint8_t GPIO_GetInputPinValue(uint16_t pin);

/**
 * Gets port source from desired GPIOx PORT
 * GPIOx: GPIO PORT for calculating port source
 * Returns calculated port source for GPIO
 */
uint16_t GPIO_GetPortSource(GPIO_TypeDef* GPIOx);

/**
 * Gets pin source from desired GPIO pin
 * GPIO_Pin: GPIO pin for calculating port source
 * Returns calculated pin source for GPIO pin
 */
uint16_t GPIO_GetPinSource(uint16_t GPIO_Pin);

/**
 * Locks GPIOx register for future changes
 * *GPIOx: GPIOx PORT where you want to lock config registers
 * GPIO_Pin: GPIO pin(s) where you want to lock config registers
 */
void GPIO_Lock(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/** 
 * Gets bit separated pins which were used at least once in library and were not deinitialized
 * *GPIOx: Pointer to GPIOx peripheral where to check used GPIO pins
 * Returns bit values for used pins
 */
uint16_t GPIO_GetUsedPins(GPIO_TypeDef* GPIOx);

/** 
 * Gets bit separated pins which were not used at in library or were deinitialized
 * *GPIOx: Pointer to GPIOx peripheral where to check used GPIO pins
 * Returns bit values for free pins
 */
uint16_t GPIO_GetFreePins(GPIO_TypeDef* GPIOx);

/**
 * @param the number of the pin
 * @retval the port 
 */
GPIO_TypeDef* GPIO_GetPort(uint16_t pin_num);

/**
 * @param the number of the pin on the board
 * @retval the GPIO pin number
 */
uint16_t GPIO_GetPin(uint16_t pin_num);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* __STM32F769I_EVAL_GPIO_H */
