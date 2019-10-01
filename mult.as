	lw	0	2	mcand	//load mcand into reg2
	lw	0	3	mplier	//load mplier into reg3
	lw	0	7	answer	//load answer to know when done
start	




	beq	1	7	done	//if right answer go to done
	beq	0	0	start
done	halt
mcand	.fill	32766
mplier	.fill	10383
answer	.fill	340209378
