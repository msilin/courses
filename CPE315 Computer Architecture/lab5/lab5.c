/*----------------------------------------------------------------------*
 * Example mips_asm program loader. This loads the mips_asm binary   *
 * named "testcase1.mb" into an array in memory. It reads      *
 * the 64-byte header, then loads the code into the mem array. *
 *                         *
 * DLR 4/18/16                   *
 *----------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"

#include "lab5.h"
#define ASCII_OFFSET 48
typedef unsigned int MIPS, *MIPS_PTR;

MB_HDR mb_hdr;    /* Header area */
MIPS mem[1024];      /* Room for 4K bytes */

int main()
  {
  FILE *fd;
  int n;
  int memp;
  int i;
  int code;
  int inst;
  Instruction instruction;
  char filename[] = "testcase1.mb"; /* This is the filename to be loaded */

/* format the MIPS Binary header */

  fd = fopen(filename, "rb");
  if (fd == NULL) { printf("\nCouldn't load test case - quitting.\n"); exit(99); }

  memp = 0;    /* This is the memory pointer, a byte offset */

/* read the header and verify it. */
  fread((void *) &mb_hdr, sizeof(mb_hdr), 1, fd);
  if (strcmp(mb_hdr.signature, "~MB")!=0)
    { printf("\nThis isn't really a mips_asm binary file - quitting.\n"); exit(98); }
  
  printf("\n%s Loaded ok, program size=%d bytes.\n\n", filename, mb_hdr.size);

/* read the binary code a word at a time */
  
  do {
    n = fread((void *) &mem[memp/4], 4, 1, fd); /* note div/4 to make word index */
    if (n) 
      memp += 4;  /* Increment byte pointer by size of instr */
    else
      break;       
    } while (memp < sizeof(mem)) ;

  fclose(fd);


/* ok, now dump out the instructions loaded: */

  for (i = 0; i<memp; i+=4){   /* i contains byte offset addresses */
    instruction.pc= i;
    inst= mem[i/4];
    code= (inst&0xFC000000)>>26;
    if((code)==0){
      /*the instruction is an r-type*/
      setRType(inst, &instruction);
     }
     else if(code!=0){
      if(!(code==0x02||code==0x03)){
        /*the instruction is a i-type*/
        setIType(inst, &instruction);
        printIType(&instruction);
      }
      else
        printJType(inst, &instruction);
     }
     }
  printf("\n");
  //fclose(fd);
  return 0;
  }
  /* this function takes in both the unsigned int instruction value, and a pointer to an Instruction struct.
   * This function has a return type of void. This sets the fields of the instruction struct for an R-type instruction, so it can 
   * be printed out in the proper format
   */
  void setRType(unsigned int inst, Instruction* instruction){
    instruction->code= inst&0x0000003F;
    instruction-> rs= (inst&0x03E00000)>>21;
    instruction-> rt=(inst&0x001F0000)>>16;
    instruction-> rd= (inst&0x0000F800)>>12;
    isValidRType(inst, instruction);
    if(instruction->is_valid==FALSE)
      printf("0X%08X Invalid Instruction\n",inst);
    else{
      printRTypeFields(instruction);
    }

}
/*This function takes an Instruction struct pointer as a parameter. This function has a return type of void. 
 * This function prints out an R-type instruction in the proper format.
*/
void printRTypeFields(Instruction* instruction){
  /*put reg num in proper format(ie. translate from 2 to $v0)*/
  char *rs=NULL;
  char* rd= NULL;
  char* rt= NULL;
  rs=translateRegister(rs, instruction->rs);
  rd=translateRegister(rd, instruction->rd);
  rt=translateRegister(rt, instruction->rt);
  printf("@PC=0x%08X, Opcode= 0x00, R Type, Function= 0x%02X (%s)\n",instruction->pc, instruction->code, instruction->inst_name);
  printf("RS= %d (%s), RT= %d (%s), RD= %d (%s), shamt= %d\n", instruction->rs, rs,instruction->rt, rt, instruction->rd, rd,instruction->shamt);
  free(rs);
  free(rd);
  free(rt);
  free(instruction->inst_name);
}
/*This function takes in a 
 * character pointer to the destination register and
 * an interger representing the register number. 
 * This funciton returns a character pointer to the 
  * destination register. This function translates the 
  * integer register number to the MIPS register 
  * representation of that.
  */
char* translateRegister(char* dst, int reg){
  if(reg==0){
    dst= malloc(sizeof(char)*6);
    dst= strcpy(dst, "$zero");
  }
  else if(reg==1){
    dst= malloc(sizeof(char)*4);
    dst=strcpy(dst, "$at");
  }
  else if(reg>1&&reg<4){
    dst= malloc(sizeof(char)*4);
    dst= strcpy(dst, "$v");
    dst[2]=(char)(reg-2+ASCII_OFFSET);
    dst[3]= (char)0;
  }
  else if(reg>=4&&reg<8){
    dst= malloc(sizeof(char)*4);
    dst= strcpy(dst, "$a");
    dst[2]=(char)(reg-4+ASCII_OFFSET);
    dst[3]= (char)0;
  }
  else if(reg>=8 && reg<16){
    dst= malloc(sizeof(char)*4);
    dst= strcpy(dst, "$t");
    dst[2]=(char)(reg-8+ASCII_OFFSET);
    dst[3]=(char)0;
  }
  else if(reg>=16&&reg<24){
    dst= malloc(sizeof(char)*4);
    dst= strcpy(dst, "$s");
    dst[2]= (char)(reg-16+ASCII_OFFSET);
    dst[3]=(char)0;
  }
  else if(reg>=24&&reg<26){
    dst= malloc(sizeof(char)*4);
    dst= strcpy(dst, "$t");
    dst[2]=(char)(reg-16+ASCII_OFFSET);
    dst[3]=(char)0;
  }
  else if(reg>=26&&reg<28){
    dst=malloc(sizeof(char)*4);
    dst= strcpy(dst, "$k");
    dst[2]=(char)(reg-26+ASCII_OFFSET);
    dst[3]=(char)0;
  }
  else if(reg==28){
    dst= malloc(sizeof(char)*4);
    dst=strcpy(dst, "$gp");
  }
  else if(reg==29){
    dst= malloc(sizeof(char)*4);
    dst= strcpy(dst, "$sp");
  }
  else if(reg==30){
    dst= malloc(sizeof(char)*4);
    dst= strcpy(dst, "$fp");
  }
  else if(reg==31){
    dst= malloc(sizeof(char)*4);
    dst=strcpy(dst, "$ra");
  }
  if(dst==NULL){
    fprintf(stderr, "bad strcpy in translate register\n");
    exit(1);
  }
  return dst;
}
  /* determines if the instruction is a valid R type instruction. also sets the inst name parameter. Also sets the shamt field of
   * the instruction struct for the necessary shift instructions. It has a return type of void. It takes in the 
   * unsigned int representing the instruction and a pointer to the instruction struct.
   */
  void isValidRType(unsigned int inst, Instruction* instruction){
    char* str= NULL;
    if(instruction->code==0x20){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name,"add");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x21){
      allocateMemInstName(instruction, 4);
      str= strcpy(instruction->inst_name, "addu");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x22){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "sub");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x23){
      allocateMemInstName(instruction, 4);
      str= strcpy(instruction->inst_name, "subu");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x24){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "and");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x27){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "nor");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x25){
      allocateMemInstName(instruction, 2);
      str= strcpy(instruction->inst_name, "or");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x26){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "xor");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    /*shift instructions*/
    if(instruction->code==0x00){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "sll");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      setShamt(inst, instruction);
      return;
    }
    if(instruction->code==0x02){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "srl");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      setShamt(inst, instruction);
      return;
    }
    if(instruction->code==0x03){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "sra");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      setShamt(inst, instruction);
      return;
    }
    if(instruction->code==0x04){
      allocateMemInstName(instruction, 4);
      str= strcpy(instruction->inst_name, "sllv");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x06){
      allocateMemInstName(instruction, 4);
      str= strcpy(instruction->inst_name, "srlv");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x07){
      allocateMemInstName(instruction, 4);
      str= strcpy(instruction->inst_name, "srav");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    /*slt instructions*/
    if(instruction->code==0x2A){
      allocateMemInstName(instruction, 3);
      str= strcpy(instruction->inst_name, "slt");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x2B){
      allocateMemInstName(instruction, 4);
      str= strcpy(instruction->inst_name, "sltu");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    /*jump r-type instructions*/
    if(instruction->code==0x08){
      allocateMemInstName(instruction, 2);
      str= strcpy(instruction->inst_name, "jr");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    if(instruction->code==0x09){
      allocateMemInstName(instruction, 4);
      str= strcpy(instruction->inst_name, "jalr");
      checkValidStrCpy(str);
      instruction->is_valid= TRUE;
      instruction->shamt=0;
      return;
    }
    instruction->is_valid= FALSE;
  }
  /*sets the shamt field for the shift instructions which utilize that field. This has a return type of void. It takes in the unsigned integer value
   * of instruction. It also takes in an instruction struct pointer.
   */
  void setShamt(unsigned int inst, Instruction* instruction){
    int shamt= (inst&0x000007C0)>>6;
    instruction->shamt= shamt;
  }
  /*allocates mem for the instruction name. length is the length of the instruction name. It also checks to make sure that
   * memory was allocated properly. It takes in length of the instruction and an instruction struct pointer as parameters. 
   * it has a return type of void.
   */
  void allocateMemInstName(Instruction* instruction, int length){
    instruction->inst_name= malloc(sizeof(char)*(length+1));/*added 1 here to account for the nul*/
    if(instruction->inst_name==NULL){
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  }
  /*This function takes in the resultant pointer of a strcpy to ensure strcpy worked and didn't return a NULL pointer 
   * this has a return type of void
   */
  void checkValidStrCpy(char* str){
    if(str==NULL){
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  }
  /* this function takes in the unsigned integer value of the instruction and a pointer to the instruction struct. 
   * This function sets the fields of the instruction struct so it can be printed in the correct format. 
   * This function has a return type of void
   */
void setIType(unsigned int inst, Instruction* instruction){
  instruction-> rs= (inst&0x03E00000)>>21;
  instruction-> rt=(inst&0x001F0000)>>16;
  instruction->code= (inst&0xFC000000)>>26;
  isValidIType(inst, instruction);
}
/* This function takes in a pointer to an instruction sturct. 
 * This fuction prints out an I-type instruction in the proper format.
 * this function has a return type of void.
 */
void printIType(Instruction* instruction){
  int opcode= instruction->code;
  char* rs=NULL;
  char* rt=NULL;
  int branch_addr;
  rs= translateRegister(rs, instruction->rs);
  rt= translateRegister(rt, instruction->rt);
  if(instruction->is_valid==TRUE){
    printf("@PC=0x%08X, Opcode= 0x%02X, I Type (%s)\n",instruction->pc, instruction->code, instruction->inst_name);
    printf("RS= %d (%s), RT= %d (%s), Imm=0x%04X, sigext: 0x%08X (%d)", instruction->rs, rs,instruction->rt, rt, instruction->immediate, 
      instruction->sign_ext_imm, instruction->sign_ext_imm);
    if(opcode==0x04||opcode==0x05){
      branch_addr= ((instruction->sign_ext_imm)<<2)+(instruction->pc+4);
        printf(",\nbranchAddr=0x%08X",branch_addr);
    }
    if(instruction->is_load_or_store==TRUE){
      printf(",\nEffaddr=R[%s] + 0x%08X",rs,instruction->sign_ext_imm);
    }
  printf("\n");
  }
  free(rs);
  free(rt);
  free(instruction->inst_name);
}
/* determines if the instruction is a valid I-type instruction. Furthermore,
 * it determines the immediate and sign_ext_imm fields of the instruction and sets the Instruction struct accordingly.
 * This function also sets the inst_name field. This function has a return type of void. It takes in an unsigned int value 
 * of the instruction and a pointer an instruction struct.
 */
void isValidIType(unsigned int inst, Instruction* instruction){
  char* str= NULL;
  int opcode= instruction->code;
  instruction->immediate= inst&0x0000FFFF;
  /*calculate and set the immediate and sign extended fields of the instruction struct*/
  if(opcode!=0x0C||opcode!=0x0D||opcode!=0x0E||opcode!=0x25){
    /*check the high order bit of the immediate field*/
    if((instruction->immediate&0x00008000)!=0)
      instruction->sign_ext_imm= (instruction->immediate | 0xFFFF0000);
    else
      instruction->sign_ext_imm= (instruction->immediate & 0x0000FFFF);
  }
  else
    instruction->sign_ext_imm= (instruction->immediate & 0x0000FFFF);
  /*calculate and determine the operation name*/
  if(opcode==0x08){ 
    allocateMemInstName(instruction, 4);
    str= strcpy(instruction->inst_name, "addi");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  else if(opcode==0x09){
    allocateMemInstName(instruction, 5);
    str= strcpy(instruction->inst_name, "addiu");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  else if(opcode==0x0C){
    allocateMemInstName(instruction, 4);
    str= strcpy(instruction->inst_name, "andi");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  else if(opcode==0x0D){
    allocateMemInstName(instruction, 3);
    str= strcpy(instruction->inst_name, "ori");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  else if(opcode==0x0E){
    allocateMemInstName(instruction, 4);
    str= strcpy(instruction->inst_name, "xori");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  /*slt instructions*/
  else if(opcode==0x0A){
    allocateMemInstName(instruction, 4);
    str= strcpy(instruction->inst_name, "slti");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  else if(opcode==0x0B){
    allocateMemInstName(instruction, 5);
    str= strcpy(instruction->inst_name, "sltiu");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  /*branch instructions*/
  else if(opcode==0x04){
    allocateMemInstName(instruction, 3);
    str= strcpy(instruction->inst_name, "beq");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  else if(opcode==0x05){
    allocateMemInstName(instruction, 3);
    str= strcpy(instruction->inst_name, "bne");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= FALSE;
    return;
  }
  /*load instructions*/
  else if(opcode==0x20){
    allocateMemInstName(instruction, 2);
    str= strcpy(instruction->inst_name, "lb");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  else if(opcode==0x24){
    allocateMemInstName(instruction, 3);
    str= strcpy(instruction->inst_name, "lbu");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  else if(opcode==0x21){
    allocateMemInstName(instruction, 2);
    str= strcpy(instruction->inst_name, "lh");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  else if(opcode==0x25){
    allocateMemInstName(instruction, 3);
    str= strcpy(instruction->inst_name, "lhu");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  else if(opcode==0x0F){
    allocateMemInstName(instruction, 3);
    str= strcpy(instruction->inst_name, "lui");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  else if(opcode==0x23){
    allocateMemInstName(instruction, 2);
    str= strcpy(instruction->inst_name, "lw");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  /*store instructions*/
  else if(opcode==0x28){
    allocateMemInstName(instruction, 2);
    str= strcpy(instruction->inst_name, "sb");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  else if(opcode==0x29){
    allocateMemInstName(instruction, 2);
    str= strcpy(instruction->inst_name, "sh");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  else if(opcode==0x2B){
    allocateMemInstName(instruction, 2);
    str= strcpy(instruction->inst_name, "sw");
    instruction->is_valid= TRUE;
    checkValidStrCpy(str);
    instruction->is_load_or_store= TRUE;
    return;
  }
  assert(opcode!=0x02||opcode!=0x03);
  instruction->is_valid= FALSE;
}
/* This fuction takes in an unsigned integer representing an instruction and an instruction pointer. 
 * It has a return type of void. This function prints a J type instruction out in the proper format.
*/
void printJType(unsigned int inst, Instruction* instruction){
  int opcode= (inst& 0xFC000000)>>26;
  int addr= inst&0x03FFFFFF;
  int jumpAddr= (addr <<2) + (instruction->pc+4);
  if(!(opcode==0x02||opcode==0x03)){
    printf("0x%08X Invalid Instruction\n",instruction->pc);
    return;
  }
  if(opcode==0x02){
    instruction->inst_name= malloc(sizeof(char)*2);
    instruction->inst_name= strcpy(instruction->inst_name, "j");
  }
  else if(opcode==0x03){
    instruction->inst_name= malloc(sizeof(char)*4);
    instruction->inst_name= strcpy(instruction->inst_name, "jal");
  }
  printf("@PC=0x%08X, Opcode= 0x%02X, J Type (%s), addr= 0x%07X\n", instruction->pc, opcode, instruction->inst_name, addr);
  printf("JumpAddr: 0x%08X\n",jumpAddr);
  free(instruction->inst_name);
}
