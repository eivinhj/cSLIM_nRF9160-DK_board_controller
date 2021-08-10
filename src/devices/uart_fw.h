/*
 * uart_fw.h
 *
 *  Created on: Mar 27, 2017
 *      Author: Waseemh
 */

#ifndef SRC_WLR08Uu0_H_
#define SRC_WLR08Uu0_H_

#define ENABLE_UART_FW true

#ifdef ENABLE_UART_FW
#define ENABLE_UART_FW_FLAG 1
#else
#define ENABLE_UART_FW_FLAG 0
#endif


#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
 #include <drivers/uart.h> 
 #include "../buffers/fifo_gen.h"


 typedef enum{
	 ok = 0,
	 invalid_param,
	 keys_not_init,
	 no_free_ch,
	 silent,
	 busy,
	 mac_paused, 
	 denied,
	 accepted,
	 not_joined,
	 frame_counter_err_rejoin_needed,
	 invalid_data_len,
	 mac_tx_ok,
	 max_rx,
	 no_ack,
	 mic_error
 } WLR_RESPONSE_CODE;

 typedef enum{
	 EU868,
	 EU433,
	 NA915,
	 KR290,
	 JPN923,
	 AS923,
	 IND865
 } WLR_MAC_BAND;

 typedef enum{
	 STANDBY,
	 BACKUP
 } WLR_SYS_SLEEP_TYPE;

extern const unsigned char  	        uart_fw_tx_buf_gnss[256];

int 	uart_fw_init( uart_irq_callback_user_data_t uart_cb);
void 	uart_fw_enable( void );
void 	uart_fw_disable( void );
int 	uart_fw_transmit_string(const unsigned char* data,uint8_t length);
int 	uart_fw_transmit_char(unsigned char data );
bool 	uart_fw_receive_char(uint8_t* c);			//not required in current scenario;implemented as blocking, change to INT if required
void 	uart_fw_reset( void );
void 	uart_fw_shutdown( void );
fifo_gen_buffer_t* get_rx_buffer();
fifo_gen_buffer_t* get_tx_buffer();


#endif /* SRC_WLR08Uu0_H_ */
