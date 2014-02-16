/*
  This file contains all necessary commands for using the
  serial connection to send/receive characters, including a
  timed version of getc.
*/

#include "bl_serial.h"
#include "bl_timer.h"

#define ULCON0  (* (volatile uint32_t *) 0x01d00000)
#define UCON0   (* (volatile uint32_t *) 0x01d00004)
#define UBRDIV0 (* (volatile uint32_t *) 0x01d00028)

#define URSTAT0 (* (volatile uint32_t *) 0x01d00010)
#define UTXH0   (* (volatile uint8_t  *) 0x01d00020)
#define URXH0   (* (volatile uint8_t  *) 0x01d00024)

#define urstat0_1 (URSTAT0 & 0x2)
#define urstat0_0 (URSTAT0 & 0x1)

void serial_init() {
  //8N1
  ULCON0  = 3;
  //polling for transmit and receive
  UCON0   = 5;
  //115200 baud
  UBRDIV0 = 35;
}

void serial_putc(const char c) {
  /* wait until you can transmit */
  while (urstat0_1 != 0x2);
  /* put c in transmission register */
  UTXH0 = c;
}

char serial_getc() {
  /* wait until you receive something */
  while (urstat0_0 != 0x1);
  /* collect what is in the reception register */
  return URXH0;
}

/* timeout helps to know if loop broke because of timeout or not.
   The content of timeout pointer is set to 1 in case of timeout */
char serial_getc_timed(int seconds, int *timeout) {
  set_timer(seconds);
  /* wait while there is nothing in the reception register
     AND time is not up yet */
  while ( (urstat0_0 != 0x1) && TCNTO3!=0 );
  stop_timer();
  if (TCNTO3==0) {
    *timeout = 1;
    return 0;
  }
  else {
    *timeout = 0;
    return URXH0;
  }
}

void serial_puts(const char *s) {
  /* display each char while '\0' (end of line) 
     is not reached; then add '\n' */
  for (; *s!=0; s++)
    serial_putc(*s);
  serial_putc('\n');
}
