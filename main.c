#include <stdio.h>
#include <string.h>

/*
 * Need to implement the following:
 * Functions (there are as of Release 1)
 * Decision tables
 * Arrays, Strings, Data Dictionaries
 * Pointers
 * Parameter Passing
*/

//Function for converting rateToEur[]

//Structure for Products & balance codes

typedef struct {
    char name[50];   // e.g., "Eau de Luxe"
    char brand[50]; // e.g., "Chanel"
    float price;           // e.g., 120.50
    int stock;             // e.g., 15 bottles available
    float discount; // e.g., how big is the discount
} Perfume;

typedef struct {
    char code[6];
    float value;
    int used; // 0 = not used, 1 = redeemed
} BalanceCode;

//ANDREAS & SASHA - ADMIN PANEL - IMPLEMENT addPerfume(), viewPerfume(), setDiscount(), addBalanceCode() work this with Britten! ;

//BRITTEN - USER PANEL - Implement addBalance() - work this with Andreas! , viewProducts();

//DIMA - SRS, ERROR HANDLING, FILE HANDLING LATER, EVERYTHING TO CHECK AT THE END

//HENRIK - FLOWCHARTS, USER STORIES (3 new ones related to the functions that
// other will implement), Implementation Options for Release 2 (SRS) & Decision Tables (SRS);

//SASHA - Data Dictionary (SRS) & Acceptance Criteria for Release 2 (SRS);

Perfume inventory[100];
int perfumeCount = 0;

BalanceCode codes[100];
int codeCount = 0;

float userBalance = 0.0f;

// Checks if the user made a valid input
int validNumber(void) {
    int x;
    while (1) {
        // Only integers are allowed!
        if (scanf("%d", &x) == 1) {
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
    int userChoice;
    do {
        printf("\n--- Customer Panel ---\n");
        printf("1. Add a new product\n");
        printf("2. View all products\n");
        printf("3. View shopping cart\n");
        printf("4. Exit to main menu\n");
        printf("INPUT: ");

        if (scanf("%d", &userChoice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("ERROR: Please enter a number.\n");
            continue;
        }

        switch (userChoice) {
            case 1:
                // addProducts();
                break;
            case 2:
                // viewProducts();
                break;
            case 3:
                // viewShoppingCart();
                break;
            case 4:
                printf("Exiting customer panel. Goodbye!\n");
                break;
            default:
                printf("ERROR: Invalid choice. Please try again.\n");
                break;
        }
        // Exit after handling options 1,2,3
        if (userChoice >= 1 && userChoice <= 3) {
            break;  // exit the menu loop after performing the action
        }
    } while (userChoice != 4);
}

// Storekeeper menu functionality
void storekeeperMenu() {
    int adminChoice;

    printf("\n--- Storekeeper Panel ---\n");
    printf("What would you like to do?\n");
    printf("1. Add a new product\n");
    printf("2. View all products\n");
    printf("3. Set discount\n");
    printf("4. Add balance code\n");
    printf("5. Exit to main menu\n");
    printf("INPUT: ");

    if (scanf("%d", &adminChoice) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {} // flush bad input
        printf("ERROR: Please enter a number.\n");
        return;
    }

    switch (adminChoice) {
        case 1:
            // addPerfume();
            break;
        case 2:
            // viewPerfume();
            break;
        case 3:
            // setDiscount();
            break;
        case 4:
            // addBalanceCode();
            break;
        case 5:
            printf("Exiting admin panel. Goodbye!\n");
            return;
        default:
            printf("ERROR: Invalid choice. Please try again.\n");
            break;
    }
}


// Password gate for storekeeper access
void storeKeeperPassCheck() {
    char adminPass[20];
    const char correctPassword[] = "admin123";

    printf("Insert the admin password to access the panel!\n");
    // Use scanf for a single-word password
    scanf("%19s", adminPass); //Reads the first 19 characters in the buffer

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
    while (1) {
        if (roleChoice == 1) {
            printf("You are a customer :)\n");
            customerMenu();
            break;
        } else if (roleChoice == 2) {
            printf("You are a storekeeper :)\n");
            storeKeeperPassCheck();
            break;
        } else {
            printf("ERROR: Not a valid number!\n");
            printf("INPUT: ");
            roleChoice = validNumber();
        }
    }
}

// Entry point
int main(void) {
    const int roleChoice = welcomeDialog();
    roleSelect(roleChoice);
    return 0;
}
