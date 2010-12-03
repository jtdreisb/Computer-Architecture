# draw.asm  
# Jason Dreisbach   
# Matt Duhon  
  
#main  
  
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
        addi $a2, $0, 40  
        addi $a3, $0, 95  
        jal line    
        j close    
#$a0 = xc  
#$a1 = yc  
#$a2 = r  
#$t0 - $t4 are x, y, g, diagonalInc, rightInc respectively   
  
  
#clearing variables  
circle: and $t0, $0, $0  
        and $t1, $0, $0   
        and $t2, $0, $0   
        and $t3, $0, $0   
        and $t4, $0, $0   
  
#setting variables          
        add $t1, $0, $a2 # y = r  
        addi $t2, $t2, 3  # g = 3  
        sub $t2, $a2, $t2 # g = 3-r  
        sub $t2, $a2, $t2 # g = 3-2*r  
  
        addi $t3, $0, 10 # diagonalInc = 10  
        sub $t3, $a2, $t3 # diagonalInc = 10 - r  
        sub $t3, $a2, $t3 # diagonalInc = 10 - 2*r  
        sub $t3, $a2, $t3 # diagonalInc = 10 - 3*r  
        sub $t3, $a2, $t3 # diagonalInc = 10 - 4*r  
  
        addi $t4, $0, 6 # rightInc = 6  
  
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
  
plot: sw $a0, 0($t9)  #
    sw $a1, 1($t9)   #
    addi $t9, $t9, 2 #  
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
init: addi $s2, $s2, 0  #
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
close: add $s1, $0, $0  
  
