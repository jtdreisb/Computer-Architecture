# draw.asm  
# Jason Dreisbach   
# Matt Duhon  
  
#main  
  
        addi $sp, $0, 4095	# initialize stack pointer  
  
          
        addi $a0, $0, 30  #loads stuff to pass to function head  
        addi $a1, $0, 100  
        addi $a2, $0, 40  
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
        addi $t6, $0, 0 #this is holding mem location  
        add $t1, $t2, $a2 # y = r  
        addi $t2, $t2, 3  # g = 3  
        sub $t2, $t2, $a2 # g = 3-r  
        sub $t2, $t2, $a2 # g = 3-2*r  
  
        addi $t3, $t3, 10 # diagonalInc = 10  
        sub $t3, $t3, $a2 # diagonalInc = 10 - r  
        sub $t3, $t3, $a2 # diagonalInc = 10 - 2*r  
        sub $t3, $t3, $a2 # diagonalInc = 10 - 3*r  
        sub $t3, $t3, $a2 # diagonalInc = 10 - 4*r  
  
        addi $t4, $t4, 6 # rightInc = 6  
  
while:  addi $t7, $t0, -1  
        slt $t7, $t7, $t1 # x<= y  
        bne $0, $t7, end  
  
        add $t5, $a0, $t0 #plot (xc+x)  
        sw $t5, 0($t6)   
  
        add $t5, $a1, $t1 #plot (yc+y)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location  
          
  
        add $t5, $a0, $t0 #plot (xc+x)  
        sw $t5, 0($t6)   
  
        sub $t5, $a1, $t1 #plot (yc-y)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location  
  
        sub $t5, $a0, $t0 #plot (xc-x)  
        sw $t5, 0($t6)   
  
        add $t5, $a1, $t1 #plot (yc+y)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location  
          
  
        sub $t5, $a0, $t0 #plot (xc-x)  
        sw $t5, 0($t6)   
  
        sub $t5, $a1, $t1 #plot (yc-y)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location  
  
   
        add $t5, $a0, $t1 #plot (xc+y)  
        sw $t5, 0($t6)   
  
        add $t5, $a1, $t0 #plot (yc+x)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location  
          
  
        add $t5, $a0, $t1 #plot (xc+y)  
        sw $t5, 0($t6)   
  
        sub $t5, $a1, $t0 #plot (yc-x)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location  
  
        sub $t5, $a0, $t1 #plot (xc-y)  
        sw $t5, 0($t6)   
  
        add $t5, $a1, $t0 #plot (yc+x)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location  
          
  
        sub $t5, $a0, $t1 #plot (xc-y)  
        sw $t5, 0($t6)   
  
        sub $t5, $a1, $t0 #plot (yc-x)  
        sw $t5, 0($t6)   
        addi $t6, $t6, 1 #this is holding mem location         
  
        addi $t5, $t2, 1  
        slt $t5, $0, $t5 # g >=0   
        bne $t5, $0, if  
  
        add $t2, $t2, $t4 #g += rightInc  
        addi $t3, $t3, 4  #diagonalInc += 4  
        j after  
  
if:     add $t2, $t2, $t3 #g += diagonalInc  
        addi $t3, $t3, 8  #diagonalInc += 8  
  
after:  addi $t4, $t4, 4  #rightInc += 4  
        addi $t0, $t0, 1  # x += 1  
  
        j while  
  
end: jr $ra         
  
  
#a0 = first point  
#a1 = second point  
#a2 = location to start storing  
  
plot:   sw $a0, 0($a2)  
        addi $a2, $a2, 1  
        sw $a1, 0($a2)   
        jr $ra  
#$a0 - x  
#$v0 - return absolute val  
abs: addi $t1, $0, 1  
    addi $t2, $0, 31  
loop: add $t1, $t1, $t1 #multiply by 2  
    addi $t2, $t2, -1  
    bne  $0, $t2, loop  
#now we have a mask  
    and $t3, $t1, $a0 #check for negativity  
    bne $0, $t3, invert  
    add $v0, $a0, $0  
    jr $ra  
invert: sub $v0, $0, $a0  
    jr $ra  
  
# Draw Line    
#$a0 - x0  
#$a1 - y0  
#$a2 - x1  
#$a3 - y1  
#$s4 - st  
#$s5 - dx  
#$s6 - dy  
#$s7 - error  
#$t0 - x  
#$t1 - y  
#$t2 - ystep  
line: add $s0, $0, $a0  
    add $s1, $0, $a1  
    add $s2, $0, $a2  
    add $s3, $0, $a3  
    sub $t1, $a3, $a1  
    sub $t2, $a2, $a0  
  
#absolute val of y1-y0  
    add $a0, $0, $t1  
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal abs  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
    add $t1, $0, $v0  
  
#absolute val of x1-x0  
    add $a0, $0, $t2  
    addi $sp, $sp, -1  
    sw $ra, 0($sp)  
    jal abs  
    lw $ra, 0($sp)  
    addi $sp, $sp, 1  
    add $t2, $0, $v0  
  
#test dx < dy  
    slt $t0, $t2, $t1  
    bne $0, $t0, setst  
    addi $s4, $0, 1   
    j swapxy  
setst: add $s4, $0, $0   
swapxy: bne $0, $s4, doswapxy  
    j swapx  
doswapxy: add $s0, $s0, $s1  
        sub $s1, $s0, $s1  
        sub $s0, $s0, $s1  
  
        add $s2, $s2, $s3  
        sub $s3, $s2, $s3  
        sub $s2, $s2, $s3  
  
swapx:  slt $t1, $s2, $s0  
        bne $0, $t1, doswapx  
        j getdelta  
# swap (x0 , x1) (y0, y1)  
doswapx: add $s0, $s0, $s2  
    sub $s2, $s0, $s2  
    sub $s0, $s0, $s2  
  
    add $s1, $s1, $s3  
    sub $s3, $s1, $s3  
    sub $s1, $s1, $s3  
getdelta: sub $s5, $s2, $s0  
        sub $a0, $s3, $s1  
        addi $sp, $sp, -1  
        sw $ra, 0($sp)  
        jal abs  
        lw $ra, 0($sp)  
        addi $sp, $sp, 1  
        add $s6, $v0, $0  
# y = y0  
        add $t1, $s1, $0  
# x = x0  
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
    sub $s7, $s7, $s5  
#loop check  
skip: slt $t5, $t0, $s2  
    addi $t0, $t0, 1  
    bne $0, $t5, finish  
    j loop2  
finish: jr $ra  
  
close: add $s1, $0, $0  
  
