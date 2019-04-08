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
#include <math.h>
#include "user.h"            /* variables/params used by user.c               */
#include "system.h"
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/
#define PWMMotorControl

/*----------------------------------------------------------------------------------
 *  PxTCON: PWM Time Base Control Register
 *  This register is used for the selection of  the Time Base mode, time base input clock
 *  prescaler, and time base output postscaler, and for enabling the time base timer.
 ---------------------------------------------------------------------------------*/
#define PWMPostScale 0b00

//PTCKPS<1:0>: PWM Time Base Input Clock Prescale Select bits
//11 = PWM time base input clock period is 64 TCY (1:64 prescale)
//10 = PWM time base input clock period is 16 TCY (1:16 prescale)
//01 = PWM time base input clock period is 4 TCY (1:4 prescale)
//00 = PWM time base input clock period is TCY (1:1 prescale)
#define PWMPrescale  0b01 //1:1

//11 = PWM time base operates in Continuous Up/Down Count mode with interrupts for double PWM updates
//10 = PWM time base operates in Continuous Up/Down Count mode
//01 = PWM time base operates in Single Event mode
//00 = PWM time base operates in Free Running mode
typedef enum PWMTimeBaseModes
{
    kPWMFreeRunning,
    kPWMSingleEvent,
    kPWMContinousUpDown,
    kPWMContinuousUpDownWInterrupt,
    kPWMTimeBaseModes
}_pwm_time_base_mode;

#define PWMTimeBaseMode kPWMContinousUpDown 

#define PWMMaxPeriod         0x07ff //period register is 15bits
#define PWMDefaultPeriodms   .001
/* <Initialize variables in user.h and insert code for user algorithms.> */



void set_pwm_period( float period_n_seconds )
{
    volatile float Fpwm, prescale;
    
    Fpwm = ( 1 / period_n_seconds );
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
    P1TCONbits.PTOPS = PWMPostScale;    // postscaler 1:1
	P1TCONbits.PTCKPS= PWMPrescale;     //prescaler 1:64
	P1TCONbits.PTMOD = PWMTimeBaseMode; // PWM time base operates in free running mode
   
    //P1TMRbits.PTMR = 0;     // PWM counter value, start at 0
    
    set_pwm_period(.001);
 
    P1SECMP=0;

    PWM1CON1bits.PMOD1 = 1; //the pairs PWM1H e PWM1L are NOT guided in complementary mode so i don't have to use the Dead Time register
    PWM1CON1bits.PMOD2 = 1; //the pairs PWM2H e PWM2L are NOT guided in complementary mode so i don't have to use the Dead Time register
    PWM1CON1bits.PMOD3 = 1;
    
    PWM1CON2bits.IUE=1;     // Updates to the active P1DC1 registers are immediate
    
    P1DC1=0;
	P1DC2=0;
	P1DC3=0;    
    
    
}


void set_pwm_duty_cycle( int pwm, float positive_duty_cycle )
{
	volatile float Fduty, prescale;
	
    if( positive_duty_cycle < 0 )
        positive_duty_cycle = 0;
	else if( positive_duty_cycle >1.0 )
        positive_duty_cycle = 1.0;

    Fduty    = ( 1 / ( positive_duty_cycle * PWMDefaultPeriodms ) );
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

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    TRISBbits.TRISB10 =  0;		//MODE1_IN2			Output	pin8 	B10
	TRISBbits.TRISB11 =  0;		//MODE2_IN4			Output  pin9    B11
	TRISBbits.TRISB12  = 0;     //ENABLE1_IN1     	Output  pin10   B12
	TRISBbits.TRISB14  = 0;		//ENABLE2_IN3		Output  pin14   B14
    
    
    initialized_pwm_module();
    /* Setup analog functionality and port direction */
    set_pwm_duty_cycle(1,.5);
    set_pwm_duty_cycle(2,.05);
    set_pwm_duty_cycle(3,.85);
    /* Initialize peripherals */

//    P1DC1 =24999;
//	P1DC2 =24999;
//	P1DC3 =24999; 

    P1TCONbits.PTEN=1; //to enable PWM 1 put this bit to 1
}
