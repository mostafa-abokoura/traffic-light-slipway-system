/****************************************************************************** 
 * Module      : CPU LED                                                      *
 * File Name   : cpuled.c                                                     *
 * Description : Source file for CPU LED module                               *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "cpuled.h "
#include "led.h"

/****************************************************************************** 
 * Name         : UtilizationLED_Init                                         *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Initializes Utilization LED as o/p.                         *
 ******************************************************************************/
void UtilizationLED_Init()
{
    /* Returns E_OK if initialization was successful. */ 
    DIO_InitPin(led[LED_UTIL_CH].port, led[LED_UTIL_CH].pin, OUTPUT);
}

/****************************************************************************** 
 * Name         : UtilizationLED_On                                           *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Turns on Utilization LED.                                   *
 ******************************************************************************/
void UtilizationLED_On()
{
    /* Returns E_OK if turning Utilization LED on was successful. */
    DIO_WritePin(led[LED_UTIL_CH].port, led[LED_UTIL_CH].pin, TURN_ON);
}

/****************************************************************************** 
 * Name         : UtilizationLED_Off                                          *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Turns off Utilization LED.                                  *
 ******************************************************************************/
void UtilizationLED_Off()
{
    /* Returns E_OK if turning Utilization LED off was successful. */
    DIO_WritePin(led[LED_UTIL_CH].port, led[LED_UTIL_CH].pin, TURN_OFF);
}

/******************************************************************************
 * Name         : HaltLED_Init                                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Initializes Halt LED as o/p.                                *
 ******************************************************************************/
void HaltLED_Init()
{
    /* Returns E_OK if initialization was successful. */
    DIO_InitPin(led[LED_HALT_CH].port, led[LED_HALT_CH].pin, OUTPUT);
}

/******************************************************************************
 * Name         : HaltLED_On                                                  *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Turns on Halt LED.                                          *
 ******************************************************************************/
void HaltLED_On()
{
    /* Returns E_OK if turning Utilization LED on was successful. */
    DIO_WritePin(led[LED_HALT_CH].port, led[LED_HALT_CH].pin, TURN_ON);
}

/******************************************************************************
 * Name         : HaltLED_Off                                                 *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Turns off Halt LED.                                         *
 ******************************************************************************/
void HaltLED_Off()
{
    /* Returns E_OK if turning Utilization LED off was successful. */
    DIO_WritePin(led[LED_HALT_CH].port, led[LED_HALT_CH].pin, TURN_OFF);
}
