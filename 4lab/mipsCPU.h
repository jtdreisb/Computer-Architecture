/*
 * Jason Dreisbach
 * Matt Duhon
 *
 * mipsCPU.h
 */
/* REGISTER DEFINITIONS */
typedef enum {
	 REG_ZERO = 0,
	 REG_V0 = 2,
	 REG_V1 = 3, REG_A0 = 4,
	 REG_A1 = 5,
	 REG_A2 = 6,
	 REG_A3 = 7,
	 REG_T0 = 8,
	 REG_T1 = 9,
	 REG_T2 = 10,
	 REG_T3 = 11,
	 REG_T4 = 12,
	 REG_T5 = 13,
	 REG_T6 = 14,
	 REG_T7 = 15,
	 REG_S0 = 16,
	 REG_S1 = 17,
	 REG_S2 = 18,
	 REG_S3 = 19,
	 REG_S4 = 20,
	 REG_S5 = 21,
	 REG_S6 = 22,
	 REG_S7 = 23,
	 REG_T8 = 24,
	 REG_T9 = 25,
	 REG_SP = 29,
	 REG_RA = 31
}REGISTER;

/* Instruction Type Definition */ 
typedef enum {
    kSTALL,
    kADD,
    kADDI,
    kAND,
    kOR,
    kSUB,
    kSLT,
    kBEQ,
    kBNE,
    kLW,
    kSW,
    kJ,
    kJR,
    kJAL
}INSTRUCTION;

typedef struct {
    INSTRUCTION inst;
	int rs,rt,rd;
	int imm;
    int squash;
}INST_STRUCT;


/* Pipeline Definition */
typedef struct {
    INST_STRUCT *IF;
    INST_STRUCT *ID;
    INST_STRUCT *EX;
    INST_STRUCT *MEM;
}Pipeline;

/* Processor Definition */
typedef struct {
	int pc;
	int reg[32];
	int dmem[8192];
    Pipeline pLine;
}MIPS_CPU;


void initMIPS ();
int execute(char *code);
void dumpRegs();
void zeroCPU();
int nextCycle(char ** instArr, int maxPC, int repeat);
int executeNext(char ** instArr, int maxPC, int repeat);
void printMem(int from, int to);
