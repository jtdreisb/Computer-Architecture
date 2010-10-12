# Jason Dreisbach
# Matt Duhon
# 
# #include <stdio.h>
# 
# 
# int cube(int num) {
# 	int i,j, c = 0;
# 	
# 	for(i = 0; i < num; i++) {
# 		for( j = 0; j < num; j++) {
# 			c += num;
# 		}
# 	}
# 	return c;
# }
# 
# int main() {
# 	
# 	printf("3 cubed is %d", cube(3));
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
	.asciiz " This program cubes a positive integer \n\n"

prompt:
	.asciiz " Enter an integer: "

sumText: 
	.asciiz " \n Cube = "

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
	ori     $a0, $a0,0x2A
	syscall

	# Read 1st integer from the user (5 is loaded into $v0, then a syscall)
	ori     $v0, $0, 5
	syscall

	# Clear $s0 for the sum
	ori     $s0, $0, 0  # c	
	ori	$s1, $0, 0  # i 

	add	$s3, $v0, 0
	


squareLoop:
	addi	$s1, $s1, 1
	ori	$s2, $0, 0  # j
cubeLoop:
	addi	$s2, $s2, 1

	
	# Magic happens here \/
	add	$s0, $s3, $s0

	bne	$s2, $s3, cubeLoop
	bne	$s1, $s3, squareLoop


	# (could have put 1st integer into $s0 and skipped clearing it above)
	
	# Display prompt (4 is loaded into $v0 to display)
	# 0x22 is hexidecimal for 34 decimal (the length of the previous welcome message)
	ori     $v0, $0, 4			
	lui     $a0, 0x1001
	ori     $a0, $a0,0x26
	syscall

	
	# Display the sum text
	ori     $v0, $0, 4			
	lui     $a0, 0x1001
	ori     $a0, $a0,0x40
	syscall
	
	# Display the sum
	# load 1 into $v0 to display an integer
	ori     $v0, $0, 1			
	add 	$a0, $s0, $0
	syscall
	
	# Exit (load 10 into $v0)
	ori     $v0, $0, 10
	syscall

