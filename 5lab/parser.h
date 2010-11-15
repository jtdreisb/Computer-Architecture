/*
 * Jason Dreisbach 
 * Matt Duhon
 *
 * header for the asm parser
 * Lab 3
 */

#define BUFSIZE				100
#define	INST_SIZE			32
#define	DEFAULT_ARR_SIZE 	10

#define	TYPE_R				1
#define	TYPE_I				2
#define	TYPE_J				3
#define TYPE_JR				4
#define TYPE_LS				5

#define REG_D				15
#define REG_S				5
#define REG_T				10

void parse(char *f_in, char *f_out);
char * getLine(char *buf, int *size, FILE *fp); 
int * getiCount();
