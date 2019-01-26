	
		#fff0 0nn0 0000 x000 yyyy 0000 0000 0000
		#0000 0000 0000 0000 yyyy 000x 0fff 00nn
		
		#0001 1001 1111 0111 0000 1111 1111 1111
		
		 #15F70FFF

.data

table1:  .asciiz "Error, 1 detected when expecting a 0\n" 


.text
li $v0, 4
la $a0, table1
syscall

	li $a2,   0x6608C000 
	jal PART6
       
        
	li $a2,   0xC2008000 
	jal PART6
	

	li $v0, 10
  	syscall




PART6:  and $v1, $v1, $zero   #v1 = 0 if valid input
        		      #a2 -> input parameter
li $t7,   0x15F70FFF         #a0 is used to make sure all of the zeros are zeros
and $t7, $a2, $t7  
slt $v1, $zero, $t7          #v1 = 1 if invalid input

         

addi $sp, $sp, -4
sw $a2, 0($sp)
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
add $fp, $sp, $zero
sw $fp, 0($sp)


li $t0, 0x0000F000           #place y in a0
and $v0, $t0, $a2


li $t3, 0xE0000000           # t3-> f mask
and $t1, $a2, $t3
srl $t0, $t1 , 25
add $v0, $t0, $v0

li $t3, 0x06000000           # t3-> n mask
and $t1, $a2, $t3
srl $t0, $t1 , 25
add $v0, $t0, $v0

li $t3, 0x00008000           # t3-> x mask
and $t1, $a2, $t3
srl $t0, $t1 , 7
add $v0, $t0, $v0

jr $ra


	#0000c133   00008161	
			
		


