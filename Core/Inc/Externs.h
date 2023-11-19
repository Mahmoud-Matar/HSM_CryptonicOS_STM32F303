
#ifndef Headers_APIs_Headers_Globels_H
#define Headers_APIs_Headers_Globels_H
#include "Defines.h"
// #include "../../GeneratedFiles/OSGenerated.h"
#include "stdint.h"
//Tasks Things

// Tasks Things
extern struct Task* OsTasksPCB[MAX_TASKS];
extern uint8_t Active_Hooks;
extern TaskType RunningTaskID;
extern ISRType Running_ISR_ID;


extern TaskType PreTaskID;
extern uint8_t Queue_Size;

extern struct Ready_List Ready_Queue;
extern struct Ready_Entry Ready_Entries[MAX_TASKS];
//OS Execution Control Things
extern AppModeType ActiveAppMode;
// Resource Things
// name resource ?
extern struct Resource *OsResourcesPCB[MAX_RESOURCES];



#endif
