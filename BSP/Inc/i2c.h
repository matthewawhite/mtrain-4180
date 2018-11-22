#ifndef __STM32F769I_EVAL_I2C_H
#define __STM32F769I_EVAL_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif 



uint8_t BSP_I2C_Init(void);
uint8_t BSP_I2C_DeInit(void);
uint8_t BSP_I2C_Read();
uint8_t BSP_I2C_Write();



#ifdef __cplusplus
}
#endif

#endif /* __STM32F769I_EVAL_I2C_H */