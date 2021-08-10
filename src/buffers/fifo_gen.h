/*
 * fifo_gen_gen.h
 *
 *  Created on: May 18, 2021
 *      Author: Eivinhj
 */

#ifndef FIFO_GEN_H
#define FIFO_GEN_H

#include <stdint.h>
#include <stdbool.h>

#define FIFO_GEN_MAX_SIZE 512

typedef struct {
	uint8_t buffer[FIFO_GEN_MAX_SIZE];
	uint8_t size;
	uint8_t front;
	uint8_t rear;
} fifo_gen_buffer_t;

void fifo_gen_init(fifo_gen_buffer_t* buf);
bool fifo_gen_is_empty(fifo_gen_buffer_t* buf);
bool fifo_gen_is_full(fifo_gen_buffer_t* buf);
char fifo_gen_remove(fifo_gen_buffer_t* buf);
void fifo_gen_add(fifo_gen_buffer_t* buf, char data);
bool fifo_gen_contain_complete_string(fifo_gen_buffer_t* buf);
uint8_t fifo_gen_get_length(fifo_gen_buffer_t* buf);

#endif //FIFO_GEN_H