/*
 * File:   encoder.c
 * Author: sstevens
 *
 * Created on April 16, 2019, 11:44 AM
 */


#include "xc.h"
#include <stdio.h>
#include "system.h"
#include <libpic30.h>
#include <string.h>
#include "encoder.h"

/*-
 * Encoder Notes
 * This test case is using an optical encoder <ID4501L>, on a linear<orientation-0 degrees>
 * optical scale. This encoder is OTP<one time programmable>.
 * 
 * We've programmed it for; 
 * <A  - orientation = 0 degrees >
 * <CPP- cycles per period = 8,192>
 *          Scale Period<mm>     |  1.20  |  1.28  |
 *          ----------------------------------------
 * <BB - maximum speed(m/s) = 2> |  0.029 |  0.031 |
 * <CC - resolution(um) = 15>    |  0.037 |  0.039 |
 * 
 * refer to datasheet if you need more info on the this encoder's<ID450L> parameters
 * 
 * After measuring, we're working with a 1.28mm period scale
 * 
 * Tests show that we get 1024Pulses<POS1CNT> per period
 * 
 * Therefore,  
 * 
 *      1024pulses per 1.28mm or 1024pulses/1.28mm -> 800pulses/mm or 1.25um/pulse
 * 
 *  
 */

volatile unsigned int EncoderCount = 0;				//!<Value of the POS1CNT register sampled this cycle
volatile unsigned int PreviousCount = 0;				//!<Value of the POS1CNT register sampled last cycle
volatile volatile long RealPositionCounter=0;				//!<Absolute Position register in encoder counts
volatile long EncoderCheck;							//!<Sampled value of RealPositionCounter used to detect an encoder
volatile long EncoderDif = 0;							//!<Used to account for overflow of POS1CNT between cycles
uint8_t idx_counter = 0;

volatile long encoder_readings[100] = {0};
volatile long encoder_difference[100] = {0};
volatile uint32_t encoder_tick = 0;
volatile uint32_t encoder_ticks[100] = {0};
bool dump_encoder_readings = false;

void initialize_qei1()
{
    //!Initialize Quadrature Interface
    QEI1CONbits.QEISIDL = 0;    // Continue module operation in idle mode
    QEI1CONbits.UPDN    = 1;    // Position Counter Direction is positive (+)
    QEI1CONbits.INDX    = 1;    // Read only - Index pin state status pin.
    QEI1CONbits.QEIM0   = 0;    // Use 4x Update mode with reset on index pulse
    QEI1CONbits.QEIM1   = 1;    // "
    QEI1CONbits.QEIM2   = 1;    // "
    QEI1CONbits.SWPAB   = 1;    // Phase A and Phase B inputs are swapped
    QEI1CONbits.PCDOUT  = 0;    // Counter Direction Status Output (Normal I/O pin operation)
    QEI1CONbits.POSRES  = 0;    // Index Pulse does not reset Position Counter
    DFLT1CONbits.CEID   = 1;    // Interrupts due to count errors are disabled
    DFLT1CONbits.QEOUT  = 0;    // Digital filter outputs enabled
    DFLT1CONbits.QECK0  = 0;//1;    // 1:2 clock divide for digital filter for Index
    DFLT1CONbits.QECK1  = 0;    // "
    DFLT1CONbits.QECK2  = 0;    // "
    DFLT1CONbits.IMV1   = 1;
    DFLT1CONbits.IMV0   = 1;
    POS1CNT = 0;
    MAX1CNT = 0xFFFF;

    IPC14bits.QEI1IP = 7;
    //IFS3bits.QEI1IF = 0;

    //Don't enable here. Enable when we know which channel we're looking at.
    IEC3bits.QEI1IE = 1;	
}

void dump_encoder_data()
{
    volatile uint8_t i = 0;
    EnableUSBUARTTransmit;
    printf( "\n\n\n\rencoder data dump: " );
    for( i = 1; i< idx_counter; i++ )
    {
        printf( "\n\rreading[%d]: %lf, diff[%d]: %lf, ticks[%d]: %ld", i,\
                    (double)encoder_readings[i], i, (double)encoder_difference[i], i, ( encoder_ticks[i]-encoder_ticks[(i-1)] ) );
    }
    
    memset( (void *)encoder_readings, 0, i );
    memset( (void *)encoder_difference, 0, i );
    memset( (void *)encoder_ticks, 0, i );
    encoder_tick = 0;
    dump_encoder_readings = false;
    EnableUSBUARTReceive;
    
    idx_counter = 0;
    IFS3bits.QEI1IF = 0;
    IEC3bits.QEI1IE = 1;
}

void __attribute__((interrupt, no_auto_psv)) _QEI1Interrupt( void )
{
    //EncoderCount = POS1CNT;
    encoder_readings[ idx_counter/*++*/ ] = POS1CNT;	
	encoder_difference[ idx_counter ] = encoder_readings[ idx_counter/*++*/ ] - PreviousCount;

	//Detect and correct for rollover in positive direction.
	if(-encoder_difference[ idx_counter ] > 32000)
	{
		encoder_difference[ idx_counter ] += 65536;
	}
	
	//Detect and correct for rollover in the negative direction.
	else if(encoder_difference[ idx_counter ]>32000)
	{
		encoder_difference[ idx_counter ] -= 65536;
	}
    
    if( encoder_difference[idx_counter] < 0 )
        encoder_difference[idx_counter] *= -1.0;
	//Update PreviousCount for next servo cycle
	PreviousCount = encoder_readings[ idx_counter++ ];
//    
//    if( POS1CNT ==  0 )
//        idx_counter++;
//    else
//        idx_counter--;
//       
    //EnableUSBUARTTransmit;
    //printf( "\n\r%lf", (double)encoder_readings[idx_counter] );
    //printf( "\n\renc: %lf" , (double)EncoderCount );
    //printf( "\n\ridx_counter: %lf" , (double)idx_counter );
    //printf( "\n\renc def: %lf" , (double)EncoderDif );
    //EnableUSBUARTReceive;
    if( idx_counter > 1 )
        T2CONbits.TON = 1;
    
    if( idx_counter >= 30 )
    {
        dump_encoder_readings = true;
        //idx_counter = 0;
        T2CONbits.TON = 0; 
        IEC3bits.QEI1IE = 0;
    }
    
    IFS3bits.QEI1IF = 0;
    //POS1CNT = 0;
}

