# This is a test program 2.  This program does nothing useful.

 add    $t0,           $t1, $t2 # more comments
	add $t3,$t4,$t5 # more comments
	add $t6, $t7,      $t8
	sub $t9, $s7, $s6
		sub $s5, $s5, $s4
	sub $s3, $s2, $s1	

	
	bne $sp, $ra, test2	
test2: add $ra, $ra, $a1 # comment on label
	beq $a0, $a1, test2
