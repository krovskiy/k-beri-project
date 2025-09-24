#include <stdio.h>
#include <string.h>

// Checks if the user made a valid input
int validNumber(void) {
    int x;
    while (1) {
        if (scanf("%d", &x) && (x == 1 || x == 2)) {
            return x;
        } else {
            printf("ERROR: Not a valid input! Try again.\n");
            printf("INPUT: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { } //Error handling when an input doesn't work!
        }
    }
}

// Displays the welcome banner and asks for the user role
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

// Placeholder for customer functionality
void customerMenu() {
    printf("You are now in the customer section. You can browse and make purchases.\n");
    // You would add the code to display products and handle purchases here
}

// Storekeeper menu functionality
void storekeeperMenu() {
    int adminChoice;

    while (1) {  // keep looping until the user chooses "3"
        printf("\n--- Storekeeper Panel ---\n");
        printf("What would you like to do?\n");
        printf("1. Add a new product\n");
        printf("2. View all products\n");
        printf("3. Exit to main menu\n");
        printf("INPUT: ");

        if (scanf("%d", &adminChoice) != 1) {
            // flush bad input
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} //gets character, returns int, until we get ENTER so we can flush the pipe
            printf("ERROR: Please enter a number.\n");
            continue;
        }

        switch (adminChoice) {
            case 1:
                printf(">> Add product functionality coming soon...\n");
                break;
            case 2:
                printf(">> View products functionality coming soon...\n");
                break;
            case 3:
                printf("Exiting admin panel. Goodbye!\n");
                return;  // break out of the loop and return to caller
            default:
                printf("ERROR: Invalid choice. Please try again.\n");
                break;
        }
    }
}

// Password gate for storekeeper access
void storeKeeperPassCheck() {
    char adminPass[20];
    const char correctPassword[] = "admin123";

    printf("Insert the admin password to access the panel!\n");
    // Use scanf for a single-word password
    scanf("%19s", adminPass, sizeof(adminPass));

    if (strcmp(adminPass, correctPassword) == 0) {
        printf("Correct password, welcome to the admin panel!\n");
        storekeeperMenu();
    } else {
        printf("ERROR: Wrong password, access denied!\n");
        storeKeeperPassCheck();
    }
}
// Routes user based on their chosen role
void roleSelect(int roleChoice) {
    if (roleChoice == 1) {
        printf("You are a customer :)\n");
        customerMenu();
    } else {
        printf("You are a storekeeper :)\n");
        storeKeeperPassCheck();
    }
}

// Entry point
int main(void) {
    const int roleChoice = welcomeDialog();
    roleSelect(roleChoice);
    return 0;
}
