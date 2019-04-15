/*
 * File:   pwm.c
 * Author: sstevens
 *
 * Created on April 8, 2019, 5:18 PM
 */

#include <math.h>
#include "xc.h"
#include "pwm.h"
#include "system.h"
#include "user.h"


void set_pwm_period( float period_us )
{
    volatile float Fpwm, prescale;
    
    Fpwm = ( 1 / period_us );
    prescale = pow( 4, PWMPrescale );

    switch(PWMTimeBaseMode)
    {
        case kPWMFreeRunning:
        case kPWMSingleEvent:
            
            /*------------------------------------------------------------------
             *  PWM Period Calculation for Free Running Count Mode (PTMOD = 00 or 01)
             *  
             *  PxTPER = ( FCY / FPWM x PxTMR Prescaler ) - 1
             *  
             *  FCY  = Clock Frequency
             *  FPWM = PWM Frequency
             *  PXTMR Prescaler = PWM Prescaler
             -----------------------------------------------------------------*/
            P1TPERbits.PTPER =  ((uint16_t)((uint16_t)( FCY / ( Fpwm * prescale ) ) & 0x000007fff)) - 1;
            break;
        case kPWMContinousUpDown:
        case kPWMContinuousUpDownWInterrupt:
            
            /*------------------------------------------------------------------
             *  PWM Period Calculation for Free Running Count Mode (PTMOD = 10 or 11)
             *  
             *  PxTPER = ( FCY / Fpwm x PxTMR Prescaler x 2 ) - 1
             *  
             *  FCY  = Clock Frequency
             *  FPWM = PWM Frequency
             *  PXTMR Prescaler = PWM Prescaler
             -----------------------------------------------------------------*/
            P1TPERbits.PTPER =  ((uint16_t)((uint16_t)( FCY / ( Fpwm * prescale * 2 ) ) & 0x000007fff)) - 1; 
            break;
        default:
            break;
        
    }
}

void initialize_pwm(void)
{
    //set stage defaults
    axis.accel     = 100000;	//setting	um/s/s
    axis.position  = 0;        //???
    axis.velocity  = 0.50;     //set low velocity by default???
    
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
    P1TCONbits.PTOPS = PWMPostScale;    // postscaler 1:1
	P1TCONbits.PTCKPS= PWMPrescale;     //prescaler 1:64
	P1TCONbits.PTMOD = PWMTimeBaseMode; // PWM time base operates in free running mode
   
    //P1TMRbits.PTMR = 0;     // PWM counter value, start at 0
    
    set_pwm_period( PWMDefaultPeriod_us );
 
    P1SECMP=0;
    
    //using IN3<PEN1H:PIN14>/IN4<PEN3L:PIN9> of A4954 driver. therefore we want to have pairs
    //1 and 3 of PWM1 module to be complementary of each other
    PWM1CON1bits.PMOD1 = PWMIOComplementaryMode; //the pairs PWM1H e PWM1L are NOT guided in complementary mode so i don't have to use the Dead Time register
    //PWM1CON1bits.PMOD2 = 1; //the pairs PWM2H e PWM2L are NOT guided in complementary mode so i don't have to use the Dead Time register
    PWM1CON1bits.PMOD3 = PWMIOComplementaryMode;
    
    //disable PWM IO
    //PWM1CON1bits.PWM_A4954_IN1 = 0;  
    //PWM1CON1bits.PWM_A4954_IN2 = 0;
    PWM1CON1bits.PWM_A4954_IN3 = 1;
    PWM1CON1bits.PWM_A4954_IN4 = 1;
    
    PWM1CON2bits.IUE=1;     // Updates to the active P1DC1 registers are immediate  
    
    set_pwm_duty_cycle(1, ( 1 - axis.velocity ));
    //set_pwm_duty_cycle(2, axis.velocity);
    set_pwm_duty_cycle(3, ( 1 - axis.velocity ));
    /* Initialize peripherals */

//  P1DC1 =24999;
//	P1DC2 =24999;
//	P1DC3 =24999; 

    P1TCONbits.PTEN=1; //to enable PWM 1 put this bit to 1    
}


void set_pwm_duty_cycle( int pwm, float positive_duty_cycle )
{
	volatile float Fduty, prescale;
	
    if( positive_duty_cycle < 0 )
        positive_duty_cycle = 0;
	else if( positive_duty_cycle >1.0 )
        positive_duty_cycle = 1.0;

    Fduty    = ( 1 / ( positive_duty_cycle * PWMDefaultPeriod_us ) );
    prescale = pow( 4, PWMPrescale );
    
	//value = 2 * ( 12500 * positive_duty_cycle ) / (period);

	//calculate the value of the register P1DC1 based on a simple proportion hightime:period=P1DC1:PTPER
	//P1DC1=(P1TPERbits.PTPER*hightime)/(period);
    
    /*------------------------------------------------------------------
     *  PWM Period Calculation for Free Running Count Mode (PTMOD = 10 or 11)
     *  
     *  PxDCx = ( FCY / Fduty x PxTMR Prescaler ) - 1
     *  
     *  FCY   = Clock Frequency
     *  Fduty = % of pwm period that will be high
     *  PXTMR Prescaler = PWM Prescaler
     -----------------------------------------------------------------*/
    switch(pwm)
    {
        case 1:
            P1DC1 = ((uint16_t)((uint16_t)( FCY / ( Fduty * prescale ) ) & 0x000007fff)) - 1;
            break;
        case 2:
            P1DC2 = ((uint16_t)((uint16_t)( FCY / ( Fduty * prescale ) ) & 0x000007fff)) - 1;
            break;
        case 3:
            P1DC3 = ((uint16_t)((uint16_t)( FCY / ( Fduty * prescale ) ) & 0x000007fff)) - 1;
            break;
	 }

}
