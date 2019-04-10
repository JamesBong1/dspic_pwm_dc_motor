/*
 * File:   axis.c
 * Author: sstevens
 *
 * Created on April 10, 2019, 11:27 AM
 */


#include "xc.h"
#include <stdio.h>
#include <libpic30.h>
#include "pwm.h"
#include "axis.h"
#include "uart.h"

//TODO: put axis_direction into a timer scheduler
_axis_direction axis_direction = kAxisIdle;

void axis_rx_isr( _ring_buffer *rx )
{
    switch( rxbuffer_peak( rx ) )
    {  
        case '\r':

            command_received = true;
            P1TCONbits.PTEN = 0; //stop pwm
            break;
        case kAxisForward:
        case kAxisReverse:
        case kAxisStop:  
            axis_direction = rxbuffer_peak( rx );
            break;
        case '\b':

            EnableUSBUARTTransmit;
            printf( "\b \b" );
            rxbuffer_clear_byte( rx );
            break;
        default:

            EnableUSBUARTTransmit;
            printf( "%c" , rxbuffer_peak( rx ) );
            break;
    }    
}

void move_axis( _axis_direction dir )
{  
    if( axis_direction == kAxisIdle )
        return;
    
    switch( dir )
    {
        case kAxisForward:
            
            PWM1CON1bits.PWM_A4954_IN1 = 1;  
            PWM1CON1bits.PWM_A4954_IN2 = 0;
            break;
        case kAxisReverse:

            PWM1CON1bits.PWM_A4954_IN1 = 0;  
            PWM1CON1bits.PWM_A4954_IN2 = 1;
            break;
        case kAxisStop:
            
            PWM1CON1bits.PWM_A4954_IN1 = 0;  
            PWM1CON1bits.PWM_A4954_IN2 = 0;
            break;
        default:
            EnableUSBUARTTransmit;
            printf( "\n\rinvalid axis direction" );
            //__delay_ms(1);
            EnableUSBUARTReceive;
            return;
            break;
    }
    
    axis_direction = kAxisIdle;
    P1TCONbits.PTEN = 1; //start pwm
}