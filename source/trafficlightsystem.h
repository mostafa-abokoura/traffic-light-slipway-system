/****************************************************************************** 
 * Module      : Traffic Light System                                         *
 * File Name   : trafficlightsystem.h                                         *
 * Description : Header file for Traffic Light System module                  *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef TRAFFICLIGHTSYSTEM_H_
#define TRAFFICLIGHTSYSTEM_H_

#include "types.h"
#include "common.h"
#include "configuration.h"
#include "timer.h"
#include "trafficlight.h"
#include "pd.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Modes */
#define MODE_NORMAL				( 0 )
#define MODE_PD					( 1 )
#define MODE_TRAIN				( 2 )

/* Default traffic light colors */
#define TL_NS_DEFAULT_COLOR		( CONFIG_NS_STARTING_COLOR )
#define TL_EW_DEFAULT_COLOR		( CONFIG_EW_STARTING_COLOR )
#define TL_NS_REVERSE_COLOR		( TL_EW_DEFAULT_COLOR )
#define TL_EW_REVERSE_COLOR		( TL_NS_DEFAULT_COLOR )

/* Possible traffic light color modes */
#define TL_DEFAULT_MODE			( 0 )
#define TL_REVERSE_MODE			( 1 )
#define TL_WARNING_MODE			( 2 )
#define TL_NO_COLOR_MODE		( 3 )

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes traffic light system */
extern void TrafficLightSystem_Init(void);

/* PD Button Handler */
extern void TrafficLightSystem_Handler(void);

/* Set all Traffic Light colors by mode */
extern void TrafficLightSystem_SetMode(uint8_t mode);

/* Save current traffic light data. */
extern void TrafficLightSystem_TrainEnterChange(void);

/* Retrieve saved data to traffic light. */
extern void TrafficLightSystem_TrainExitChange(void);


#endif /* TRAFFICLIGHTSYSTEM_H_ */
