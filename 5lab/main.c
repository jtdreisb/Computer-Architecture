/* Jason Dreisbach
 * Matt Duhon
 *
 * CPE-315 
 * Lab 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parser.h"
#include "mipsCPU.h"

void print_usage(char *arg0);
void printHelp();

int main(int argc, char **argv) {
	FILE *c_fp, *i_fp;

	char *outFile = "machine.o";	
	int cbuf_size = BUFSIZE;
	int ibuf_size = BUFSIZE;
	char **instArr;
	int i, repeat, iCount;
	int first, last;

   	char *cbuf = malloc(cbuf_size);
	if(!cbuf){
		perror("mallocing bufs");
		exit(1);
	}
	if(argc < 2 || argc > 3) {
		print_usage(NULL);
	}

	if(argc == 3 || argc == 4) {
		c_fp = fopen(argv[2], "r");
	} else {
		c_fp = stdin;
	}
	if(!c_fp) {
		perror("MAIN\n");
		exit(1);
	}
	
	initMIPS();
	parse(argv[1], outFile); 
	i_fp = fopen(outFile, "r");
	if(!i_fp) {
		perror("can't open outFile");
		exit(1);
	}
	instArr = malloc(ibuf_size * sizeof(char *));
	if(!instArr) {
		perror("malloc instArr");
		exit(1);
	}
	i = 0;

	while(!feof(i_fp)) {
		if(i == ibuf_size) {
			ibuf_size = ibuf_size + BUFSIZE;
			fprintf(stderr, "\n BUFSIZE IS %d\n", ibuf_size);
			instArr = realloc(instArr, ibuf_size);
			if(!instArr) {
				perror("realloc instArr");
				exit(1);
			}
		}
		cbuf = getLine(cbuf, &cbuf_size, i_fp);	
		if(!cbuf) {
			break;
		}	
		instArr[i] = malloc(strlen(cbuf) * sizeof(char));
		if(!instArr[i]) {
			perror("main");
			exit(1);
		}
		strcpy(instArr[i++],cbuf); 
	}
	iCount = i-1;
	cbuf = malloc(cbuf_size);
	if(!cbuf){
		perror("mallocing bufs");
		exit(1);
	}

	while(!feof(c_fp)){
		fprintf(stdout, "\nmips> ");
		cbuf = getLine(cbuf, &cbuf_size, c_fp);
		switch(cbuf[0]) {	
		case 'h':
			printHelp();
			break;
		case 'd':
			dumpRegs();
			break;
		case 's':
			repeat = 1;
			for(i = 1; cbuf[i]; i++) {
				if(isdigit(cbuf[i])) {
					sscanf(&cbuf[i], "%d", &repeat);
					break;
				}	
			}
			executeNext(instArr, iCount, repeat);
			break;
		case 'r':
			repeat = -1;
			executeNext(instArr, iCount, repeat);
			break;
		case 'm':
			for(i=1; cbuf[i]; i++) {
				if(isdigit(cbuf[i])) {
					sscanf(&cbuf[i], "%d", &first);
					break;
				}
			}
			while(isdigit(cbuf[i])) {
				i++;
			}
			for(; cbuf[i]; i++) {
				if(isdigit(cbuf[i])) {
					sscanf(&cbuf[i], "%d", &last);
					break;
				}
			}
			printMem(first, last);
			break;
		case 'c':
			zeroCPU();
			fprintf(stdout,"\n\tSimulator reset\n");
			break;
		case 'b':
            fprintf(stdout,"need to impliment this\n");
            break;
		case 'q':
			fprintf(stdout,"\n");
			exit(0);
			break;
		default:
			fprintf(stdout, "Invalid command\n");
			break; 
		}
	}

	
	return 0;
}

void print_usage(char *arg0) {
	fprintf(stderr, "USAGE:\n\t%s <file.asm>\n",arg0);
	exit(1);
}

void printHelp() {
	printf("\n\th = show help\n"
	"\td = dump register state\n"
	"\ts = single step through the program (i.e. execute 1 instruction and stop)\n"
	"\ts num = step through num instructions of the program\n"
	"\tr = run until the program ends\n"
	"\tm num1 num2 = display data memory from location num1 to num2 \n"
	"\tc = clear all registers, memory, and the program counter to 0\n"
	"\tq = exit the program\n");

}
