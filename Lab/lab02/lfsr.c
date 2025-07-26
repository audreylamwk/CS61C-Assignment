#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    unsigned xor0 = (* reg >> 2 & 0x1) ^ (* reg & 0x1);
    unsigned xor1 = xor0 ^ (* reg >> 3 & 0x1);
    unsigned xor2 = xor1 ^ (* reg >> 5 & 0x1);
    // shift 1 bit to the right
    * reg >>= 1;
    // set 15th bit as result of xors
    * reg |= (xor2 << 15);
}

