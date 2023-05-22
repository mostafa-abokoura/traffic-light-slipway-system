/****************************************************************************** 
 * Module      : Train Alert Led                                              *
 * File Name   : trainalertled.h                                              *
 * Description : Header file for Train Alert Led module                       *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef TRAINALERTLED_H_
#define TRAINALERTLED_H_

#include "types.h"
#include "common.h"
#include "led.h"

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes Train Alert LED */
extern void TrainAlertLED_Init(void);

/* Turns on Train Alert LED */
extern void TrainAlertLED_On(void);

/* Turns off Train Alert LED */
extern void TrainAlertLED_Off(void);


#endif /* TRAINALERTLED_H_ */
