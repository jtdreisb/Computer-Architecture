#include <stdio.h> 

int parity(int num) {
	int p = 1;
	unsigned int mask = 0x80000000;

	
	while(mask != 0) {

		if( mask & num) {
			p = !p;
		}
		mask = mask/2;
	}
	return p;
}

int main() {
	
	printf("IsEvenParity: %d\n", parity(3));
	printf("IsEvenParity: %d\n", parity(2));
	printf("IsEvenParity: %d\n", parity(4));
	printf("IsEvenParity: %d\n", parity(0));
	printf("IsEvenParity: %d\n", parity(1));
	printf("IsEvenParity: %d\n", parity(5));

	return 0;

}
