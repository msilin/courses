.data
table1:    .word



.text

la    	$a1, table1
Addi $t4, $zero, 8
				#t4 is our bit counter             
Addi $t3, $zero, 9
				#t3 is used to distinguish the difference 
				#between 1-9 and A-F on ASCII table  
           
				Li $a0, 0

				#Test value -> $a0, delete this line 
				#before turnin

BINTOHEX: LUI $t0, 0xF000
	     AND $t0, $t0, $a0
		Srl $t0, $t0, 28

		#move the left 4 bits to the right 4 bit location

		bgt $t0, $t3, AthruF

           #if selected 4bit is > 9, branch to AthruF ascii

OnethruNine:             ADDi $t0, $t0, 48
				   j Return

AthruF:	ADDi $t0, $t0, 55

Return:	Sb $t0, ($a1)
		ADDi $a1, $a1, 1
		SLL $a0, $a0, 4
		Addi $t4, $t4, -1
			
		#store byte, increment pointer, shift a0 left, 				#lower bit counter
			
		Bgt $t4, $zero, BINTOHEX
		sb $zero, ($a1)
		
		#add 0 to the end
		li $v0, 4 
		la $a0, table1     # $address of string to print
    		syscall  


