// gcc globalstatic.c

#include <stdio.h>
#include <string.h>

char username[10] = "maxpl0it";

void exploit() {
    printf("username at %p\n", username);
    strcpy(username, "AAAAAAAAAAAAAAAAAAAA");
}

int check_login() {
    static int logged_in = 0;
    printf("logged_in at %p\n", &logged_in);
    return logged_in;
}

int main() {
	printf("Welcome to 'Global Static' which shows how global and static variables can affect one another.\n\n");
	printf("First let's check if we're logged in:\n");
    printf(check_login() ? "Logged in!\n" : "Not logged in...\n");
    printf("Now let's call our exploit...\n");
    exploit();
    printf("Finally, let's check if we're now logged in:\n");
    printf(check_login() ? "Logged in!\n" : "Not logged in...\n");
}
