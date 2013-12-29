mov r0, #0xef
add r0,r0, #0xbe00
add r0, r0, #0xad0000
add r0, r0, #0xde000000
mov r1, #0x100
mov r2, #0x100
Loop:	
str r0, [r1], #4
subs r2, r2, #4
bne Loop

mov r1, #0x300
b Loop
	
xxx:b xxx


