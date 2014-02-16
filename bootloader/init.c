#include <stdint.h>

#define PCONA  (* (volatile uint32_t *) 0x01d20000) 
#define PDATB  (* (volatile uint32_t *) 0x01d2000c) 
#define PCONB  (* (volatile uint32_t *) 0x01d20008) 
#define PDATC  (* (volatile uint32_t *) 0x01d20014) 
#define PCONC  (* (volatile uint32_t *) 0x01d20010) 
#define PUPC   (* (volatile uint32_t *) 0x01d20018) 
#define PCOND  (* (volatile uint32_t *) 0x01d2001c) 
#define PUPD   (* (volatile uint32_t *) 0x01d20024) 
#define PCONE  (* (volatile uint32_t *) 0x01d20028)
#define PDATE  (* (volatile uint32_t *) 0x01d2002c) 
#define PUPE   (* (volatile uint32_t *) 0x01d20030) 
#define PCONF  (* (volatile uint32_t *) 0x01d20034)
#define PUPF   (* (volatile uint32_t *) 0x01d2003c) 
#define PCONG  (* (volatile uint32_t *) 0x01d20040) 
#define PUPG   (* (volatile uint32_t *) 0x01d20048) 
#define SPUCR  (* (volatile uint32_t *) 0x01d2004c) 
#define INTMOD (* (volatile uint32_t *) 0x01e00008) 
#define EXTINT (* (volatile uint32_t *) 0x01d20050) 

//SDRAM registers
#define REG1  (* (volatile uint32_t *) 0x01c80000)
#define REG2  (* (volatile uint32_t *) 0x01c80004)
#define REG3  (* (volatile uint32_t *) 0x01c80008)
#define REG4  (* (volatile uint32_t *) 0x01c8000c)
#define REG5  (* (volatile uint32_t *) 0x01c80010)
#define REG6  (* (volatile uint32_t *) 0x01c80014)
#define REG7  (* (volatile uint32_t *) 0x01c80018)
#define REG8  (* (volatile uint32_t *) 0x01c8001c)
#define REG9  (* (volatile uint32_t *) 0x01c80020)
#define REG10 (* (volatile uint32_t *) 0x01c80024)
#define REG11 (* (volatile uint32_t *) 0x01c80028)
#define REG12 (* (volatile uint32_t *) 0x01c8002c)
#define REG13 (* (volatile uint32_t *) 0x01c80030)

//watch dog register
#define WTCON  (* (volatile uint32_t *) 0x01d30000)
//INTMSK
#define INTMSK (* (volatile uint32_t *) 0x01e0000c)
//INTCON
#define INTCON (* (volatile uint32_t *) 0x01e00000)
//LOCKTIME
#define LOCK_T (* (volatile uint32_t *) 0x01d8000c)
//PLLCON
#define PLLCON (* (volatile uint32_t *) 0x01d80000)
//CLKON
#define CLKON  (* (volatile uint32_t *) 0x01d80004)

void initialize() {

  /************* initialize the board *************/
  //init registers
  PCONA  = 0x000003ff;
  PDATB  = 0x7cf;
  PCONB  = 0x07ff;
  PDATC  = 0x0100;
  PCONC  = 0xfff5ff54;
  PUPC   = 0;
  PCOND  = 0x0000aaaa;
  PUPD   = 0;
  PCONE  = 0x00021569;
  PDATE  = 0;
  PUPE   = 0;
  PCONF  = 0x24900a;
  PUPF   = 0;
  PCONG  = 0xff3c;
  PUPG   = 0;
  SPUCR  = 0x6;
  INTMOD = 0;
  EXTINT = 0x00040440;

  //init SDRAM
  REG1  = 0x01001102;
  REG2  = 0x00007ff4;
  REG3  = 0x00000a40;
  REG4  = 0x00001480;
  REG5  = 0x00007ffc;
  REG6  = 0x00007ffc;
  REG7  = 0x00000c40;
  REG8  = 0x00018004;
  REG9  = 0x00000a40;
  REG10 = 0x008603fb;
  REG11 = 0x00000010;
  REG12 = 0x00000020;
  REG13 = 0x00000020;
  
  //disable watchdog
  WTCON = 0;
  //other reset configs
  INTMSK = 0x03fffeff;
  INTCON = 0x5;
  LOCK_T = 0xf0;
  PLLCON = 0x0003a031;
  CLKON  = 0x00007ff8; 

  /************* init data and bss sections in memory *************/
  extern char _bss, _ebss, _data, _edata, _erodata;
  char *src = &_erodata;
  char *dst = &_bss;
  
  //zero out .bss
  while (dst < &_ebss) {
    *dst = 0;
    dst ++;
  }
  
  //copy .data from rom to ram
  for (dst=&_data; dst<&_edata; dst++) {
    *dst = *src;
    src ++;
  }
}
