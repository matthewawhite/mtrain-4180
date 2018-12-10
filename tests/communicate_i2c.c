#include "mtrain.h"

int main(void) {
	I2C_Init(I2C1, I2C_PinsPack_1, I2C_CLOCK_STANDARD);

	GPIO_Init(GPIOE, GPIO_PIN_4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);
	GPIO_Init(GPIOA, GPIO_PIN_8, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);
	GPIO_Init(GPIOB, GPIO_PIN_15, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);

	uint8_t buf[10] = "Hello I2C!";

	int counter = 0;
    while (1) {
		HAL_Delay(100);

		if (counter >= 5) {
			I2C_WriteMultiNoRegister(I2C1, 0x0F, buf, 10);
			counter = 0;
		}

		int button_val = GPIO_GetInputPinValue(GPIOA, GPIO_PIN_8);
		GPIO_SetPinValue(GPIOB, GPIO_PIN_15, !button_val);

    	GPIO_TogglePinValue(GPIOE, GPIO_PIN_4);

    	counter++;
    }
}