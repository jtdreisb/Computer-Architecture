    addi $sp, $0, 100#
    addi $a0, $0, 1  #loads stuff to pass to function body  #
    addi $a1, $0, 2  #
    addi $a2, $0, 30  #
    addi $a3, $0, 20  #
    jal line    #
    j end #
plot: sw $a0, 0($t9)  #
    addi $t9, $t9, 1  #
    sw $a1, 0($t9)   #
    jr $ra  #
abs:    add $v0, $0, $a0  #
        slt $t8, $a0, $0  #
        beq $t8, $0, jumpTo  #
        sub $v0, $v0, $0   #
jumpTo: jr $ra    #
line: add $s0, $0, $a0  #first copy over all the args#
    add $s1, $0, $a1  #
    add $s2, $0, $a2  #
    add $s3, $0, $a3  #
    sub $t1, $s1, $s3  #calculate dy#
    add $a0, $0, $t1  #load dy for abs#
    addi $sp, $sp, -1  #
    sw $ra, 0($sp)  #
    jal abs  #
    lw $ra, 0($sp)  #
    addi $sp, $sp, 1  #
    add $t1, $0, $v0  # save the value of v0
    sub $t2, $s0, $s2  # and dx#
    add $a0, $0, $t2  #
    addi $sp, $sp, -1  #
    sw $ra, 0($sp)  #
    jal abs  #
    lw $ra, 0($sp)  #
    addi $sp, $sp, 1  #
    add $t2, $0, $v0  #
    slt $t0, $t2, $t1  # abs(dx) < abs(dy)
    bne $0, $t0, setst  #
    addi $s4, $0, 0   #
    j swapxy  #
setst: addi $s4, $0, 1   #
swapxy: beq $0, $s4, swapx  #
    add $s0, $s0, $s1  #
    sub $s1, $s1, $s0  #
    sub $s0, $s1, $s0  #
    add $s2, $s2, $s3  #
    sub $s3, $s3, $s2  #
    sub $s2, $s3, $s2  #
swapx:  slt $t1, $s2, $s0  # x1 < x0
    beq $0, $t1, getdelta  #
    add $s0, $s0, $s2  #
    sub $s2, $s2, $s0  #
    sub $s0, $s2, $s0  #
    add $s1, $s1, $s3  #
    sub $s3, $s3, $s1  #
    sub $s1, $s3, $s1  #
getdelta: sub $s5, $s0, $s2  #
    sub $a0, $s1, $s3  #
    addi $sp, $sp, -1  #
    sw $ra, 0($sp)  #
    jal abs  #
    lw $ra, 0($sp)  #
    addi $sp, $sp, 1  #
    add $s6, $v0, $0  # set delta y
    add $t1, $s1, $0  # setting y to y0
    add $s7, $0, $0  # error?
    add $t0, $s0, $0  # x = x0
    slt $t3, $s1, $s3  # y0 < y1
    beq $t3, $0, negyStep   #
    addi $t2, $0, 1  #
    j init  #
negyStep: addi $t2, $0, -1  #
init: addi $s2, $s2, 1  #
loop2: bne $s4, $0, rev  # plot(x,y)
    add $a0, $t0, $0  #
    add $a1, $t1, $0  #
    addi $sp, $sp, -1  #
    sw $ra, 0($sp)  #
    jal plot  #
    lw $ra, 0($sp)  #
    addi $sp, $sp, 1  #
    j error  #
rev: add $a1, $t0, $0  # plot (y,x)
    add $a0, $t1, $0  #
    addi $sp, $sp, -1  #
    sw $ra, 0($sp)  #
    jal plot  #
    lw $ra, 0($sp)  #
    addi $sp, $sp, 1  #
error: add $s7, $s7, $s6  # error += dy
    add $t4, $s7, $s7 # 2 * error 
    addi $t4, $t4, 1  #
    slt $t5, $s5, $t4 #2*error >= deltax 
    beq $0, $t5, skip  #
    add $t1, $t1, $t2  # y += ystep
    sub $s7, $s5, $s7  # error -dx
skip: slt $t5, $t0, $s2  # if(x < x1)
    addi $t0, $t0, 1  # x++
    bne $0, $t5, loop2  #
finish: jr $ra  #
end: and $t1, $0, $0 #
