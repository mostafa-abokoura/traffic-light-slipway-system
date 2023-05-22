/******************************************************************************
 * Module      : None                                                         *
 * File Name   : types.h                                                      *
 * Description : Header file for common types used                            *
 * Created on  : Mar 23, 2020                                                 *
 ******************************************************************************/

#ifndef TYPES_H_
#define TYPES_H_

#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
 *                                                                            *
 *                                 Datatypes                                  *
 *                                                                            *
 ******************************************************************************/

/* Error status datatype */
typedef uint8_t E_status;

/* Color datatype */
typedef uint8_t color_t;

/* Software Timer datatype */
typedef struct
{
    bool status;
    const uint16_t alarm;
    uint16_t ticks;
    void (*fn_ptr)(void);
} timer_ch;

/* LED channel datatype */
typedef struct
{
    uint8_t port;
    uint8_t pin;
} led_ch;

/* Digital Sensor channel datatype */
typedef struct
{
    uint8_t port;
    uint8_t pin;
    uint8_t* pointer;
} digitalsensor_ch;

/* Traffic Light channel datatype */
typedef struct
{
	uint8_t red_ch;
	uint8_t green_ch;
	color_t* pointer;
} trafficlight_ch;

/* Task datatype */
typedef struct
{
    bool is_enabled;        /* Task enable flag */
    void (*pointer)(void);	/* Task pointer to function */
} task_t;

#endif /* TYPES_H_ */
