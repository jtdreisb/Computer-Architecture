    addi $t0, $0, 0  
    addi $t1, $0, 1  
    addi $t2, $0, 2  
    slt  $s0, $t0, $t1   # 0 < 1
    slt  $s2, $t2, $t1  # 2 < 1
    slt  $s3, $t1, $t1  # 1 < 1
