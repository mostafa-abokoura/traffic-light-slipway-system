/******************************************************************************
 * Module      : PD                                                           *
 * File Name   : pd.h                                              			  *
 * Description : Header file for PD module                        			  *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#ifndef PD_H_
#define PD_H_

#include "common.h"
#include "types.h"
#include "digitalsensor.h"

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Possible PD states */
#define PD_PRESSED    	( 0 )
#define PD_RELEASED		( 1 )

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes all PD buttons */
extern E_status PD_Init(void);

/* Get PD status of any button is pressed */
extern bool PD_GetStatus(void);

#endif /* PD_H_ */
