/*
  This program illuminates LEDs D3-D6 in 
  chaser mode, and in loop.
*/

#include <stdint.h>

#define PORT_C (* (volatile uint32_t *) 0x01d20014) 
#define PORT_D (* (volatile uint32_t *) 0x01d2002c)
#define BIG_NUMBER 0x0000ffff

int main() {

  while (1) {
    /*volatile keyword is to prevent compiler
    from removing empty loop in O2 optimization*/
    volatile int i; 
    //led D3 on
    PORT_C = 0x2;
    for (i=0; i<BIG_NUMBER; i++);
    //led D3 off, led D4 on
    PORT_C = 0x4; 
    for (i=0; i<BIG_NUMBER; i++);
    //led D4 off, led D5 on
    PORT_C = 0x8;
    for (i=0; i<BIG_NUMBER; i++);
    //led D5 off, led D6 on
    PORT_C = 0x0;
    PORT_D = 0x32; 
    for (i=0; i<BIG_NUMBER; i++);
    //led D6 off
    PORT_D = 0x0;
  }

  return 0;
}
