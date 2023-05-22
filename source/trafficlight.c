/****************************************************************************** 
 * Module      : Traffic Light                                                *
 * File Name   : trafficlight.c                                               *
 * Description : Source file for Traffic Light module                         *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "trafficlight.h"

/******************************************************************************
 * Name         : TrafficLight_Init                                           *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        * 
 * Return Value : E_status                                                    * 
 * Description  : Initializes traffic light LEDs.                             *
 ******************************************************************************/
E_status TrafficLight_Init(uint8_t channel)
{
    /* Check if initialization is successful. */
    if ((LED_Init(trafficlight[channel].red_ch) == E_OK) &&
        (LED_Init(trafficlight[channel].green_ch) == E_OK))
    {
        return E_OK;                            /* Return E_OK. */
    }
    else /* ERROR */
    {
        return E_NOT_OK;                        /* Return E_NOT_OK. */
    }
}

/****************************************************************************** 
 * Name         : TrafficLight_SetColor                                       *
 * Inputs       : channel & color                                             *
 * Outputs      : None                                                        * 
 * Return Value : E_status                                                    *
 * Description  : Sets traffic light color.                                   *
 ******************************************************************************/
E_status TrafficLight_SetColor(uint8_t channel, color_t color)
{
	/* Save new color. */
	*trafficlight[channel].pointer = color;

	/* Check if required color is red. */
	if (COLOR_RED == color)
	{
		/* Turn on red channel. */
		if (LED_On(trafficlight[channel].red_ch) == E_NOT_OK)
		{
			return E_NOT_OK;
		}
		else
		{
			/* MISRA */
		}
	}
	else /* NOT RED */
	{
		/* Turn off red channel. */
		if (LED_Off(trafficlight[channel].red_ch) == E_NOT_OK)
		{
			return E_NOT_OK;
		}
		else
		{
			/* MISRA */
		}
	}

	/* Check if required color is green. */
	if (COLOR_GREEN == color)
	{
		/* Turn on green channel. */
		if (LED_On(trafficlight[channel].green_ch) == E_NOT_OK)
		{
			return E_NOT_OK;
		}
		else
		{
			/* MISRA */
		}
	}
	else /* NOT GREEN */
	{
		/* Turn off green channel. */
		if (LED_Off(trafficlight[channel].green_ch) == E_NOT_OK)
		{
			return E_NOT_OK;
		}
		else
		{
			/* MISRA */
		}
	}

	return E_OK;								/* Returns E_OK. */
}

/******************************************************************************
 * Name         : TrafficLight_GetColor                                       *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : color_t                                                     *
 * Description  : Gets traffic light color.                                   *
 ******************************************************************************/
color_t TrafficLight_GetColor(uint8_t channel)
{
	/* Returns traffic light color. */
	return *trafficlight[channel].pointer;
}
