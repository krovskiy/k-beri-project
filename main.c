#include <stdio.h>
#include <string.h>

// Checks if the user made a valid input

int validNumber(void) {
    int x;
    while (1) {
        if (scanf_s("%d", &x)&&(x == 1 || x == 2)) {
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
           "Type '1' if you're a CUSTOMER navigating through the site\n"
           "or type '2' if you're an STOREKEEPER and want some changes!\n\n"
           "**************************************************\n"
           "Happy shopping! :)\n", store);
    printf("INPUT: ");
    return validNumber();
}

void customerMenu() {
    //pasdomsething
}

void storekeeperMenu() {
    //ask password first
}

void storeKeeperPassCheck() {
    char adminPass[20];
    const char correctPassword[] = "admin123";

    printf("Insert the admin password to access the panel!\n");
    // Use scanf for a single-word password
    scanf("%19s", adminPass);

    if (strcmp(adminPass, correctPassword) == 0) {
        printf("Correct password, welcome to the admin panel!\n");
        storekeeperMenu();
    } else {
        printf("Wrong password, access denied!\n");
    }
}

void roleSelect(int roleChoice) {
    if (roleChoice == 1) {
        printf("you are a customer :)\n");
        customerMenu();
    } else {
        printf("you are a storekeeper :)\n");
        storeKeeperPassCheck();
    }
}

int main(void) {
    char store[] = "Frag.ee";
    int roleChoice = welcomeDialog(store);
    roleSelect(roleChoice);
    return 0;
}