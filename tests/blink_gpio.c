#include "mtrain.h"

int main(void) {
  BSP_GPIO_INIT(GPIOE, GPIO_PIN_4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);

  while (1) {
    HAL_Delay(100);
    GPIO_TogglePinValue(GPIOA, GPIO_PIN_8);
  }
}