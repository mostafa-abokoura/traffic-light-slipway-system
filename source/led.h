/****************************************************************************** 
 * Module      : Led                                                          * 
 * File Name   : led.h                                                        * 
 * Description : Header file for led module                                   * 
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "types.h"
#include "common.h"
#include "diodrv.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* LED Commands */
#define TURN_ON			( HIGH )
#define TURN_OFF		( LOW )

/* LED channels */
#define LED_TL_N_R_CH	( 0 )
#define LED_TL_N_G_CH   ( 1 )
#define LED_TL_E_R_CH   ( 2 )
#define LED_TL_E_G_CH   ( 3 )
#define LED_TL_W_R_CH   ( 4 )
#define LED_TL_W_G_CH   ( 5 )
#define LED_TL_S_R_CH   ( 6 )
#define LED_TL_S_G_CH   ( 7 )
#define LED_TA_CH		( 8 )
#define LED_UTIL_CH		( 9 )
#define LED_HALT_CH		( 10 )

/****************************************************************************** 
 *                                                                            * 
 *                               Configuration                                * 
 *                                                                            * 
 ******************************************************************************/

/* LED channels configuration */
static const led_ch led[] =
{
    { /* Channel 0: Traffic Light North Red */
        .port = PORT_A,
        .pin  = PIN_0
    },
    { /* Channel 1: Traffic Light North Green */
        .port = PORT_A,
        .pin  = PIN_1
    },
    { /* Channel 2: Traffic Light East Red */
        .port = PORT_A,
        .pin  = PIN_2
    },
    { /* Channel 3: Traffic Light East Green */
        .port = PORT_A,
        .pin  = PIN_3
    },
    { /* Channel 4: Traffic Light West Red */
        .port = PORT_A,
        .pin  = PIN_4
    },
    { /* Channel 5: Traffic Light West Green */
        .port = PORT_A,
        .pin  = PIN_5
    },
    { /* Channel 6: Traffic Light South Red */
        .port = PORT_A,
        .pin  = PIN_6
    },
    { /* Channel 7: Traffic Light South Green */
        .port = PORT_A,
        .pin  = PIN_7
    },
	{ /* Channel 8: Train Alarm LED */
		.port = PORT_B,
		.pin  = PIN_0
	},
    { /* Channel 9: CPU Utilization LED */
		.port = PORT_C,
		.pin  = PIN_0
	},
    { /* Channel 10: Micro-controller Halt LED */
		.port = PORT_C,
		.pin  = PIN_1
	}
};

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes selected LED */
extern E_status LED_Init(uint8_t channel);

/* Turns on selected LED */
extern E_status LED_On(uint8_t channel);

/* Turns off selected LED */
extern E_status LED_Off(uint8_t channel);


#endif /* LED_H_ */
