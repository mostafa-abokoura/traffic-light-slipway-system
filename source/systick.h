/****************************************************************************** 
 * Module      : Systick                                                      * 
 * File Name   : systick.h                                                    * 
 * Description : Header file for systick module                               * 
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "types.h"
#include "common.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Systick Prescale (remember to change CS bits in TCCR0) */
#define PRESCALE			( 256 )

/* CPU frequency in KHZ */
#define F_CPU_KHZ			( 1000 )

/* Systick tick in milliseconds */
#define TICK_MS				( 10 )

#define PRELOAD				( TICK_MS * F_CPU_KHZ / PRESCALE - 10 )

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Starts systick */
extern void Systick_Start(void);

/* Stops systick */
extern void Systick_Stop(void);

/* Sets systick callback function */
extern void Systick_SetCallBack(void(*fn_ptr)(void));


#endif /* SYSTICK_H_ */
