#ifndef BL_TIMER_H
#define BL_TIMER_H

#include <stdint.h>

//timer info register
#define TCNTO3 (* (volatile uint32_t *) 0x01d50038)

void set_timer  (int);
void stop_timer ();

#endif /* BL_TIMER_H */
