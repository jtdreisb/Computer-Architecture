# This is test program 1.  This program does nothing useful.
# Assume that the instructions will be stored in a word-addressable memory
	
	add $s0, $0, $0
	addi $t0, $t0, 100
	addi $a0, $a0, 100
test:	add $s0, $s0, $a0 # this is a comment
	addi $a0, $a0, -1
	bne $a0, $0, test	# this is another comment
	addi $a0, $a0, 100
	
test1:    lw	$a0, 8($a1)
	sw $a0, 4($a1)
  j test1		
jr	$ra
	jal test1
	slt $t0, $a0, $a1
	beq $t0, $t1, test
	sub $t3, $t1, $t1




	
