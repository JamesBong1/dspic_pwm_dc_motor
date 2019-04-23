/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif

#include <dsp.h>
//#include <libq.h>
#include "pwm.h"
#include "uart.h"
#include "user.h"
#include "cli.h"
#include "axis.h"            /* variables/params used by user.c               */
#include "encoder.h"

tPID pid;

// Declares variables for the derived coefficients and controller history samples
fractional abcCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));

// The abcCoefficients referenced by the fooPID data structure
// are derived from the gain coefficients, Kp, Ki and Kd;
// so, declare Kp, Ki and Kd in an array
fractional kCoeffs[] = {0,0,0};
   
/* <Initialize variables in user.h and insert code for user algorithms.> */
//!Map Peripheral Inputs and Outputs to Pins
void initialize_periheral_mapping(void)
{
	AD1PCFGL = 0xFFFF;

	__builtin_write_OSCCONL(OSCCON & 0xDF); //Clear IO Lock

	//Inputs
	RPINR18bits.U1RXR  = 0b00001; //RP1  pin22
	RPINR15bits.INDX1R = 0b10100; //RP20  pin37
	RPINR14bits.QEA1R  = 0b10011; //RP19  pin36
	RPINR14bits.QEB1R  = 0b10010; //RP18 pin27
//DONT NEED. No Data comes back from DAC.	
//RPINR20bits.SDI1R  = 0b10110; //RP22 pin2
	RPINR22bits.SDI2R = 0b11000;  //RP24 pin4

	//Outputs
//	RPOR0bits.RP1R = 0b00111;	//SDO1 pin22
	RPOR10bits.RP21R = 0b00111;	//SDO1 pin38
	RPOR3bits.RP7R   = 0b01000;	//SCK1 pin43
	RPOR0bits.RP0R   = 0b00011;	//U1TX pin21
	RPOR11bits.RP22R = 0b01011;	//SCK2 pin43 RP7 Dataflash clock line
	RPOR11bits.RP23R = 0b01010;	//SDO2 pin15 RP15 Dataflash data line

	__builtin_write_OSCCONL(OSCCON | 0x40); //Set IO Lock
}

void initialize_timers()
{
    T2CON = 0x0000;		//Driver Interrupt

    PR2 = 10000;   //PR2 - 10000: freq         = 2.5kHz
                   //             period       = 400us 
                   //             trigger freq = 5kHz
                   //             tick time    = 200us

    IFS0bits.T2IF = 0;
    IPC1bits.T2IP = 5;

    IEC0bits.T2IE = 1;
    //T2CONbits.TON = 1;
}


//!Initialize SPI1
void initialize_spi1()
{
	/* enable SPI1 interrupt*/
	IEC0bits.SPI1IE = 1;
	
    /* set interrupt priority level */
	IPC2bits.SPI1IP = 6;
	
	//Secondary Prescaler 3:1
	// Primary Prescaler 1:1
	// 16 bit operation
	// sck rising edge triggered active high
	// ss enabled
	// uC is master 
	
	SPI1CON1 = 0x0477;
	//SPI1CON1   = 0x047B;
	/* Not using frame mode */
	SPI1CON2 = 0x0000;
	
	/* Clear Overflow Bit */
	SPI1STATbits.SPIROV = 0;
	
	
	/* Enable SPI1 */
	SPI1STATbits.SPIEN = 1;	
	
	
	/* reset SPI1 interrupt flag */
	IFS0bits.SPI1IF = 0;
    
    DACLoad       = 1;
    DACChipSelect = 1;
}


void initialize_pid(void)
{
    /* PID CONFIGURATION*/
    pid.abcCoefficients = &abcCoefficient[0];   // Set up pointer to derived coefficients
    pid.controlHistory  = &controlHistory[0];   // Set up pointer to controller history samples
    PIDInit(&pid);                              // Clear controller history and output
    
    kCoeffs[0] = Q15(0.70); //Kp
    kCoeffs[1] = Q15(0.0);  //Ki
    kCoeffs[2] = Q15(0.10); //Kd
    PIDCoeffCalc(&kCoeffs[0], &pid);             // Derives the a,b, & c coefficients from the Kp, Ki & Kd    
}

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    initialize_periheral_mapping();
    
    TRISBbits.TRISB10 =  0;		//MODE1_IN2			Output	pin8 	 PWM1H3
	TRISBbits.TRISB11 =  0;		//MODE2_IN4			Output  pin9     PWM1L3
	TRISBbits.TRISB12  = 0;     //ENABLE1_IN1     	Output  pin10    PWM1H2
	TRISBbits.TRISB14  = 0;		//ENABLE2_IN3		Output  pin14    PWM1H1
    
    TRISAbits.TRISA10 =  0;		//RS485_CONTROL		Output  pin12   A10
    
    TRISAbits.TRISA9  =  0;     //DAC_LOAD  		Output  pin35   A9
	TRISAbits.TRISA4  =  0;		//DAC_CHIP_SELECT   Output  pin34   A4
    
    initialize_timers();
    
    initialize_uart();
   
    initialize_spi1();
    
    //initialize_qei1();
    
    //initialize_pwm();
    
    /* Setup analog functionality and port direction */
    current_cli_menu = cMain;
    axis_command   = kAxisIdle;
}


void __attribute__((interrupt, no_auto_psv)) _T2Interrupt( void )
{
    //encoder_ticks[idx_counter] = encoder_tick++;
    if( LATBbits.LATB11 )
        LATBbits.LATB11 = 0;
    else
        LATBbits.LATB11 = 1;
    
    IFS0bits.T2IF = 0;
}