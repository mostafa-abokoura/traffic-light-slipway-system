/****************************************************************************** 
 * Module      : Application                                                  * 
 * File Name   : app.h                                                        * 
 * Description : Header file for Application module                           *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef APP_H_
#define APP_H_

#include "common.h"
#include "types.h"

/****************************************************************************** 
 *                                                                            * 
 *                              Shared Variables                              *
 *                                                                            * 
 ******************************************************************************/

/* Tasks container */
extern task_t task[];

/* Number of tasks */
extern const uint8_t g_TaskNumber;

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes tasks */
void Task_Init(void);


#endif /* APP_H_ */
