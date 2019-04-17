/*
 * File:   axis.c
 * Author: sstevens
 *
 * Created on April 10, 2019, 11:27 AM
 */


#include "xc.h"
#include <stdio.h>
#include "system.h"
#include <libpic30.h>
#include "pwm.h"
#include "axis.h"
#include "uart.h"
#include "user.h"

//TODO: put axis_direction into a timer scheduler
_axis_settings axis;

_axis_command axis_command = kAxisIdle;


void set_axis_velocity( float velocity )
{
    EnableUSBUARTTransmit;
    if( ( velocity <= 0.00 ) || ( velocity >= 1.0 ) )
    {
        printf( "\n\n\r%1.3f is an illegal speed value. use a value in the 0-100 range", (double)velocity );
        return;
    }
    
    printf( "\n\n\raxis.velocity: %1.3f -> %1.3f", (double)axis.velocity, (double)velocity );
    
    axis.velocity = velocity;
    
    //set_pwm_duty_cycle(1, axis.velocity);
    //set_pwm_duty_cycle(2, axis.velocity);
    //set_pwm_duty_cycle(3, axis.velocity);
}

void axis_rx_isr( _ring_buffer *rx )
{
    switch( rxbuffer_peak( rx ) )
    {  
        case '\r':
            EnableUSBUARTTransmit;
            printf( "\n\r" );
            command_received = true;
            //P1TCONbits.PTEN = 0; //stop pwm
            break;
        case kAxisForward:
        case kAxisReverse:
        case kAxisStop:
        case kAxisDecreaseSpeed:
        case kAxisIncreaseSpeed:
            axis_command = rxbuffer_peak( rx );
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

/**
 * \brief   receives axis commands and delegates them to axis subroutines
 *
 * \param 	_axis_command cmd - command to handled
 *
 * \returns  
 */
void axis_command_handler()
{
    if( axis_command == kAxisIdle )
        return;
    
    switch( axis_command )
    {
        case kAxisDecreaseSpeed:
            
            set_axis_velocity( ( axis.velocity - 0.01 ) );
            break;
        case kAxisIncreaseSpeed:
            
            set_axis_velocity( ( axis.velocity + 0.01 ) );
            break;
        case kAxisSetVelocity:
            
            //TODO: pass a parameter for velocity
            break;
        case kAxisForward:
        case kAxisReverse:
        case kAxisStop:

            axis_motion_handler( axis_command );
            break;
        default:
            
            EnableUSBUARTTransmit;
            printf( "\n\rinvalid axis command" );
            break;
    }
    
    EnableUSBUARTReceive;
    axis_command = kAxisIdle;
    
}

/**
 * \brief   executes axis motion<forward, reverse, stop, etc...> commands
 *
 * \param 	_axis_command dir - motion command to be executed
 *
 * \returns  
 */
void axis_motion_handler( _axis_command dir )
{   
    if( dir == kAxisIdle )
        return;
    
    switch( dir )
    {
        case kAxisForward:
            
            //PWM1CON1bits.PWM_A4954_IN2 = 0;
            
            //PWM1CON1bits.PWM_A4954_IN1 = 1;
 
            //P1TCONbits.PTEN = 1;
            set_pwm_duty_cycle(3, axis.velocity);
            //set_pwm_duty_cycle(2, axis.velocity);
            set_pwm_duty_cycle(1, axis.velocity);
//            __delay_ms(10);
//            
//            P1DC1 = 0x0137;
//            P1DC3 = 0x0137;
            //set_pwm_duty_cycle(1, 0.50 );
            //set_pwm_duty_cycle(2, axis.velocity);
            //set_pwm_duty_cycle(3, 0.50 );
            
            //P1TCONbits.PTEN = 0;
            //PWM1CON1bits.PWM_A4954_IN2 = 1;
            //PWM1CON1bits.PWM_A4954_IN4 = 0;
            
            //LATBbits.LATB10  = 1;       //ENABLE1_IN1     	Output  pin10    PWM1H2
            //LATBbits.LATB11  = 1;       //ENABLE2_IN3		Output  pin14    PWM1H1
            break;
        case kAxisReverse:
            
            //PWM1CON1bits.PWM_A4954_IN1 = 0;

            //PWM1CON1bits.PWM_A4954_IN2 = 1;
            //PWM1CON1bits.PWM_A4954_IN4 = 1;
  
            //P1TCONbits.PTEN = 1;
 
            set_pwm_duty_cycle(1, ( 1 - axis.velocity ) );
            //set_pwm_duty_cycle(2, axis.velocity);
            set_pwm_duty_cycle(3, ( 1 - axis.velocity ) );
            
//            __delay_ms(10);
// 
//            P1DC1 = 0x0137;
//            P1DC3 = 0x0137;
            //set_pwm_duty_cycle(1, 0.50);
            //set_pwm_duty_cycle(2, axis.velocity);
            //set_pwm_duty_cycle(3, 0.50 );
            //P1TCONbits.PTEN = 0;
            //PWM1CON1bits.PWM_A4954_IN1 = 1;
            //LATBbits.LATB12  = 1;       //ENABLE1_IN1     	Output  pin10    PWM1H2
            //LATBbits.LATB14  = 1;       //ENABLE2_IN3		Output  pin14    PWM1H1
            break;
        case kAxisStop:
            
            //PWM1CON1bits.PWM_A4954_IN1 = 1;
            //PWM1CON1bits.PWM_A4954_IN3 = 0;
            
            //PWM1CON1bits.PWM_A4954_IN2 = 1;
            //PWM1CON1bits.PWM_A4954_IN4 = 0;
            P1TCONbits.PTEN = 0;
            break;
        default:
            EnableUSBUARTTransmit;
            printf( "\n\rinvalid axis direction" );
            EnableUSBUARTReceive;
            return;
            break;
    }
    
    //axis_direction = kAxisIdle;
    //P1TCONbits.PTEN = 1; //start pwm
}