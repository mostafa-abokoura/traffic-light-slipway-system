/****************************************************************************** 
 * Module      : Systick                                                      * 
 * File Name   : systick_regs.h                                               * 
 * Description : Header file for registers of systick module                  * 
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#ifndef SYSTICK_REGS_H_
#define SYSTICK_REGS_H_

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* TCCR0 */
#define TCCR0	(*((volatile uint8_t *)(0x33 + 0x20)))
#define CS00	( 0 )
#define CS01	( 1 )
#define CS02	( 2 )
#define WGM01	( 3 )
#define COM00	( 4 )
#define COM01	( 5 )
#define WGM00	( 6 )
#define FOC0	( 7 )

/* TIMSK */
#define TIMSK	(*((volatile uint8_t *)(0x39 + 0x20)))
#define TOIE0	( 0 )
#define OCIE0	( 1 )

/* OCR0 */
#define OCR0	(*((volatile uint8_t *)(0x3C + 0x20)))

/* SREG */
#define SREG	(*((volatile uint8_t *)(0x3F + 0x20)))
#define SREG_C	( 0 )
#define SREG_Z	( 1 )
#define SREG_N	( 2 )
#define SREG_V	( 3 )
#define SREG_S	( 4 )
#define SREG_H  ( 5 )
#define SREG_T	( 6 )
#define SREG_I	( 7 )

/* ISR TIMER0 COMPARE */
#define ISR_SYSTICK_HANDLER \
	void __vector_19 (void) __attribute__ ((signal, used, externally_visible));\
	void __vector_19 (void)

#endif /* SYSTICK_REGS_H_ */
