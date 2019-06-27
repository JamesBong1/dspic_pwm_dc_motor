/*
 * File:   motor_driver.c
 * Author: sstevens
 *
 * Created on April 30, 2019, 11:36 AM
 */


#include "xc.h"
#include <stdio.h>
#include <string.h>
#include "encoder.h"
#include "project.h"
#include "system.h"

_driver_vars mmc200;

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt( void )
{

    encoder.position_count = POS1CNT;

    encoder.change_in_count = (int32_t)encoder.position_count - (int32_t)encoder.previous_position_count;

	if( -encoder.change_in_count > 32000 ) //Detect and correct for rollover in positive direction
        encoder.change_in_count += 65536;
	else if( encoder.change_in_count > 32000 ) //Detect and correct for rollover in the negative direction
		encoder.change_in_count -= 65536;

//    if( ( encoder.change_in_count > 15 ) || ( encoder.change_in_count < -15 ) )
//    {
//        EnableUSBUARTTransmit;
//        printf( "\n\rencoder diff: %1f", (double)encoder.change_in_count );
//        EnableUSBUARTReceive;
//    }
    
    //Update PreviousCount for next servo cycle
	encoder.previous_position_count = encoder.position_count;

    encoder.absolute_position += encoder.change_in_count;

    /*
     * encoder resolution is in nanometers. QEI is in x4 mode. therefore, position is
     * quarter nanometers -> nm/4???
     */
    mmc200.position_nm = ( encoder.absolute_position * encoder.resolution_nm * 1 ); 
    //encoder_ticks[idx_counter] = encoder_tick++;

    encoder.count_accumulation += encoder.change_in_count * encoder.resolution_nm;
    //EncoderAccum += EncoderDif * (long)Setting_EncoderResolution;

//    if( LATBbits.LATB11 )
//        LATBbits.LATB11 = 0;
//    else
//        LATBbits.LATB11 = 1;

    IFS0bits.T2IF = 0;
}