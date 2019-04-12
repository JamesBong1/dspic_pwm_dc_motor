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

#define _Version        "v19.4.12.0"
/*
 * v19.4.12.0;
 * - use pwm matching <both hbridge inputs have the same pwm when the motor is stopped>
 *   whenever the motor is not in use
 * - add manual velocity changes via the up/down keys of the keyboard. each change is 
 *   set to plus/minus .01 == 1%, and test
 * - enable DAC output 1, which is the bridge enable signal of the motor we use. this was
 *   just copied/pasted from the current MMC-200 project used for production
 * - break up axis sub routines into control and movment
 * - increase pwm frequency to 200khz. NOTE!!! TODO: find proper way of choosing pwm frequency
 * note!!! I've learned the hard way that there is no way to get a good consistent
 *         pwm signal to drive a motor in the single event mode. !!!TODO!!! TODO:
 *         I'll have to figure out how to calculate the time needed to enable a
 *         motor to get to a desired distance. 
 */
#define _ProductTitle   "MMC-200 dc motor controller tester"

#define _Enable     1
#define _Disable    0

// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* PR0JECT_H */

