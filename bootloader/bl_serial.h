#ifndef BL_SERIAL_H
#define BL_SERIAL_H

#include <stdint.h>

void serial_init       ();
void serial_putc       (const char);
char serial_getc       ();
char serial_getc_timed (int, int *);
void serial_puts       (const char *);

#endif /* BL_SERIAL_H */
