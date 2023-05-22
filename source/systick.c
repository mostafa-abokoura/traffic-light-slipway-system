/****************************************************************************** 
 * Module      : Systick                                                      * 
 * File Name   : systick.h                                                    * 
 * Description : Source file for systick module                               * 
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include "systick.h"
#include "systick_regs.h"

/****************************************************************************** 
 *                                                                            * 
 *                              Global Variables                              * 
 *                                                                            * 
 ******************************************************************************/

/* Systick callback function */
static void(*g_Systick_Callback)(void) = NULL_PTR;

/****************************************************************************** 
 * Name         : Systick_Start                                               * 
 * Inputs       : None                                                        * 
 * Outputs      : None                                                        * 
 * Return Value : None                                                        * 
 * Description  : Starts systick and enable systick interrupts.               * 
 ******************************************************************************/
void Systick_Start(void)
{
	/* Set timer0 mode */
	TCCR0 = (1 << FOC0 ) | (0 << WGM00) | (0 << COM01) | (0 << COM00) |\
			(1 << WGM01) | (1 << CS02 ) | (0 << CS01 ) | (0 << CS00 );

	/* Set time */
	OCR0 = PRELOAD;

	/* Enable timer0 interrupt */
	TIMSK = (1 << OCIE0) | (0 << TOIE0);

	/* Enable global interrupt */
	SREG = (1 << SREG_I) ;
}

/****************************************************************************** 
 * Name         : Systick_Stop                                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Stops systick.                                              *
 ******************************************************************************/
void Systick_Stop(void)
{
	/* Set timer0 mode */
	TCCR0 = (0 << FOC0 ) | (0 << WGM00) | (0 << COM01) | (0 << COM00) |\
			(0 << WGM01) | (0 << CS02 ) | (0 << CS01 ) | (0 << CS00 );
}

/******************************************************************************
 * Name         : Systick_GetCallBack                                         *
 * Inputs       : fn_ptr                                                      * 
 * Outputs      : None                                                        * 
 * Return Value : None                                                        * 
 * Description  : Sets systick callback function.                             * 
 ******************************************************************************/
void Systick_SetCallBack(void(*fn_ptr)(void))
{
    /* Set systick pointer to function. */
	g_Systick_Callback = fn_ptr;
}

/****************************************************************************** 
 * Name         : ISR_SYSTICK_HANDLER                                         *
 * Inputs       : None                                                        * 
 * Outputs      : None                                                        * 
 * Return Value : None                                                        * 
 * Description  : Systick Interrupt Handler.                                  * 
 ******************************************************************************/
ISR_SYSTICK_HANDLER
{
    /* Execute callback function. */
	(*g_Systick_Callback)();
}

