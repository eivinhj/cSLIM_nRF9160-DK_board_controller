#include "uart_fw_task.h"

#include <zephyr.h>
#include <logging/log.h>
#include <string.h>

#include "../devices/uart_fw.h"
#include "../buffers/fifo_gen.h"
LOG_MODULE_REGISTER(LoRa_task, LOG_LEVEL_INF);

/* size of stack area used by each thread */
#define TASK_DEFAULT_STACKSIZE 128

/* scheduling priority used by each thread */
#define TASK_DEFAULT_PRIORITY 7

K_FIFO_DEFINE(loRa_task_fifo);

/*
 * INT handlers
 */

static void WLR089U0_ISR(const struct device *dev, void* data) {
	uart_irq_update(dev);
	//LOG_INF("ISR");

	if (uart_irq_tx_ready(dev)){    
        uart_irq_tx_complete(dev);
	}
	if (uart_irq_rx_ready(dev)){
       // LOG_INF("ISR RX Ready");
       
			uint8_t receive_char;
            uart_fifo_read(dev, &receive_char, 1);
			printk("%c", receive_char);      //Forward character to console
	 }
}	


void uart_fw_task(void)
{
	//k_sleep(K_SECONDS(1));
	LOG_INF("Starting Logger forwarding");
	uart_fw_init(WLR089U0_ISR);

	while(1)
	{
		k_sleep(K_FOREVER);
				
	}
}