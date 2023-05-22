/******************************************************************************
 * Module      : Digital Sensor                                               *
 * File Name   : digitalsensor.c                                              *
 * Description : Source file for Digital Sensor module                        *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#include "digitalsensor.h"

/******************************************************************************
 * Name         : DigitalSensor_Init                                          *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : E_status                                                    *
 * Description  : Initializes button as i/p.                                  *
 ******************************************************************************/
E_status DigitalSensor_Init(uint8_t channel)
{
    /* Return E_OK if initialization is successful. */
    return DIO_InitPin(sensor[channel].port, sensor[channel].pin, INPUT_PU);
}

/******************************************************************************
 * Name         : DigitalSensor_UpdateStatus                                  *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : E_status                                                    *
 * Description  : Updates button status.                                      *
 ******************************************************************************/
E_status DigitalSensor_UpdateStatus(uint8_t channel)
{
    /* Check if data is not a null pointer. */
    if (NULL_PTR == sensor[channel].pointer)
    {
        /* Return E_NOT_OK. */
        return E_NOT_OK;
    }

    /* Return E_OK if reading is successful. */
    return DIO_ReadPin(sensor[channel].port, \
    				   sensor[channel].pin, \
					   sensor[channel].pointer);
}

/******************************************************************************
 * Name         : DigitalSensor_GetStatus                                     *
 * Inputs       : channel                                                     *
 * Outputs      : None                                                        *
 * Return Value : uint8_t                                                     *
 * Description  : Gets button status.                                         *
 ******************************************************************************/
uint8_t DigitalSensor_GetStatus(uint8_t channel)
{
	/* Return current traffic light. */
	return *(sensor[channel].pointer);
}
