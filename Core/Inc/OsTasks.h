#ifndef Headers_APIs_Headers_OsTasks_H
#define Headers_APIs_Headers_OsTasks_H



#include "Defines.h"


/**
 * @brief Public system function changes a task from suspended to ready state
 *
 * This public system function takes a task ID and changes a task from suspended to ready state.
 *
 * @param[in] TaskID The ID of the Task
 */
void OS_ActivateTask(TaskType TaskID);

/**
 * @brief Public system function changes a task from running to suspended state
 *
 * This public system function makes the current running task changes from running to suspended state.
 */
void OS_TerminateTask(void);
void OS_Schedule(void);
void OS_Insert(struct Task* newTask);
void OS_Delete(TaskType TaskID);
void OS_SortByPriority(void);

#endif
