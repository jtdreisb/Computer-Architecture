        addi $sp, $0, 4095	# initialize stack pointer  
        addi $t9, $0, 0 #this is holding mem location  
        addi $a0, $0, 30  #loads stuff to pass to function head  
        addi $a1, $0, 100  
        addi $a2, $0, 20  
        jal circle   
        addi $a0, $0, 30  #loads stuff to pass to function body  
        addi $a1, $0, 80  
        addi $a2, $0, 30  
        addi $a3, $0, 30  
        jal line    
        addi $a0, $0, 20 #loads stuff to pass to function left leg  
        addi $a1, $0, 1  
        addi $a2, $0, 30  
        addi $a3, $0, 30  
        jal line    
        addi $a0, $0, 40 #loads stuff to pass to function right leg  
        addi $a1, $0, 1  
        addi $a2, $0, 30  
        addi $a3, $0, 30  
        jal line    
        addi $a0, $0, 15 #loads stuff to pass to function left arm  
        addi $a1, $0, 60  
        addi $a2, $0, 30  
        addi $a3, $0, 50  
        jal line    
        addi $a0, $0, 30 #loads stuff to pass to function right arm  
        addi $a1, $0, 50  
        addi $a2, $0, 45  
        addi $a3, $0, 60  
        jal line    
        addi $a0, $0, 24 #loads stuff to pass to function left eye  
        addi $a1, $0, 105  
        addi $a2, $0, 3  
        jal circle    
        addi $a0, $0, 36 #loads stuff to pass to function right eye  
        addi $a1, $0, 105  
        addi $a2, $0, 3  
        jal circle    
        addi $a0, $0, 25 #loads stuff to pass to function mouth center  
        addi $a1, $0, 90  
        addi $a2, $0, 35  
        addi $a3, $0, 90  
        jal line    
        addi $a0, $0, 25 #loads stuff to pass to function mouth left  
        addi $a1, $0, 90  
        addi $a2, $0, 20  
        addi $a3, $0, 95  
        jal line    
        addi $a0, $0, 35  #loads stuff to pass to function mouth right  
        addi $a1, $0, 90  
        addi $a2, $0, 20  
        addi $a3, $0, 95  
        jal line    
        j close    
circle: and $t0, $0, $0  
        and $t1, $0, $0   
        and $t2, $0, $0   
        and $t3, $0, $0   
        and $t4, $0, $0   
        add $t1, $0, $a2 # y = r  
        addi $t2, $t2, 3  # g = 3  
        sub $t2, $a2, $t2 # g = 3-r  
        sub $t2, $a2, $t2 # g = 3-2*r  
        addi $t3, $t3, 10 # diagonalInc = 10  
        sub $t3, $a2, $t3 # diagonalInc = 10 - r  
        sub $t3, $a2, $t3 # diagonalInc = 10 - 2*r  
        sub $t3, $a2, $t3 # diagonalInc = 10 - 3*r  
        sub $t3, $a2, $t3 # diagonalInc = 10 - 4*r  
        addi $t4, $t4, 6 # rightInc = 6  
while:  addi $t7, $t1, 1  
        slt $t7, $t0, $t7 # x<= y  
        beq $0, $t7, end  
        add $t5, $a0, $t0 #plot (xc+x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        add $t5, $a1, $t1 #plot (yc+y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location  
        add $t5, $a0, $t0 #plot (xc+x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        sub $t5, $t1, $a1 #plot (yc-y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location  
        sub $t5, $t0, $a0 #plot (xc-x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        add $t5, $a1, $t1 #plot (yc+y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location  
        sub $t5, $t0, $a0 #plot (xc-x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        sub $t5, $t1, $a1 #plot (yc-y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location  
        add $t5, $a0, $t1 #plot (xc+y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        add $t5, $a1, $t0 #plot (yc+x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location  
        add $t5, $a0, $t1 #plot (xc+y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        sub $t5, $t0, $a1 #plot (yc-x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location  
        sub $t5, $t1, $a0 #plot (xc-y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        add $t5, $a1, $t0 #plot (yc+x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location  
        sub $t5, $t1, $a0 #plot (xc-y)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        sub $t5, $t0, $a1 #plot (yc-x)  
        sw $t5, 0($t9)   
        addi $t9, $t9, 1 #this is holding mem location         
        addi $t5, $t2, 1  
        slt $t5, $0, $t5 # g >=0   
        bne $t5, $0, if  
        add $t2, $t2, $t4 #g += rightInc  
        addi $t3, $t3, 4  #diagonalInc += 4  
        j after  
if:     add $t2, $t2, $t3 #g += diagonalInc  
        addi $t3, $t3, 8  #diagonalInc += 8  
        addi $t1, $t1, -1  # y -= 1  
after:  addi $t4, $t4, 4  #rightInc += 4  
        addi $t0, $t0, 1  # x += 1  
        j while  
end: jr $ra         
plot:   sw $a0, 0($t9)  
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
line: add $s0, $0, $a0  
    add $s1, $0, $a1  
    add $s2, $0, $a2  
    add $s3, $0, $a3  
    sub $t1, $a1, $a3  
    sub $t2, $a0, $a2  
    add $a0, $0, $t1  
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal abs  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
    add $t1, $0, $v0  
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
#loop check  
skip: slt $t5, $t0, $s2  
    addi $t0, $t0, 1  
    bne $0, $t5, finish  
    j loop2  
finish: jr $ra  
close: add $s1, $0, $0  
