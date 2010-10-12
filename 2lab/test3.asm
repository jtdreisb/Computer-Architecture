#This is test program 3.  This program does nothing useful.
#test3.asm

i:  or $a0, $a1, $a2
and $a0, $s0, $t1
or $s0, $s1, $s2
and $s0, $0, $0

j i #test comment
bne $a0, $a1, i
beq $a2, $a3, i


#more comments




#

