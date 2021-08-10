/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/gpio.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#include "tasks/uart_fw_task.h"
#include "buffers/fifo_gen.h"

/* size of stack area used by each thread */
#define TASK_DEFAULT_STACKSIZE 1024

/* scheduling priority used by each thread */
#define TASK_DEFAULT_PRIORITY 7


void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);
	LOG_INF("Test");
	int ret = 0;
	while(1)
	{
		k_sleep(K_FOREVER);
	}		
}

K_THREAD_DEFINE(uart_fw_task_id, TASK_DEFAULT_STACKSIZE, uart_fw_task, NULL, NULL, NULL, TASK_DEFAULT_PRIORITY, 0, 0);