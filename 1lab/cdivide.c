#include <stdio.h> 

int divide(int a1,int a2,int b,int * c1,int *c2) { 
	int carry;
	printf("a1=%d\na2 = %d\n", a1,a2);
	b = b/2;
	while(b) { 
		if(a1 & 0x1) { 
			carry = 1;
		} else { 
			carry = 0;
		}
		a1 = a1/2;
		a2 = a2/2;
		if(carry) {
			a2 |= 0x80000000;
		} else {
			a2 &= 0x7FFFFFFF;
		}
		
		b = b/2;
	}
	*c1 = a1;
       	*c2 = a2;	

	return 0;
}


int main() {
	int a1, a2, b, c1, c2;
	
	printf("sizeof: int =%d\n", sizeof(int));
	printf("sizeof: long =%d\n", sizeof(long));
	printf("sizeof: char =%d\n", sizeof(char));
	printf("1/2 = %d\n",1/2);
			
	a1 = 1;
	a2 = 0;

	b = 4; 

	divide(a1,a2,b, &c1, &c2);

	printf("Divide: [%x] [%x] by [%x] = [%x] [%x]\n",a1,a2,b,c1,c2);

	a1 = 1;
	a2 = 1;

	b = 65536; 

	divide(a1,a2,b, &c1, &c2);

	printf("Divide: [%x] [%x] by [%x] = [%x] [%x]\n",a1,a2,b,c1,c2);
	
	a1 = 2;
	a2 = 10;

	b = 65536; 

	divide(a1,a2,b, &c1, &c2);

	printf("Divide: [%x] [%x] by [%x] = [%x] [%x]\n",a1,a2,b,c1,c2);

	return 0;

}
