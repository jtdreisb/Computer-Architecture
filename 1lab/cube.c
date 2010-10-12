#include <stdio.h>


int cube(int num) {
	int i, j, k, c = 0;
	
	for(i = 0; i < num; i++) {
		for( j = 0; j < num; j++) {
			c += num;
		}
	}
	return c;
}

int main() {
	
	printf("3 cubed is %d", cube(3));
	return 0;

}
