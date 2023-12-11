#include "OSExecutionControl.h"
#include "Externs.h"
#include "Tasks.h"
// #include "../../Headers/APIs_Headers/Globels.h"
// #include "Tasks.c"
AppModeType GetActiveApplicationMode(void)
{
  return ActiveAppMode;
}

void StartOS (AppModeType Mode)
{
  // Disable Interaputs
  // Check for Auto Starts and appmode
if ((Active_Hooks & Startuphook) != 0)
	{
		StartupHook();
	}
  if(Mode == OSDEFAULTAPPMODE)
  {
	  OS_ActivateTask(199);


  }
}



void ShutDownOS (StatusType Error)
{
  if ((Active_Hooks & Shutdownhook) != 0)
	{
		ShutdownHook();
	}
  //hooks
  for(;;)
  {
    
  }
}
