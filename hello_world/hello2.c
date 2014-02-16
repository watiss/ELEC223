/*
  This program displays the string
  "Hello World!\n" tby sending characters
  through the serial connection.
*/

#include "serial.h"

int main() {
  serial_init();
  const char * const chaine = "Hello World!\r";
  serial_puts(chaine);
  return 0;
}
