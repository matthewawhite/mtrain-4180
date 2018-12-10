#ifndef __STM32F769I_EVAL_I2C_H
#define __STM32F769I_EVAL_I2C_H

/* C++ detection */
#ifdef __cplusplus
 extern "C" {
#endif 


/*
 * This chart is based off of the mtrain pinout, not STM32F7 pinout
 * 
       |PINSPACK 1   |PINSPACK 2
I2CX   |SCL   SDA    |SCL   SDA    
       |             |          
I2C1   |PB6   PB7    |             
I2C4   |PB8   PB9    |PH11  PH12
 *
 *
 */
#include "stm32f7xx_hal.h"
#include "gpio.h"

/* Clock values */
#define I2C_CLOCK_STANDARD         100000  /*!< I2C Standard speed */
#define I2C_CLOCK_FAST_MODE        400000  /*!< I2C Fast mode speed */
#define I2C_CLOCK_FAST_MODE_PLUS   1000000 /*!< I2C Fast mode plus speed */

/**
 * I2C pinspack enum
 */
typedef enum {
	I2C_PinsPack_1 = 0x00, /*!< Use Pinspack1 from Pinout table for I2Cx */
	I2C_PinsPack_2         /*!< Use Pinspack2 from Pinout table for I2C4 */
} I2C_PinsPack_t;

/**
 * I2C result enum
 */
typedef enum {
	I2C_Result_Ok = 0x00, /*!< Everything OK */
	I2C_Result_Error      /*!< An error has occurred */
} I2C_Result_t;

/**
 * Initializes I2C peripheral
 * *I2Cx: Pointer to I2Cx peripheral you will use for iintialization
 * pinspack: Pinspack used for GPIO initialization. This parameter can be a value of @ref I2C_PinsPack_t enumeration
 * clockSpeed: Clock speed in units of Hz for I2C communication
 * Returns a member of the I2C_Result_t enum
 */
I2C_Result_t I2C_Init(I2C_TypeDef* I2Cx, I2C_PinsPack_t pinspack, uint32_t clockSpeed);

/**
 * Reads single byte from device
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * register_address: Register address from where read will be done
 * *data: Pointer to variable where data will be stored from read operation
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_Read(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t* data);

/**
 * Reads multiple bytes from device
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit device address used for communication
 * register_address: Register address from where read operation will start
 * *data: Pointer to variable where data will be stored from read operation
 * count: Number of elements to read from device
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_ReadMulti(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t* data, uint16_t count);

/**
 * Reads I2C data without specifying register address
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * *data: Pointer to variable where data will be stored from read operation
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_ReadNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t* data);

/**
 * Reads multiple bytes from device without specifying register address
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * *data: Pointer to variable where data will be stored from read operation
 * count: Number of elements to read from device
 * Returns a member of theI2C_Result_t enumeration
 */
I2C_Result_t I2C_ReadMultiNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t* data, uint16_t count);

/**
 * Writes single byte to device
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * register_address: Register address where you want to write data
 * data: Data to be written to device
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_Write(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t data);

/**
 * Writes multiple data to device
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * register_address: Register address where data will be written
 * *data: Data to be written to device.
 * count: Number of elements to write starting at register register_address
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_WriteMulti(I2C_TypeDef* I2Cx, uint8_t device_address, uint16_t register_address, uint8_t *data, uint16_t count);

/**
 * Writes single byte to device without specifying register address, can be used for command write
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * data: Data to be written to device
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_WriteNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t data);

/**
 * Writes multiple data to device without register address
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * *data: Pointer to data array t obe written to device. Array length is the same as number of elements you want to write
 * count: Number of elements to write
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_WriteMultiNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t* data, uint16_t count);

/**
 * Checks if device is connected to I2C port and ready to use
 * *I2Cx: Pointer to I2Cx peripheral to be used in communication
 * device_address: 7-bit, left aligned device address used for communication
 * Returns a member of the I2C_Result_t enumeration
 */
I2C_Result_t I2C_IsDeviceConnected(I2C_TypeDef* I2Cx, uint8_t address);

/**
 * Gets pointer to I2C handle structure for specific I2C
 * *I2Cx: Pointer to I2Cx used for handle
 * Returns a pointer to the I2C Handle structure
 */
I2C_HandleTypeDef* I2C_GetHandle(I2C_TypeDef* I2Cx);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* __STM32F769I_EVAL_I2C_H */
