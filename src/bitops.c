#include "bitops.h"
#include <stdio.h>

unsigned int set_bit_u32(unsigned int value, int position){
    if(position < 0 || position >= 32) return value;
    return value | (1u << position);
}

unsigned int clear_bit_u32(unsigned int value, int position){
    if(position < 0 || position >= 32) return value;
    return value & ~(1u << position);
}

unsigned int toggle_bit_u32(unsigned int value, int position){
    if(position < 0 || position >= 32) return value;
    return value ^ (1u << position);
}

int get_bit_u32(unsigned int value, int position){
    if(position < 0 || position >= 32) return 0;
    return (value >> position) & 1u;
}

int count_bits_u32(unsigned int value){
    int c = 0;
    while(value){
        c += value & 1u;
        value >>= 1u;
    }
    return c;
}

unsigned int shift_left_u32(unsigned int value, int positions){
    if(positions <= 0) return value;
    if(positions >= 32) return 0u;
    return value << positions;
}

unsigned int shift_right_u32(unsigned int value, int positions){
    if(positions <= 0) return value;
    if(positions >= 32) return 0u;
    return value >> positions;
}

void print_binary_u32(unsigned int value){
    for(int i=31;i>=0;i--){
        putchar(((value>>i)&1u)?'1':'0');
        if(i%4==0 && i!=0) putchar(' ');
    }
    putchar('\n');
}

void print_hex_u32(unsigned int value){
    printf("0x%08X\n", value);
}