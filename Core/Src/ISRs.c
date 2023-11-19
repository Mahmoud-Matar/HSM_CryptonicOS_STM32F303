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

}
void SuspendAllInterrupts(void)
{
}
void ResumeOSInterrupts(void)
{
}
void SuspendOSInterrupts (void)
{
}
