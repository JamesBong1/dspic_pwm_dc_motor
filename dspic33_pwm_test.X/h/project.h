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
#ifndef PR0JECT_H
#define	PR0JECT_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <dsp.h>

#define _Version        "v19.4.25.0"
/*
 * v19.4.22.1
 * - !!!THIS TEST HAS SERIOUS BUGS!!!
 *   set up closed loop test within timer2 interrupt, that makes where ever the motor
 *   is on power up the zero position. the test detects whenever the motor has been moved
 *   out position and attempts to get it back to the zero point, but manipulating the PWM
 *   signals with the values calculated from Microchip's PID functions in their PID library.
 *   TODO:I'll have to figure out how to calculate the time needed to enable a
 *        motor to get to a desired distance.
 */

#define _ProductTitle   "MMC-200 linear voicecoil tester"

#define _Enable     1
#define _Disable    0

extern tPID pid;

// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    typedef struct _DriverVariables
    {
        int32_t position_nm;
        volatile int32_t target_position; //!<Theoretical Position include servo interpolation
        uint8_t motor_polarity;
    }_driver_vars;

    extern _driver_vars mmc200;
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* PR0JECT_H */

