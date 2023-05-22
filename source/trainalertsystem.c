/****************************************************************************** 
 * Module      : Train Alert System                                           *
 * File Name   : trainalertsystem.c                                           *
 * Description : Source file for Train Alert System module                    *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "trainalertsystem.h"

/******************************************************************************
 *                                                                            *
 *                              Static Variables                              *
 *                                                                            *
 ******************************************************************************/

/* Train Request Flag */
static bool g_train_safety_time = false;

/* Train Sensor Order */
static uint8_t g_ts_1;
static uint8_t g_ts_2;

/* Sensors flags */
static bool g_sensor_1;
static bool g_sensor_2;

/* Train Alert System invoke flag */
static bool g_trainalertsystem_invoke = false;

/****************************************************************************** 
 *                                                                            *
 *                            Function Prototypes                             *
 *                                                                            *
 ******************************************************************************/

/* Timer Event: Train Alert System Siren */
static void TrainAlertSystem_TimerEvent_SIREN(void);

/* Timer Event: Train Sensor Safety */
static void TrainAlertSystem_TimerEvent_TSS(void);

/* Timer Event: Train Alert LED */
static void TrainAlertSystem_TimerEvent_LED(void);

/* Train Alert System (What happens after a train exits) */
static void TrainAlertSystem_TrainExitSequence(void);

/* Train Alert System (Checking for train) */
static void TrainAlertSystem_CheckTrainExit(void);

/* Train Alert System (What happens in a fatal failure) */
static void TrainAlertSystem_SystemFailureHalt(void);

/* Train Alert System (What happens after a train enters) */
static void TrainAlertSystem_TrainEnterSequence(void);

/******************************************************************************
 * Name         : TrainAlertSystem_Init                                       *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Initializes train alert system.                             *
 ******************************************************************************/
void TrainAlertSystem_Init(void)
{
	TrainSensor_Init();					/* Initialize train sensors. */
	TrainAlertLED_Init();				/* Initialize train alert led. */

	/* Set timer callback */
	Timer_SetCallBack(TIMER_SIREN_CH, &TrainAlertSystem_TimerEvent_SIREN);
	Timer_SetCallBack(TIMER_TSS_CH, &TrainAlertSystem_TimerEvent_TSS);
	Timer_SetCallBack(TIMER_LED_CH, &TrainAlertSystem_TimerEvent_LED);
}

/******************************************************************************
 * Name         : TrainAlertSystem_TimerEvent_SIREN                           *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Timer Event - Train Alert System Siren                      *
 ******************************************************************************/
static void TrainAlertSystem_TimerEvent_SIREN(void)
{

}

/******************************************************************************
 * Name         : TrainAlertSystem_TimerEvent_TSS                             *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Timer Event - Train Sensor Safety.                          *
 ******************************************************************************/
static void TrainAlertSystem_TimerEvent_TSS(void)
{
	Timer_Stop(TIMER_TSS_CH);			/* Stop safety timer. */
	g_train_safety_time = true;			/* Set Train Safety Timer flag */
}

/******************************************************************************
 * Name         : TrainAlertSystem_TimerEvent_LED                             *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Timer Event - Train Alert LED.                              *
 ******************************************************************************/
static void TrainAlertSystem_TimerEvent_LED(void)
{
static bool blink = false;				/* Blinking flag */

	/* Check if train alert LED has blinked. */
	if (blink == false)
	{
		blink = true;					/* Set blink to true. */
		TrainAlertLED_Off();			/* Turn off train alert LED. */
	}
	else /* TRUE */
	{
		blink = false;					/* Set blink to false. */
		TrainAlertLED_On();				/* Turn on train alert LED. */
	}
}

/******************************************************************************
 * Name         : TrainAlertSystem_Handler                                    *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Train Alert System - Handler.                               *
 ******************************************************************************/
void TrainAlertSystem_Handler(void)
{
static bool invoke = false;				/* static invoke flag */

	/* Check if system is not invoked. */
	if (g_trainalertsystem_invoke == false)
	{
		/* Check if train sensors have reading. */
		if (TrainSensor_GetStatus(TS_RIGHT_CH) == TS_EXIST)
		{
			invoke = true;				/* Set invoke. */
			g_ts_1 = TS_RIGHT_CH;		/* Set TS1 to right. */
			g_ts_2 = TS_LEFT_CH;		/* Set TS2 to left. */
		}
		else if (TrainSensor_GetStatus(TS_LEFT_CH) == TS_EXIST)
		{
			invoke = true;				/* Set invoke flag. */
			g_ts_1 = TS_LEFT_CH;		/* Set TS1 to left. */
			g_ts_2 = TS_RIGHT_CH;		/* Set TS2 to right. */
		}
		else
		{
			//MISRA
		}

		if (invoke == true)
		{
			invoke = false;				/* Clear invoke flag. */

			/* Train Enter Sequence. */
			TrainAlertSystem_TrainEnterSequence();
		}
		else
		{
			//MISRA
		}
	}
	else /* TRAIN ALERT SYSTEM IS INVOKED BY AN INCOMING TRAIN */
	{
		/* Check train until it leaves. */
		TrainAlertSystem_CheckTrainExit();
	}
}

/******************************************************************************
 * Name         : TrainAlertSystem_CheckTrainExit                             *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Train Alert System - Check Train Exit.                      *
 ******************************************************************************/
static void TrainAlertSystem_CheckTrainExit(void)
{
	/* Check until sensor 1 has no reading. */
	if (g_sensor_1 == true)
	{
		/* Check if sensor 1 does not read. */
		if (TrainSensor_GetStatus(g_ts_1) == TS_LEAVE)
		{
			/* Clear sensor 1 flag. */
			g_sensor_1 = false;
		}
		else if (TrainSensor_GetStatus(g_ts_2) == TS_EXIST)
		{
			/* SYSTEM FATAL ERROR */
			TrainAlertSystem_SystemFailureHalt();
		}
		else /* TRAIN SENSOR STILL READS */
		{
			//MISRA
		}
	}
	else /* SENSOR #1 FALSE (SEQUENCE) */
	{
		/* Check if sensor 1 does not read and sensor 2 go through changes. */
		if (TrainSensor_GetStatus(g_ts_1) == TS_EXIST)
		{
			/* SYSTEM FATAL ERROR */
			TrainAlertSystem_SystemFailureHalt();
		}
		else if (g_sensor_2 == false)
		{
			/* Check if sensor 2 is reading. */
			if (TrainSensor_GetStatus(g_ts_2) == TS_EXIST)
			{
				/* Set sensor 2 flag. */
				g_sensor_2 = true;
			}
			else /* TRAIN SENSOR NO READING */
			{
				//MISRA
			}
		}
		else /* SENSOR #2 TRUE (SEQUENCE) */
		{
			/* Check if sensor 2 is not reading. */
			if (TrainSensor_GetStatus(g_ts_2) == TS_LEAVE)
			{
				/* Clear train system invoke flag. */
				g_trainalertsystem_invoke = false;

				/* Train Alert System changes at train exit. */
				TrainAlertSystem_TrainExitSequence();
			}
			else /* TRAIN SENSOR STILL READS */
			{
				//MISRA
			}
		}
	}
}

/******************************************************************************
 * Name         : TrainAlertSystem_TrainEnterSequence                         *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Train Alert System - Train Enter Sequence.                  *
 ******************************************************************************/
static void TrainAlertSystem_TrainEnterSequence(void)
{
	g_trainalertsystem_invoke = true;	/* Set invoke flag. */
	g_sensor_1 = true;					/* Set sensor 1 reading. */
	g_sensor_2 = false;					/* Clears sensor 2 reading. */

	/* Start Train System Safety Timer. */
	Timer_Reset(TIMER_TSS_CH);
	Timer_Start(TIMER_TSS_CH);

	/* Start Train Alert LED Timer. */
	Timer_Reset(TIMER_LED_CH);
	Timer_Start(TIMER_LED_CH);

	/* Change Traffic Light System at train enter. */
	TrafficLightSystem_TrainEnterChange();
}

/******************************************************************************
 * Name         : TrainAlertSystem_TrainExitSequence                          *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Train Alert System - Train Exit Sequence.                   *
 ******************************************************************************/
static void TrainAlertSystem_TrainExitSequence(void)
{
	/* Check train safety timer flag. */
	if (g_train_safety_time == false)
	{
		/* SYSTEM FATAL ERROR */
		TrainAlertSystem_SystemFailureHalt();
	}
	else /* FLAG TRUE */
	{
		/* Clear Train safety timer. */
		g_train_safety_time = false;
	}

	/* Stop Train System Safety Timer. */
	Timer_Reset(TIMER_TSS_CH);
	Timer_Stop(TIMER_TSS_CH);

	/* Stop Train Alert LED. */
	Timer_Reset(TIMER_LED_CH);
	Timer_Stop(TIMER_LED_CH);
	TrainAlertLED_Off();

	/* Change Traffic Light System at train exit. */
	TrafficLightSystem_TrainExitChange();
}

/******************************************************************************
 * Name         : TrainAlertSystem_SystemFailureHalt                          *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Train Alert System - System Failure Halt.                   *
 ******************************************************************************/
static void TrainAlertSystem_SystemFailureHalt(void)
{
	HaltLED_On();						/* Turn Halt LED on. */
	TrainAlertLED_On();					/* Turn Train Alert LED on. */

	/* Set traffic light mode to warning. */
	TrafficLightSystem_SetMode(TL_WARNING_MODE);

	Systick_Stop();						/* Stop SYSTICK. */
}
