/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        7370000L
#define FCY             50000000UL //SYS_FREQ/2

#define EnableUSBUARTReceive    LATAbits.LATA10 = 0;
#define EnableUSBUARTTransmit   LATAbits.LATA10 = 1;

#define DAC1Mask 0x1000			//!<Control Byte for DAC to select DAC1
#define DAC2Mask 0x9000			//!<Control Byte for DAC to select DAC2

#define DACLoad         LATAbits.LATA9      //!<DAC Load Pulse Output
#define DACChipSelect   LATAbits.LATA4		//!<DAC Chip Select Output


/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

