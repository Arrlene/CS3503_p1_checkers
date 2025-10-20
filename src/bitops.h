#ifndef BITOPS_H
#define BITOPS_H


#include <stdint.h>

unsigned int set_bit_u32(unsigned int value, int position);
unsigned int clear_bit_u32(unsigned int value, int position);
unsigned int toggle_bit_u32(unsigned int value, int position);
int get_bit_u32(unsigned int value, int position);
int count_bits_u32(unsigned int value);
unsigned int shift_left_u32(unsigned int value, int positions);
unsigned int shift_right_u32(unsigned int value, int positions);
void print_binary_u32(unsigned int value);
void print_hex_u32(unsigned int value);

#endif