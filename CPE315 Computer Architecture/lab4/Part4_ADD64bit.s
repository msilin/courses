.data
table1:    .word
.text

       la    	$t5, table1
       Addi $t3, $zero, 9
       				#t3 is used to distinguish the difference 
	li $a1 , 0xFFFFFFF1
	li $a3 , 0x0000000F

ADDhi:  addu $v1, $a1, $a3
	sltu $t0, $v1, $a1 #check for carry if result < start
	sltu $t1, $v1, $a3 #check for carry if result < start
	or $t0, $t0, $t1 # or the two potential carry bits

        add $v0, $a0, $a2 # add the high bits
        add $v0, $t0, $v0 # add the carry bit        
        addi $a0, $v0, 0 # transfer high order bits to a0 for printing


	Addi $t4, $zero, 8
				#t4 is our byte counter  
        jal BINTOHEX
        
         addi $a0, $v1, 0 # transfer low order bits to a0 for printing
         Addi $t4, $zero, 8
				#t4 is our byte counter  
         jal BINTOHEX
         li $v0, 4 
	 la $a0, table1     # $address of string to print
	 syscall	         
         li $v0, 10
         syscall
         
BINTOHEX: 			
				#between 1-9 and A-F on ASCII table  
				#Addi $a0, $zero, 0x9A9A
				#Test value -> $a0, delete this line 
				#before turnin
          LUI $t0, 0xF000
	  AND $t0, $t0, $a0
	  Srl $t0, $t0, 28
		#move the left 4 bits to the right 4 bit location
	  bgt $t0, $t3, AthruF
           #if selected 4bit is > 9, branch to AthruF ascii
OnethruNine:   ADDi $t0, $t0, 48	
          j Return

AthruF:	ADDi $t0, $t0, 55
Return:	Sb $t0, ($t5)

	ADDi $t5, $t5, 1
	SLL $a0, $a0, 4
	Addi $t4, $t4, -1
	#store byte, increment pointer, shift a0 left, 				#lower bit counter
	Bgt $t4, $zero, BINTOHEX
	sb $zero, ($t5)
	#add 0 to the end
	
	jr $ra
	
	
	







	




				
		


		
			
		


