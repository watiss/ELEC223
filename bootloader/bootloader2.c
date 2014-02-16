/*
  This file is the main program of the bootloader. It:
  -> tells the user how to use the bootloader
  -> treats command entered by user (and checks whether it's syntaxically correct)
  -> deduces command letter (L/G/R) and integer address (converted from string).
  -> calls the right sub-function according to command letter (L/G/R).
*/

#include "bl_commands.h"
#include "bl_serial.h"
#include "bl_utilities.h"

#define HOW_TO "L addr -> load program at addr.\
 G addr -> jump to addr. R addr -> display memory \
at addr. \r\nPut a space between L/G/R and the adress.\
 Adress must be 32-bits and hexadecimal (0x-prefixed).\
 Then press 'Enter'.\r"

int main() {

  serial_init();
  serial_puts(HOW_TO);
  
  while (1) {
    /* 'L'/'R'/'G' (command letter) + ' ' + 8 (adress digits)
       + 2 ('0x') + '\r' ==> a 13-characters str to store what
       user entered */
    char str[13], c;
    int i = 0;

    int timeout_flag = 0;
    do {
      //7s-delay to type something
      c = serial_getc_timed(7, &timeout_flag);
      
      //if timeout, re-time 3s to make it 10s in total
      if (timeout_flag==1) {        
        c = serial_getc_timed(3, &timeout_flag);
        //if 10s time is out, execute code at address 0x00003000
        if (timeout_flag==1) {
          int no_hex = 0;        
          exec_prg( char_to_int("00003000", &no_hex) );
        }
      }

      //echo character
      serial_putc(c);
      str[i] = c;
      i++;
    } while ( (c!=ENTER) && (i<13) );

    //i>=13 and the last character wasn't ENTER
    if (c!=ENTER)
      serial_puts("\r\n***Too many characters.***\r");
    //the last character was ENTER
    else
      //too few chars
      if (i<13)
        serial_puts("\n***Too few characters.***\r");
      else
        if ( (str[0]!='L' && str[0]!='G' && str[0]!='R') 
             || (str[1]!=' ') || str[2]!='0' || str[3]!='x' )
          serial_puts("\n***Invalid syntax.***\r");
        else {
          //extract address from str
          char addr_str[STR_SIZE];
          for (i=4; i<12; i++)
            addr_str[i-4] = str[i];
          //convert string addr to integer
          /* no_hex is a flag which is set to 1 by 
             char_to_int when there is a non 
             hexadecimal character in addr_str. */
          int no_hex = 0;
          uint32_t addr = char_to_int(addr_str, &no_hex);
          if (no_hex==1)
            serial_puts("\n***Address must be hexadecimal and lower case.***\r");
          else if (addr%4 != 0)
            serial_puts("\n***Address must be a multiple of 4.***\r");
          //treat command
          else if (str[0]=='L') load_prg(addr);
          else if (str[0]=='G') exec_prg(addr);
          else if (str[0]=='R') display_mem(addr);
        }
  }

  return 0;
}
