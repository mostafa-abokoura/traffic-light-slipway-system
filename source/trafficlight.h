/****************************************************************************** 
 * Module      : Traffic Light                                                *
 * File Name   : trafficlight.h                                               *
 * Description : Header file for Traffic Light module                         *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "common.h"
#include "types.h"
#include "led.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Colors */
#define COLOR_NONE      ( 0 )
#define COLOR_RED       ( 1 )
#define COLOR_GREEN     ( 2 )

/* Traffic Light channels */
#define TL_NORTH_CH		( 0 )
#define TL_EAST_CH 		( 1 )
#define TL_WEST_CH   	( 2 )
#define TL_SOUTH_CH   	( 3 )

/****************************************************************************** 
 *                                                                            *
 *                              Static Variables                              *
 *                                                                            *
 ******************************************************************************/

/* TrafficLight North Color */
static color_t g_TL_N_Color = COLOR_NONE;

/* TrafficLight East Color  */
static color_t g_TL_E_Color = COLOR_NONE;

/* TrafficLight West Color  */
static color_t g_TL_W_Color = COLOR_NONE;

/* TrafficLight South Color  */
static color_t g_TL_S_Color = COLOR_NONE;


/******************************************************************************
 *                                                                            * 
 *                               Configuration                                *
 *                                                                            *
 ******************************************************************************/

/* Traffic Light channels */
static const trafficlight_ch trafficlight[] =
{
    { /* Channel 0: North Traffic Light */
        .red_ch   = LED_TL_N_R_CH,
        .green_ch = LED_TL_N_G_CH,
		.pointer  = &g_TL_N_Color
    },
	{ /* Channel 1: East Traffic Light */
		.red_ch   = LED_TL_E_R_CH,
		.green_ch = LED_TL_E_G_CH,
		.pointer  = &g_TL_E_Color
	},
	{ /* Channel 2: West Traffic Light */
		.red_ch   = LED_TL_W_R_CH,
		.green_ch = LED_TL_W_G_CH,
		.pointer  = &g_TL_W_Color
	},
	{ /* Channel 3: South Traffic Light */
		.red_ch   = LED_TL_S_R_CH,
		.green_ch = LED_TL_S_G_CH,
		.pointer  = &g_TL_S_Color
	}
};

/******************************************************************************
 *                                                                            *
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes Traffic Light LEDs */
extern E_status TrafficLight_Init(uint8_t channel);

/* Set Traffic Light color */
extern E_status TrafficLight_SetColor(uint8_t channel, color_t color);

/* Get Traffic Light color */
extern color_t TrafficLight_GetColor(uint8_t channel);


#endif /* TRAFFICLIGHT_H_ */
