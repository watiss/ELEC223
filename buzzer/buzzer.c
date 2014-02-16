/*
  This program makes the buzzer beep (using a timer
  to invert TOUT3 at frequency 2kHz).
*/

#include <stdint.h>

#define TCNTB3 (* (volatile uint32_t *) 0x01d50030)
#define TCMPB3 (* (volatile uint32_t *) 0x01d50034)
#define TCON   (* (volatile uint32_t *) 0x01d50008)
#define TCFG0  (* (volatile uint32_t *) 0x01d50000)
#define TCFG1  (* (volatile uint32_t *) 0x01d50004)
#define TCNTO3 (* (volatile uint32_t *) 0x01d50038)

#define PORT_E (* (volatile uint32_t *) 0x01d20028)

/* timer 3 start/stop bit */ 
#define T3_onoff (TCON & 0x10000)

/* counter value = 4 so that it counts for (1/(2*10^3))seconds since 
   f = (66MHz)/(prescaler+1)/divider = 8057Hz */
#define COUNT 0x4
/* counter value = 2 so that it reverts TOUT3 every (1/(4*10^3))seconds 
   f = (66MHz)/(prescaler+1)/divider = 8057Hz */

#define COMPARE 0x2

int main() {
  
  //configure E6 to go out on TOUT3
  PORT_E = 0x2000;

  //wait while timer is not stopped
  while (T3_onoff != 0x0);
  
  //prescaler 255
  TCFG0 = 0xff00;
  //divider 32
  TCFG1 = 0x4000;
  //set timer value
  TCNTB3 = COUNT;
  //set compare value
  TCMPB3 = COMPARE;

  //auto-reload on, inverter on, manual update on, stop
  TCON = 0xe0000;
  //auto-reload on, inverter off, manual update off, start
  TCON = 0x90000;
   
  return 0;
}
