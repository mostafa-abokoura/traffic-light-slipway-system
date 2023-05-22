/******************************************************************************
 * Module      : diodrv                                                       *
 * File Name   : diodrv.h                                                     *
 * Description : Header file for diodrv module                                *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#ifndef DIODRV_H_
#define DIODRV_H_

#include "common.h"
#include "types.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Ports */
#define PORT_A          ( 0 )
#define PORT_B          ( 1 )
#define PORT_C          ( 2 )
#define PORT_D          ( 3 )

/* Pins */
#define PIN_0           ( 1U << 0 )
#define PIN_1           ( 1U << 1 )
#define PIN_2           ( 1U << 2 )
#define PIN_3           ( 1U << 3 )
#define PIN_4           ( 1U << 4 )
#define PIN_5           ( 1U << 5 )
#define PIN_6           ( 1U << 6 )
#define PIN_7           ( 1U << 7 )

/* Modes */
#define OUTPUT          ( 0 )
#define INPUT			( 1 )
#define INPUT_PU        ( 2 )

/* Standard o/p pin states */
#define LOW             ( 0 )
#define HIGH            ( 1 )

/******************************************************************************
 *                                                                            *
 *                            Function Prototypes                             *
 *                                                                            *
 ******************************************************************************/

/* Initializes dio pins. */
extern E_status DIO_InitPin(uint8_t port, uint8_t pin, uint8_t mode);

/* Reads dio pins (i/p). */
extern E_status DIO_ReadPin(uint8_t port, uint8_t pin, uint8_t* ptr);

/* Changes dio pins (o/p). */
extern E_status DIO_WritePin(uint8_t port, uint8_t pin, uint8_t data);

#endif /* DIODRV_H_ */
