#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

void serial_init();
void serial_putc(const char c);
char serial_getc();
void serial_puts(const char *s);

#endif /* SERIAL_H */
