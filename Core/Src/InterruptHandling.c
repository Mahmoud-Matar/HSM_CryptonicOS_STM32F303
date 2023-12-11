#include <InterruptHandling.h>
#include "Externs.h"
#include <stdio.h>




// CHANGE ACTIVE_HOOK variable & better conditioning on the hooks


void EnableAllInterrupts(void)
{
	CS_ON

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_DisableAll)
		{

			__enable_irq();
			Active_ISR_Disable_Type = ISR_Disable_Type_NoDisable;
		}

	}

	CS_OFF
}

void DisableAllInterrupts(void)
{
	CS_ON

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_NoDisable)
		{
			__disable_irq();
			Active_ISR_Disable_Type = ISR_Disable_Type_DisableAll;
		}
		else
		{
			CS_OFF
		}

	}
	else
	{
		CS_OFF
	}



	//

}

void ResumeAllInterrupts(void)
{
	CS_ON

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_SuspendAll || Active_ISR_Disable_Type == ISR_Disable_Type_SuspendOS )
		{
			for(int i =0;i<MAX_ISRs;i++)
			{
				HAL_NVIC_ClearPendingIRQ(i);
			}
			ISR_Suspend_Counter--;

			if(ISR_Suspend_Counter == 0)
			{
				Active_ISR_Disable_Type =  ISR_Disable_Type_NoDisable;
				CS_OFF
			}
			else
			{
				Active_ISR_Disable_Type = ISR_Disable_Type_SuspendAll;
			}
		}
	}
	else
	{
		CS_OFF
	}
}

void SuspendAllInterrupts(void)
{
	CS_ON

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_NoDisable)
		{
			for(int i =0;i<MAX_ISRs;i++)
			{
				HAL_NVIC_SetPendingIRQ(i);
			}

			Active_ISR_Disable_Type = ISR_Disable_Type_SuspendAll;
			ISR_Suspend_Counter =  1;
		}
		else
		{
			if(Active_ISR_Disable_Type == ISR_Disable_Type_DisableAll)
			{
				CS_OFF
			}
			else
			{
				ISR_Suspend_Counter++;
			}

		}

	}
	else
	{
		CS_OFF
	}



}

void ResumeOSInterrupts(void)
{

	CS_ON

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_SuspendAll || Active_ISR_Disable_Type == ISR_Disable_Type_SuspendOS )
		{
			for(int i =0;i<MAX_ISRs;i++)
			{
				if(ISRPCB[i]->Category == 2)
				{
					HAL_NVIC_ClearPendingIRQ(i);
				}
			}

			ISR_Suspend_Counter--;

			if(ISR_Suspend_Counter == 0)
			{
				Active_ISR_Disable_Type =  ISR_Disable_Type_NoDisable;
				CS_OFF
			}
			else
			{
				Active_ISR_Disable_Type = ISR_Disable_Type_SuspendOS;

			}

		}

	}
	else
	{
		CS_OFF
	}








}

void SuspendOSInterrupts (void)
{
	CS_ON


	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_NoDisable)
		{
			for(int i =0;i<MAX_ISRs;i++)
			{
				if(ISRPCB[i]->Category == 2)
				{
					HAL_NVIC_SetPendingIRQ(i);
				}
			}

			Active_ISR_Disable_Type = ISR_Disable_Type_SuspendOS;
			ISR_Suspend_Counter =  1;
		}
		else
		{
			if(Active_ISR_Disable_Type == ISR_Disable_Type_DisableAll)
			{
				CS_OFF
			}
			else
			{
				ISR_Suspend_Counter++;
			}

		}

	}
	else
	{
		CS_OFF
	}



}



bool CheckPending(void){
	for(int i =0;i<MAX_ISRs;i++)
			{
				if(HAL_NVIC_GetPendingIRQ(i))
					{
						return true;
					}
			}
	return false;
}

void USART2_Config(){
	SAVECTX(0);
	USART2_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
		{
			OsTasksPCB[RunningTaskID]->first = 1;
			LOADCTX_FIRST;
		}
		else
		{
		   LOADCTX;
		}

}
void USART3_Config(){
	SAVECTX(0);
	USART3_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
			{
				OsTasksPCB[RunningTaskID]->first = 1;
				LOADCTX_FIRST;
			}
			else
			{
			   LOADCTX;
			}

}
void I2C1_EV_Config(){
	SAVECTX(0);
	I2C1_EV_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
			{
				OsTasksPCB[RunningTaskID]->first = 1;
				LOADCTX_FIRST;
			}
			else
			{
			   LOADCTX;
			}
}
void I2C1_ER_Config(){
	SAVECTX(0);
	I2C1_ER_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
			{
				OsTasksPCB[RunningTaskID]->first = 1;
				LOADCTX_FIRST;
			}
			else
			{
			   LOADCTX;
			}
}
void I2C2_EV_Config(){
	SAVECTX(0);
	I2C2_EV_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
			{
				OsTasksPCB[RunningTaskID]->first = 1;
				LOADCTX_FIRST;
			}
			else
			{
			   LOADCTX;
			}
}
void I2C2_ER_Config(){
	SAVECTX(0);
	I2C2_ER_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
			{
				OsTasksPCB[RunningTaskID]->first = 1;
				LOADCTX_FIRST;
			}
			else
			{
			   LOADCTX;
			}

}
void SPI1_Config(){
	SAVECTX(0);
	SPI1_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
			{
				OsTasksPCB[RunningTaskID]->first = 1;
				LOADCTX_FIRST;
			}
			else
			{
			   LOADCTX;
			}

}
void SPI3_Config(){
	SAVECTX(0);
	SPI3_IRQHandler();
	OS_Schedule();
	if(OsTasksPCB[RunningTaskID]->first ==0)
			{
				OsTasksPCB[RunningTaskID]->first = 1;
				LOADCTX_FIRST;
			}
			else
			{
			   LOADCTX;
			}
}
void EXTI3_Config(){


	SAVECTX(0);
	EXTI3_IRQHandler();
		OS_Schedule();
		if(OsTasksPCB[RunningTaskID]->first ==0)
				{
					OsTasksPCB[RunningTaskID]->first = 1;
					LOADCTX_FIRST;
				}
				else
				{
				   LOADCTX;
				}



}
void EXTI0_Config(){


	SAVECTX(0);
	EXTI0_IRQHandler();
		OS_Schedule();
		if(OsTasksPCB[RunningTaskID]->first ==0)
				{
					OsTasksPCB[RunningTaskID]->first = 1;
					LOADCTX_FIRST;
				}
				else
				{
				   LOADCTX;
				}



}

