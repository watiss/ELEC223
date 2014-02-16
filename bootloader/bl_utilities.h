#ifndef BL_UTILITIES
#define BL_UTILITIES

#include <stdint.h>

#define ENTER '\r'
#define STR_SIZE 8

uint32_t char_to_int (char *, int *);
void     int_to_char (uint32_t, char *);

#endif /* BL_UTILITIES */
