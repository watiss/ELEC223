/*
  This file lets you use the timer. Use set_timer function
  to set duration and launch the timer. Stop it with stop_timer.
*/

#include "bl_timer.h"

#define TCNTB3 (* (volatile uint32_t *) 0x01d50030)
#define TCMPB3 (* (volatile uint32_t *) 0x01d50034)
#define TCON   (* (volatile uint32_t *) 0x01d50008)
#define TCFG0  (* (volatile uint32_t *) 0x01d50000)
#define TCFG1  (* (volatile uint32_t *) 0x01d50004)

/* timer 3 start/stop bit */ 
#define T3_onoff (TCON & 0x10000)
/* counter value = 8057 so that it counts for 1s
   since f = 66MHz/(prescaler+1)/divider = 8057Hz */
#define COUNT 0x1f79

void set_timer(int seconds) {
  //wait while timer is not stopped
  while (T3_onoff != 0x0);
  
  //prescaler 255
  TCFG0 = 0xff00;
  //divider 32
  TCFG1 = 0x4000;
  //set timer value
  TCNTB3 = COUNT*seconds;
  //auto-reload off, inverter on, manual update on, stop
  TCON = 0x60000;
  //auto-reload off, inverter off, manual update off, start
  TCON = 0x10000;
}

void stop_timer() {
  //stop timer
  TCON = 0x0;
}
