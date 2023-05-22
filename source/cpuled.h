/****************************************************************************** 
 * Module      : CPU LED                                                      *
 * File Name   : cpuled.h                                                     *
 * Description : Header file for CPU LED module                               *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef CPULED_H_
#define CPULED_H_

#include "types.h"
#include "common.h"

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes Utilization LED */
extern void UtilizationLED_Init(void);

/* Turns on Utilization LED */
extern void UtilizationLED_On(void);

/* Turns off Utilization LED */
extern void UtilizationLED_Off(void);

/* Initializes Halt LED */
extern void HaltLED_Init(void);

/* Turns on Halt LED */
extern void HaltLED_On(void);

/* Turns off Halt LED */
extern void HaltLED_Off(void);


#endif /* CPULED_H_ */
