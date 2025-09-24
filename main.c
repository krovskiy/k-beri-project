#include <stdio.h>
#include <string.h>

// Checks if the user made a valid input
int validNumber(void) {
    int x;
    while (1) {
        if (scanf_s("%d", &x) && (x == 1 || x == 2)) {
            return x;
        } else {
            printf("Not a valid input! Try again.\n");
            printf("INPUT: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { } //Error handling when an input doesn't work!
        }
    }
}

int welcomeDialog() {
    printf("___________                                        \n");
    printf("\\_   _____/___________     ____      ____   ____  \n");
    printf(" |    __) \\_  __ \\__  \\   / ___\\   _/ __ \\_/ __ \\ \n");
    printf(" |     \\   |  | \\/ __ \\_/ /_/  >  \\  ___/\\  ___/ \n");
    printf(" \\___  /   |__|  (____  /\\___  / /\\ \\___  >\\___  >\n");
    printf("     \\/               \\/_____/  \\/     \\/     \\/  \n");
    printf("\n");
    printf("Welcome to the Frag.ee Store! \n\n"
           "**************************************************\n\n"
           "Type '1' if you're a CUSTOMER navigating through the site\n"
           "or type '2' if you're an STOREKEEPER and want some changes!\n\n"
           "**************************************************\n"
           "Happy shopping! :)\n");
    printf("INPUT: ");
    return validNumber();
}

void customerMenu() {
    printf("You are now in the customer section. You can browse and make purchases.\n");
    // You would add the code to display products and handle purchases here
}

void storekeeperMenu() {
    int adminChoice;
    printf("\n--- Welcome to the Storekeeper Panel! ---\n");
    printf("What would you like to do?\n");
    printf("1. Add a new product\n");
    printf("2. View all products\n");
    printf("3. Exit to main menu\n");
    printf("INPUT: ");
    
    // Using scanf_s to get the admin's choice
    scanf_s("%d", &adminChoice);
    
    switch(adminChoice) {
        case 1:
            printf("You would add a new product here. (Functionality not implemented yet)\n");
            break;
        case 2:
            printf("You would view all products here. (Functionality not implemented yet)\n");
            break;
        case 3:
            printf("Exiting admin panel. Goodbye!\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

void storeKeeperPassCheck() {
    char adminPass[20];
    const char correctPassword[] = "admin123";

    printf("Insert the admin password to access the panel!\n");
    // Use scanf_s for a single-word password
    scanf_s("%19s", adminPass, sizeof(adminPass));

    if (strcmp(adminPass, correctPassword) == 0) {
        printf("Correct password, welcome to the admin panel!\n");
        storekeeperMenu();
    } else {
        printf("Wrong password, access denied!\n");
        storeKeeperPassCheck();
    }
}

void roleSelect(int roleChoice) {
    if (roleChoice == 1) {
        printf("You are a customer :)\n");
        customerMenu();
    } else {
        printf("You are a storekeeper :)\n");
        storeKeeperPassCheck();
    }
}

int main(void) {
    const int roleChoice = welcomeDialog();
    roleSelect(roleChoice);
    return 0;
}
