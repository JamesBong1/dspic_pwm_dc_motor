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


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdio.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include <libpic30.h>
#include "user.h"
#include "project.h"
#include "ring_buffer.h"
#include "uart.h"          /* User funct/params, such as InitApp              */
#include "cli.h"
#include "axis.h"
#include "encoder.h"



//update config bits to stop triggering the XC compiler warnings according
//to the doc, for this chip; file:///C:/Program%20Files%20(x86)/Microchip/xc16/v1.36/docs/config_docs/33FJ128MC804.html
#pragma config FNOSC    = FRC    //Oscillator Mode:             FRC     - Internal Fast RC (FRC) no PLL
//_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT & IOL1WAY_OFF);
#pragma config FCKSM    = CSECMD//Clock Switching and Monitor: CSECMD  - Clock switching is enabled, Fail-Safe Clock Monitor is disabled
#pragma config OSCIOFNC = OFF   //OSC2 Pin Function:           OFF     - OSC2 pin has clock out function
#pragma config POSCMD   = XT    //Primary Oscillator Source:   XT      - XT Oscillator Mode
#pragma config IOL1WAY  = OFF   //Peripheral Pin Select Config:OFF     - Allow Multiple Re-configurations
//_FWDT(FWDTEN_OFF);
#pragma config FWDTEN   = OFF   //Watchdog Timer Enable:       OFF     - Watchdog timer enabled/disabled by user software
//_FICD(ICS_PGD3 & JTAGEN_OFF);
#pragma config ICS      = PGD3  //Comm Channel Select:         PGD3    - Communicate on PGC3/EMUC3 and PGD3/EMUD3
#pragma config JTAGEN   = OFF   //JTAG Port Enable:            OFF     - JTAG is Disabled  





void cli_command_handler( _ring_buffer *rx );
/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
//tPID pid;
//
//// Declares variables for the derived coefficients and controller history samples
//fractional abcCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
//fractional controlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));
//
//// The abcCoefficients referenced by the fooPID data structure
//// are derived from the gain coefficients, Kp, Ki and Kd;
//// so, declare Kp, Ki and Kd in an array
//fractional kCoeffs[] = {0,0,0};

int16_t main(void)
{
    __C30_UART =1;
    /* Configure the oscillator for the device */
    ConfigureOscillator();
      
    /* Initialize IO ports and peripherals */
    InitApp();
    
//    /* PID CONFIGURATION*/
//    pid.abcCoefficients = &abcCoefficient[0];   // Set up pointer to derived coefficients
//    pid.controlHistory  = &controlHistory[0];   // Set up pointer to controller history samples
//    PIDInit(&pid);                              // Clear controller history and output
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */

    //DTCON1bits.DTA = 59;
    EnableUSBUARTTransmit;
    __delay_ms(500);
    
    printf( "\n\n\n\n\r%s %s\n\r", _ProductTitle,_Version );
    __delay_ms(100);
    //P1TCONbits.PTEN=1;
    
    DACChipSelect = 0;  //Set Chip Select Low Before Transfer
    SPI1BUF = ( /*sin_phase*/(0x0ff0 - 150 ) | DAC2Mask );
    
    EnableUSBUARTReceive;
    __delay_ms(100);
    //Turn on UART RX interrupt after board addressing is completed
	IFS0bits.U1RXIF = 0;
	IEC0bits.U1RXIE = 1;
    
    T2CONbits.TON = 1;
    
    while(1)
    {
        cli_command_handler( &uart_rx );
        axis_command_handler( axis_command );
        
        if( dump_encoder_readings )
            dump_encoder_data();
    }
}


void cli_command_handler( _ring_buffer *rx )
{

    if( !command_received )
        return;

    EnableUSBUARTTransmit;
    __delay_ms(1);

    if( !execute_command( rx, cli_menu_ptr_list[current_cli_menu] ) )
        printf( "\n\rinvalid command!\n\r" );

    command_received = false;

    rxbuffer_purge( rx );

    EnableUSBUARTReceive
    __delay_ms(1);
}