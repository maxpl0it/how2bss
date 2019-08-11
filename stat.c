// gcc stat.c

#include <stdio.h>
#include <string.h>

void exploit(unsigned int location_of_user) {
	static char name[10] = "maxpl0it";
	int buffer_fill = location_of_user - (unsigned int)name;
	printf("Variable 'name' is at %p in the data segment.\n", name);
	printf("Overflow size: %d\n", buffer_fill);
	char to_strcpy[30];
	memset(to_strcpy, 'A', buffer_fill);
	strcpy(to_strcpy + buffer_fill, "admin");
	printf("About to copy %s to name (%p) which has a size 10 bytes.\n", to_strcpy, name);
	strcpy(name, to_strcpy);
}

unsigned int check_user() {
	static char user[10] = "not_admin";
	printf("Variable 'user' is at %p in the data segment.\n", user);
	if(!strcmp(user, "admin")) {
		printf("You are logged in as the admin!\n");
	}
	else {
		printf("You are NOT logged in as the admin :(\n");
	}
	return (unsigned int)&user;
}

int main() {
	printf("Welcome to 'Static' in which we show how an overflow in one static variable can be used to overwrite a second static variable regardless of scope.\n\nFirst, lets check if the user is logged in as the admin user.\n");
	int user = check_user();
	printf("Now let's overflow a second static variable called 'name'.\n");
	exploit(user);
	printf("Done! Now let's check if the user is logged in as admin...\n");
	check_user();
}
