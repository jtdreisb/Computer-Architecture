#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mipsCPU.h"

typedef struct {
	int rs,rt,rd;
	int imm;
}INST_STRUCT;

static MIPS_CPU *cpu = NULL;

void initMIPS () {
	if(!cpu) {
		cpu = malloc(sizeof(MIPS_CPU));
		if(!cpu) {
			perror("getCPU");
			exit(1);
		}
	} else {
		fprintf(stderr, "CPU is already RUNNING");
	}
}



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

int execute(char *code) {
	if(!code && (strlen(code) != 32)) {
		fprintf(stderr, "INVALID INSTRUCTION: EXECUTE\n");
		exit(1);
	}
	if(executeInstruction(code)) {
		fprintf(stderr, "ERROR: executing \n\t%s\n",code);
	}
	return 0;
}


int executeInstruction(char *code) {
	int ret;
	/* and, or, add, addi, sub, slt, beq, bne, lw, sw, j, jr, jal */
	if(strncmp(code, "000000", 6)) {
		/* add or and sub slt jr */
		if(strncmp(&code[26], "100000", 6)) {
			/* add */
			ret = doAdd(code);
		} else if(strncmp(&code[26], "100101", 6)) {
			/* or */
			ret = doOr(code);
		} else if(strncmp(&code[26], "100100", 6)) {
			/* and */
			ret = doAnd(code);
		} else if(strncmp(&code[26], "100010", 6)) {
			/* sub */
		} else if(strncmp(&code[26], "101010", 6)) {
			/* slt */
		} else if(strncmp(&code[26], "001000", 6)) {
			/* jr */
		}
	} else if(strncmp(code , "001000", 6)) {
		/* addi */
	} else if(strncmp(code , "000100", 6)) {
		/* beq */
	} else if(strncmp(code , "000101", 6)) {
		/* bne */
	} else if(strncmp(code , "100011", 6)) {
		/* lw */
	} else if(strncmp(code , "101011", 6)) {
		/* sw */
	} else if(strncmp(code , "000010", 6)) {
		/* j */
	} else if(strncmp(code , "000011", 6)) {
		/* jal */
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
	cpu->reg[inst->rd] = cpu->reg[inst->rs] + cpu->reg[inst->rt];
	return 0;
}
int doOr(char *code) {
	INST_STRUCT *inst;

	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
	cpu->reg[inst->rd] = cpu->reg[inst->rs] | cpu->reg[inst->rt];
	return 0;
}
int doAnd(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
	cpu->reg[inst->rd] = cpu->reg[inst->rs] & cpu->reg[inst->rt];
	return 0;
}
int doAddi(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
	cpu->reg[inst->rd] = cpu->reg[inst->rs] + inst->imm;
	return 0;
}
int doSub(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
	cpu->reg[inst->rd] = cpu->reg[inst->rs] - cpu->reg[inst->rt];
	return 0;
}
int doSlt(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
	cpu->reg[inst->rd] = cpu->reg[inst->rs] < cpu->reg[inst->rt];
	return 0;
}
int doBeq(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
	if( cpu->reg[inst->rs] == cpu->reg[inst->rt] ) {
		cpu->pc += inst->imm;
	}
	return 0;
}
int doBne(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
	return 0;
}
int doLw(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
	return 0;
}
int doSw(char *code) {
	INST_STRUCT *inst;
	inst = parseIType(code);
	if(!cpu || !inst) {
		return 1;
	}
	return 0;
}
int doJ(char *code) {
	INST_STRUCT *inst;
	inst = parseJType(code);
	if(!cpu || !inst) {
		return 1;
	}
	return 0;
}
int doJr(char *code) {
	INST_STRUCT *inst;
	inst = parseRType(code);
	if(!cpu || !inst) {
		return 1;
	}
	return 0;
}
int doJal(char *code) {
	INST_STRUCT *inst;
	inst = parseJType(code);
	if(!cpu || !inst) {
		return 1;
	}
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
	p = code + 6;	/* rs */
	for(i=0;i<5;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->rs = temp;

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
	inst->rt = temp;

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
	p = code + 6;	/* rs */
	for(i=0;i<5;i++) {
		if(*p == '1') {
			temp++;  	
		}
		temp = temp << 1;
		p++;	
	}	
	temp = temp >> 1; /* account for overshift */
	inst->rs = temp;

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
	inst->rt = temp;

	/* imm */
	temp = 0;
	for(i=0;i<16;i++) {
		if(*p == '1') {
			if(i==0){
				temp &= 0xFFFF0000;	
			}
			temp++;  	
		}
		temp = temp << 1;
		p++;	
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



