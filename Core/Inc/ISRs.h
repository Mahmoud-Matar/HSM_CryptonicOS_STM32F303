#ifndef Headers_APIs_Headers_ISRs_H
#define Headers_APIs_Headers_ISRs_H

#include "Defines.h"
#include "stm32f3xx_hal.h"




void EnableAllInterrupts(void);
void DisableAllInterrupts(void);
void ResumeAllInterrupts(void);
void SuspendAllInterrupts(void);
void ResumeOSInterrupts(void);
void SuspendOSInterrupts (void);

#endif
