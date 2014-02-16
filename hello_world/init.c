/*
  This file contains the init procedure
  that prepares the execution environment
  (here by zero-ing out .bss section
  in memory) before we jump to main.
*/

void initialize() {
  extern char _bss, _ebss;
  char *dst = &_bss;

  //zero out .bss
  while (dst < &_ebss) {
    *dst = 0;
    dst ++;
  }

}
