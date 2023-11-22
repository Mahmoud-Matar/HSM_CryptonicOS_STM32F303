#include "ISRs.h"
#include "Externs.h"
#include <stdio.h>







void EnableAllInterrupts(void)
{
	CS_ON

		__asm volatile( "CPSIE i;");

	CS_OFF
}
void DisableAllInterrupts(void)
{
	CS_ON

	__asm volatile( "CPSID i;");

	USER_THREAD

}
void ResumeAllInterrupts(void)
{
	CS_ON
	for(int i =0;i<MAX_ISRs;i++)
	{
		HAL_NVIC_ClearPendingIRQ(i);
	}
	CS_OFF
}
void SuspendAllInterrupts(void)
{
	CS_ON
	for(int i =0;i<MAX_ISRs;i++)
	{
		HAL_NVIC_SetPendingIRQ(i);
	}
	CS_OFF
}
void ResumeOSInterrupts(void)
{
	CS_ON
	for(int i =0;i<MAX_ISRs;i++)
	{
		if(ISRPCB[i]->Category == 2)
		{
			HAL_NVIC_ClearPendingIRQ(i);
		}
	}
	CS_OFF
}
void SuspendOSInterrupts (void)
{
	CS_ON
	for(int i =0;i<MAX_ISRs;i++)
	{
		if(ISRPCB[i]->Category == 2)
		{
			HAL_NVIC_SetPendingIRQ(i);
		}
	}
	CS_OFF
}
