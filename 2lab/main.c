/* Jason Dreisbach
 * Matt Duhon
 *
 * CPE-315 
 * Lab 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define	INST_SIZE			32
#define	DEFAULT_ARR_SIZE 	10

#define	TYPE_R				1
#define	TYPE_I				2
#define	TYPE_J				3

typedef struct { 
	char *name;
	int line;
}Label;

char * resizeBuf(char *buf, int *size);
char * getLine(char *buf, int *size, FILE *fp);
char ** parseLine(char *line);

Label ** getLabelArr(int elements); 
void generate(FILE *fp, char ** instArr, Label **lArr);

void print_usage() {
	printf("Usage:\n");
	printf("\tmass <Filename>\n");
	exit(1);
}


int main(int argc, char **argv) {
	FILE *f_asm;
	char *buf;
	int i;
	int line = 0;	
	int buf_size = 10;
	char ** instArr;

	Label ** lArr;
	buf = malloc(buf_size * sizeof(char));
	
	if(argc < 2) {
		print_usage();
	}
	
	f_asm = fopen(argv[1], "r");	

	if(!f_asm) {
		/* Check errno*/
		perror("Couldn't open f_asm");
		exit(1);
	}
	
	while(!feof(f_asm)) {
		buf = getLine(buf, &buf_size, f_asm);
	/*	printf("%d:\t%s\n",line,buf);	*/
		instArr = parseLine(buf);
		line++;
	}	
	
	/*
	 * printf("---- Valid Instructions ----\n");
	i = 0;
	while(instArr[i]) {
		printf("%d: %s\n", i, instArr[i]);
		i++;
	}
	printf("---- Valid Labels ----\n");
	*/
	lArr = getLabelArr(0);
	/*if(lArr) {
		i = 0;
		while(lArr[i]) {
			printf("%d: %s\n", lArr[i]->line, lArr[i]->name); 
			i++;
		}	
	}*/

	generate(stdout, instArr, lArr);
	free(buf);
	fclose(f_asm);
	return 0;
}

Label ** getLabelArr(int elements) {
	static Label ** arr = NULL;
	static int size = DEFAULT_ARR_SIZE;
	if(!arr) {
		if(size) {
			arr = calloc((size), sizeof(Label*));
		} else {
		}
		if(!arr) {
			perror("getLabelArr");
			exit(1);
		}
		
	} else { 
		if(elements == size-1) {
			size = size + DEFAULT_ARR_SIZE;
			arr = realloc(arr, size * sizeof(Label*));
		}
		if(!arr) {
			perror("getLabelArr");
			exit(1);
		}
	}
	return arr;
}

Label ** addToLabels(char *line, int lineNo) {
	char *label;
	int i, lineLen = 0;
	static int	curArri = 0;

	Label ** arr = NULL;
	Label * lbl = NULL;

	lineLen = strlen(line);
	for(i = 0; (line[i] != ':') && (i < lineLen); i++) {
	}
	if(i == lineLen) {
		return NULL;
	}
	label = malloc((i + 1) * sizeof(char));
	memcpy(label, line, i);
	label[i] = '\0';

	arr = getLabelArr(curArri);

	/* add to array here */
	/*curArri is the current index in the array*/
	lbl = malloc(sizeof(Label*));	
	if(!lbl) {
		perror("addLabel");
		exit(1);
	}
	lbl->name = label;
	lbl->line = lineNo;
	arr[curArri] = lbl;	
	curArri++;

	return arr;
}

char * insertInstruction(char *p) {
	char *inst = NULL;
	int i;
	while(*p) {
		if(isspace(*p)) {
			p++;
			continue;	
		} else if (isalpha(*p)) {
			i = 0;
			while(p[i] != '#' && p[i] != '\0') {
				i++;
			}
			inst = malloc((i+1) * sizeof(char));
			if(!inst) {
				perror("insertInstruction");
				exit(1);
			}

			strncpy(inst,p,i);
			break;
		} else {
			fprintf(stderr, "Invalid syntax\n"); 
			exit(1);
		}

	}
	return inst;
}

int * getiCount() {
	static int iCount = 0;
	return &iCount;
}

char ** parseLine(char *line) {
	int i;

	static int iArrSize = DEFAULT_ARR_SIZE;
	static char **instructionArray = NULL;
	int *iCount = getiCount();


	if(!instructionArray) {
		instructionArray = calloc(iArrSize, sizeof(char*));
	}
	
	if(*iCount == iArrSize-1) {
		iArrSize = iArrSize + DEFAULT_ARR_SIZE;
		instructionArray = realloc(instructionArray, iArrSize * sizeof(char*));	
	}
	if(line) {
		/* 
		 * If the start of the line is either a digit or char
		 * then line could possibly be a label
		 * or valid instruction
		 */
		if(isalpha(line[0]) || isdigit(line[0])) {
			for(i = 0; line[i] != '\0'; i++) {
				if(line[i] == '#') {
					line[i] = '\0';
					i = 0;
					break;
				} else if(line[i] == ':') {
					addToLabels(line,*iCount);
					i++;
					line = &line[i];
					break;
				} 
				
			}
			instructionArray[*iCount] = insertInstruction(line);
			if(instructionArray[*iCount]) {
					(*iCount)++;
				}

		} else if (isspace(line[0])) {
			instructionArray[*iCount] = insertInstruction(line);			
			if(instructionArray[*iCount]) {
						(*iCount)++;
			}
		}		
	}

	return instructionArray;
}


/*
 * getLine()
 *
 * will read a complete line reallocating buf if neccessary
 * Does NOT append the newline to the string
 * returns null terminated string pointer to valid buffer
 */
char * getLine(char *buf, int *size, FILE *fp) {
	char *line = buf;
	int i;
	for( i=0; (line[i] = getc(fp)) != EOF && line[i] != '\n';  i++ ) {
		if( i == (*size -1)) {
			*size = *size * 2;
			line = realloc(line, *size);
			if(!line) {
				perror("getLine: Realloc");
				exit(1);
			}
		}
	}
	if(line[i] == '\n' ) {
		line[i] = '\0';
	} else if (line[i] == EOF) {
		return NULL;
	} else {
		printf("Error: line[i] = %c" , line[i]);
		exit(1);
	}

	return line;
}
/*
 * returns type of instruction
 * 0 - failure
 * 1 - register
 * 2 - immediate
 * 3 - jump
 */

int getInstType(char *inst, char *code) {
	if(!strcmp("and", inst))	 {
		code[26] = '1';	
		code[29] = '1';	
		return TYPE_R;
	} else if (!strcmp("or",inst)) {
		code[26] = '1';	
		code[29] = '1';	
		code[31] = '1';	
		return TYPE_R;
	} else if (!strcmp("add",inst)) {
		code[26] = '1';	
		return TYPE_R;
	} else if (!strcmp("addi",inst)) {
		code[2] = '1';	
		return TYPE_I;
	} else if (!strcmp("sub",inst)) {
		code[26] = '1';	
		code[30] = '1';	
		return TYPE_R;
	} else if (!strcmp("slt",inst)) {
		code[26] = '1';	
		code[28] = '1';	
		code[30] = '1';	
		return TYPE_R;
	} else if (!strcmp("beq",inst)) {
		code[3] = '1';	
		return TYPE_I;
	} else if (!strcmp("bne",inst)) {
		code[3] = '1';	
		code[5] = '1';	
		return TYPE_I;
	} else if (!strcmp("lw",inst)) {
		code[0] = '1';	
		code[4] = '1';	
		code[5] = '1';	
		return TYPE_I;
	} else if (!strcmp("sw",inst)) {
		code[0] = '1';	
		code[2] = '1';	
		code[4] = '1';	
		code[5] = '1';	
		return TYPE_I;
	} else if (!strcmp("j",inst)) {
		code[4] = '1';	
		return TYPE_J;
	} else if (!strcmp("jr",inst)) {
		code[28] = '1';	
		return TYPE_R;
	} else if (!strcmp("jal",inst)) {
		code[4] = '1';	
		code[5] = '1';	
		return TYPE_J;
	} else  {
		fprintf(stderr, "InvalidInstruction: %s\n", inst);
		exit(1);
	}

}

void parseArgs(char *arg, int iType,char * code) {
	char *p;

	p = arg;
	while (isspace(*p)) {
		p++;
	}	

	if(iType == TYPE_R) {
		p = getReg(code, p, REG_1);
		while (isspace(*p)) {
			p++;
		}
		p = getReg(code, p, REG_2);
		while (isspace(*p)) {
			p++;
		}
		p = getReg(code, p, REG_3);
	} else if(iType == TYPE_I) {

	} else if(iType == TYPE_J) {

	} else {

	}
}
void parseInstruction(FILE * fp, const char * instruction, int insIndex, Label ** lArr) {
	char code[INST_SIZE+1];
	char *inst, *p;
	int i, iType;

	if(instruction) {
		inst = malloc((strlen(instruction) +1) * sizeof(char));
	} else {
		fprintf(stderr, "instruction is NULL") ;
		exit(1);
	}
	strcpy(inst, instruction);
 
	for(i=0;i< INST_SIZE; i++) {
		code[i] = '0';
	}
	code[INST_SIZE] = '\0';

	i=0;
	while(!isspace(inst[i])) {
		i++;
	}
	inst[i] = '\0';
	/* we need inst to free it
	 * therefore use p to traverse the rest
	 */
	p =	 &inst[i+1];


	/* determine instruction type */
	iType = getInstType(inst, code);


	parseArgs(p, iType, code);

	fprintf(fp,"%s\n",code);
	free(inst);
}

void generate(FILE *fp, char ** instArr, Label **lArr) {
	int i;
	int *iCount = getiCount();
	
	for(i=0;i<*iCount;i++) {
		parseInstruction(fp, instArr[i], i, lArr);	
	}	
}
