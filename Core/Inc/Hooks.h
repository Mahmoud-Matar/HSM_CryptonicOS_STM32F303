#ifndef Headers_APIs_Headers_Hooks_H
#define Headers_APIs_Headers_Hooks_H

#include "Defines.h"

void ErrorHook (StatusType Error);
/*
Calling points:
1- functions that return StatusType != E_OK. //done
2- Alarm expires, Failed task activation, fail event setting.
*/
void PreTaskHook (void);
/*
Calling points:
1- After new Task moves to running state (Must be new task).
*/
void PostTaskHook (void);
/*
Calling points:
1- Before finished task move out of running state.
*/
void StartupHook (void);
/*
Calling points:
1- At the end of system initialization before scheduling is done.
*/
void ShutdownHook (StatusType Error);
/*
Calling points:
1- During shutdown.
*/
//review hooks macros when working on interrupts
#endif