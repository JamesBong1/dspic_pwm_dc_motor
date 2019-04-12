/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PWM_H
#define	PWM_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "project.h"
// TODO Insert appropriate #include <>
//#include "pwm.h"
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

#define PWMTimeBaseMode kPWMContinousUpDown //kPWMContinousUpDown 

#define PWMMaxPeriod         0x07ff //period register is 15bits
#define PWMDefaultPeriod_s  .001
#define PWMDefaultPeriod_us ( 5 * pow( 10, -6 ) )

// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation
#define A4954ControlIn1     PWM1CON1BITS.PEN2H
#define A4954ControlIn2     PWM1CON1BITS.PEN3H

#define PWM_A4954_IN1       PEN2H
#define PWM_A4954_IN2       PEN3H
#define PWM_A4954_IN3       PEN1H
#define PWM_A4954_IN4       PEN3L

void set_pwm_period( float period_us );



void set_pwm_duty_cycle( int pwm, float positive_duty_cycle );

extern void initialize_pwm(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* PWM_H */

