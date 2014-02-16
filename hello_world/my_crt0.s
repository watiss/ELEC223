.global _start
_start:
	LDR sp, = _stack
	bl initialize
	bl main

_exit:
	b _exit
        