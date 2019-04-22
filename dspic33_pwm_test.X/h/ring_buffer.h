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
#ifndef RING_BUFFER_H
#define	RING_BUFFER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>

/* \brief  Receive buffer size: 2,4,8,16,32,64,128 or 256 bytes. */
#define RXRingBuffSize 64

/* \brief Receive buffer mask. */
#define USART_RX_BUFFER_MASK ( RXRingBuffSize - 1 )


#if( RXRingBuffSize & USART_RX_BUFFER_MASK )
    #error RX buffer size is not a power of 2
#endif



/* \brief USART transmit and receive ring buffer. */
typedef struct _RXRingBuffer
{
	/* \brief Receive buffer. */
	volatile uint8_t rx[RXRingBuffSize];
	/* \brief Receive buffer head. */
	volatile uint8_t head;
	/* \brief Receive buffer tail. */
	volatile uint8_t tail;
}_ring_buffer;

extern _ring_buffer uart_rx;

bool    rxbuffer_full(_ring_buffer * rx);
bool    rxbuffer_data_available(_ring_buffer *rx);
uint8_t rxbuffer_getByte(_ring_buffer *rx);
uint8_t rx_complete(_ring_buffer *rx, uint8_t rx_data);
void    rxbuffer_purge(_ring_buffer * rx);
void    rxbuffer_clear_byte(_ring_buffer * rx);
uint8_t rxbuffer_peak(_ring_buffer * rx);
//void USART_DataRegEmpty(USART_data_t * usart_data);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* RING_BUFFER_H */

