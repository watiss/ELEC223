/* Definition des parametres dont vous avez besoin */
        .SET  rPDATC,       0x1d20014 @ Adresse du port C

main: .global main
/*.............mettez votre code ici !!*/
redo:
	ldr r0, =rPDATC
	ldr r1, =0x00000002
	mov r2, #0x0000ff00
	
	str	r1, [r0]
wait1:
	subs r2, r2, #1
	bne wait1
	
	ldr r1, =0
	str	r1, [r0]
wait2:
	adds r2, r2, #1
	cmp r2, #0x0000ff00	
	bne wait2	
	
	b	redo

exit:   NOP
        B exit
