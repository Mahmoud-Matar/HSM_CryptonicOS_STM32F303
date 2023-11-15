#include "Externs.h"
#include "ContextSwitch.h"
#include <stddef.h>




void LoadContextFirstTime(TaskType TaskID)
{





}

void LoadContext(TaskType TaskID)
{
//	 struct TaskContext ctx = OsTasksPCB[TaskID]->ctx;
//
//	__asm volatile (
//	            // Load general-purpose registers r0-r12 from local variables
//	            "mov r0, %[r0_val];"
//	            "mov r1, %[r1_val];"
//	            "mov r2, %[r2_val];"
//	            "mov r3, %[r3_val];"
//	            "mov r4, %[r4_val];"
//	            "mov r5, %[r5_val];"
//	            "mov r6, %[r6_val];"
//	            "mov r7, %[r7_val];"
//	            "mov r8, %[r8_val];"
//	            "mov r9, %[r9_val];"
//	            // ... repeat for r2-r12 ...
//
//	            // Load lr (r14) and pc (r15) from local variables
//	            "mov lr, %[lr_val];"
//	            "mov pc, %[pc_val];"
//
//			 	 	 : [r0_val] "=r" (ctx.r[0]), [r1_val] "=r" (ctx.r[1]), [r2_val] "=r" (ctx.r[2]),[r3_val] "=r" (ctx.r[3]), [r4_val] "=r" (ctx.r[4]), [r5_val] "=r" (ctx.r[5]), [r6_val] "=r" (ctx.r[6]),[r7_val] "=r" (ctx.r[7]),[r8_val] "=r" (ctx.r[8]), [r9_val] "=r" (ctx.r[9]),  /* repeat for r2-r12 */ [lr_val] "=r" (ctx.lr), [pc_val] "=r" (ctx.pc)
//			        :
//			        : "memory"
//	        );
//
//	LoadContextFirstTime( TaskID);
//
//	uint32_t sp = OsTasksPCB[TaskID]->stack[98]+4;
//
//		 __asm volatile(
//		 			 "mov sp, %r0;"
//				 	 ""
//		 			 :
//		 			 : "r" (sp)
//		 			 : "memory"
//		 			 );
//		 __asm volatile (
////		        "MOV R0, %0\n\t"
//				 "MOV r15 ,%0\n\t"// Move the address to jump to into register R0
////		               // Branch to the address in R0 (task1.address)
////				 "LDR R1,[%0]"
//		        :
//		        : "r" (OsTasksPCB[TaskID]->current_pc)
//		        : "memory"s
//		    );
//	__asm volatile(
//
//				"PUSH {r0-r12};"
//
//			);


//
//	    __asm volatile(
//	        "MOV %0, LR;"  // Save the current LR value
//	        : "=r" (lr_value)
//	    );

//	  register uint32_t sp_value;
//
//	    __asm volatile(
//	   	  	        "MOV sp, %0;"  // Save the current LR value
//	   	    		  :
//	   	    		  : "r" (OsTasksPCB[TaskID]->sp+2)
//	   	              : "memory"
//	   	  	    );
//	    __asm volatile(
//
//	    			"POP {r7,lr};"
//
//	    		);
//	    __asm volatile(
//
//	   	   	  	        "MOV %0, r7;"  // Save the current LR value
//						:"=r" (sp_value)
//	   	   	  	    );
//	    __asm volatile(
//
//	   	   	   	  	        "MOV r7,%0;"  // Save the current LR value
//	   				:
//					:"r" (sp_value-16)
//	   	:"memory"
//	    );
//	    return;
//	    __asm volatile(
//	    		  "BLX %0;"
//	  	        :
//	  	        : "r" (OsTasksPCB[TaskID]->current_pc)
//	  	        : "memory"
//	  	    );
//	    __asm volatile(
//	        "MOV LR, %0;"  // Restore the LR value
//	        :
//	        : "r" (lr_value)
//	    );
//
}

void SaveContext(TaskType TaskID)
{




}




void * rd_proc_stack_ptr(void){
  void * result=NULL;
  __asm volatile ("MRS %0, psp\n\t"   
     : "=r" (result) );
  return result;
}

void * wr_proc_stack_ptr(void){
  void * result=NULL;
  __asm volatile ("MSR psp,%0 \n\t"   
      : "=r" (result) );
  return result;
}
