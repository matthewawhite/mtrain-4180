#include "gpio.h"

/* Private function */
static uint16_t GPIO_UsedPins[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

/* Private functions */
void GPIO_INT_EnableClock(GPIO_TypeDef* GPIOx);
void GPIO_INT_DisableClock(GPIO_TypeDef* GPIOx);
void GPIO_INT_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Mode_t GPIO_Mode, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed);

void GPIO_Init(uint16_t pin, GPIO_Mode_t GPIO_Mode, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed) {	
	uint16_t GPIO_Pin = GPIO_GetPin(pin);
	GPIO_TypeDef* GPIOx = GPIO_GetPort(pin);

	/* Check input */
	if (GPIO_Pin == 0x00) {
		return;
	}
	
	/* Enable clock for GPIO */
	GPIO_INT_EnableClock(GPIOx);
	
	/* Do initialization */
	GPIO_INT_Init(GPIOx, GPIO_Pin, GPIO_Mode, GPIO_OType, GPIO_PuPd, GPIO_Speed);
}

void GPIO_InitAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed, uint8_t Alternate) {
	uint32_t pinpos;

	/* Check input */
	if (GPIO_Pin == 0x00) {
		return;
	}
	
	/* Enable GPIOx clock */
	GPIO_INT_EnableClock(GPIOx);
	
	/* Set alternate functions for all pins */
	for (pinpos = 0; pinpos < 0x10; pinpos++) {
		/* Check pin */
		if ((GPIO_Pin & (1 << pinpos)) == 0) {
			continue;
		}
		
		/* Set alternate function */
		GPIOx->AFR[pinpos >> 0x03] = (GPIOx->AFR[pinpos >> 0x03] & ~(0x0F << (4 * (pinpos & 0x07)))) | (Alternate << (4 * (pinpos & 0x07)));
	}
	
	/* Do initialization */
	GPIO_INT_Init(GPIOx, GPIO_Pin, GPIO_Mode_AF, GPIO_OType, GPIO_PuPd, GPIO_Speed);
}

void GPIO_DeInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	uint8_t i;
	uint8_t ptr = GPIO_GetPortSource(GPIOx);
	
	/* Go through all pins */
	for (i = 0x00; i < 0x10; i++) {
		/* Pin is set */
		if (GPIO_Pin & (1 << i)) {
			/* Set 11 bits combination for analog mode */
			GPIOx->MODER |= (0x03 << (2 * i));
			
			/* Pin is not used */
			GPIO_UsedPins[ptr] &= ~(1 << i);
		}
	}
}

void GPIO_SetPinAsInput(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	uint8_t i;
	/* Go through all pins */
	for (i = 0x00; i < 0x10; i++) {
		/* Pin is set */
		if (GPIO_Pin & (1 << i)) {
			/* Set 00 bits combination for input */
			GPIOx->MODER &= ~(0x03 << (2 * i));
		}
	}
}

void GPIO_SetPinAsOutput(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	uint8_t i;
	/* Go through all pins */
	for (i = 0x00; i < 0x10; i++) {
		/* Pin is set */
		if (GPIO_Pin & (1 << i)) {
			/* Set 01 bits combination for output */
			GPIOx->MODER = (GPIOx->MODER & ~(0x03 << (2 * i))) | (0x01 << (2 * i));
		}
	}
}

void GPIO_SetPinAsAnalog(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	uint8_t i;
	/* Go through all pins */
	for (i = 0x00; i < 0x10; i++) {
		/* Pin is set */
		if (GPIO_Pin & (1 << i)) {
			/* Set 11 bits combination for analog mode */
			GPIOx->MODER |= (0x03 << (2 * i));
		}
	}
}

void GPIO_SetPinAsAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	uint8_t i;
	
	/* Set alternate functions for all pins */
	for (i = 0; i < 0x10; i++) {
		/* Check pin */
		if ((GPIO_Pin & (1 << i)) == 0) {
			continue;
		}
		
		/* Set alternate mode */
		GPIOx->MODER = (GPIOx->MODER & ~(0x03 << (2 * i))) | (0x02 << (2 * i));
	}
}

void GPIO_SetPullResistor(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PuPd_t GPIO_PuPd) {
	uint8_t pinpos;
	
	/* Go through all pins */
	for (pinpos = 0; pinpos < 0x10; pinpos++) {
		/* Check if pin available */
		if ((GPIO_Pin & (1 << pinpos)) == 0) {
			continue;
		}

		/* Set GPIO PUPD register */
		GPIOx->PUPDR = (GPIOx->PUPDR & ~(0x03 << (2 * pinpos))) | ((uint32_t)(GPIO_PuPd << (2 * pinpos)));
	}
}

void GPIO_Lock(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	uint32_t d;
	
	/* Set GPIO pin with 16th bit set to 1 */
	d = 0x00010000 | GPIO_Pin;
	
	/* Write to LCKR register */
	GPIOx->LCKR = d;
	GPIOx->LCKR = GPIO_Pin;
	GPIOx->LCKR = d;
	
	/* Read twice */
	(void)GPIOx->LCKR;
	(void)GPIOx->LCKR;
}

uint16_t GPIO_GetPinSource(uint16_t GPIO_Pin) {
	uint16_t pinsource = 0;
	
	/* Get pinsource */
	while (GPIO_Pin > 1) {
		/* Increase pinsource */
		pinsource++;
		/* Shift right */
		GPIO_Pin >>= 1;
	}
	
	/* Return source */
	return pinsource;
}

uint16_t GPIO_GetPortSource(GPIO_TypeDef* GPIOx) {
	/* Get port source number */
	/* Offset from GPIOA                       Difference between 2 GPIO addresses */
	return ((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE));
}

/* Private functions */
void GPIO_INT_EnableClock(GPIO_TypeDef* GPIOx) {
	/* Set bit according to the 1 << portsourcenumber */
	RCC->AHB1ENR |= (1 << GPIO_GetPortSource(GPIOx));
}

void GPIO_INT_DisableClock(GPIO_TypeDef* GPIOx) {
	/* Clear bit according to the 1 << portsourcenumber */
	RCC->AHB1ENR &= ~(1 << GPIO_GetPortSource(GPIOx));
}

void GPIO_INT_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Mode_t GPIO_Mode, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed) {
	uint8_t pinpos;
	uint8_t ptr = GPIO_GetPortSource(GPIOx);
	
	/* Go through all pins */
	for (pinpos = 0; pinpos < 0x10; pinpos++) {
		/* Check if pin available */
		if ((GPIO_Pin & (1 << pinpos)) == 0) {
			continue;
		}
		
		/* Pin is used */
		GPIO_UsedPins[ptr] |= 1 << pinpos;
		
		/* Set GPIO PUPD register */
		GPIOx->PUPDR = (GPIOx->PUPDR & ~(0x03 << (2 * pinpos))) | ((uint32_t)(GPIO_PuPd << (2 * pinpos)));
		
		/* Set GPIO MODE register */
		GPIOx->MODER = (GPIOx->MODER & ~((uint32_t)(0x03 << (2 * pinpos)))) | ((uint32_t)(GPIO_Mode << (2 * pinpos)));
		
		/* Set only if output or alternate functions */
		if (GPIO_Mode == GPIO_Mode_OUT || GPIO_Mode == GPIO_Mode_AF) {		
			/* Set GPIO OTYPE register */
			GPIOx->OTYPER = (GPIOx->OTYPER & ~(uint16_t)(0x01 << pinpos)) | ((uint16_t)(GPIO_OType << pinpos));
			
			/* Set GPIO OSPEED register */
			GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~((uint32_t)(0x03 << (2 * pinpos)))) | ((uint32_t)(GPIO_Speed << (2 * pinpos)));
		}
	}
}

uint8_t GPIO_GetInputPinValue(uint16_t pin) {
	uint16_t GPIO_Pin = GPIO_GetPin(pin);
	GPIO_TypeDef* GPIOx = GPIO_GetPort(pin);

	return ((GPIOx)->IDR & (GPIO_Pin)) == 0 ? 0 : 1;
}

void GPIO_SetPinValue(uint16_t pin, uint8_t val) {
	val ? GPIO_SetPinHigh(pin) : GPIO_SetPinLow(pin);
}

void GPIO_SetPinLow(uint16_t pin) {
	uint16_t GPIO_Pin = GPIO_GetPin(pin);
	GPIO_TypeDef* GPIOx = GPIO_GetPort(pin);

	(GPIOx)->BSRR = (uint32_t)(((uint32_t)GPIO_Pin) << 16);
}

void GPIO_SetPinHigh(uint16_t pin) {
	uint16_t GPIO_Pin = GPIO_GetPin(pin);
	GPIO_TypeDef* GPIOx = GPIO_GetPort(pin);

	(GPIOx)->BSRR = (uint32_t)(GPIO_Pin);
}

void GPIO_TogglePinValue(uint16_t pin) {
	uint16_t GPIO_Pin = GPIO_GetPin(pin);
	GPIO_TypeDef* GPIOx = GPIO_GetPort(pin);

	(GPIOx)->ODR ^= (GPIO_Pin);
}


GPIO_TypeDef* GPIO_GetPort(uint16_t pin_num) {
	if (pin_num == 3 || pin_num == 3 || pin_num == 6 || pin_num == 7 || pin_num == 31
		|| pin_num == 32 || pin_num == 33) {
		return GPIOA;
	} else if (pin_num == 4 || pin_num == 5 || pin_num == 19 || pin_num == 20 || pin_num == 25
			   || pin_num == 26 || pin_num == 35) {
		return GPIOB;
	} else if (pin_num == 8 || pin_num == 9 || pin_num == 10 || pin_num == 11 || pin_num == 34 
			   || pin_num == 36) {
		return GPIOC;
	} else if (pin_num == 16 || pin_num == 17 || pin_num == 18) {
		return GPIOD;
	} else if (pin_num == 27 || pin_num == 28 || pin_num == 29 || pin_num == 30) {
		return GPIOF;
	} else if (pin_num == 12 || pin_num == 13 || pin_num == 14) {
		return GPIOH;
	} else if (pin_num == 15) {
		return GPIOI;
	} else if (pin_num >= 40) {
		return GPIOE;
	}

	return GPIOA;
}

uint16_t GPIO_GetPin(uint16_t pin_num) {
	if (pin_num == 3 || pin_num == 10 || pin_num == 20 || pin_num == 28) {
		return GPIO_PIN_8;
	} else if (pin_num == 9 || pin_num == 18 || pin_num == 26 || pin_num == 29) {
		return GPIO_PIN_7;
	} else if (pin_num == 15 || pin_num == 31) {
		return GPIO_PIN_0;
	} else if (pin_num == 33 || pin_num == 35) {
		return GPIO_PIN_4;
	} else if (pin_num == 16) {
		return GPIO_PIN_5;
	} else if (pin_num == 8 || pin_num == 17 || pin_num == 25 || pin_num == 30 || pin_num == 32) {
		return GPIO_PIN_6;
	} else if (pin_num == 11 || pin_num == 19 || pin_num == 27) {
		return GPIO_PIN_9;
	} else if (pin_num == 12 || pin_num == 34) {
		return GPIO_PIN_10;
	} else if (pin_num == 7 || pin_num == 13) {
		return GPIO_PIN_11;
	} else if (pin_num == 6 || pin_num == 14 || pin_num == 36) {
		return GPIO_PIN_12;
	} else if (pin_num == 5) {
		return GPIO_PIN_14;
	} else if (pin_num == 4) {
		return GPIO_PIN_15;
	} else if (pin_num == 40) {
		return GPIO_PIN_4;
	} else if (pin_num == 41) {
		return GPIO_PIN_3;
	} else if (pin_num == 42) {
		return GPIO_PIN_6;
	} else if (pin_num == 43) {
		return GPIO_PIN_5;
	}

	return GPIO_PIN_0;
}