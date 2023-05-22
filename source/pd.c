/******************************************************************************
 * Module      : PD                                                           *
 * File Name   : pd.h                                              			  *
 * Description : Source file for PD module                        			  *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#include "pd.h"

/******************************************************************************
 * Name         : PD_Init                                                     *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : E_status                                                    *
 * Description  : Initializes all PD button as i/p.                           *
 ******************************************************************************/
E_status PD_Init(void)
{
	/* Return E_OK if initialization is successful. */
	if ((DigitalSensor_Init(DS_PD_N_CH) == E_OK) &&
	    (DigitalSensor_Init(DS_PD_E_CH) == E_OK) &&
		(DigitalSensor_Init(DS_PD_W_CH) == E_OK) &&
		(DigitalSensor_Init(DS_PD_S_CH) == E_OK))
	{
		return E_OK;						/* Return E_OK */
	}
	else /* ERROR */
	{
		return E_NOT_OK;					/* Return E_NOT_OK */
	}
}

/******************************************************************************
 * Name         : PD_GetStatus                                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : boolean                                                     *
 * Description  : Get PD current status.                                      *
 ******************************************************************************/
bool PD_GetStatus(void)
{
	/* Update PD button status. */
	DigitalSensor_UpdateStatus(DS_PD_N_CH);
	DigitalSensor_UpdateStatus(DS_PD_E_CH);
	DigitalSensor_UpdateStatus(DS_PD_W_CH);
	DigitalSensor_UpdateStatus(DS_PD_S_CH);

	/* Check if all is not pressed. */
	if ((DigitalSensor_GetStatus(DS_PD_N_CH) == IS_NOT_PRESSED) &&
		(DigitalSensor_GetStatus(DS_PD_E_CH) == IS_NOT_PRESSED) &&
		(DigitalSensor_GetStatus(DS_PD_W_CH) == IS_NOT_PRESSED) &&
		(DigitalSensor_GetStatus(DS_PD_S_CH) == IS_NOT_PRESSED))
	{
		return PD_RELEASED;					/* Return PD_RELEASED */
	}
	else /* AT LEAST ONE PD BUTTON IS PRESSED */
	{
		return PD_PRESSED;					/* Return PD_PRESSED */
	}
}
