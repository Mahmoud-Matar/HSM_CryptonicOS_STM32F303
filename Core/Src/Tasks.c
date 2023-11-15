#include "Tasks.h"
#include "Externs.h"
#include "OsTasks.h"
#include "Hooks.h"
#include <stdio.h>

TaskType GlobalID;
StatusType ActivateTask(TaskType TaskID)
{
	GlobalID = TaskID;
	SAVECTX(16);
	TaskID = GlobalID;
	StatusType StatusMsg = E_OK;
	if (TaskID >= MAX_TASKS) // max number of active tasks
	{

		// error msg
		StatusMsg = E_OS_ID;
		if ((Active_Hooks & Errorhook) != 0)
		{
			//ErrorHook(StatusMsg);
		}
		//return StatusMsg;
	}
	if ((OsTasksPCB[TaskID]->State == SUSPENDED) && (OsTasksPCB[TaskID]->Activation_Request != OsTasksPCB[TaskID]->Activation_Record)) // if task is suspended and activationrecord not max
	{
		OS_ActivateTask(TaskID);
		StatusMsg = E_OK;
		//return StatusMsg;
	}
	else
	{
		StatusMsg = E_OS_LIMIT;
		if ((Active_Hooks & Errorhook) != 0)
		{
			//ErrorHook(StatusMsg);
		}
	}
	//LOADCTX;
	return E_OK;
}

StatusType TerminateTask(void)
{
	// to be continued later, i.e to free reasourses
//	SAVECTX;
//	SYSTEM_STACK;
	StatusType StatusMsg = E_OK;

	if (OsTasksPCB[RunningTaskID]->Reasourses_Occupied != 0)
	{
		StatusMsg = E_OS_RESOURCE;
	}
	else
	{
		OS_TerminateTask();
	}
	// return calllevel error msg when called from ISR...
	if ((Active_Hooks & Errorhook) != 0 && StatusMsg != E_OK)
	{
		ErrorHook(StatusMsg);
	}
	return StatusMsg;
}

StatusType ChainTask(TaskType TaskID)
{
	StatusType StatusMsg = E_OK;

	// E_OS_CALLEVEL
	if (RunningTaskID >= INVALID_TASK) //  implement RunningTaskID later
	{
		StatusMsg = E_OS_ID;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}
		return StatusMsg;
	}
	if (OsTasksPCB[RunningTaskID]->Reasourses_Occupied != 0)
	{
		StatusMsg = E_OS_RESOURCE;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}
		return StatusMsg;
	}
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

	if (TaskID >= INVALID_TASK)
	{
		// error msg
		StatusMsg = E_OS_ID;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}
		return StatusMsg;
	}

	if (OsTasksPCB[TaskID]->State == SUSPENDED) // if task is suspended
	{
		if (OsTasksPCB[TaskID]->Activation_Request == OsTasksPCB[TaskID]->Activation_Record)
		{
			StatusMsg = E_OS_LIMIT;
			if ((Active_Hooks & Errorhook) != 0)
			{
				ErrorHook(StatusMsg);
			}
			return StatusMsg;
		}
		OS_ActivateTask(TaskID);
		StatusMsg = E_OK;
		return StatusMsg;
	}
	return StatusMsg;
}

StatusType Schedule(void)
{

	StatusType StatusMsg = E_OK;
	// check if running task exists
	// check if running task is preimpteable
	// check if readyqueue has priority higher than running task

	if (RunningTaskID == INVALID_TASK)
	{

		// feth highest priority task from ready queue
		RunningTaskID = Ready_Queue.Head->task->ID;

		Ready_Queue.Head->task->State = RUNNING;

		// context switch?????
		StatusMsg = E_OK;
	}
	else
	{
		if (OsTasksPCB[RunningTaskID]->F_PREEM == TASK_FULL)
		{
			if (Ready_Queue.Head->task->Priority > OsTasksPCB[RunningTaskID]->Priority)
			{

				OsTasksPCB[RunningTaskID]->State = READY;
				RunningTaskID = Ready_Queue.Head->task->ID;
				Ready_Queue.Head->task->State = RUNNING;
				// context switch
			}
			else // running task still highest prio
			{
				// do nothing
				StatusMsg = E_OK;
			}
		}
		else // non preinmteable running task
		{
			// do nothing
			StatusMsg = E_OK;
		}
	}

	return StatusMsg;
}

StatusType GetTaskID(TaskRefType TaskID)
{
	StatusType StatusMsg = E_OK;

	if (RunningTaskID == INVALID_TASK) //  implement RunningTaskID later
	{
		*TaskID = INVALID_TASK;
	}
	else
	{
		*TaskID = OsTasksPCB[RunningTaskID]->ID;
	}
	return StatusMsg;
}

StatusType GetTaskState(TaskType TaskID, TaskStateRefType State)
{
	StatusType StatusMsg = E_OK;

	if (TaskID >= MAX_TASKS)
	{
		StatusMsg = E_OS_ID;
	}
	else
	{
		*State = OsTasksPCB[TaskID]->State; // Note: implement PCB later
	}
	if ((Active_Hooks & Errorhook) != 0 && StatusMsg !=E_OK)
		{
			ErrorHook(StatusMsg);
		}
	return StatusMsg;
}
