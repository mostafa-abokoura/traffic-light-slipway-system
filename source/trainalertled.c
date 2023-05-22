/****************************************************************************** 
 * Module      : Train Alert Led                                              *
 * File Name   : trainalertled.c                                              *
 * Description : Source file for Train Alert Led module                       *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "trainalertled.h"

/****************************************************************************** 
 * Name         : TrainAlertLED_Init                                          *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Initializes Train Alert LED as o/p.                         *
 ******************************************************************************/
void TrainAlertLED_Init()
{
    /* Returns E_OK if initialization was successful. */ 
    DIO_InitPin(led[LED_TA_CH].port, led[LED_TA_CH].pin, OUTPUT);
}

/****************************************************************************** 
 * Name         : TrainAlertLED_On                                            *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Turns on Train Alert LED.                                   *
 ******************************************************************************/
void TrainAlertLED_On()
{
    /* Returns E_OK if turning Train Alert LED on was successful. */
    DIO_WritePin(led[LED_TA_CH].port, led[LED_TA_CH].pin, TURN_ON);
}

/****************************************************************************** 
 * Name         : TrainAlertLED_Off                                           *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        * 
 * Return Value : None                                                        *
 * Description  : Turns off Train Alert LED.                                  *
 ******************************************************************************/
void TrainAlertLED_Off()
{
    /* Returns E_OK if turning Train Alert LED off was successful. */
    DIO_WritePin(led[LED_TA_CH].port, led[LED_TA_CH].pin, TURN_OFF);
}
