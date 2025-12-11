#include <stdio.h>
#include <string.h>
#include "../include/ui.h"
#include "../include/models.h"
#include "../include/logic.h"


//////////////////////////////////////////////////////////////////////////////////////

    /*Display functions*/

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
            "To exit type '0'\n"
            "**************************************************\n"
            "Happy shopping! :)\n");
        printf("INPUT: ");
        return validNumber();
    }

    // Customer viewing perfumes
    void viewPerfumes(const StorekeeperList *skList) {
    if (skList->count == 0) {
        printf("\nNo stores available!\n");
        return;
    }

    typedef struct {
        char name[50];
        char brand[50];
        float price;
        float discountedPrice;  // ADDED: Store the actual discounted price
        int sex;
        float discount;
        int storeIndices[10];
        int stockByStore[10];
        int storeCount;
    } PerfumeSummary;

    PerfumeSummary perfumes[100];
    int perfumeCount = 0;

    for (int storeIdx = 0; storeIdx < skList->count; storeIdx++) {
        Storekeeper *sk = &skList->data[storeIdx];

        for (int i = 0; i < sk->stockCount; i++) {
            Perfume *p = &sk->stock[i];

            int found = -1;
            for (int j = 0; j < perfumeCount; j++) {
                if (strcmp(perfumes[j].name, p->name) == 0 &&
                    strcmp(perfumes[j].brand, p->brand) == 0) {
                    found = j;
                    break;
                }
            }

            if (found >= 0) {
                int idx = perfumes[found].storeCount;
                perfumes[found].storeIndices[idx] = storeIdx;
                perfumes[found].stockByStore[idx] = p->stock;
                perfumes[found].storeCount++;
            } else {
                strcpy(perfumes[perfumeCount].name, p->name);
                strcpy(perfumes[perfumeCount].brand, p->brand);
                perfumes[perfumeCount].price = p->price;
                perfumes[perfumeCount].discountedPrice = calculateDiscountedPrice(p->price, p->discount); // CALCULATE DISCOUNTED PRICE
                perfumes[perfumeCount].sex = p->gender;
                perfumes[perfumeCount].discount = p->discount;
                perfumes[perfumeCount].storeIndices[0] = storeIdx;
                perfumes[perfumeCount].stockByStore[0] = p->stock;
                perfumes[perfumeCount].storeCount = 1;
                perfumeCount++;
            }
        }
    }

    printf("\nAvailable Perfumes\n");
    printf("%-5s %-25s %-20s %-12s %-8s %-8s\n", "No.", "Name", "Brand", "Price", "Stock", "Sex");
    printf("=======================================================================================\n");

    for (int i = 0; i < perfumeCount; i++) {
        char sex[7];
        if (perfumes[i].sex == MENS) {
            strcpy(sex, "Male");
        }
        else {
            strcpy(sex, "Female");
        }

        int totalStock = 0;
        for (int j = 0; j < perfumes[i].storeCount; j++) {
            totalStock += perfumes[i].stockByStore[j];
        }

        if (perfumes[i].discount > 0) {
            printf("%-5d %-25s %-20s EUR%-9.2f  %-8d %-8s",
                i + 1,
                perfumes[i].name,
                perfumes[i].brand,
                perfumes[i].discountedPrice,
                totalStock,
                sex);

            printf(" (Original: EUR%.2f, -%.0f%%)",
                   perfumes[i].price,
                   perfumes[i].discount);
        } else {
            printf("%-5d %-25s %-20s EUR%-9.2f  %-8d %-8s",
                i + 1,
                perfumes[i].name,
                perfumes[i].brand,
                perfumes[i].price,  // Show regular price if no discount
                totalStock,
                sex);
        }
        printf("\n");

        printf("      Stores: ");
        for (int j = 0; j < perfumes[i].storeCount; j++) {
            int storeIdx = perfumes[i].storeIndices[j];
            printf("%s (%d)",
                   skList->data[storeIdx].name,
                   perfumes[i].stockByStore[j]);
            if (j < perfumes[i].storeCount - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
    // shows a menu with all the codes yeah
    void viewCodes(const BalanceCodesList* BCL) {

        printf("\n======================= BALANCE CODES =======================\n");
        printf("%-5s %-12s %-12s %-10s\n", "No.", "Code", "Value (EUR)", "Status");
        printf("-------------------------------------------------------------\n");

        for (int i = 0; i < BCL->count; ++i) {
            const char *status = (BCL->data + i)->used ? "USED" : "NOT USED";

            printf("%-5d %-12d %-12.2f %-10s\n",
                   i + 1,
                   (BCL->data + i)->code,
                   (BCL->data + i)->value,
                   status);
        }

        printf("-------------------------------------------------------------\n");
        printf("Total codes: %d\n", BCL->count);
        printf("=============================================================\n");
    }

    void displayStorekeepers(const StorekeeperList* list) {
        if (list == NULL || list->data == NULL) {
            printf("Error: Storekeeper list is null or empty.\n");
            return;
        }

        if (list->count == 0) {
            printf("\nNo storekeepers registered yet.\n");
            return;
        }

        printf("\n=========== REGISTERED STOREKEEPERS ===========\n");
        printf("Total storekeepers: %d\n", list->count);
        printf("================================================\n");

        for (int i = 0; i < list->count; i++) {
            Storekeeper* sk = &list->data[i];
            printf("\n--- Storekeeper %d ---\n", i + 1);
            printf("Name: %s\n", sk->name);
            printf("Address: %s\n", sk->address);
            printf("Perfumes in stock: %d\n", sk->stockCount);
            printf("Stock capacity: %d\n", sk->stockCapacity);

            // Show perfume count by gender
            int maleCount = 0, femaleCount = 0, unisexCount = 0;
            for (int j = 0; j < sk->stockCount; j++) {
                switch (sk->stock[j].gender) {
                    case MENS: maleCount++; break;
                    case WOMENS: femaleCount++; break;
                    case UNISEX: unisexCount++; break;
                }
            }
            printf("Perfume breakdown: Male(%d) Female(%d) Unisex(%d)\n",
                   maleCount, femaleCount, unisexCount);
        }

        printf("\n================================================\n");
        }

    void displayCustomer(const Customer* c){
        if (c == NULL) {
            printf("Error: Customer data is null.\n");
            return;
        }

        char decryptedAddress[80];
        strcpy(decryptedAddress, c->address);
        decrypt(decryptedAddress);

        printf("\n=== CUSTOMER INFORMATION ===\n");
        printf("Name: %s\n", c->name);
        printf("Address: %s, House: %d, Apartment: %d\n",
               decryptedAddress, c->houseNum, c->apartmentNum);
        printf("Balance: EUR %.2f\n", c->balance);
        printf("Cart Items: %d\n", c->cartItemCount);

        if (c->cartItemCount > 0) {
            printf("Shopping Cart:\n");
            for (int i = 0; i < c->cartItemCount; i++) {
                printf("  - Item %d: Quantity %d\n", i + 1, c->cart[i].quantity);
            }
        } else {
            printf("Shopping Cart: Empty\n");
        }
        printf("=============================\n");
        }

    void displayCustomers(const CustomersList* custList){
        if (custList == NULL || custList->data == NULL) {
            printf("Error: Customer list is null or empty.\n");
            return;
        }

        if (custList->count == 0) {
            printf("\nNo customers registered yet.\n");
            return;
        }

        printf("\n=========== REGISTERED CUSTOMERS ===========\n");
        printf("Total customers: %d\n", custList->count);
        printf("============================================\n");

        for (int i = 0; i < custList->count; i++) {
            printf("\n--- Customer %d ---\n", i + 1);
            displayCustomer(&custList->data[i]);
        }

        printf("\n============================================\n");
        }

void customerMenu(const StorekeeperList* list, Customer* c, BalanceCodesList* BCL) {
        do {
            printf("\n--- Customer Panel ---\n");
            printf("Current balance: %.2f\n", c->balance);
            printf("1. Add a perfume to shopping cart\n");
            printf("2. View all perfumes\n");
            printf("3. View shopping cart\n");
            printf("4. Add balance\n");
            printf("5. Edit address\n");
            printf("6. Show information\n");
            printf("7. Exit to main menu\n");
            printf("INPUT (0-7): ");

            int userChoice = validNumber();

            switch (userChoice) {
                case 1:
                    addPerfumeToCart(list, c);
                    break;
                case 2:
                    viewPerfumes(list);
                    break;
                case 3:
                    viewShoppingCart(list, c);
                    break;
                case 4:
                    addBalance(c, BCL);
                    break;
                case 5:
                    editCustomerAddress(c);
                    break;
                case 6:
                    displayCustomer(c);
                    break;
                case 7:
                    printf("Exiting customer panel.\n");
                    return;
                default:
                    printf("ERROR: Invalid choice.\n");
            }
        } while (1);
    }

int customerLogin(CustomersList* custList) {
        char username[50];
        char password[50];
        char hash[100];

        printf("Username: ");
        scanf("%49s", username);

        printf("Password: ");
        scanf("%49s", password);

        pwdHashing(password, hash);

        for (int i = 0; i < custList->count; i++) {
            if (strcmp(custList->data[i].name, username) == 0 &&
                strcmp(custList->data[i].password, hash) == 0) {

                printf("Login successful!\n");
                return i;
                }
        }

        printf("Invalid username or password.\n");
        return -1;
    }
void customerLoginMenu(const StorekeeperList* list, BalanceCodesList* BCL, CustomersList* custList) {

        while (1) {
            printf("\n--- CUSTOMER LOGIN ---\n");
            printf("1. Login\n");
            printf("2. Register\n");
            printf("0. Back\n");
            printf("INPUT: ");

            int choice = validNumber();
            if (choice == 1) {
                int index = customerLogin(custList);
                if (index != -1) {
                    printf("Login successful! Welcome, %s.\n", custList->data[index].name);
                    customerMenu(list, &custList->data[index], BCL);
                }
            }
            else if (choice == 2) {
                customerRegister(custList);
            }
            else if (choice == 0) {
                return;
            }
            else {
                printf("Invalid option.\n");
            }
        }
    }

    // Storekeeper menu functionality
    void storekeeperMenu(const Storekeeper *sk, const StorekeeperList *skList, BalanceCodesList* BCL, const CustomersList* custlist) {
        int adminChoice;
        clearScreen();
        do {
            printf("\n--- Storekeeper Panel (%s) ---\n", sk->name);
            printf("What would you like to do?\n");
            printf("1. Add a new perfume\n");
            printf("2. Remove a perfume\n");
            printf("3. Edit a perfume\n");
            printf("4. View all perfumes\n");
            printf("5. Set discount\n");
            printf("6. Add balance code\n");
            printf("7. View balance codes\n");
            printf("8. Show customers\n");
            printf("9. Show storekeepers\n");
            printf("10. Exit to main menu\n");
            printf("INPUT (1-10): ");

            if (scanf("%d", &adminChoice) != 1) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("ERROR: Please enter a number.\n");
                continue;
            }

            switch (adminChoice) {
                case 1:
                    addPerfume(skList);
                    break;
                case 2:
                    removePerfume(skList);
                    break;
                case 3:
                    editPerfume(skList);
                    break;
                case 4:
                    viewPerfumes(skList);
                    break;
                case 5:
                    setDiscount(skList);
                    break;
                case 6:
                    addBalanceCode(BCL);
                    break;
                case 7:
                    viewCodes(BCL);
                    break;
                case 8:
                    displayCustomers(custlist);
                    break;
                case 9:
                    displayStorekeepers(skList);
                    break;
                case 10:
                    printf("\nExiting storekeeper panel. Goodbye!\n");
                    return;
                default:
                    printf("ERROR: Invalid choice. Please try again.\n");
                    break;
            }
        } while (adminChoice != 10);
    }

    // Password gate for storekeeper access
    void storeKeeperLogin(const StorekeeperList* skList, BalanceCodesList* BCL, const CustomersList* custlist) {
        char adminPass[20];
        char adminName[20];
        printf("\nDEV: username - Tallinn, password - pass123\n \n");

        printf("Insert the admin username to access the panel!\n");
        printf("USERNAME: ");
        scanf("%19s", adminName);

        printf("Insert the admin password to access the panel!\n");
        printf("PASSWORD: ");
        scanf("%19s", adminPass);
        int found = 0;

        for (int i = 0; i < skList->count; i++) {
            if (strcmp(skList->data[i].name, adminName) == 0) {
                found = 1;
                if (strcmp(skList->data[i].pwd, adminPass) == 0) {
                    printf("Successfully logged in!");
                    storekeeperMenu(&skList->data[i], skList, BCL, custlist);
                    return;
                }
                else {
                    printf("Invalid password!");
                    return;
                }
            }
        }
        if (!found) {
            printf("No such storekeeper exists!\n");
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////

/*Navigation*/

// Routes user based on their chosen role
void roleSelect(int roleChoice, StorekeeperList* list, BalanceCodesList* BCL, CustomersList* custList) {
        while (1) {
            if (roleChoice == 1) {
                printf("You are a customer :)\n");
                customerLoginMenu(list, BCL, custList);
                break;
            }
            else if (roleChoice == 2) {
                printf("You are a storekeeper :)\n");
                storeKeeperLogin(list, BCL, custList);
                break;
            }
            else if (roleChoice == 0) {
                printf("Bye! \n");
                break;
            }
            else {
                printf("ERROR: Not a valid number!\n");
                printf("INPUT: ");
                roleChoice = validNumber();
            }
        }
    }

/////////////////////////////////////////////////////////