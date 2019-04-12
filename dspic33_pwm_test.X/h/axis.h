/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef AXIS_H
#define	AXIS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "ring_buffer.h"

typedef enum _AxisDirection
{
    kAxisIdle               ,
    kAxisIncreaseSpeed =0x41, //A
    kAxisDecreaseSpeed      ,
    kAxisForward            ,
    kAxisReverse            ,
    kAxisSetVelocity        ,        
    kAxisStop          =0x53, //S 
    cAxisDirections
}_axis_command;

extern _axis_command axis_command;

/**
 * \brief   receives axis commands and delegates them to axis subroutines
 *
 * \param 	_axis_command cmd - command to handled
 *
 * \returns  
 */
void axis_command_handler();

/**
 * \brief   executes axis motion<forward, reverse, stop, etc...> commands
 *
 * \param 	_axis_command dir - motion command to be executed
 *
 * \returns  
 */
void axis_motion_handler( _axis_command dir );

void axis_rx_isr( _ring_buffer *rx );
// TODO Insert appropriate #include <>


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* AXIS_H */

