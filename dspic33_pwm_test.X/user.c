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

#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/
#define PWMMotorControl


/* <Initialize variables in user.h and insert code for user algorithms.> */
void initialized_pwm_module(void)
{
	/*----------------------------------------------------------------------------------
     *  PxTCON: PWM Time Base Control Register
     *  This register is used for the selection of  the Time Base mode, time base input clock
     *  prescaler, and time base output postscaler, and for enabling the time base timer.
     ---------------------------------------------------------------------------------*/
    //PTEN: PWM Time Base Timer Enable bit
    //1 = PWM time base is on
    //0 = PWM time base is off
    P1TCONbits.PTEN     = 0;
	
    //PTSIDL: PWM Time Base Stop in Idle Mode bit
    //1 = PWM time base halts in CPU Idle mode
    //0 = PWM time base runs in CPU Idle mode
    P1TCONbits.PTSIDL   = 0;
    
    //PTOPS<3:0>: PWM Time Base Output Postscale Select bits
    P1TCONbits.PTOPS = 0b00; // postscaler 1:1
    
    //PTCKPS<1:0>: PWM Time Base Input Clock Prescale Select bits
    //11 = PWM time base input clock period is 64 TCY (1:64 prescale)
    //10 = PWM time base input clock period is 16 TCY (1:16 prescale)
    //01 = PWM time base input clock period is 4 TCY (1:4 prescale)
    //00 = PWM time base input clock period is TCY (1:1 prescale)
	P1TCONbits.PTCKPS = 0b11;   //prescaler 1:64
    
    //PTMOD<1:0>: PWM Time Base Mode Select bits
    //11 = PWM time base operates in Continuous Up/Down Count mode with interrupts for double PWM updates
    //10 = PWM time base operates in Continuous Up/Down Count mode
    //01 = PWM time base operates in Single Event mode
    //00 = PWM time base operates in Free Running mode
	P1TCONbits.PTMOD=0b00; // PWM time base operates in free running mode
   
    P1TMRbits.PTMR = 0;     // PWM counter value, start at 0
    
    /*The formula to find the value of PTPER is:
	 *
	 *  PTPER = ((Frequence of device[called Fcy])/(PWM frequence * PWM prescaler * 2)) -1
	 *
	 * How to find Fcy = Fosc / 4;
	 *
	 * How to find PWM frequence : The period of the PWM signal is 20ms, so the frequency is "1 / 20ms"
	 *
	 *I use the PWM prescaler set to 1:64
	 * */
    P1TPERbits.PTPER =  19999;
     
    P1SECMP=0;

    PWM1CON1bits.PMOD1 = 1; //the pairs PWM1H e PWM1L are NOT guided in complementary mode so i don't have to use the Dead Time register
    PWM1CON1bits.PMOD2 = 1; //the pairs PWM2H e PWM2L are NOT guided in complementary mode so i don't have to use the Dead Time register
    
    PWM1CON2bits.IUE=1;     // Updates to the active P1DC1 registers are immediate
    
    P1DC1=0;
	P1DC2=0;
	P1DC3=0;    
    
    
}

void set_pwm_duty_cycle(int pwm, float hightime, float period)
{
	unsigned long value;
	
    if( hightime < 0.6 )
        hightime = 0.6;
	else if( hightime >2.4 )
        hightime = 2.4;

	if( period > 20 )
        period = 20;

	value = 2 * ( 12500 * hightime ) / (period);

	//calculate the value of the register P1DC1 based on a simple proportion hightime:period=P1DC1:PTPER
	//P1DC1=(P1TPERbits.PTPER*hightime)/(period);

    switch(pwm)
    {
        case 1:
            P1DC1=value;
            break;
        case 2:
            P1DC2=value;
            break;
        case 3:
            P1DC3=value;
            break;
	 }

}

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    TRISBbits.TRISB10 =  0;		//MODE1_IN2			Output	pin8 	B10
	TRISBbits.TRISB11 =  0;		//MODE2_IN4			Output  pin9    B11
	TRISBbits.TRISB12  = 0;     //ENABLE1_IN1     	Output  pin10   B12
	TRISBbits.TRISB14  = 0;		//ENABLE2_IN3		Output  pin14   B14
    
    
    initialized_pwm_module();
    /* Setup analog functionality and port direction */
    set_pwm_duty_cycle(1,.6, 20);
    set_pwm_duty_cycle(2,.6, 20);
    set_pwm_duty_cycle(3,.6, 20);
    /* Initialize peripherals */

    P1DC1 =100;
	P1DC2 =10000;
	P1DC3 =20000; 

    P1TCONbits.PTEN=1; //to enable PWM 1 put this bit to 1
}
