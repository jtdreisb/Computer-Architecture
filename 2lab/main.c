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

#define  DEFAULT_ARR_SIZE 10
typedef struct { 
	char *name;
	int line;
}Label;

char * resizeBuf(char *buf, int *size);
char * getLine(char *buf, int *size, FILE *fp);
char ** parseLine(char *line);

Label ** getLabelArr(int elements); 
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
		printf("%d:\t%s\n",line,buf);	
		instArr = parseLine(buf);
		line++;
	}	
	
	printf("---- Valid Instructions ----\n");
	i = 0;
	while(instArr[i]) {
		printf("%d: %s\n", i, instArr[i]);
		i++;
	}
	printf("---- Valid Labels ----\n");
	lArr = getLabelArr(0);
	if(lArr) {
		i = 0;
		while(lArr[i]) {
			printf("%d: %s\n", lArr[i]->line, lArr[i]->name); 
			i++;
		}	
	}

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
				perror("parseLine");
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
char ** parseLine(char *line) {
	int i;

	static int iCount = 0;
	static int iArrSize = DEFAULT_ARR_SIZE;
	static char **instructionArray = NULL;


	if(!instructionArray) {
		instructionArray = calloc(iArrSize, sizeof(char*));
	}
	
	if(iCount == iArrSize-1) {
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
					instructionArray[iCount] = insertInstruction(line);
					if(instructionArray[iCount]) {
						iCount++;
					}
					break;
				} else if(line[i] == ':') {
					addToLabels(line,iCount);
					instructionArray[iCount] = insertInstruction(&line[i+1]);
					if(instructionArray[iCount]) {
						iCount++;
					}
					break;
				} 
				
			}
		} else if (isspace(line[0])) {
			instructionArray[iCount] = insertInstruction(line);			
			if(instructionArray[iCount]) {
						iCount++;
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

