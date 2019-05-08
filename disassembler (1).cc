#include <stdio.h>
#include <string.h>
//defines
#define DEST 0x0E00
#define PCOFFSET09 0x01FF
#define BASE 0x01C0

//prototypes
void printAssembly(char filename[]);
void printBr(int, int);
void printAdd(int);
void printLd(int, int);
void printSt(int, int);
void printJsrJsrr(int, int);
void printAnd(int);
void printLdr(int);
void printStr(int);
void printRti(int);
void printNot(int);
void printLdi(int, int);
void printSti(int, int);
void printJmpRet(int);
void printLea(int, int);
void printTrap(int);
#define LIMIT 40

void printAssembly(char filename[]);

//**************************************************
//Make sure to comment main out before submitting
//**************************************************
/*int main()
{       
        char filename[] = "test1.hex";
        printAssembly(filename);
}*/

void printAssembly(char filename[])
{
        FILE *infile;
        infile = fopen(filename, "r");

        if (infile == NULL)
            printf("File %s is null.\n", filename);
            
        else {
    int count = 0;
    int instruction = 0;
    int PC = 0;
    fscanf(infile, "%x", &PC);
    //While not at end of file and not over the limit
    while (fscanf(infile, "%x", &instruction) != EOF && count < LIMIT)
    {
      count++;  //Count number of lines for limit
      //Remove the print and put your code here
      
      //printf("%X\n", instruction);
        PC++;
      //Figure out the oppcode from the high order 4 bits of the instruction
      //Use a big if or switch to call the appropriate print function.
      //Pass the function the full instruction and the PC, but only if necessary.
         int op_code = instruction >> 12;
         int no_op = instruction & 0x0fff; //instruction without the op-code

        switch(op_code){
        case 0:
                printBr(no_op, PC);
                break;
        case 1:
                printAdd(no_op);
                break;
        case 2:
                printLd(no_op, PC);
                break;
        case 3:
                printSt(no_op, PC);
                break;
        case 4:
                printJsrJsrr(no_op, PC);
                break;
        case 5:
                printAnd(no_op);
                break;
        case 6:
                printLdr(no_op);
                break;
        case 7:
                printStr(no_op);
                break;
        case 8:
                printRti(no_op);
                break;
        case 9:
                printNot(no_op);
                break;
        case 10:
                printLdi(no_op, PC);
                break;
        case 11:
                printSti(no_op, PC);
                break;
        case 12:
                printJmpRet(no_op);
                break;
        case 13:
                break;
        case 14:
                printLea(no_op, PC);
                break;
        case 15:
                printTrap(no_op);
                break;
        default:
                break;
        }
    }
  }
}

void printBr(int instruction,int PC)
{
        int n = instruction & 0x0800;
        n = n >> 11;

        int z = instruction & 0x0400;
        z = z >> 10;

        int p = instruction & 0x0200;
        p = p >> 9;

        int migos = (instruction & PCOFFSET09) << 23; //migos = offset
        migos = migos >> 23;

        printf("BR");

        if(n)
        printf("N");
        
        if(z)
        printf("Z");
        
        if(p)
        printf("P");

        printf("\tx%X\n", PC + migos);
}

void printAdd(int instruction)
{
	int immediate = instruction & 0x0020;
	
	int r_one = (instruction & 0x01C0) >> 6;
	int r_dest = (instruction & DEST) >> 9;
	
	if(immediate)
	{
		int add_im = (instruction & 0x001f) << 27;
		add_im = add_im >> 27;
		r_one = (instruction & 0x01C0) >> 6;
		
		printf("ADD\tR%d, R%d, #%d\n", r_dest, r_one, add_im);
		
	}
	
	else
	{
		int r_two = instruction & 0x0007;
		printf("ADD\tR%d, R%d, R%d\n", r_dest, r_one, r_two);
	}
}

void printLd(int instruction, int PC)
{
  int dest = (instruction & DEST) >> 9;
  int migos = (instruction & PCOFFSET09) << 23;
  
  migos = migos >> 23;
  
  printf("LD\tR%d, x%X\n", dest, PC + migos);
}

void printSt(int instruction, int PC)
{
  int dest = (instruction & DEST) >> 9;
  int migos = (instruction & PCOFFSET09) << 23;
  
  migos = migos >> 23;
  printf("ST\tR%d, x%X\n", dest, PC + migos);
}

void printJsrJsrr(int instruction, int PC)
{
	if(instruction & 0x800) //jsr
	{
		int migos = (instruction & 0x07ff) << 21;
		migos = migos >> 21;
		
		printf("JSR\tx%X\n", PC + migos);
	}
	else //jsrr
	{
		int r_base = (instruction & BASE) >> 6;
		
		printf("JSRR\tR%d\n", r_base);
	}
}

void printAnd(int instruction)
{
  int dest = (instruction & DEST) >> 9;
  int r_one = (instruction & BASE) >> 6;
  
  if((instruction & 0x0020) >> 5)
  {
    int immediate = (instruction & 0x001F) << 27;
    immediate = immediate >> 27;
    
    printf("AND\tR%d, R%d, #%d\n", dest, r_one, immediate);
  }
  else
  {
    int r_two = instruction & 0x0007;
    
    printf("AND\tR%d, R%d, R%d\n", dest, r_one, r_two);
  }
}

void printLdr(int instruction)
{
  int dest = (instruction & DEST) >> 9;
  int r_base = (instruction & BASE) >> 6;
  int migos = (instruction & 0x003F) << 26;
  migos = migos >> 26;
  printf("LDR\tR%d, R%d, #%d\n", dest, r_base, migos); 
}

void printStr(int instruction)
{
  int r_source = (instruction & DEST) >> 9;
  int r_base = (instruction & BASE) >> 6;
  int migos = (instruction & 0x003F) << 26;
  migos = migos >> 26;
  
  printf("STR\tR%d, R%d, #%d\n", r_source, r_base, migos);
}

void printRti(int instruction)
{
  printf("RTI\n");
}

void printNot(int instruction)
{
  int r_dest = (instruction & DEST) >> 9;
  int r_source = (instruction & BASE) >> 6;
  
  printf("NOT\tR%d, R%d\n", r_dest, r_source);
}

void printLdi(int instruction, int PC)
{
  int r_dest= (instruction & DEST) >> 9;
  int migos = (instruction & PCOFFSET09) << 23;
  migos = migos >> 23;
  printf("LDI\tR%d, x%X\n", r_dest, PC + migos);
}

void printSti(int instruction, int PC)
{
  int r_source = (instruction & DEST) >> 9;
  int migos = (instruction & PCOFFSET09) << 23;
  migos = migos >> 23;
  
  printf("STI\tR%d, x%X\n", r_source, PC + migos);
}

void printJmpRet(int instruction)
{
  int r_base = (instruction & BASE) >> 6;
  if(r_base == 7)
    printf("RET\n");
  else
    printf("JMP\tR%d\n", r_base);
}

void printLea(int instruction, int PC)
{
  int r_dest = (instruction & DEST) >> 9;
  int migos = (instruction & PCOFFSET09) << 23;
  migos = migos >> 23;
  printf("LEA\tR%d, x%X\n", r_dest, PC + migos);
}

void printTrap(int instruction)
{
  int trap_v = instruction & 0x00FF;
  
  switch(trap_v)
  {
    case 0x0020:
      			printf("GETC\n");
      break;
    case 0x0021:
      			printf("OUT\n");
      break;
    case 0x0022:
      			printf("PUTS\n");
      break;
    case 0x0023:
      			printf("IN\n");
      break;
    case 0x0024:
      			printf("PUTSP\n");
      break;
    case 0x0025:
      			printf("HALT\n");
      break;
    default:
      break;
  }
}


















