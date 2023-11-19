#ifndef Headers_APIs_Headers_Defines_H
#define Headers_APIs_Headers_Defines_H


#include "stdint.h"
#include "TaskConfig.h"
#include "OSExecutionControlConfig.h"
#include "ResourceConfig.h"
#include "AlarmsConfig.h"

#define INVALID_TASK MAX_TASKS

#define RUNNING 1
#define READY 2
#define WAITING 3
#define SUSPENDED 4

#define TASK_NON 0
#define TASK_FULL 1

#define E_OK 0
#define E_OS_ACCESS 1
#define E_OS_CALLEVEL 2
#define E_OS_ID 3
#define E_OS_LIMIT 4
#define E_OS_NOFUNC 5
#define E_OS_RESOURCE 6
#define E_OS_STATE 7
#define E_OS_VALUE 8

#define START_F 0
#define START_T 1

#define INVALID_RESOURCE MAX_RESOURCES



#define OSDEFAULTAPPMODE 0
#define INVALID_APPMODE 255

#define Errorhook    0b00000001
#define PreTaskhook  0b00000010
#define PostTaskhook 0b00000100
#define Startuphook  0b00001000
#define Shutdownhook 0b00010000
#define INVALID_HOOK 255




//#define SAVECTX __asm volatile(	"ADD sp, #16;" "PUSH {lr};"  "MOV  %0, sp \n\t" :"=r" (OsTasksPCB[RunningTaskID]->sp) )
#define SAVECTX(indent) __asm volatile(	"ADD sp, %1;" "PUSH {lr};"  "MOV  %0, sp \n\t"  "SUB r7 , #4"  :"=r" (OsTasksPCB[RunningTaskID]->sp) :"r" (indent) )
#define LOADCTX __asm volatile( "MOV sp, %0 \n\t" "POP {lr};" "ADD sp,#8;" "MOV r7,sp;" "MOV r0,%1;" "BX lr;": : "r" (OsTasksPCB[RunningTaskID]->sp),"r" (OsTasksPCB[RunningTaskID]->retStatus) : "memory");
#define LOADCTX_FIRST __asm volatile( "MOV sp, %0 \n\t" "BX %1;": : "r" (&OsTasksPCB[RunningTaskID]->sp), "r"(OsTasksPCB[RunningTaskID]->address) : "memory");
#define SYSTEM_STACK __asm volatile( "MOV sp, %0 \n\t" "MOV r7, %0 \n\t": : "r" (SYS_SP) : "memory");
#define CS_ON  __asm volatile( "SVC #0;");
#define CS_OFF __asm volatile( "CPSIE i;" "MRS r10, CONTROL;" "ORR r10, r10, #1;" "MSR CONTROL, r10;");
#define USER_THREAD __asm volatile( "MRS r10, CONTROL;" "ORR r10, r10, #1;" "MSR CONTROL, r10;");



typedef uint8_t StatusType;
typedef uint8_t TaskType;
typedef uint8_t *TaskRefType;
typedef uint8_t TaskStateType;
typedef uint8_t *TaskStateRefType;

typedef uint64_t EventMaskType;
typedef uint64_t *EventMaskRefType;

typedef uint8_t ResourceType;

typedef uint8_t AppModeType;


struct Event
{
	uint64_t Configured_Events; // 64 bit configured events
	uint64_t Event_Waiting; // 64 bit event id
	uint64_t Event_State; // 64 bit event state

};
struct Resource
{
	ResourceType Res_ID;
	uint8_t Ceiling_Priority;

	ResourceType *Linked_Resource ;
	ResourceType Resource_Property;

	TaskType Resource_Owner;
	ResourceType Prev_Resource;

};


// ALARMS //
typedef uint32_t TickType;
typedef TickType* TickRefType;
typedef struct {
    TickType maxallowedvalue; // Maximum possible allowed count value in ticks
    TickType ticksperbase;   // Number of ticks required to reach a counter-specific unit
    TickType mincycle;       // Smallest allowed value for the cycle-parameter of SetRelAlarm/SetAbsAlarm (only for systems with extended status)
} AlarmBaseType;
typedef AlarmBaseType* AlarmBaseRefType;
typedef struct {
    TickType alarmValue;    // The value at which the alarm will trigger
    AlarmBaseRefType base;  // Reference to the AlarmBaseType
	TickType cycle;         // The value of the cycle parameter of SetRelAlarm/SetAbsAlarm
} AlarmType;
// END ALARMS // 

//ISRs//

#define INVALID_ISR 255

typedef uint32_t ISRType;

//ISRs//

struct TaskContext
{
    uint32_t r[16];  // r0 to r12 registers
//    uint32_t lr;     // link register (r14)
//    uint32_t pc;

};


//sp = ostaskspcb[taskid]->ctx
struct Task
{
	//struct TaskContext ctx;
	uint32_t stack[100];
	uint32_t* sp;
	uint8_t first;
	void (*address)(void); //address of the task in memory
	uint32_t current_pc; //no remove later
	TaskType ID; //id of task
	TaskStateType State; //current state of task
	uint8_t CONFIG_PRIORITY; //configured priority of task  CONST
	uint8_t Priority; //current priority of task
	uint8_t F_PREEM; // flag of preemetivety 0 or 1  CONST
	uint8_t Preeimpted; // flag wether it was preimpted or not
	uint8_t Activation_Record; // activation record of task
	uint8_t Activation_Request; // request record of task
	uint8_t Reasourses_Occupied; //reimplement later using array CONST
	// add function pointer refrence to task function

	// for events
	uint8_t Extended;			   // flag wether it is extended or basic
	//EventMaskType *Waiting_Events; // array of events that the task is waiting for
	struct Event EventMask;
	// for resoruces
	ResourceType Last_Running_Resource; // Current/Last assigned reso

	struct Resource *Needed_Resources[MAX_RESOURCES];		// refrence to Resources needed by Task


	void* SP; //Stack_Pointer
    uint8_t Started;
    StatusType retStatus;
	// BAAAD WARNING FROM HERE here 

};
struct Ready_Entry
{ // Is for an array holding all entries of the ready list
	struct Task *task;
	struct Ready_Entry *Prev;
	struct Ready_Entry *Next;
};

struct Ready_List
{ // Is for size and head/tail pointers to navigate the ready entries
	uint8_t Queue_Size;
	struct Ready_Entry *Head;
	struct Ready_Entry *Tail;
};

struct ISR
{

	ISRType ID; //id of task
	uint8_t Priority; //current priority of task
	ISRType Category;

	struct Resource *Needed_Resources[MAX_RESOURCES];


	ResourceType Prev_Resource;

};


 #endif
