/*
  This file contains the sub-functions that will be called
  by main according to the command entered by user (L/G/R).
*/
  
#include "bl_commands.h"
#include "bl_serial.h"
#include "bl_utilities.h"

extern char _stack, _ebss;

/* fix start addr to end of bss */ 
static const char *start = &_ebss;
/* fix end addr to beginning of stack - 512B (approx.) */
static const char *end   = &_stack - 0x100;

void load_prg(uint32_t addr) {
  serial_init();

  //check that address is in the right boundary
  if ( (addr>(uint32_t) end) || (addr<(uint32_t) start) ) {
    serial_puts("\r\nAddress not in the right boundary.\r");
    return;
  }
  
  /* receive data to load */
  serial_puts("\r\nSend data to load...\r");
  char c;
  /* timeout_flag is a flag which is set to 1 by 
     serial_getc_timed when time is up. */
  int timeout_flag = 0;
  while (1) {
    c = serial_getc_timed(5, &timeout_flag);
    if (timeout_flag==1) break;
    *((uint8_t *) addr) = c;
    /* since we load byte after byte 
      the next character is loaded at 
      address addr+1 */
    addr ++;
  }
  serial_puts("Time's up. Data has been correctly loaded.\r");  
}

void exec_prg(uint32_t addr) {
  serial_init();
  serial_putc('\n');
  
  /* fct is a function pointer whose address is 
     the address where we want to jump to */
  void (*fct)(void);
  fct = (void (*)(void)) addr;
  fct();
}

void display_mem(uint32_t addr) {
  serial_init();
  serial_puts("\nMemory content:\r");
  /* we display 32bits starting from address */
  uint32_t mem_content = *((uint32_t *) addr);
  /* the +1 is for the '\0' character */
  char mem_content_str[STR_SIZE+1];
  int_to_char(mem_content, mem_content_str);
  serial_puts(mem_content_str);
  serial_putc('\r');
}
