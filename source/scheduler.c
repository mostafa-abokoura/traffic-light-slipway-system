/****************************************************************************** 
 * Module      : Scheduler                                                    * 
 * File Name   : scheduler.h                                                  * 
 * Description : Source file for scheduler module                             * 
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "scheduler.h"
#include "app.h"
#include "systick.h"
#include "cpuled.h"

/****************************************************************************** 
 *                                                                            * 
 *                         Static Function Prototypes                         * 
 *                                                                            * 
 ******************************************************************************/

/* Scheduler New Systick tick */
static void Scheduler_NewTimerTick(void);

/******************************************************************************
 * Name         : Scheduler_Init                                              *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Initializes scheduler.                                      *
 ******************************************************************************/
void Scheduler_Init(void)
{
	/* Initialize Utilization LED. */
	UtilizationLED_Init();

	/* Initialize Halt LED. */
	HaltLED_Init();

	/* Initialize tasks. */
	Task_Init();

    /* Pass function to be called every systick. */
	Systick_SetCallBack(&Scheduler_NewTimerTick);

    /* Starts systick timer */
	Systick_Start();
}

/******************************************************************************
 * Name         : Scheduler_NewTimerTick                                      *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : New Systick interrupt.                                      *
 ******************************************************************************/
void Scheduler_NewTimerTick(void)
{
uint8_t index;

	/* Turn on Utilization LED. */
	UtilizationLED_On();

	/* Loop over tasks and execute enabled tasks. */
	for (index=0; index < g_TaskNumber; ++index)
	{
		/* Check if task is enabled. */
		if (task[index].is_enabled)
		{
			/* Execute task. */
			task[index].pointer();
		}
	}

	/* Turn off Utilization LED. */
	UtilizationLED_Off();
}
