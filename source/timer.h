/****************************************************************************** 
 * Module      : Timer                                                        *
 * File Name   : timer.h                                                      *
 * Description : Header file for software timer module                        *
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "types.h"
#include "common.h"
#include "systick.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Possible software timer status */
#define TIMER_DISABLED		( 0 )
#define TIMER_ENABLED		( 1 )

/* Software timer channels */
#define TIMER_SIREN_CH		( 0 )
#define TIMER_TL1_CH		( 1 )
#define TIMER_TL2_CH		( 2 )
#define TIMER_PDS_CH		( 3 )
#define TIMER_TSS_CH		( 4 )
#define TIMER_TLB_CH		( 5 )
#define TIMER_LED_CH		( 6 )

/* Software timer (in milli-seconds) */
#define TIMER_SIREN_TIME	( 10 )
#define TIMER_TL1_TIME		( 5000 )
#define TIMER_TL2_TIME		( 2500 )
#define TIMER_PDS_TIME		( 10000 )
#define TIMER_TSS_TIME		( 30000 )
#define TIMER_TLB_TIME		( 250 )
#define TIMER_LED_TIME		( 250 )

/* Macro-like function to calculate timer time using systick */
#define CALCULATE_TIME(t)	( t / TICK_MS )

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Handles all timers in software timer array. */
extern void Timer_Handler(void);

/* Starts a software timer */
extern void Timer_Start(uint8_t channel);

/* Stops a software timer */
extern void Timer_Stop(uint8_t channel);

/* Resets a software timer */
extern void Timer_Reset(uint8_t channel);

/* Gets a software timer status. */
extern bool Timer_GetStatus(uint8_t channel);

/* Sets callback function of a software timer */
extern void Timer_SetCallBack(uint8_t channel, void(*fn_ptr)(void));


#endif /* TIMER_H_ */
