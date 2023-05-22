/******************************************************************************
 * Module      : Digital Sensor                                               *
 * File Name   : digitalsensor.h                                              *
 * Description : Header file for Digital Sensor module                        *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_

#include "common.h"
#include "types.h"
#include "diodrv.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* DigitalSensor Channels */
#define DS_PD_N_CH      ( 0 )
#define DS_PD_E_CH      ( 1 )
#define DS_PD_W_CH      ( 2 )
#define DS_PD_S_CH      ( 3 )
#define DS_TS_R_CH      ( 4 )
#define DS_TS_L_CH      ( 5 )

/* Possible button states */
#define IS_PRESSED    	( LOW )
#define IS_NOT_PRESSED	( HIGH )


/****************************************************************************** 
 *                                                                            * 
 *                              Static Variables                              *
 *                                                                            * 
 ******************************************************************************/

/* Shared PD North status */
static uint8_t g_PD_N_Status;

/* Shared PD East status */
static uint8_t g_PD_E_Status;

/* Shared PD West status */
static uint8_t g_PD_W_Status;

/* Shared PD South status */
static uint8_t g_PD_S_Status;

/* Shared TS_1 status */
static uint8_t g_TS_R_Status;

/* Shared TS_2 status */
static uint8_t g_TS_L_Status;
   
/****************************************************************************** 
 *                                                                            * 
 *                               Configuration                                * 
 *                                                                            * 
 ******************************************************************************/

/* Button channels */
static const digitalsensor_ch sensor[] =
{
    { /* Channel 0: PD North button */
        .port = PORT_B,
        .pin  = PIN_1,
		.pointer = &g_PD_N_Status
    },
	{ /* Channel 1: PD East button */
		.port = PORT_B,
		.pin  = PIN_2,
		.pointer = &g_PD_E_Status
	},
	{ /* Channel 2: PD West button */
		.port = PORT_B,
		.pin  = PIN_3,
		.pointer = &g_PD_W_Status
	},
	{ /* Channel 3: PD South button */
		.port = PORT_B,
		.pin  = PIN_4,
		.pointer = &g_PD_S_Status
	},
	{ /* Channel 4: Train Sensor 1 */
		.port = PORT_B,
		.pin  = PIN_5,
		.pointer = &g_TS_R_Status
	},
	{ /* Channel 5: Train Sensor 2 */
		.port = PORT_B,
		.pin  = PIN_6,
		.pointer = &g_TS_L_Status
	}
};

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes selected button. */
extern E_status DigitalSensor_Init(uint8_t channel);

/* Updates selected button status. */
extern E_status DigitalSensor_UpdateStatus(uint8_t channel);

/* Gets selected button status. */
extern uint8_t DigitalSensor_GetStatus(uint8_t channel);

#endif /* DIGITALSENSOR_H_ */
