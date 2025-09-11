#include <stdio.h>


int validNumber(void) {
    int x;
    while (1) {
        if (scanf("%d", &x)&&(x == 1 || x == 2)) {
            return x;
        }
        else {
            printf("Not a valid input! Try again.\n");
            printf("INPUT: ");
        }
    }
}


int welcomeDialog(char store[]) {
    printf("Welcome to the %s Store! \n\n"
           "**************************************************\n\n"
           "Type '1' if you're a USER navigating through the site\n"
           "or type '2' if you're an ADMINISTRATOR and want some changes!\n\n"
           "**************************************************\n"
           "Happy shopping! :)\n", store);
    printf("INPUT: ");
    return validNumber();
}



int main(void) {
    char store[] = "SOMETHING";
    int choice = welcomeDialog(store);

    return 0;


}