.global _start
_start:
	LDR sp, =_stack
	bl main

_exit:
	b _exit
	
