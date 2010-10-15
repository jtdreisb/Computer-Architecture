/* Jason Dreisbach
 * Matt Duhon
 *
 * CPE-315 
 * Lab 3
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

void print_usage(char *arg0);

int main(int argc, char **argv) {
	FILE *f_in;

	char *outFile = "machine.o";	
	int hasScript = 0;

	if(argc < 2 || argc > 3) {
		print_usage(argv[0]);
	}

	if(parse(argv[1],outFile)) {
		fprintf(stderr, "There was an error");
	}

	if(argc == 3) {
		f_in = open(argv[2], "r");
	} else {
		f_in = stdin;
	}


	
	return 0;
}

void print_usage(char *arg0) {
	fprintf(stdout, "USAGE:\n\t%s <file.asm>\n",arg0);
	fflush(stdout);
	exit(1);
}
