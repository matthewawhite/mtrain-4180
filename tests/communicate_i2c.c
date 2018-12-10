#include "mtrain.h"

int main(void) {
	I2C_Init(I2C1, I2C_PinsPack_1, I2C_CLOCK_STANDARD);

	// On board LEDs
	GPIO_Init(42, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);
	GPIO_Init(43, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);

	// Button input
	GPIO_Init(3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);

	// LED output
	GPIO_Init(4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);

	uint8_t buf[10] = "Hello I2C!";

	int counter = 0;
    while (1) {
    	// Delay for 100ms
		HAL_Delay(100);

		// Don't write too often, otherwise mbed will respond too slowly
		if (counter >= 5) {
			// Write entire buffer
			I2C_WriteMultiNoRegister(I2C1, 0x0F, buf, 10);
			counter = 0;
		}

		// Set LED to button value
		int button_val = GPIO_GetInputPinValue(3);
		GPIO_SetPinValue(4, !button_val);

		// Toggle on board LEDs
		if (counter % 2 == 0)
			GPIO_TogglePinValue(42);
		else 
    		GPIO_TogglePinValue(43);

    	counter++;
    }
}