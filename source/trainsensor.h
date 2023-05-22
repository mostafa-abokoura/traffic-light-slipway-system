/******************************************************************************
 * Module      : Train Sensor                                                 *
 * File Name   : trainsensor.h                                     			  *
 * Description : Header file for Train Sensor module              			  *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#ifndef TRAINSENSOR_H_
#define TRAINSENSOR_H_

#include "common.h"
#include "types.h"
#include "digitalsensor.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Possible Train Sensor States */
#define TS_EXIST    ( 0 )
#define TS_LEAVE	( 1 )

/* Train sensor channels */
#define TS_RIGHT_CH	( DS_TS_R_CH )
#define TS_LEFT_CH	( DS_TS_L_CH )

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes all train sensors */
extern E_status TrainSensor_Init(void);

/* Get train sensor status */
extern bool TrainSensor_GetStatus(uint8_t channel);

#endif /* TRAINSENSOR */
