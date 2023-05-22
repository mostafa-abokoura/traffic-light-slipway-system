/****************************************************************************** 
 * Module      : Traffic Light System                                         *
 * File Name   : trafficlightsystem.c                                         *
 * Description : Source file for Traffic Light System module                  *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "trafficlightsystem.h"

/******************************************************************************
 *                                                                            *
 *                              Static Variables                              *
 *                                                                            *
 ******************************************************************************/

/* PD Request Flag */
static bool g_pd_request = false;

/* Train Exist Flag */
static bool g_train_exist = false;

/* PD Mode activation flag */
static bool g_pd_activated = false;

/* Saved timer channel */
static uint8_t g_saved_timer_ch;

/* Saved traffic light mode */
static uint8_t g_saved_mode;

/****************************************************************************** 
 *                                                                            *
 *                            Function Prototypes                             *
 *                                                                            *
 ******************************************************************************/

/* Timer Event: Traffic Light #1 */
static void TrafficLightSystem_TimerEvent_TL1(void);

/* Timer Event: Traffic Light #2 */
static void TrafficLightSystem_TimerEvent_TL2(void);

/* Timer Event: PD Safety */
static void TrafficLightSystem_TimerEvent_PDS(void);

/* Timer Event: Traffic Light Blink */
static void TrafficLightSystem_TimerEvent_TLB(void);

/* PD Button is pressed */
static void TrafficLightSystem_PDButtonIsPressed(void);

/* Check PD Request */
static void TrafficLightSystem_PDRequest(uint8_t next_timer_ch);

/******************************************************************************
 * Name         : TrafficLightSystem_Init                                     *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Initializes traffic light system.                           *
 ******************************************************************************/
void TrafficLightSystem_Init(void)
{
	/* Initializes PD buttons. */
	PD_Init();

	/* Initializes Traffic lights. */
	TrafficLight_Init(TL_NORTH_CH);
	TrafficLight_Init(TL_EAST_CH);
	TrafficLight_Init(TL_WEST_CH);
	TrafficLight_Init(TL_SOUTH_CH);

	/* Set Initial Traffic Light colors. */
	TrafficLightSystem_SetMode(TL_DEFAULT_MODE);

	/* Set timers callback functions. */
	Timer_SetCallBack(TIMER_TL1_CH, &TrafficLightSystem_TimerEvent_TL1);
	Timer_SetCallBack(TIMER_TL2_CH, &TrafficLightSystem_TimerEvent_TL2);
	Timer_SetCallBack(TIMER_PDS_CH, &TrafficLightSystem_TimerEvent_PDS);
	Timer_SetCallBack(TIMER_TLB_CH, &TrafficLightSystem_TimerEvent_TLB);

	/* Enable 1st Traffic light Timer and save current. */
	Timer_Start(TIMER_TL1_CH);
}

/******************************************************************************
 * Name         : TrafficLightSystem_Handler                                  *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Traffic Light System - Handler.                             *
 ******************************************************************************/
void TrafficLightSystem_Handler(void)
{
	/* Check if any PD button is pressed. */
	if (PD_GetStatus() == PD_PRESSED)
	{
		/* Handle PD situation. */
		TrafficLightSystem_PDButtonIsPressed();
	}
	else
	{
		//MISRA
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_SetColor                                 *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Sets all traffic light colors at once.                      *
 ******************************************************************************/
void TrafficLightSystem_SetMode(uint8_t mode)
{
uint8_t traffic_ns;							/* North & South pair */
uint8_t traffic_ew;							/* East & West pair */

	/* Detect mode. */
	switch (mode)
	{
	case TL_DEFAULT_MODE:
		traffic_ns = TL_NS_DEFAULT_COLOR;	/* Set NS pair to default. */
		traffic_ew = TL_EW_DEFAULT_COLOR;	/* Set EW pair to default. */
	break;

	case TL_REVERSE_MODE:
		traffic_ns = TL_NS_REVERSE_COLOR;	/* Set NS pair to reversed. */
		traffic_ew = TL_EW_REVERSE_COLOR;	/* Set EW pair to reversed. */
	break;

	case TL_WARNING_MODE:
		traffic_ns = COLOR_RED;				/* Set NS pair to Red. */
		traffic_ew = COLOR_RED;				/* Set EW pair to Red. */
	break;

	case TL_NO_COLOR_MODE:
		traffic_ns = COLOR_NONE;			/* Turn off NS pair. */
		traffic_ew = COLOR_NONE;			/* Turn off EW pair. */
	break;

	default: /* UNKNOWN MODE */
		return;									/* Return from ERROR. */
	break;
	}

	/* Set traffic light colors. */
	TrafficLight_SetColor(TL_NORTH_CH, traffic_ns);
	TrafficLight_SetColor(TL_EAST_CH, traffic_ew);
	TrafficLight_SetColor(TL_WEST_CH, traffic_ew);
	TrafficLight_SetColor(TL_SOUTH_CH, traffic_ns);
}

/******************************************************************************
 * Name         : TrafficLightSystem_TrainEnterChange                         *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Save current traffic light data when train enters.          *
 ******************************************************************************/
void TrafficLightSystem_TrainEnterChange(void)
{
	/* Set train exist flag. */
	g_train_exist = true;

	/* Set Traffic Light Mode to warning. */
	TrafficLightSystem_SetMode(TL_WARNING_MODE);

	/* Start Traffic Light Blink Timer. */
	Timer_Reset(TIMER_TLB_CH);			/* Reset timer channel. */
	Timer_Start(TIMER_TLB_CH);			/* Start timer channel. */

	/* Check if PD is not activated. */
	if (g_pd_activated == false)
	{
		if (g_pd_request == true)
		{
			Timer_Start(TIMER_PDS_CH);	/* Enable PD Safety Timer. */
		}

		/* Check which timer is enabled. */
		if (Timer_GetStatus(TIMER_TL1_CH) == TIMER_ENABLED)
		{
			/* Save timer channel to timer 1. */
			g_saved_timer_ch = TIMER_TL1_CH;
		}
		else if (Timer_GetStatus(TIMER_TL2_CH) == TIMER_ENABLED)
		{
			/* Save timer channel to timer 2. */
			g_saved_timer_ch = TIMER_TL2_CH;
		}
		else
		{
			//MISRA
		}

		/* Stop both timers. */
		Timer_Stop(TIMER_TL1_CH);
		Timer_Stop(TIMER_TL2_CH);

		/* Check saved timer channel to determine current mode. */
		if (g_saved_timer_ch == TIMER_TL1_CH)
		{
			/* Save mode to default mode. */
			g_saved_mode = TL_DEFAULT_MODE;
		}
		else /* TIMER 2 */
		{
			/* Save mode to reverse mode. */
			g_saved_mode = TL_REVERSE_MODE;
		}
	}
	else
	{
		//MISRA
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_TrainExitChange                          *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Retrieve saved data to traffic light when train exits.      *
 ******************************************************************************/
void TrafficLightSystem_TrainExitChange(void)
{
	/* Clear train exist flag. */
	g_train_exist = false;

	/* Traffic Light Blink Timer. */
	Timer_Reset(TIMER_TLB_CH);			/* Reset timer channel. */
	Timer_Stop(TIMER_TLB_CH);			/* Start timer channel. */

	/* Check if PD is not activated. */
	if (g_pd_activated == false)
	{
		/* Start saved timer. */
		Timer_Start(g_saved_timer_ch);

		/* Set saved mode. */
		TrafficLightSystem_SetMode(g_saved_mode);
	}
	else /* PD MODE IS ACTIVATED */
	{
		/* Set Traffic Light Mode to warning. */
		TrafficLightSystem_SetMode(TL_WARNING_MODE);
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_PDButtonIsPressed                        *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : PD Button is pressed.                                       *
 ******************************************************************************/
static void TrafficLightSystem_PDButtonIsPressed(void)
{
	/* Check if a PD request does not exist. */
	if (g_pd_request == false)
	{
		/* Rise a PD request. */
		g_pd_request = true;
	}
	else /* PD REQUEST EXIST */
	{
		/* Check if PD activated status with respect to train existence. */
		if ((g_train_exist == true) && (g_pd_activated == false))
		{
			g_pd_activated = true;		/* Activate PD mode. */
			Timer_Start(TIMER_PDS_CH);	/* Enable PD Safety Timer. */
		}
		else if (g_pd_activated == true)
		{
			Timer_Reset(TIMER_PDS_CH);	/* Reset PD Safety timer. */
		}
		else /* PD MODE IS DEACTIVATED */
		{
			//MISRA
		}
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_Timer_TL1                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Timer Event - Traffic Light #1.                             *
 ******************************************************************************/
static void TrafficLightSystem_TimerEvent_TL1(void)
{
	/* Check if PD Request exists. */
	if (g_pd_request == true)
	{
		/* Activated PD and save next state. */
		TrafficLightSystem_PDRequest(TIMER_TL2_CH);
	}
	else /* NO REQUEST */
	{
		Timer_Stop(TIMER_TL1_CH);	/* Disable 1st Traffic light Timer. */
		Timer_Start(TIMER_TL2_CH);	/* Enable 2nd Traffic light Timer. */

		/* Set Traffic Light colors to reversed. */
		TrafficLightSystem_SetMode(TL_REVERSE_MODE);
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_Timer_TL2                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Timer Event - Traffic Light #2.                             *
 ******************************************************************************/
static void TrafficLightSystem_TimerEvent_TL2(void)
{
	/* Check if PD Request exists. */
	if (g_pd_request == true)
	{
		/* Activated PD and save next state. */
		TrafficLightSystem_PDRequest(TIMER_TL1_CH);
	}
	else /* NO REQUEST */
	{
		Timer_Stop(TIMER_TL2_CH);	/* Disable 2nd Traffic light Timer. */
		Timer_Start(TIMER_TL1_CH);	/* Enable 1st Traffic light Timer. */

		/* Set Traffic Light colors to default. */
		TrafficLightSystem_SetMode(TL_DEFAULT_MODE);
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_Timer_PDS                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Timer Event - PD Safety.                                    *
 ******************************************************************************/
static void TrafficLightSystem_TimerEvent_PDS(void)
{
	g_pd_request = false;			/* Clear PD Request flag. */
	g_pd_activated = false;			/* Clear PD Activation flag. */

	Timer_Stop(TIMER_PDS_CH);		/* Disable PD Safety Timer. */

	/* Check if train does not exist first. */
	if (g_train_exist == false)
	{
		Timer_Start(g_saved_timer_ch);	/* Enable next Traffic light Timer. */

		/* Set Traffic Light Mode to next saved mode (default or reversed). */
		TrafficLightSystem_SetMode(g_saved_mode);
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_Timer_TLB                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Timer Event - Traffic Light Blink.                          *
 ******************************************************************************/
static void TrafficLightSystem_TimerEvent_TLB(void)
{
static bool blink = false;			/* Blinking flag */

	/* Check if traffic lights has blinked. */
	if (blink == false)
	{
		blink = true;				/* Set blink to true. */

		/* Change mode to turn off all traffic lights. */
		TrafficLightSystem_SetMode(TL_NO_COLOR_MODE);
	}
	else /* TRUE */
	{
		blink = false;				/* Set blink to false. */

		/* Change mode to turn on all traffic lights to red. */
		TrafficLightSystem_SetMode(TL_WARNING_MODE);
	}
}

/******************************************************************************
 * Name         : TrafficLightSystem_PDRequest                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Activate PD due to request.                                 *
 ******************************************************************************/
static void TrafficLightSystem_PDRequest(uint8_t next_timer_ch)
{
	Timer_Stop(TIMER_TL1_CH);		/* Disable 1st Traffic Light Timer. */
	Timer_Stop(TIMER_TL2_CH);		/* Disable 2nd Traffic Light Timer. */

	g_pd_activated = true;			/* Activate PD mode. */
	Timer_Start(TIMER_PDS_CH);		/* Enable PD Safety Timer. */

	/* Check if train does not exist first. */
	if (g_train_exist == false)
	{
		/* Set Traffic Light Mode to warning (PD or train). */
		TrafficLightSystem_SetMode(TL_WARNING_MODE);

		/* Save next timer to be enabled after PD mode is terminated. */
		g_saved_timer_ch = next_timer_ch;

		/* Check next timer channel to determine next mode. */
		if (next_timer_ch == TIMER_TL2_CH)
		{
			/* Set next mode to Reversed mode. */
			g_saved_mode = TL_REVERSE_MODE;
		}
		else /* DEFAULT */
		{
			/* Set next mode to default mode. */
			g_saved_mode = TL_DEFAULT_MODE;
		}
	}
	else
	{
		//MISRA
	}
}
