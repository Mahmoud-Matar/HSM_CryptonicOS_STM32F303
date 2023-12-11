#include"Events.h"
#include"Resources.h"
#include"Tasks.h"
#include "Externs.h"
#include "main.h"

extern UART_HandleTypeDef huart2;
void USART2_ISR(){
	  uint8_t c;
	  HAL_UART_Receive(&huart2, &c, 1 , 1000);
	  if ( c == '0')
	  {
		  OS_ActivateTask(0);
	  }
	  else if (c == '1')
	  {
		  OS_ActivateTask(1);
	  }

}
void USART3_ISR(){}
void SPI1_ISR(){}
void SPI3_ISR(){}
void I2C2_ER_ISR(){}
void I2C2_EV_ISR(){}
void I2C1_ER_ISR(){}
void I2C1_EV_ISR(){}
void EXTI0_ISR(){OS_ActivateTask(0);}
void EXTI3_ISR(){OS_ActivateTask(1);}
