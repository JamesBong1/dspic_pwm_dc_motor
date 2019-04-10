/*
 * File:   uart.c
 * Author: sstevens
 *
 * Created on April 8, 2019, 5:30 PM
 */


#include "xc.h"
#include <stdio.h>
#include <string.h>
//#include <libpic30.h>
#include "ring_buffer.h"
#include "uart.h"
#include "system.h"

//#include <stdio.h>

bool command_received;
_ring_buffer uart_rx;

//!Initialize UART1
void initialize_uart(void)
{
    //__C30_UART = 1;
    
	U1BRG = BRGVAL;

	//U1MODE = 0x8000;
	U1MODEbits.UARTEN = 1;

	/* Set Up Receive Interrupt and Enable Transmitter */
	U1STA = 0x2400;
	U1STAbits.UTXEN = 1;

	//why did I set this to such a high priority?
	//IPC3bits.U1TXIP = 6;
	//IEC0bits.U1TXIE = 1;
	//IFS0bits.U1TXIF = 0;
	
	IPC2bits.U1RXIP = 5;
	
    memset( (void *)uart_rx.rx, 0, sizeof( uart_rx.rx ) );
    rxbuffer_purge(&uart_rx);
    
    command_received = false;
	//Don't enable receive interrupt here. Do it in main.c after board id is initialized.
}

//!Send character to UART
int UART1_PutChar(char c)
{
	while(U1STAbits.UTXBF);
	U1TXREG = c;
	return 1;
}

//!UART1 Receive Interrupt
//Function runs every time a character is received.
//It strips whitespace and increments a counter when a full
//line is received.
//
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt( void )
{
	//clear flag
	IFS0bits.U1RXIF = 0;	
    
    if( rx_complete( &uart_rx, U1RXREG ) == 0 )
        return;
    
    switch( rxbuffer_peak( &uart_rx ) )
    {
        
        case '\r':
            
            command_received = true;
            //rxbuffer_purge( &uart_rx );
            break;
        case '\b':
            
            printf( "\b \b" );
            rxbuffer_clear_byte( &uart_rx );
            break;
        default:
            EnableUSBUARTTransmit;
            //UART1_PutChar(data);
            printf( "%c" , rxbuffer_peak( &uart_rx ) );
            
            break;
    }
    
    
    if( rxbuffer_full( &uart_rx ) )
        rxbuffer_purge( &uart_rx );
    
    EnableUSBUARTReceive;
}

