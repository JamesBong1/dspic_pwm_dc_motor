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


#include "pwm.h"
#include "uart.h"
#include "user.h"            /* variables/params used by user.c               */

//had to add 'extern' prototypes to avoid the implicit declaration error. mplab gcc bug???
_stage_settings stage;

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
	RPOR3bits.RP7R  = 0b01000;	//SCK1 pin43
	RPOR0bits.RP0R  = 0b00011;	//U1TX pin21
	RPOR11bits.RP22R = 0b01011;	//SCK2 pin43 RP7 Dataflash clock line
	RPOR11bits.RP23R = 0b01010;	//SDO2 pin15 RP15 Dataflash data line

	__builtin_write_OSCCONL(OSCCON | 0x40); //Set IO Lock
}


void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    initialize_periheral_mapping();
    
    TRISBbits.TRISB10 =  0;		//MODE1_IN2			Output	pin8 	B10
	TRISBbits.TRISB11 =  0;		//MODE2_IN4			Output  pin9    B11
	TRISBbits.TRISB12  = 0;     //ENABLE1_IN1     	Output  pin10   B12
	TRISBbits.TRISB14  = 0;		//ENABLE2_IN3		Output  pin14   B14
    
    TRISAbits.TRISA10 =  0;		//RS485_CONTROL		Output  pin12   A10
    
    
    
    initialize_uart();
    
    initialize_pwm();
    
    /* Setup analog functionality and port direction */
    
    //set stage defaults
    stage.accel     = 100000;	//setting	um/s/s
    stage.position  = 0;        //???
    stage.velocity  = 0.10;     //set low velocity by default???
    
}
