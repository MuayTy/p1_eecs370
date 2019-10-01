	lw	0	2	mcand	//load mcand into reg2
	lw	0	3	mplier	//load mplier into reg3
	lw	0	4	1	//mask in reg4
	lw	0	6	fdigit	//use this to check if 1st digit is 1
check	nor	3	4	5
	beq	5	6	math	//digit was 1, perform math
	beq	0	0	shfmsk	//digit was 0, inc mask for next digit check
	add	0	2	1	//add first round of multi, build onto this location.
shfmsk	add	4	4	4	//left shift mask to check net digit

	beq	1	7	done	//if right answer go to done
	beq	0	0	start
done	halt
mcand	.fill	32766			//binary: 111111111111110
mplier	.fill	10383			//binary: 010100010001111
fdigit	.fill	22384			//        000000000000001
					//nor:    101011101110000
					//decimal 22384
