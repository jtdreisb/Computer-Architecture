#main

        #loads stuff to pass to function head
        addi $a0, $0, 30
        addi $a1, $0, 100
        addi $a2, $0, 40
        jal circle

        #loads stuff to pass to function body
        addi $a0, $0, 30
        addi $a1, $0, 80
        addi $a2, $0, 30
        addi $a3, $0, 30
        jal line

        #loads stuff to pass to function left leg
        addi $a0, $0, 20
        addi $a1, $0, 1
        addi $a2, $0, 30
        addi $a3, $0, 30
        jal line 

        #loads stuff to pass to function right leg
        addi $a0, $0, 40
        addi $a1, $0, 1
        addi $a2, $0, 30
        addi $a3, $0, 30
        jal line 

        #loads stuff to pass to function left arm
        addi $a0, $0, 15
        addi $a1, $0, 60
        addi $a2, $0, 30
        addi $a3, $0, 50
        jal line 

        #loads stuff to pass to function right arm
        addi $a0, $0, 30
        addi $a1, $0, 50
        addi $a2, $0, 45
        addi $a3, $0, 60
        jal line 

        #loads stuff to pass to function left eye
        addi $a0, $0, 24
        addi $a1, $0, 105
        addi $a2, $0, 3
        jal circle 

        #loads stuff to pass to function right eye
        addi $a0, $0, 36
        addi $a1, $0, 105
        addi $a2, $0, 3
        jal circle

        #loads stuff to pass to function mouth center
        addi $a0, $0, 25
        addi $a1, $0, 90
        addi $a2, $0, 35
        addi $a3, $0, 90
        jal circle

        #loads stuff to pass to function mouth left 
        addi $a0, $0, 25
        addi $a1, $0, 90
        addi $a2, $0, 20
        addi $a3, $0, 95
        jal circle

        #loads stuff to pass to function mouth right
        addi $a0, $0, 35
        addi $a1, $0, 90
        addi $a2, $0, 20
        addi $a3, $0, 95
        jal circle

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
