/*
 * Jason Dreisbach
 * Matt Duhon
 *
 * Mips CPU c file
 *
 * contains all logic for mips cpu
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mipsCPU.h"

#define DEBUG

#undef DEBUG

typedef struct {
	int rs,rt,rd;
	int imm;
}INST_STRUCT;

static MIPS_CPU *cpu = NULL;



INST_STRUCT *parseRType(char *code);
INST_STRUCT *parseIType(char *code);
INST_STRUCT *parseJType(char *code);

int executeInstruction(char *code); 

int doAdd(char *code);
int doOr(char *code);
int doAnd(char *code);
int doAddi(char *code);
int doSub(char *code);
int doSlt(char *code);
int doBeq(char *code);
int doBne(char *code);
int doLw(char *code);
int doSw(char *code);
int doJ(char *code);
int doJr(char *code);
int doJal(char *code);

void printMem(int from, int to) {
	for(; from <= to; from++) {
		fprintf(stdout, "[%d] = %d\n", from, cpu->dmem[from]);
	}
}

void initMIPS () {
	if(!cpu) {
		cpu = malloc(sizeof(*cpu));
		if(!cpu) {
			perror("getCPU");
			exit(1);
		}
		zeroCPU();
	} else {
		fprintf(stderr, "CPU is already RUNNING");
	}
}


int execute(char *code) {

	if(!code || (strlen(code) != 32)) {
		fprintf(stderr, "INVALID INSTRUCTION: EXECUTE\n");
		return 1;
	}
	if(executeInstruction(code)) {
		fprintf(stderr, "ERROR: executing \n\t%s\n",code);
	}
	return 0;
}

int executeNext(char ** instArr, int maxPC, int repeat) {
	int i = 0;
	if(repeat == -1) {
		while(cpu->pc < maxPC+1) {
				execute(instArr[cpu->pc]);
				i++;
		}
	} else {
		for(i = 0; i < repeat; i++) {
			if(execute(instArr[cpu->pc])) {
				fprintf(stderr, "bad instruction");
			}
			if(cpu->pc > maxPC) {
				fprintf(stdout, "Reached end of executable\n");
				return 1;
			}
			
		}
		fprintf(stdout, "\n\t%d instruction(s) executed\n", i);
	}
	return 0;
}	

void dumpRegs() {
	fprintf(stdout,
			"\npc = %d\n"
			"$0 = %d\t$v0 = %d\t$v1 = %d\t$a0 = %d\n"
			"$a1 = %d\t$a2 = %d\t$a3 = %d\t$t0 = %d\n"
			"$t1 = %d\t$t2 = %d\t$t3 = %d\t$t4 = %d\n"
			"$t5 = %d\t$t6 = %d\t$t7 = %d\t$s0 = %d\n"
			"$s1 = %d\t$s2 = %d\t$s3 = %d\t$s4 = %d\n"
			"$s5 = %d\t$s6 = %d\t$s7 = %d\t$t8 = %d\n"
			"$t9 = %d\t$sp = %d\t$ra = %d\n", cpu->pc, 
			cpu->reg[REG_ZERO],
			cpu->reg[REG_V0],
			cpu->reg[REG_V1],
			cpu->reg[REG_A0],
			cpu->reg[REG_A1],
			cpu->reg[REG_A2],
			cpu->reg[REG_A3],
			cpu->reg[REG_T0],
			cpu->reg[REG_T1],
			cpu->reg[REG_T2],
			cpu->reg[REG_T3],
			cpu->reg[REG_T4],
			cpu->reg[REG_T5],
			cpu->reg[REG_T6],
			cpu->reg[REG_T7],
			cpu->reg[REG_S0],
			cpu->reg[REG_S1],
			cpu->reg[REG_S2],
			cpu->reg[REG_S3],
			cpu->reg[REG_S4],
			cpu->reg[REG_S5],
			cpu->reg[REG_S6],
			cpu->reg[REG_S7],
			cpu->reg[REG_T8],
			cpu->reg[REG_T9],
			cpu->reg[REG_SP],
			cpu->reg[REG_RA]);
}
void zeroCPU() {
	int i;
	cpu->pc = 0;
	for(i=0; i< 32; i++) {
		cpu->reg[i] = 0;
	} 
	for(i=0; i<8192;i++) {
		cpu->dmem[i] = 0;
	}
}
int executeInstruction(char *code) {
	int ret;
	/* and, or, add, addi, sub, slt, beq, bne, lw, sw, j, jr, jal */
	if(strncmp(code, "000000", 6) == 0) {
		/* add or and sub slt jr */
		if(strncmp(&code[26], "100000", 6) == 0) {
			/* add */
			ret = doAdd(code);
		} else if(strncmp(&code[26], "100101", 6) == 0) {
			/* or */
			ret = doOr(code);
		} else if(strncmp(&code[26], "100100", 6) == 0) {
			/* and */
			ret = doAnd(code);
		} else if(strncmp(&code[26], "100010", 6) == 0) {
			/* sub */
			ret = doSub(code);
		} else if(strncmp(&code[26], "101010", 6) == 0) {
			/* slt */
			ret = doSlt(code);
		} else if(strncmp(&code[26], "001000", 6) == 0) {
			/* jr */
			ret = doJr(code);
		}
	} else if(strncmp(code , "001000", 6) == 0) {
		/* addi */
		ret = doAddi(code);
	} else if(strncmp(code , "000100", 6) == 0) {
		/* beq */
		ret = doBeq(code);
	} else if(strncmp(code , "000101", 6) == 0) {
		/* bne */
		ret = doBne(code);
	} else if(strncmp(code , "100011", 6) == 0) {
		/* lw */
		ret = doLw(code);
	} else if(strncmp(code , "101011", 6) == 0) {
		/* sw */
		ret = doSw(code);
	} else if(strncmp(code , "000010", 6) == 0) {
		/* j */
		ret = doJ(code);
	} else if(strncmp(code , "000011", 6) == 0) {
		/* jal */
		ret = doJal(code);
	} else {
		fprintf(stderr, "INVALID OPCODE\n");
		exit(1);
	}
	return ret;
}




int doAdd(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "add %d+%d= reg[%d]", cpu->reg[inst->rs], 
								cpu->reg[inst->rt], inst->rd);
	fprintf(stderr,"\n");
#endif
	cpu->reg[inst->rd] = cpu->reg[inst->rs] + cpu->reg[inst->rt];
	cpu->pc++;
	free(inst);	
	return 0;
}

/* 
 * doOr
 *
 */
int doOr(char *code) {
	INST_STRUCT *inst;

	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "OR %x|%x= reg[%d]", cpu->reg[inst->rs], 
								cpu->reg[inst->rt], inst->rd);
	fprintf(stderr,"\n");
#endif
	cpu->reg[inst->rd] = cpu->reg[inst->rs] | cpu->reg[inst->rt];
	cpu->pc++;
	free(inst);	
	return 0;
}
int doAnd(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "and %x&%x= reg[%d]", cpu->reg[inst->rs], 
								cpu->reg[inst->rt], inst->rd);
	fprintf(stderr,"\n");
#endif
	cpu->reg[inst->rd] = cpu->reg[inst->rs] & cpu->reg[inst->rt];
	cpu->pc++;
	free(inst);	
	return 0;
}
int doAddi(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "addi %d+%d= reg[%d]\n", cpu->reg[inst->rs], 
								inst->imm, inst->rt);
	/*fprintf(stderr, "rs = %d\nrt=%d\nimm=%d",
					inst->rs, inst->rt,
					inst->imm);
*/
	fprintf(stderr,"\n");
#endif
	cpu->reg[inst->rt] = cpu->reg[inst->rs] + inst->imm;
	cpu->pc++;
	free(inst);	
	return 0;
}
int doSub(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "sub %d-%d= reg[%d]", cpu->reg[inst->rs], 
								cpu->reg[inst->rt], inst->rd);
	fprintf(stderr,"\n");
#endif
	cpu->reg[inst->rd] = cpu->reg[inst->rs] - cpu->reg[inst->rt];
	cpu->pc++;
	free(inst);	
	return 0;
}
int doSlt(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "if %d<%d= reg[%d]", cpu->reg[inst->rs], 
								cpu->reg[inst->rt], inst->rd);
	fprintf(stderr,"\n");
#endif
	cpu->reg[inst->rd] = cpu->reg[inst->rt] < cpu->reg[inst->rs];
	cpu->pc++;
	free(inst);	
	return 0;
}
int doBeq(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "beq %d==%d then pc = %d", cpu->reg[inst->rs], 
								cpu->reg[inst->rt], inst->imm);
	fprintf(stderr,"\n");
#endif
	if( cpu->reg[inst->rs] == cpu->reg[inst->rt] ) {
		cpu->pc = inst->imm;
	} else {
		cpu->pc++;
	}
	free(inst);	
	return 0;
}
int doBne(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "bne %d!=%d then pc = %d", cpu->reg[inst->rs], 
								cpu->reg[inst->rt], inst->imm);
	fprintf(stderr,"bne\n");
#endif
	if( cpu->reg[inst->rs] != cpu->reg[inst->rt] ) {
		cpu->pc += inst->imm;
	}
	cpu->pc++;
	free(inst);	
	return 0;
}
int doLw(char *code) {
	INST_STRUCT *inst;
	int addr;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
/*	fprintf(stderr, "lw\nrs = %d\nrt=%d\nimm=%d\n",
					inst->rs, inst->rt,
					inst->imm);
*/
	fprintf(stderr,"\n");
#endif
	addr = cpu->reg[inst->rt] + inst->imm;
	cpu->reg[inst->rs] = cpu->dmem[addr];
	cpu->pc++;
	free(inst);	
	return 0;
}
int doSw(char *code) {
	INST_STRUCT *inst;
	int addr;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr,"sw\n");
/*	fprintf(stderr, "rs = %d\nrt=%d\nimm=%d",
					inst->rs, inst->rt,
					inst->imm);
					*/
#endif
	addr = cpu->reg[inst->rt] + inst->imm;
	cpu->dmem[addr] = cpu->reg[inst->rs];
	cpu->pc++;
	free(inst);	
	return 0;
}
int doJ(char *code) {
	INST_STRUCT *inst;
	inst = parseJType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "j pc = %d", inst->imm); 
	fprintf(stderr,"\n");
#endif
	cpu->pc = inst->imm;
	free(inst);	
	return 0;
}
int doJr(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "jr = %d", cpu->reg[inst->rt]); 
	fprintf(stderr,"\n");
#endif

	cpu->pc = cpu->reg[inst->rt];
	free(inst);	
	return 0;
}
/*
 * doJal()
 *
 */
int doJal(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "jal = %d",inst->imm ); 
	fprintf(stderr,"\n");
#endif
	cpu->reg[REG_RA] = cpu->pc + 1;
	cpu->pc = inst->imm;
	free(inst);	
	return 0;
}

INST_STRUCT *parseRType(char *code) {
	char *p;
	int i, temp = 0;	
	INST_STRUCT *inst = malloc(sizeof(INST_STRUCT));

	if(!inst) {
		perror("parseRType");
		exit(1);
	}
	p = code + 6;	/* rt */
	for(i=0;i<5;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->rt = temp;

	/* rs */
	temp = 0;
	for(i=0;i<5;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->rs = temp;

	/* rd */
	temp = 0;
	for(i=0;i<5;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->rd = temp;

	return inst;
}

INST_STRUCT *parseIType(char *code) {
	char *p;
	int i, temp = 0;	
	INST_STRUCT *inst = malloc(sizeof(INST_STRUCT));

	if(!inst) {
		perror("parseIType");
		exit(1);
	}
	p = code + 6;	/* rt */
	for(i=0;i<5;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->rt = temp;

	/* rt */
	temp = 0;
	for(i=0;i<5;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->rs = temp;

	/* imm */
	temp = 0;
	for(i=0;i<16;i++) {
		if(p[i] == '1') {
			temp++;  	
		}
		temp = temp << 1;
	}	
	if(*p == '1') {
		temp |= 0xFFFF0000;
	}
	temp = temp >> 1; /* account for overshift */
	inst->imm = temp;

	return inst;
}

INST_STRUCT *parseJType(char *code) {
	char *p;
	int i, temp = 0;	
	INST_STRUCT *inst = malloc(sizeof(INST_STRUCT));

	if(!inst) {
		perror("parseJType");
		exit(1);
	}
	p = code + 6;	/* rs */
	for(i=0;i<26;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->imm = temp;
	
	return inst;
}



