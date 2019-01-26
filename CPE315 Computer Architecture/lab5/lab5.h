/*----------------------------------------------------------------------*
 * mips_asm Binary header (.mb) file header format.  This header  *
 * provides for future information on mips assembler files. *
 *                         *
 * write_header - writes mips_asm header, along with test data *
 *                         *
 * This shows how the mips_asm header is written, and provides *
 * a test case (testcase1.mb) to be used for lab projects.     *
 *----------------------------------------------------------------------*/
#define FALSE 0
#define TRUE 1
typedef struct _mb_hdr
  {
  char signature[4];    /* Signature = 0x7F, 'M', 'B", 0x00 */
  unsigned int size;    /* Size of assembler program portion, bytes */
  unsigned int entry;      /* Entry point offset of program if not zero */
  unsigned int filler1;    /* Unused ... reserved for future use. */
  unsigned char filler2[64-16];  /* Overall header is 64 bytes */
  } MB_HDR, *MB_HDR_PTR;

typedef struct{
   char* inst_name;
   int code;
   int rs;
   int rt; 
   int rd;
   int is_valid;
   int shamt;
   int pc;
   int immediate;
   int sign_ext_imm;
   int is_load_or_store;
}Instruction;

void setRType(unsigned int inst, Instruction* instruction);
void printRTypeFields(Instruction* instruction);
char* translateRegister(char* dst, int reg);
void isValidRType(unsigned int inst, Instruction* instruction);
void setShamt(unsigned int inst, Instruction* instruction);
void allocateMemInstName(Instruction* instruction, int length);
void checkValidStrCpy(char* str);
void isValidIType(unsigned int inst, Instruction* instruction);
void printIType(Instruction* instruction);
void setIType(unsigned int inst, Instruction* instruction);
void printJType(unsigned int inst, Instruction* instruction);