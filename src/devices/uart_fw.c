/*
 * uart_fw.c
 *
 *  Created on: Mar 27, 2017
 *      Author: Waseemh
 */

#include "uart_fw.h"

 #include <zephyr.h>                                                                                                     
 #include <logging/log.h> 
 LOG_MODULE_REGISTER(cslim_uart_fw, LOG_LEVEL_INF);                                                                                           
 #include <drivers/gpio.h>

/*
 * Zephyr devices
 */
 #define WLR_UART_DEVICE_NAME		DT_LABEL(DT_ALIAS(uart1))



const struct device *uart_uart_fw;

 
 /* End of Zephyr devices*/

//const unsigned char  	        uart_fw_tx_buf_gnss[256];
static 			char 			uart_fw_isr_rx_tx_char='0';

fifo_gen_buffer_t tx_buf;
fifo_gen_buffer_t rx_buf;

uint8_t to_send;

int uart_fw_init( uart_irq_callback_user_data_t uart_cb) {
	fifo_gen_init(&tx_buf);
	fifo_gen_init(&rx_buf);

    LOG_INF("wlr init");


    if (ENABLE_UART_FW_FLAG) {
        uint8_t err;
        //Enable UART
        uart_uart_fw = device_get_binding(WLR_UART_DEVICE_NAME);        
        if(uart_uart_fw == NULL)
        {
            LOG_ERR("Uart UART_FW not configured");
        }
        


        //uart_irq_update(uart_uart_fw);
        //uart_rx_enable(uart_uart_fw, rx_buf.buffer, FIFO_GEN_MAX_SIZE, 1);
        
        uart_irq_callback_user_data_set(uart_uart_fw, uart_cb, NULL); 
        uart_irq_rx_enable(uart_uart_fw);
        err = uart_irq_tx_complete(uart_uart_fw);
        if(err)
        {
            LOG_ERR("Error init 1");
        }
        uart_irq_tx_enable(uart_uart_fw);

    }
    else uart_fw_shutdown();
    return 0;
}

void uart_fw_enable( void ) {
    //if (ENABLE_UART_FW_FLAG) USART_Enable(UART_FW_USART, usartEnable);
}


void uart_fw_disable( void ) {
    //if (ENABLE_UART_FW_FLAG) USART_Enable(UART_FW_USART, usartDisable);
}


int uart_fw_transmit_string(const unsigned char* data, uint8_t length) {
    if (ENABLE_UART_FW_FLAG) {
        int loop_var = 0;
        int ret_val = 0;
        if (!fifo_gen_is_full(&tx_buf)) {
            for (loop_var = 0; loop_var < length; loop_var++) {
                fifo_gen_add(&tx_buf, data[loop_var]);
            }
            uart_irq_tx_enable(uart_uart_fw);
            ret_val = 1;
        } else {
            ret_val = -1;
        }
        return ret_val;
    }
    else return 1;
}


int uart_fw_transmit_char(uint8_t data) {
    if (ENABLE_UART_FW_FLAG) {
        int ret_val = 0;
        if (!fifo_gen_is_full(&tx_buf)) {
            fifo_gen_add(&tx_buf, data);
                    uart_irq_tx_enable(uart_uart_fw);
            ret_val = 1;
        } else {
            ret_val = -1;
        }
        return ret_val;
    }
    else return 1;
}


bool 	uart_fw_receive_char(uint8_t* c){
	*c ='@';
    if (ENABLE_UART_FW_FLAG) {
        if (!fifo_gen_is_empty(&rx_buf)) {
            (*c) = fifo_gen_remove(&rx_buf);
            return true;
        }
    }
	return false;
}


void uart_fw_reset( void ) {
    //if (ENABLE_UART_FW_FLAG) USART_Reset(UART_FW_USART);
}


void uart_fw_shutdown( void ) {
//	gpio_pin_set(gpio_uart_fw_nen, UART_FW_nEN_GPIO_PIN, 1);
}

fifo_gen_buffer_t* get_rx_buffer()
{
    return &rx_buf;
}
fifo_gen_buffer_t* get_tx_buffer()
{
    return &tx_buf;
}

/*****************************************************************************************************************************
 * LoRaWAN Parser functions, 
 * For use with https://github.com/MicrochipTech/atsamr34_lorawan_rn_parser/blob/master/02_command_guide/README.md#top
 ***************************************************************************************************************************** */
/*
WLR_RESPONSE_CODE wlr_sys_sleep_ms(uint32_t ms);
WLR_RESPONSE_CODE wlr_sys_reset();
WLR_RESPONSE_CODE wlr_sys_factory_reset();
WLR_RESPONSE_CODE wlr_sys_set_customparam(uint32_t param);
int wlr_sys_get_customparam();
void wlr_sys_get_ver(char* charstring); //use strcpy
int wlr_sys_get_hweui();*/

