#ifndef Headers_APIs_Headers_ContextSwitch_H
#define Headers_APIs_Headers_ContextSwitch_H



#include "Defines.h"

void SaveContext(TaskType Task);
void LoadContextFirstTime(TaskType TaskID);
void LoadContext(TaskType Task);

void * rd_proc_stack_ptr(void);

void * wr_proc_stack_ptr(void);
#endif
