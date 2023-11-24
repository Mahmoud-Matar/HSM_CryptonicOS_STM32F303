#include "OsTasks.h"
#include "Externs.h"

#include "Hooks.h"
#include "ContextSwitch.h"

#include <stdio.h>
// extern struct Task* OsTasksPCB[MAX_TASKS];
// extern TaskType RunningTaskID;
// extern uint8_t Queue_Size;
// extern struct Ready_List Ready_Queue;
// // need to be modified
// extern struct Ready_Entry Ready_Entries[MAX_TASKS];

void OS_ActivateTask(TaskType TaskID)
{
	// assign registers????
	OsTasksPCB[TaskID]->State = READY;
	OsTasksPCB[TaskID]->Activation_Record++;
	OsTasksPCB[TaskID]->Started = START_F;
	OS_Insert(OsTasksPCB[TaskID]);
	OS_Schedule();



	return;
}

void OS_TerminateTask(void)
{

	// Context_Switch();
	if ((Active_Hooks & PostTaskhook) != 0)
	{
		PostTaskHook();
	}
	if (OsTasksPCB[RunningTaskID]->Activation_Record == 1)
	{
		OsTasksPCB[RunningTaskID]->State = SUSPENDED;
		OS_Delete(RunningTaskID);
		RunningTaskID = INVALID_TASK;
	}
	else
	{
		OsTasksPCB[RunningTaskID]->Activation_Record--;
		OsTasksPCB[RunningTaskID]->State = READY;
	}

	OS_Schedule();
	// return calllevel error msg when called from ISR...
	return;
}

void OS_Schedule(void)
{
	if(Running_ISR_Count!=0)
		return;
	PreTaskID=RunningTaskID;
	if (RunningTaskID == INVALID_TASK)
	{
		Ready_Queue.Head->task->Started = START_T;
		RunningTaskID = Ready_Queue.Head->task->ID;
		Ready_Queue.Head->task->State = RUNNING;

//		LoadContextFirstTime(RunningTaskID);

		if(OsTasksPCB[RunningTaskID]->first ==0)
					{
						OsTasksPCB[RunningTaskID]->first = 1;

						LOADCTX_FIRST;
					}
					else
					{
						LOADCTX;
					}

		return;
	}
	else if (OsTasksPCB[RunningTaskID]->F_PREEM == TASK_FULL)
	{
		if (Ready_Queue.Head->task->Priority > OsTasksPCB[RunningTaskID]->Priority)
		{
			if ((Active_Hooks & PreTaskhook) != 0 && OsTasksPCB[RunningTaskID]->Started != START_T)
			{
				PreTaskHook();
			}
			OsTasksPCB[RunningTaskID]->State = READY;
		//	SaveContext(RunningTaskID);
//			ContextSwitch(Ready_Queue.Head->task->ID);
			RunningTaskID = Ready_Queue.Head->task->ID;
			Ready_Queue.Head->task->State = RUNNING;
//			if(OsTasksPCB[RunningTaskID]->first ==0)
//			{
//				OsTasksPCB[RunningTaskID]->first = 1;
//				//LOADCTX_FIRST;
//			}
//			else
//			{
//			//	LOADCTX;
//			}

//			if(OsTasksPCB[RunningTaskID]->first ==0)
//			{
//				OsTasksPCB[RunningTaskID]->first = 1;
//				//LoadContextFirstTime(RunningTaskID);
//			}
//			else
//			{
//				//LoadContext(RunningTaskID);
//			}
			// context switch
			// assign pc to task
			// save context for current task in stack
			// load context for next task from stack
			// change pc
		}
//		if (Ready_Queue.Head->task->Priority == OsTasksPCB[RunningTaskID]->Priority)
//		{
//			LOADCTX;
//		}
	}
return;
}


void OS_Insert(struct Task *newTask)
{
	Ready_Entries[newTask->ID] = (struct Ready_Entry){newTask, NULL, NULL};

	if (Ready_Queue.Queue_Size == 0)
	{

		Ready_Queue.Head = &Ready_Entries[newTask->ID];
		Ready_Queue.Tail = Ready_Queue.Head;
	}
	else
	{
		struct Ready_Entry *Current = Ready_Queue.Head;
		while (Current != NULL)
		{
			if (newTask->Priority > Current->task->Priority)
			{
				if (Ready_Queue.Head == Current)
				{
					Ready_Queue.Head = &Ready_Entries[newTask->ID];
				}
				else
				{
					Ready_Entries[newTask->ID].Prev = Current->Prev;
					Current->Prev->Next = &Ready_Entries[newTask->ID];
				}
				Ready_Entries[newTask->ID].Next = Current;
				Current->Prev = &Ready_Entries[newTask->ID];
				break;
			}
			if (Current->Next == NULL)
			{
				Current->Next = &Ready_Entries[newTask->ID];
				Ready_Entries[newTask->ID].Prev = Current;

				Ready_Queue.Tail = &Ready_Entries[newTask->ID];
				break;
			}
			Current = Current->Next;
		}
	}
	Ready_Queue.Queue_Size++;
}

void OS_Delete(TaskType TaskID)
{
	// free registers????
	struct Ready_Entry *Current = Ready_Queue.Head;

	while (Current != NULL)
	{
		if (Current->task->ID == TaskID)
		{

			if (Ready_Queue.Head == Current)
			{
				Ready_Queue.Head = Current->Next;
				if (Ready_Queue.Head != NULL)
				{
					Ready_Queue.Head->Prev = NULL;
				}
			}
			else
			{
				Current->Prev->Next = Current->Next;
			}
			if (Ready_Queue.Tail == Current)
			{
				Ready_Queue.Tail = Current->Prev;
				if (Ready_Queue.Tail != NULL)
				{
					Ready_Queue.Tail->Next = NULL;
				}
			}
			else
			{
				Current->Next->Prev = Current->Prev;
			}
			Ready_Queue.Queue_Size--;
			break;
		}
		Current = Current->Next;
	}
}

void OS_SortByPriority(void) {
    // Implement your sorting logic here
    // You may need to modify the data structures and their relationships accordingly

    // For example, you can use a simple bubble sort algorithm for demonstration purposes
    int swapped;
    struct Ready_Entry *ptr1;
    struct Ready_Entry *lptr = NULL;

    // Checking for empty list
    if (Ready_Queue.Head == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr1 = Ready_Queue.Head;

        while (ptr1->Next != lptr) {
            if (ptr1->task->Priority < ptr1->Next->task->Priority) {
                // Swap the tasks
                struct Task *temp = ptr1->task;
                ptr1->task = ptr1->Next->task;
                ptr1->Next->task = temp;

                swapped = 1;
            }
            ptr1 = ptr1->Next;
        }
        lptr = ptr1;
    } while (swapped);
}
