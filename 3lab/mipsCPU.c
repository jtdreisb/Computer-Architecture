#include "
#include "mipsCPU.h"

int getInstructionType(char *code);

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
	if(!code && (strlen(code) == 32)) {
		fprintf(stderr, "INVALID INSTRUCTION: EXECUTE\n");
		exit(1);
	}

	getInstructionType(code);


	return 0;
}


int getInstructionType(char *code) {
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
	return 0;
}
int doOr(char *code) {
	return 0;
}
int doAnd(char *code) {
	return 0;
}
int doAddi(char *code) {
	return 0;
}
int doSub(char *code) {
	return 0;
}
int doSlt(char *code) {
	return 0;
}
int doBeq(char *code) {
	return 0;
}
int doBne(char *code) {
	return 0;
}
int doLw(char *code) {
	return 0;
}
int doSw(char *code) {
	return 0;
}
int doJ(char *code) {
	return 0;
}
int doJr(char *code) {
	return 0;
}
int doJal(char *code) {
	return 0;
}


