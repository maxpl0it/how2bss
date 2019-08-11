// gcc -no-pie aslrusage.py

#include <stdio.h>
#include <unistd.h>
#include <string.h>

char str[20];

void write_primitive(char *destination, char *input) {
	memcpy(destination, input, 8);
}

int main() {
	printf("Welcome to 'ASLR Usage'. This example doesn't involve exploiting overruns, but instead introduces an interesting property of the BSS segment: It’s unaffected by ASLR (when PIE is not enabled - the default for Ubuntu < 16.10).\nBecause of this, we can use an uninitialised global or static variable to hold strings and know the exact location of them.\nIn this example, we assume that the attacker has a write primitive (perhaps from a buffer overflow).\n\n");

	printf("You can repeat this and you will notice that the addresses of str (%p) will never change\n\n", str);
	
	printf("First, the buffer is filled with the command we want to execute.\n");
	write_primitive(str, "/bin/sh\x00");
	
	printf("Second, we append a pointer to this string (/bin/sh is at %p and the pointer is at %p).\n", str, str + 8);
	long int address_of_str = str;
	write_primitive(str + 8, &address_of_str);

	printf("Now we append some nulls to the end since we don't want any more arguments.\n");
	write_primitive(str + 8 + sizeof(&str), "\x00\x00\x00\x00\x00\x00\x00\x00");

	printf("Now we call execve with our known addresses.\n");
	execve(str, str+8, 0);
}
