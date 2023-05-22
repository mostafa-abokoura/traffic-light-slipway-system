/****************************************************************************** 
 * Module      : Application                                                  * 
 * File Name   : app.h                                                        * 
 * Description : Source file for Application module                           *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "app.h"
#include "trainalertsystem.h"
#include "trafficlightsystem.h"
#include "timer.h"

/****************************************************************************** 
 *                                                                            * 
 *                              Tasks Container                               * 
 *                                                                            * 
 ******************************************************************************/
task_t task[] =
{
	{
        .is_enabled = true,
		.pointer = &TrainAlertSystem_Handler
	},
	{
        .is_enabled = true,
		.pointer = &TrafficLightSystem_Handler
	},
	{
        .is_enabled = true,
		.pointer = &Timer_Handler
	}
};

/****************************************************************************** 
 *                                                                            * 
 *                              Global Variables                              * 
 *                                                                            * 
 ******************************************************************************/

/* Number of Tasks for scheduler */
const uint8_t g_TaskNumber = (sizeof(task) / sizeof(task_t));

/******************************************************************************
 * Name         : Task_Init                                                   *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Initializes tasks used in application.                      *
 ******************************************************************************/
void Task_Init(void)
{
	/* Initialize Traffic Light System. */
	TrafficLightSystem_Init();

	/* Initialize Train Alert System. */
	TrainAlertSystem_Init();
}
