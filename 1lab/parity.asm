# Jason Dreisbach
# Matt Duhon
# #include <stdio.h> 
# 
# int parity(int num) {
# 	int p = 1;
# 	unsigned int mask = 0x80000000;
# 
# 	
# 	while(mask != 0) {
# 
# 		if( mask & num) {
# 			p = !p;
# 		}
# 		mask = mask/2;
# 	}
# 	return p;
# }
# 
# int main() {
# 	
# 	printf("IsEvenParity: %d\n", parity(3));
# 	printf("IsEvenParity: %d\n", parity(2));
# 	printf("IsEvenParity: %d\n", parity(4));
# 	printf("IsEvenParity: %d\n", parity(0));
# 	printf("IsEvenParity: %d\n", parity(1));
# 	printf("IsEvenParity: %d\n", parity(5));
# 
# 	return 0;
# 
# }



#########################
# ASM code follows
#########################



# Demo Program
# 
#   CPE 315


# declare global so programmer can see actual addresses.
.globl welcome
.globl prompt
.globl sumText

#  Data Area (this area contains strings to be displayed during the program)
.data

welcome:
	.asciiz " This program determines parity of an integer \n\n"
#48
#0x30

prompt:
	.asciiz " Enter an integer: "
#67
#0x43
sumText: 
	.asciiz " \n Parity = "
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

	# Display prompt
	ori     $v0, $0, 4			
	
	# This is the starting address of the prompt (notice the
	# different address from the welcome message)
	lui     $a0, 0x1001
	ori     $a0, $a0,0x31
	syscall

	# Read 1st integer from the user (5 is loaded into $v0, then a syscall)
	ori     $v0, $0, 5
	syscall

	# Clear $s1 for the parity 
	ori     $s1, $0, 1  # P 

	# Load $s0 for the mask 
	addi	$s0,  $0, 1
	sll	$s0,$s0, 31

	add	$s3, $v0, 0
	


loop:
	# Magic happens here \/
	and	$s2, $s3, $s0
	beq	$s2, $0, skip	
	xori	$s1, $s1, 0x1

skip:	srl	$s0, $s0, 1
	bne	$s0, $0, loop


	# (could have put 1st integer into $s0 and skipped clearing it above)
	
	# Display output string
	# 0x22 is hexidecimal for 34 decimal (the length of the previous welcome message)
	ori     $v0, $0, 4			
	lui     $a0, 0x1001
	ori     $a0, $a0,0x46
	syscall

	
	# Display the sum
	# load 1 into $v0 to display an integer
	ori     $v0, $0, 1			
	add 	$a0, $s1, $0
	syscall
	
	# Exit (load 10 into $v0)
	ori     $v0, $0, 10
	syscall


