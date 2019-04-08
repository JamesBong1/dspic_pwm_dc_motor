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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

//Start with FRC and allow clock switching
//Oscillator Mode: FNOSC_FRC            Internal Fast RC (FRC)
//_FOSCSEL(FNOSC_FRC);									//!<Select Oscillator

//Clock Switching and Monitor:          FCKSM_CSECMD         Clock switching is enabled, Fail-Safe Clock Monitor is disabled
//OSC2 Pin Function:                    OSCIOFNC_OFF         OSC2 pin has clock out function
//Primary Oscillator Source:            POSCMD_XT            XT Oscillator Mode
//Peripheral Pin Select Configuration:  IOL1WAY_OFF          Allow Multiple Re-configurations
//_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT & IOL1WAY_OFF);			//!<Configure Oscillator

//Watchdog Timer Enable:    FWDTEN_OFF           Watchdog timer enabled/disabled by user software
//_FWDT(FWDTEN_OFF);										//!<Turn Watchdog Timer off

//Comm Channel Select:  ICS_PGD3             Communicate on PGC3/EMUC3 and PGD3/EMUD3
//JTAG Port Enable:     JTAGEN_OFF           JTAG is Disabled
//_FICD(ICS_PGD3 & JTAGEN_OFF);							//!<Select Communication Channel 3 and Disable JTAG


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




/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    PWM1CON1bits.PEN1H = 1;
    PWM1CON1bits.PEN1L = 1;
    PWM1CON1bits.PEN2H = 1;
    PWM1CON1bits.PEN2L = 1;
    PWM1CON1bits.PEN3H = 1;
    PWM1CON1bits.PEN3L = 1;
    
    //DTCON1bits.DTA = 59;
    
    P1TCONbits.PTEN=1;
    
    while(1)
    {
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
    }
}
