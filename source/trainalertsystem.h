/****************************************************************************** 
 * Module      : Train Alert System                                           *
 * File Name   : trainalertsystem.h                                           *
 * Description : Header file for Train Alert System module                    *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef TRAINALERTSYSTEM_H_
#define TRAINALERTSYSTEM_H_

#include "types.h"
#include "common.h"
#include "configuration.h"
#include "timer.h"
#include "trainsensor.h"
#include "trainalertled.h"
#include "trafficlightsystem.h"
#include "CPUled.h"

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes Train Alert System */
extern void TrainAlertSystem_Init(void);

/* Train Alert System Handler */
extern void TrainAlertSystem_Handler(void);


#endif /* TRAINALERTSYSTEM_H_ */
