/* 
   This file contains all useful functions that the
   bootloader needs at different moments.
*/

#include "bl_utilities.h"

uint32_t char_to_int(char *str, int *no_hex) {
  uint32_t addr = 0;
  int i;
  for (i=0; i<STR_SIZE; i++) {
    //characters '0-9'
    if ( (str[i]>='0') && (str[i]<='9') )
      /* shift address to left (i.e. addr*=16) and add new character's value
         ('1'-'0' is equal to 1, since in ascii all numbers are adjacent */
      addr = (addr << 4) + (str[i]-'0');

    //characters 'a-f'
    else if ( (str[i]>='a') && (str[i]<='f') )
      /* same procedure as for numbers. Letter ascii codes are also 
         adjacent. We add 10 because letter a equals 10 (hexa), letter
         b equals 11, etc.*/
      addr = (addr << 4) + (10+str[i]-'a');

    //character wasn't part of a hex number
    else {
      *no_hex = 1;
      return 0;
    }
  }
  return addr;
}

void int_to_char(uint32_t content, char *str) {
  uint32_t i = content;
  static const char characters[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
  int j = STR_SIZE-1;
  while (j>=0) {
    str[j] = characters[i % 16];
    i = i/16;
    j --;
  }
  //the end of string character
  str[STR_SIZE] = '\0';
}
