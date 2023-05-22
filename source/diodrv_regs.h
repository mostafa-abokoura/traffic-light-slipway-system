/******************************************************************************
 * Module      : diodrv                                                       *
 * File Name   : diodrv_regs.h                                                *
 * Description : Header file for hardware registers of diodrv module          *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#ifndef DIODRV_REGS_H_
#define DIODRV_REGS_H_

#include <stdbool.h>
#include <stdint.h>

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* H/W values */
#define MAX_PORT        ( 3 )

/* Registers */
#define DDRA_BASE      	( 0x3A )
#define OFFSET			( 3 )

/* Function-like macros */
#define HWREG(b)        (*(volatile uint8_t *)(b))
#define DDR(n)         	( DDRA_BASE - (OFFSET * n) + 0 )
#define PORT(n)			( DDRA_BASE - (OFFSET * n) + 1 )
#define PIN(n)			( DDRA_BASE - (OFFSET * n) - 1 )

#endif /* DIODRV_REGS_H_ */
