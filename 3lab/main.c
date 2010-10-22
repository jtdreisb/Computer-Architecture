/* Jason Dreisbach
 * Matt Duhon
 *
 * CPE-315 
 * Lab 3
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "mipsCPU.h"

void print_usage(char *arg0);

int main(int argc, char **argv) {
	FILE *f_in;

	char *outFile = "machine.o";	
	int buf_size = BUFSIZE;
	char *buf = malloc(buf_size);

	if(argc < 2 || argc > 3) {
		print_usage(argv[0]);
	}

	if(parse(argv[1], outFile)) {
		fprintf(stderr, "There was an error");
	}

	if(argc == 3) {
		f_in = fopen(argv[2], "r");
	} else {
		f_in = stdin;
	}
	if(!f_in) {
		perror("MAIN\n");
		exit(1);
	}
	
	initMIPS();
	parse(argv[1], outFile);

	while(!feof(f_in)){
		buf = getLine(buf, &buf_size, f_in);

			

	}



	
	return 0;
}

void print_usage(char *arg0) {
	fprintf(stderr, "USAGE:\n\t%s <file.asm>\n",arg0);
	exit(1);
}
