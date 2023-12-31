#include "Resources.h"
#include "Externs.h"

#include "Hooks.h"

#include "OsTasks.h"
// struct Task *OsTasksPCB[MAX_TASKS];
// TaskType RunningTaskID;
// uint8_t Queue_Size;
// struct Ready_List Ready_Queue;
// struct Ready_Entry Ready_Entries[MAX_TASKS];

// struct Task *OsTasksPCB[MAX_TASKS];
// struct Resource *OsResourcesPCB[MAX_RESOURCES];

ResourceType GlobalResID;

StatusType GetResource(ResourceType ResID)
{
    StatusType StatusMsg = E_OK;

    // validate that the reuqest is from and ISR

    if (ResID >= INVALID_RESOURCE)
    {

        StatusMsg = E_OS_ID;
    }
    else
    {
        if (OsResourcesPCB[ResID]->Resource_Owner != INVALID_TASK ||
            OsTasksPCB[RunningTaskID]->Priority > OsResourcesPCB[ResID]->Ceiling_Priority)
        {
            StatusMsg = E_OS_ACCESS; // return later
        }
        else
        {

            OsTasksPCB[RunningTaskID]->Priority = OsResourcesPCB[ResID]->Ceiling_Priority;
            OsResourcesPCB[ResID]->Resource_Owner = OsTasksPCB[RunningTaskID]->ID;
            OsResourcesPCB[ResID]->Prev_Resource = OsTasksPCB[RunningTaskID]->Last_Running_Resource;
            OsTasksPCB[RunningTaskID]->Last_Running_Resource = ResID;
            // OS_Schedule();
        }
    }
    if ((Active_Hooks & Errorhook) != 0 && StatusMsg != E_OK)
    {
        ErrorHook(StatusMsg);
    }
    return StatusMsg;
}

StatusType ReleaseResource(ResourceType ResID)
{
	GlobalResID = ResID;
	SAVECTX(16);
	ResID = GlobalResID;
    StatusType StatusMsg = E_OK;

    // validate that the reuqest is from and ISR

    // return to ERORR E_OS_ACESS LATER
    if (ResID >= INVALID_RESOURCE)
    {
        StatusMsg = E_OS_ID;
    }
    else
    {

        // t1(5) , T2(3)>> prioity 3
        if (OsResourcesPCB[ResID]->Resource_Owner == INVALID_TASK || (OsTasksPCB[RunningTaskID]->Last_Running_Resource != ResID && OsTasksPCB[OsResourcesPCB[ResID]->Resource_Owner]->State == RUNNING))
        { // get taks get a resource and then another taks
            StatusMsg = E_OS_NOFUNC;
        }
        // cieling priority alwayas takes hgihtes fromm all resource <<! configuration
        else
        {
            if (OsResourcesPCB[ResID]->Ceiling_Priority < OsTasksPCB[RunningTaskID]->Priority)
            { //
                StatusMsg = E_OS_ACCESS;
            }
            else
            {

                OsTasksPCB[RunningTaskID]->Last_Running_Resource = OsResourcesPCB[ResID]->Prev_Resource;

                // access the previous resource priority
                if (OsResourcesPCB[ResID]->Prev_Resource != INVALID_RESOURCE)
                {
                    OsTasksPCB[RunningTaskID]->Priority = OsResourcesPCB[OsResourcesPCB[ResID]->Prev_Resource]->Ceiling_Priority;
                }
                else
                {
                    OsTasksPCB[RunningTaskID]->Priority = OsTasksPCB[RunningTaskID]->CONFIG_PRIORITY;
                }

                OsResourcesPCB[ResID]->Prev_Resource = INVALID_RESOURCE;

                OsResourcesPCB[ResID]->Resource_Owner = INVALID_TASK;

                	OS_SortByPriority();
                	 OS_Schedule();

//                if (OsTasksPCB[RunningTaskID]->F_PREEM == TASK_FULL)
//                {
//                    OS_Schedule();
//                }
            }
        }
    }
    if ((Active_Hooks & Errorhook) != 0 && StatusMsg != E_OK)
    {
        ErrorHook(StatusMsg);
    }

    OsTasksPCB[PreTaskID]->retStatus = StatusMsg;
	if(Running_ISR_Count!=0)
			return E_OK;
    	if(OsTasksPCB[RunningTaskID]->first ==0)
    						{
    							OsTasksPCB[RunningTaskID]->first = 1;
    							LOADCTX_FIRST;
    						}
    						else
    						{
    							LOADCTX;
    						}
    return StatusMsg;
}
