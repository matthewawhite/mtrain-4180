#include "mtrain.h"


I2C_HandleTypeDef  I2CHandle;

// For reference, can be removed
typedef struct __I2C_HandleTypeDef
{

  I2C_InitTypeDef            Init;           /*!< I2C communication parameters              */

  uint8_t                    *pBuffPtr;      /*!< Pointer to I2C transfer buffer            */

  uint16_t                   XferSize;       /*!< I2C transfer size                         */

  __IO uint16_t              XferCount;      /*!< I2C transfer counter                      */

  __IO uint32_t              XferOptions;    /*!< I2C sequantial transfer options, this parameter can
                                                  be a value of @ref I2C_XFEROPTIONS */

  __IO uint32_t              PreviousState;  /*!< I2C communication Previous state          */

  HAL_StatusTypeDef (*XferISR)(struct __I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources); /*!< I2C transfer IRQ handler function pointer */

  DMA_HandleTypeDef          *hdmatx;        /*!< I2C Tx DMA handle parameters              */

  DMA_HandleTypeDef          *hdmarx;        /*!< I2C Rx DMA handle parameters              */

  HAL_LockTypeDef            Lock;           /*!< I2C locking object                        */

  __IO HAL_I2C_StateTypeDef  State;          /*!< I2C communication state                   */

  __IO HAL_I2C_ModeTypeDef   Mode;           /*!< I2C communication mode                    */

  __IO uint32_t              ErrorCode;      /*!< I2C Error code                            */

  __IO uint32_t              AddrEventCount; /*!< I2C Address Event counter                 */
}I2C_HandleTypeDef;


// For reference, can be removed
typedef struct
{
  uint32_t Timing;              /*!< Specifies the I2C_TIMINGR_register value.
                                  This parameter calculated by referring to I2C initialization
                                         section in Reference manual */

  uint32_t OwnAddress1;         /*!< Specifies the first device own address.
                                  This parameter can be a 7-bit or 10-bit address. */

  uint32_t AddressingMode;      /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
                                  This parameter can be a value of @ref I2C_ADDRESSING_MODE */

  uint32_t DualAddressMode;     /*!< Specifies if dual addressing mode is selected.
                                  This parameter can be a value of @ref I2C_DUAL_ADDRESSING_MODE */

  uint32_t OwnAddress2;         /*!< Specifies the second device own address if dual addressing mode is selected
                                  This parameter can be a 7-bit address. */

  uint32_t OwnAddress2Masks;    /*!< Specifies the acknowledge mask address second device own address if dual addressing mode is selected
                                  This parameter can be a value of @ref I2C_OWN_ADDRESS2_MASKS */

  uint32_t GeneralCallMode;     /*!< Specifies if general call mode is selected.
                                  This parameter can be a value of @ref I2C_GENERAL_CALL_ADDRESSING_MODE */

  uint32_t NoStretchMode;       /*!< Specifies if nostretch mode is selected.
                                  This parameter can be a value of @ref I2C_NOSTRETCH_MODE */

}I2C_InitTypeDef;

// Need to add lock and unlock for writes/reads when mutex is ready

uint8_t BSP_I2C_Init(void) {
  I2C_HandleTypeDef.Instance = I2C1;
}

uint8_t BSP_I2C_DeInit(void) {

}

uint8_t BSP_I2C_Read() {

}

uint8_t BSP_I2C_Write() {

}
