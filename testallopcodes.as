	add	0	1	2	load reg1 with 5 (symbolic address)
	nor	0	2	7	load reg2 with -1 (numeric address)
start	lw	1	2	1	decrement reg1
	lw	0	1	start	goto end of program when reg1==0
	lw	0	1	-5	go back to the beginning of the loop
	sw	0	1	1	com
	sw	0	1	-1	com
	sw	0	1	start	com
	beq	0	0	start	com
	beq	0	1	1	com
	beq	0	1	-1	com
	jalr	0	1		com
	noop
done	halt				end of program
five	.fill	5
neg1	.fill	-1
stAddr	.fill	start			will contain the address of start (2)
