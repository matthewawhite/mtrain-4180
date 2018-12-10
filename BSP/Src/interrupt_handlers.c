#include "mtrain.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

extern PCD_HandleTypeDef hpcd;

/*  */
#ifdef USE_USB_FS
void OTG_FS_IRQHandler(void)
#else
void OTG_HS_IRQHandler(void)
#endif
{
    HAL_PCD_IRQHandler(&hpcd);
}

extern QSPI_HandleTypeDef QSPIHandle;

void QUADSPI_IRQHandler(void)
{
    HAL_QSPI_IRQHandler(&QSPIHandle);
}

// #ifdef I2C1
// extern I2C_HandleTypeDef I2C1Handle;
// #else
// extern I2C_HandleTypeDef I2C4Handle;
// #endif

// #ifdef I2C1
// void I2C1_EV_IRQHandler(void) 
// {
// 	HAL_I2C_EV_IRQHandler(&I2C1Handle);
// }
// #else
// void I2C4_EV_IRQHandler(void)
// {
// 	HAL_I2C_EV_IRQHandler(&I2C4Handle);
// }
// #endif