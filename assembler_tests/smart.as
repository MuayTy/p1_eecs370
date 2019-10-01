	lw	0	1	five	load reg1 with 5 (symbolic address)
	lw	1	2	3	load reg2 with -1 (numeric address)
	nor	1	2	4
start	add	1	2	1	decrement reg1
	beq	0	1	2	goto end of program when reg1==0
	beq	0	0	start	go back to the beginning of the loop
	noop				com1 com2 com 4
done	halt				end of program
five	.fill	5			comments1 com2 com3
neg1	.fill	-1			com1 com2 com3
stAddr	.fill	start			will contain the address of start (2)
