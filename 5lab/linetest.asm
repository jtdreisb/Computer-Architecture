    addi $sp, $0, 100
    addi $a0, $0, 0  #loads stuff to pass to function body  
    addi $a1, $0, 0  
    addi $a2, $0, 30  
    addi $a3, $0, 0  
    jal line    
    j end 
plot: sw $a0, 0($t9)  
    addi $t9, $t9, 1  
    sw $a1, 0($t9)   
    jr $ra  
abs: addi $t1, $0, 1  
    addi $t2, $0, 31  
loop: add $t1, $t1, $t1 #multiply by 2  
    addi $t2, $t2, -1  
    bne  $0, $t2, loop  
    and $t3, $t1, $a0 #check for negativity  
    bne $0, $t3, invert  
    add $v0, $a0, $0  
    jr $ra  
invert: sub $v0, $a0, $0  
    jr $ra  
line: add $s0, $0, $a0  #first copy over all the args
    add $s1, $0, $a1  
    add $s2, $0, $a2  
    add $s3, $0, $a3  
    sub $t1, $s1, $s3  #calculate dy
    add $a0, $0, $t1  #load dy for abs
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal abs  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
    add $t1, $0, $v0  #this will collide !!!!!! TODO
    sub $t2, $s0, $s2  # and dx
    add $a0, $0, $t2  
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal abs  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
    add $t2, $0, $v0  
    slt $t0, $t2, $t1  
    bne $0, $t0, setst  
    addi $s4, $0, 1   
    j swapxy  
setst: add $s4, $0, $0   
swapxy: bne $0, $s4, doswapxy  
    j swapx  
doswapxy: add $s0, $s0, $s1  
    sub $s1, $s1, $s0  
    sub $s0, $s1, $s0  
    add $s2, $s2, $s3  
    sub $s3, $s3, $s2  
    sub $s2, $s3, $s2  
swapx:  slt $t1, $s2, $s0  
    bne $0, $t1, doswapx  
    j getdelta  
doswapx: add $s0, $s0, $s2  
    sub $s2, $s2, $s0  
    sub $s0, $s2, $s0  
  
    add $s1, $s1, $s3  
    sub $s3, $s3, $s1  
    sub $s1, $s3, $s1  
getdelta: sub $s5, $s0, $s2  
    sub $a0, $s1, $s3  
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal abs  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
    add $s6, $v0, $0  
    add $t1, $s1, $0  
    add $s7, $0, $0  
    add $t0, $s0, $0  
    slt $t3, $s1, $s3  
    bne $t3, $0, pos   
    addi $t2, $0, -1  
    j init  
pos: addi $t2, $0, 1  
init: addi $s2, $s2, 1  
loop2: bne $s4, $0, rev  
    add $a0, $t0, $0  
    add $a1, $t1, $0  
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal plot  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
    j error  
rev: add $a1, $t0, $0  
    add $a0, $t1, $0  
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal plot  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
error: add $s7, $s7, $s6  
    add $t4, $s7, $s7 # 2 * error  
    addi $t4, $t4, 1  
    slt $t5, $s5, $t4 #2*error >= deltax  
    bne $0, $t5, skip  
    add $t1, $t1, $t2  
    sub $s7, $s5, $s7  
skip: slt $t5, $t0, $s2  
    addi $t0, $t0, 1  
    bne $0, $t5, finish  
    j loop2  
finish: jr $ra  
end: and $t1, $0, $0
