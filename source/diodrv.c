/******************************************************************************
 * Module      : diodrv                                                       *
 * File Name   : diodrv.c                                                     *
 * Description : Source file for diodrv module                                *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#include "diodrv.h"
#include "diodrv_regs.h"

/******************************************************************************
 * Name         : DIO_InitPin                                                 *
 * Inputs       : port, pin & mode                                            *
 * Outputs      : None                                                        *
 * Return Value : E_status                                                    *
 * Description  : Initializes DIO pins and return E_OK if successful.         *
 ******************************************************************************/
E_status DIO_InitPin(uint8_t port, uint8_t pin, uint8_t mode)
{
uint8_t* ddr_b;                       		/* ddr base address */
uint8_t* port_b;							/* port base address */

    /* Check if selected port not is supported by hardware. */
    if (port > MAX_PORT)
    {
        return E_NOT_OK;                    /* Return E_NOT_OK. */
    }

    ddr_b = (uint8_t *)DDR(port);           /* Get DDR address. */

    /* Identify mode. */
    if (OUTPUT == mode)                     /* Check if mode is o/p. */
    {
    	HWREG(ddr_b) |= pin;             	/* Set direction as o/p. */
    }
    else if ((INPUT == mode) || (INPUT_PU == mode))
    {
    	HWREG(ddr_b) &= ~pin;            	/* Set Direction as i/p. */

        if (INPUT_PU == mode)
        {
        	port_b = (uint8_t *)PORT(port);	/* Get PORT address. */
            HWREG(port_b) |= pin;           /* Enable pull-up resistor. */
        }
    }
    else /* UNKNOWN MODE */
    {
        return E_NOT_OK;                    /* Return E_NOT_OK. */
    }

    return E_OK;                            /* Return E_OK. */
}

/******************************************************************************
 * Name         : DIO_ReadPin                                                 *
 * Inputs       : port & pin                                                  *
 * Outputs      : data                                                        *
 * Return Value : E_status                                                    *
 * Description  : Reads DIO pins.                                             *
 ******************************************************************************/
E_status DIO_ReadPin(uint8_t port, uint8_t pin, uint8_t* ptr)
{
uint8_t* ddr_b;                            	/* ddr base address */
uint8_t* pin_b;								/* pin base address */
uint8_t data;                           	/* Pin data */

    /* Check if selected port is not supported by hardware & pointer is null. */
    if ((port > MAX_PORT) || (NULL_PTR == ptr))
    {
        return E_NOT_OK;                    /* Return E_NOT_OK. */
    }

    ddr_b = (uint8_t *)DDR(port);        	/* Get DDR address. */
    pin_b = (uint8_t *)PIN(port);			/* Get PIN address. */

    data = HWREG(pin_b) & pin;      		/* Get required pin data. */

    /* Identify pin_data. */
    if (LOW == data)
    {
        *ptr = LOW;                       	/* Change data to low. */
    }
    else /* HIGH */
    {
        *ptr = HIGH;                       /* Change data to high. */
    }

    return E_OK;                            /* Return E_OK. */
}

/******************************************************************************
 * Name         : DIO_WritePin                                                *
 * Inputs       : port, pin & data                                            *
 * Outputs      : None                                                        *
 * Return Value : E_status                                                    *
 * Description  : Changes actual DIO pins voltage.                            *
 ******************************************************************************/
E_status DIO_WritePin(uint8_t port, uint8_t pin, uint8_t data)
{
uint8_t* ddr_b;                        		/* ddr base address */
uint8_t* port_b;							/* port base address */

    /* Check if selected port is not supported by hardware. */
    if (port > MAX_PORT)
    {
        return E_NOT_OK;                    /* Return E_NOT_OK. */
    }

    ddr_b = (uint8_t *)DDR(port);       	/* Get DDR address. */
	port_b = (uint8_t *)PORT(port);			/* Get PORT address. */

    /* Identify Data. */
    if (HIGH == data)
    {
        HWREG(port_b) |= pin;            	/* Set pin to high. */
    }
    else if (LOW == data)
    {
        HWREG(port_b) &= ~pin;           	/* Set pin to low. */
    }
    else /* UNDEFINED */
    {
        return E_NOT_OK;                    /* Return E_NOT_OK. */
    }

    return E_OK;                            /* Return E_NOT_OK. */
}
