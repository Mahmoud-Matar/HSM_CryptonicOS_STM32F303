#ifndef Generated
#define Generated


#include <stdio.h>
#include "Defines.h"
#include "TaskConfig.h"
#include "AlarmsConfig.h"
#include "ResourceConfig.h"
#include "OSExecutionControlConfig.h"

struct ISR* ISRPCB[MAX_ISRs];
ISRType Running_ISR_ID;

TaskType RunningTaskID=INVALID_TASK;
TaskType PreTaskID = INVALID_TASK;
uint8_t Queue_Size;
struct Ready_List Ready_Queue;
struct Ready_Entry Ready_Entries[MAX_TASKS];
AppModeType ActiveAppMode;
uint8_t Active_Hooks = INVALID_HOOK;
ISRType Active_ISR_Disable_Type = ISR_Disable_Type_NoDisable;
uint8_t ISR_Suspend_Counter = 0;



#define Event1 1

#define Event2 2

#define Event3 4






#define R1 0
struct Resource resource0={
    .Res_ID = 0,
    .Ceiling_Priority = 7,
    .Linked_Resource = 0,
    .Resource_Property = 0,
    .Resource_Owner = INVALID_TASK,
    .Prev_Resource = INVALID_RESOURCE
};

#define R2 1
struct Resource resource1={
    .Res_ID = 1,
    .Ceiling_Priority = 5,
    .Linked_Resource = 0,
    .Resource_Property = 0,
    .Resource_Owner = INVALID_TASK,
    .Prev_Resource = INVALID_RESOURCE
};



struct Resource *OsResourcesPCB[MAX_RESOURCES]={
    
    &resource0,
    
    &resource1,
    
};


#define Task1 0
void Task1Func();
struct Task task0 = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &Task1Func,
    .current_pc = &Task1Func,
    .ID = 0,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 4,
    .Priority = 4,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 1,
    .EventMask = { (Event1 | Event2),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};

#define Task2 1
void Task2Func();
struct Task task1 = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &Task2Func,
    .current_pc = &Task2Func,
    .ID = 1,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 6,
    .Priority = 6,
    .F_PREEM = TASK_NON,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 0,
    .EventMask = { (Event1 | Event2 | Event3),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};

#define Task3 2
void Task3Func();
struct Task task2 = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &Task3Func,
    .current_pc = &Task3Func,
    .ID = 2,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 1,
    .Priority = 1,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 1,
    .EventMask = { (Event3|Event2),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};


void IdleFunc();
struct Task idle = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &IdleFunc,
    .current_pc = &IdleFunc,
    .ID = IDLE_TASK,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 0,
    .Priority = 0,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 200,
    .Reasourses_Occupied = 0,
    .Extended = 0,
    .EventMask = {0,0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = INVALID_RESOURCE
};
void USART2_Func();
struct ISR isr0 = {
		.ID = 38,
		.Priority = 5,
		.Category = 2,
		.Needed_Resources = INVALID_RESOURCE,
		.Prev_Resource = INVALID_RESOURCE

};
struct Task* OsTasksPCB[MAX_TASKS]={
    
    &task0,
    
    &task1,
    
    &task2,
    
    [MAX_TASKS-1]=&idle
};


#endif
