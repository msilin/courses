.data
table1:    .word

#Do we have to use the stack for temporary storage??
#I dont think this is recursive enough

.text

	Addi $t4, $zero, 20
				
				#t4 is our nth fibonnaci number 		
		
	     Addi $t1, $zero, 0 
	     Addi $t2, $zero, 1
	     jal FIBB
		
OUTPUT:    li $v0, 1
		add $a0, $t1, $zero 		     
    		syscall  
		li $v0, 10
   		syscall

	

FIBB: 	Blt $t4, $zero, FIBB2

		Addi $t4, $t4, -1
		addi $sp, $sp, -4 
		sw $ra 0($sp)
	
		#Find next fibb number, shift t2->t1, and t3->t2
		jal FIBB		
		
		Add $t3, $t2, $t1
		Add $t1, $t2, $zero 
		Add $t2, $t3, $zero
		
FIBB2: 	lw $ra,0($sp)  
		add $sp,$sp,4
		jr $ra  


		



		
			
		


