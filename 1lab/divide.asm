# Jason Dreisbach
# Matt Duhon
#
#int divide(int a1,int a2,int b,int * c1,int *c2) { 
#	int carry;
#	printf("a1=%d\na2 = %d\n", a1,a2);
#	b = b/2;
#	while(b) { 
#		if(a1 & 0x1) { 
#			carry = 1;
#		} else { 
#			carry = 0;
#		}
#		a1 = a1/2;
#		a2 = a2/2;
#		if(carry) {
#			a2 |= 0x80000000;
#		} else {
#			a2 &= 0x7FFFFFFF;
#		}
#		
#		b = b/2;
#	}
#	*c1 = a1;
#       	*c2 = a2;	
#
#	return 0;
#}

# Jason Dreisbach 
# Matt Duhon


#########################
# ASM code follows
#########################



# Demo Program
# 
#   CPE 315


# declare global so programmer can see actual addresses.
.globl welcome
.globl prompt
.globl firstText
.globl secondText

#  Data Area (this area contains strings to be displayed during the program)
.data

welcome:
	.asciiz " This program divides a 64 bit int by a 32 bit one \n\n"

#56
#0x37
prompt:
	.asciiz " Enter an integer: "
#75
#0x50
	
firstText: 
	.asciiz " \n First num  = "
	
secondText:
	.asciiz " \n Second num = "

#79
#0x4F

#Text Area (i.e. instructions)
.text

main:

	# Display the welcome message (load 4 into $v0 to display)
	ori     $v0, $0, 4			
	
	# This generates the starting address for the welcome message.
	# (assumes the register first contains 0).
	lui     $a0, 0x1001
	syscall

	jal getint
	add $s0, $v0, $0

	jal getint
	add $s1, $v0, $0
	
	jal getint
	add $s2, $v0, $0


	# Clear $s1 for the parity 
	add $t1, $0, $0  # Carry 

	# Load $s0 for the mask 
	addi	$t2,  $0, 1 
	sll	$t2,$t2, 31

# s0: a1
# s1: a2
# s2: b
# t1: carry
# t2: bitmask

	srl	$s2, $s2, 1
loop:
	# Magic happens here \/
	srl	$s1, $s1, 1
	andi	$t5, $s0, 1 

	beq	$t5, $0, skip	
	or 	$s1, $s1, $t2

skip:	srl	$s0, $s0, 1
	srl	$s2, $s2, 1
	bne	$s2, $0, loop


	# (could have put 1st integer into $s0 and skipped clearing it above)
	
	# Display output string
	# 0x22 is hexidecimal for 34 decimal (the length of the previous welcome message)
	ori     $v0, $0, 4			
	lui     $a0, 0x1001
	ori     $a0, $a0,0x4a
	syscall

	add $a0, $s0,$0
   	jal outputint

	# Display output string
	# 0x22 is hexidecimal for 34 decimal (the length of the previous welcome message)
	ori     $v0, $0, 4			
	lui     $a0, 0x1001
	ori     $a0, $a0,0x5b
	syscall

	add $a0, $s1, $0
	jal outputint

	# Exit (load 10 into $v0)
	ori     $v0, $0, 10
	syscall


getint: 
		# Display prompt
	ori     $v0, $0, 4			
	
	# This is the starting address of the prompt (notice the
	# different address from the welcome message)
	lui     $a0, 0x1001
	ori     $a0, $a0,0x36
	syscall

	# Read 1st integer from the user (5 is loaded into $v0, then a syscall)
	ori     $v0, $0, 5
	syscall
	jr $ra
	
outputint: 
	# Display the sum
	# load 1 into $v0 to display an integer
	ori     $v0, $0, 1			
	syscall
	jr $ra

