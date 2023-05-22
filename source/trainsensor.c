/******************************************************************************
 * Module      : Train Sensor                                                 *
 * File Name   : trainsensor.h                                     			  *
 * Description : Source file for Train Sensor module              			  *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#include "trainsensor.h"

/******************************************************************************
 * Name         : TrainSensor_Init                                            *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : E_status                                                    *
 * Description  : Initializes all train sensors as i/p.                       *
 ******************************************************************************/
E_status TrainSensor_Init(void)
{
	/* Return E_OK if initialization is successful. */
	if ((DigitalSensor_Init(TS_RIGHT_CH) == E_OK) &&
	    (DigitalSensor_Init(TS_LEFT_CH) == E_OK))
	{
		return E_OK;						/* Return E_OK */
	}
	else /* ERROR */
	{
		return E_NOT_OK;					/* Return E_NOT_OK */
	}
}

/******************************************************************************
 * Name         : TrainSensor_GetStatus                                       *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : boolean                                                     *
 * Description  : Get selected Train sensor status.                           *
 ******************************************************************************/
bool TrainSensor_GetStatus(uint8_t channel)
{
	/* Update selected train sensor status. */
	DigitalSensor_UpdateStatus(channel);

	/* Check selected train sensor is not reading. */
	if (DigitalSensor_GetStatus(channel) == IS_NOT_PRESSED)
	{
		return TS_LEAVE;					/* Return TS_RELEASED */
	}
	else /* EXIST */
	{
		return TS_EXIST;					/* Return TS_PRESSED */
	}
}
