/*
 * File:   ring_buffer.c
 * Author: sstevens
 *
 * Created on April 9, 2019, 1:54 PM
 */


#include "xc.h"
#include "ring_buffer.h"

//_ring_buffer uart_rx;

/*! \brief RX Complete Interrupt Service Routine.
 *
 *  RX Complete Interrupt Service Routine.
 *  Stores received data in RX software buffer.
 *
 *  \param usart_data      The USART_data_t struct instance.
 */
uint8_t rx_complete(_ring_buffer *rx, uint8_t rx_data)
{
	_ring_buffer * buf_ptr;
	volatile uint8_t ans, temp_head, temp_tail;

	buf_ptr = rx;
	/* Advance buffer head. */
	/*uint8_t*/ temp_head = (buf_ptr->head + 1) & USART_RX_BUFFER_MASK;

	/* Check for overflow. */
	/*uint8_t*/ temp_tail = buf_ptr->tail;
	///*uint8_t*/ data = usart_data->usart->DATA;

	if(temp_head == temp_tail){
	  	ans = 0;
	}else{
		ans = 1;
		rx->rx[rx->head] = rx_data;
		rx->head = temp_head;
	}
	return ans;
}

/*! \brief tells us if the RX buffer is full
 *
 *  \param usart_data         The USART_data_t struct instance
 */
bool rxbuffer_full(_ring_buffer * rx)
{
	return (_Bool)( ( rx->head >= (RXRingBuffSize-1) )?1:0 );
}


bool rxbuffer_data_available(_ring_buffer *rx)
{
    /* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = rx->head;
	uint8_t tempTail = rx->tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);   
}



/*! \brief  clears rx buffer
 *
 *  \param usart_data       The USART_data_t struct instance.
 */
void rxbuffer_purge(_ring_buffer * rx)
{
	rx->tail = 0;
	rx->head = 0;	
}

/*! \brief  clears a single byte from the rx buffer
 *
 *  \param usart_data       The USART_data_t struct instance.
 */
void rxbuffer_clear_byte(_ring_buffer * rx)
{
	_ring_buffer * bufPtr;

	bufPtr = rx;

	if( bufPtr->head > 1 )
	{
		bufPtr->head -= 2;
		bufPtr->rx[ bufPtr->head	 ] = 0;	
		bufPtr->rx[ bufPtr->head + 1 ] = 0;		
	}
}

/*! \brief Get received data (5-8 bit character) WITHOUT advancing tail
 *
 *  Returns data from RX software buffer.
 *
 *  \param usart_data       The USART_data_t struct instance.
 *
 *  \return         Received data.
 */
uint8_t rxbuffer_peak(_ring_buffer * rx)
{
	return ( rx->rx[ ( rx->head - 1 ) ] );
} 
