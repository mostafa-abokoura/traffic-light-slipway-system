/****************************************************************************** 
 * Module      : Timer                                                        *
 * File Name   : timer.c                                                      *
 * Description : Source file for software timer module                        *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "timer.h"

/****************************************************************************** 
 *                                                                            *
 *                            Function Prototypes                             *
 *                                                                            *
 ******************************************************************************/

/* Ticks a software timer if enabled. */
static void Timer_Tick(uint8_t channel);

/* Triggers a software timer. */
static void Timer_Trigger(uint8_t channel);

/******************************************************************************
 *                                                                            *
 *                               Configuration                                *
 *                                                                            *
 ******************************************************************************/

/* Software timer channels configuration */
static timer_ch timer[] =
{
    { /* Channel 0: Siren Timer */
    	.status = TIMER_DISABLED,
    	.alarm 	= CALCULATE_TIME(TIMER_SIREN_TIME),
		.ticks  = INITIALIZED_TO_ZERO,
		.fn_ptr = NULL_PTR
    },
    { /* Channel 1: Traffic Light Timer 1 */
		.status = TIMER_DISABLED,
		.alarm 	= CALCULATE_TIME(TIMER_TL1_TIME),
		.ticks  = INITIALIZED_TO_ZERO,
		.fn_ptr = NULL_PTR
    },
    { /* Channel 2: Traffic Light Timer 2 */
		.status = TIMER_DISABLED,
		.alarm 	= CALCULATE_TIME(TIMER_TL2_TIME),
		.ticks  = INITIALIZED_TO_ZERO,
		.fn_ptr = NULL_PTR
    },
	{ /* Channel 3: PD Safety Timer */
		.status = TIMER_DISABLED,
		.alarm 	= CALCULATE_TIME(TIMER_PDS_TIME),
		.ticks  = INITIALIZED_TO_ZERO,
		.fn_ptr = NULL_PTR
	},
    { /* Channel 4: Train Sensor Safety Timer */
		.status = TIMER_DISABLED,
		.alarm 	= CALCULATE_TIME(TIMER_TSS_TIME),
		.ticks  = INITIALIZED_TO_ZERO,
		.fn_ptr = NULL_PTR
	},
    { /* Channel 5: Traffic Light Blink Timer */
		.status = TIMER_DISABLED,
		.alarm 	= CALCULATE_TIME(TIMER_TLB_TIME),
		.ticks  = INITIALIZED_TO_ZERO,
		.fn_ptr = NULL_PTR
	},
    { /* Channel 6: Train Alert LED */
		.status = TIMER_DISABLED,
		.alarm 	= CALCULATE_TIME(TIMER_LED_TIME),
		.ticks  = INITIALIZED_TO_ZERO,
		.fn_ptr = NULL_PTR
	}
};

/******************************************************************************
 * Name         : Timer_Handler                                               *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Handles all software timers at once and at ease.            *
 ******************************************************************************/
void Timer_Handler(void)
{
uint8_t index;							/* Timer index */

	/* Loop over timer array to tick all enabled timers. */
	for (index=0; index<(sizeof(timer)/sizeof(timer_ch)); ++index)
	{
		Timer_Tick(index);				/* Tick a timer if enabled. */
	}
}

/******************************************************************************
 * Name         : Timer_Start                                                 *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Starts a software timer.                                    *
 ******************************************************************************/
void Timer_Start(uint8_t channel)
{
	/* Enable timer. */
	timer[channel].status = TIMER_ENABLED;
}

/******************************************************************************
 * Name         : Timer_Stop                                                  *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Stops a software timer.                                     *
 ******************************************************************************/
void Timer_Stop(uint8_t channel)
{
	/* Disable timer. */
	timer[channel].status = TIMER_DISABLED;
}

/******************************************************************************
 * Name         : Timer_Reset                                                 *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Resets a software timer.                                    *
 ******************************************************************************/
void Timer_Reset(uint8_t channel)
{
	/* Reset timer. */
	timer[channel].ticks = INITIALIZED_TO_ZERO;
}

/******************************************************************************
 * Name         : Timer_GetStatus                                             *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : boolean                                                     *
 * Description  : Gets a software timer status.                               *
 ******************************************************************************/
bool Timer_GetStatus(uint8_t channel)
{
	/* Return timer status. */
	return timer[channel].status;
}

/******************************************************************************
 * Name         : Timer_SetCallBack                                           *
 * Inputs       : channel & function pointer                                  *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Sets callback function of a software timer.                 *
 ******************************************************************************/
void Timer_SetCallBack(uint8_t channel, void(*fn_ptr)(void))
{
	/* Set callback function of a software timer. */
	timer[channel].fn_ptr = fn_ptr;
}

/******************************************************************************
 * Name         : Timer_Trigger                                               *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Triggers a software timer.                                  *
 ******************************************************************************/
static void Timer_Trigger(uint8_t channel)
{
	/* Execute callback function of a software timer. */
	(*timer[channel].fn_ptr)();
}

/******************************************************************************
 * Name         : Timer_Tick                                                  *
 * Inputs       : channel                                                     * 
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Increment a software timer.                                 *
 ******************************************************************************/
static void Timer_Tick(uint8_t channel)
{
	/* Check if Timer is enabled. */
	if (timer[channel].status == TIMER_ENABLED)
	{
		/* Increment timer ticks by 1. */
		timer[channel].ticks += 1;

		/* Check if ticks reached alarm ticks. */
		if (timer[channel].alarm == timer[channel].ticks)
		{
			Timer_Trigger(channel);		/* Software timer is triggered. */
			Timer_Reset(channel);		/* Software timer is reseted. */
		}
	}
	else /* TIMER IS DISABLED */
	{
		//MISRA
	}
}
