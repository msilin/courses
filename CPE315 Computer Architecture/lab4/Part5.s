.data
.text
main: 

#load value into $a0
   li $a0, 0x12341234

   #load values into $a1
   li $a1, 0x56785678

   #load shift value into $a2
   li $a2, 0x00000004
   #place 32- shift value into $t0
   li $t0, 32
   sub $t0, $t0, $a2
   #place the value that "falls off" of right end of $a0 into $t0
   sllv $t0, $a0, $t0
   #do shifting
   srlv $a1, $a1, $a2
   srlv $a0, $a0, $a2
   or $a1, $t0, $a1
.end