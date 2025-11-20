    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    /*
     * Separate data nd utility functions into modules (headers.h, foo.c) -> NOT YET
     * input-cleaning code could later be replaced by a unified handler using fgets for better consistency. -> NOT YET
     * Simple enums, such as GenderType { Male, Female } -> YES
     * Static arrays: inventory, codes and shoppingCart with malloc and realloc -> YES CODES AND REST OF THE STUFF USE MALLOC
     * Use index access a[i] and pointer access *(a + i) -> YES SOME ARE INDEX ACCESS, SOME ARE POINTER ACCESS
     * FEEDBACK FROM RELEASE 2 ^^^
     * Login system YES
     * Password encryption NOT YET - SASHSA NEEDS TO DO IT
     * User & Storekeeper Info -> NOT YET (FREE SPOT)
     * removePerfume(), editPerfume() for Storekeeper -> YES
     */

    // ALL IMPLEMENTED SO IGNORE

    ////////////////////////////////////////////////////////////////////////////////////
    // TEAM RESPONSIBILITIES — RELEASE 3
    // Dima
    //
    // - add Henrik's code (removePerfume(), editPerfume())
    // - SRS & Code review from the group
    // - start working on header files (MAYBE!)
    //
    // STEPS TO ACHIEVE THIS:
    //
    // 1. Integrate removePerfume() and editPerfume() functions into the current project.
    // 2. Test these functions with sample perfumes to ensure correctness.
    // 3. Coordinate with Henrik to understand how his code handles perfume IDs and inventory.
    // 4. Begin creating header files (store.h, customer.h, storekeeper.h) to organize function declarations.
    //
    // Brit
    //
    // - Add a new login & register system for the Customers
    // - Customers structure (address, house, apartment, name) & CustomersList structure (how many customers are registered)
    // - try to use dynamic memory allocation (malloc, calloc, free, etc.).
    // - CHECK Release 3 Dynamic Memory Allocation (Extended Track).pdf!!!!!!
    //
    // STEPS TO ACHIEVE THIS:
    // 1. implement structures: Customers, CustomersList
    // 2. Add a function that works as CustomerLogin(), which opens this interrogation: 1. Do you want to log in? 2. Do you want to register?
    // 3. RegisterFunction() -> takes input name, password.
    // 4. Sasha's function of pwdHashing() will hash the password
    // 5. Return the customer back to the CustomerLogin()
    // 6. If the customer selects login, validate input against CustomersList using hashed passwords
    //
    // CustomerMenu() should have a 6 options now, the 5. Edit current address, apartment number
    //
    //
    // Sasha
    //
    // - Address, apartment number, other optional data encryption function for Customers
    // - Hashing the password for Customers & StoreKeepers
    // - Review code and look for logical errors that might ruin the program
    //
    // STEPS TO ACHIEVE THIS:
    //
    // 1. implement encryptData() and decryptData() for sensitive customer fields.
    // 2. ensure pwdHashing() works with both Customers and Storekeepers.
    // 3. test hashing and encryption with sample data to ensure consistency.
    // 4. review all current code for logical errors, memory leaks
    //
    //
    // Andi
    //
    // - SRS Document together with Dima
    // - Add a function to change the
    // - Transaction log?
    // - Implement editCustomerInformation(), editStoreKeeperInformation()
    //
    // STEPS TO ACHIEVE THIS:
    // IDK tbh, however u want lol, should be the last things
    //
    // Henriiiik
    //
    // - Add a new login & register system for Storekeepers
    // - Other Storekeepers can add other stores, use structures however you want
    // - Display which store has those perfumes, and which store doesn't
    // - try to use dynamic memory allocation (malloc, calloc, free, etc.).
    // - CHECK Release 3 Dynamic Memory Allocation (Extended Track).pdf!!!!!!
    //
    // STEPS TO ACHIEVE THIS:
    // 1. implement StorekeeperLogin() and RegisterStorekeeper() functions.
    // 2. create Storekeeper and StoresList structures to track multiple storekeepers and stores.
    // 3. add functions to let storekeepers add new stores.
    // 4. implement a function to display perfume availability by store (e.g., showStoreInventory(perfumeID)).
    // 5. test program
    ////////////////////////////////////////////////////////////////////////////////////

    /* STRUCTURES */

    typedef enum {
        MENS,
        WOMENS,
        UNISEX
    } Gender;

    typedef struct {
        char name[50];
        char brand[50];
        float price;
        Gender gender;
        int stock;
        float discount;    // Percentage (0-100)
    } Perfume;

    typedef struct {
        int code;
        float value;
        int used;          // 0 = not used, 1 = redeemed
    } BalanceCode;

    typedef struct {
        BalanceCode* data;
        int count;
        int capacity;
    } BalanceCodesList;

    typedef struct {
        int storekeeperIndex;
        int perfumeIndex;  //Added by dima
        int quantity;
    } CartItem;

    typedef struct {
        char name[50];
        char password[100];
        char address[80];
        int houseNum;
        int apartmentNum;
        CartItem* cart;
        int cartItemCount;
        int cartCapacity;
        float balance;
    } Customer;

    typedef struct {
        Customer* data;
        int count;
        int capacity;
    } CustomersList;

    typedef struct {
        char name[80];
        char pwd[30];
        char address[40];
        Perfume* stock;
        int stockCount;
        int stockCapacity;
    } Storekeeper;

    typedef struct {
        Storekeeper* data;
        int count;
        int capacity;
    } StorekeeperList;

    ////////////////////////////////////////////////////////////////////////////////////

    /* GLOBAL VARIABLES */


    //ALMOST ALL GLOBAL VARIABLES REMOVED YEEEEEEAA

    //////////////////////////////////////////////////////////////////////////////////////

    // Initialization
    void defaultPerfumes(Storekeeper* sk);
    void defaultPerfumes2(Storekeeper* sk);
    void defaultLogin(Storekeeper* sk);
    void defaultCodes(BalanceCodesList* BCL);

    // Utility Functions
    int validNumber(void);
    float validFloat(void);
    int get_int_input(const char* prompt, int min, int max);
    void clearInputBuffer();
    float calculateDiscountedPrice(float price, float discount);
    Gender getGenderInput();
    void clearScreen();
    void encrypt(); // NEEDS TO BE IMPLEMENTED BY SASHA
    void decrypt(); // NEEDS TO BE IMPLEMENTED BY SASHSA


    // Display Functions
    int welcomeDialog();
    void viewPerfumes(const StorekeeperList* list);
    void viewCodes(const BalanceCodesList* BCL);

    // Customer Functions
    void customerMenu(const StorekeeperList* list, Customer* c, const BalanceCodesList* BCL);
    void addPerfumeToCart(const StorekeeperList* list, Customer* c);
    void viewShoppingCart(const StorekeeperList* list, Customer* c);
    void checkout(Customer* c, const StorekeeperList* skList, float* userBalance);
    void addBalance(Customer *c, BalanceCodesList* BCL);
    int customerLogin(); //IMPLEMENTED BY BRITTEN
    void customerRegister(); //IMPLEMENTED BY BRITTEN
    void customerLoginMenu(const StorekeeperList* list, BalanceCodesList* BCL); //IMPLEMENTED BY BRITTEN
    void pwdHashing(const char* input, char* output); //IMPLEMENTED BY BRITTEN
    void editCustomerAddress(Customer* c); //IMPLEMENTED BY BRITTEN
    void addCustomer(char* name, char* pwd, char* address, int houseNum); //IMPLEMENTED BY BRITTEN

    // Storekeeper Functions
    void storekeeperMenu(const Storekeeper *sk, const StorekeeperList *skList, BalanceCodesList* BCL);
    void storeKeeperLogin(const StorekeeperList* skList, BalanceCodesList* BCL); //FIX BY DIMA
    void addPerfume(const StorekeeperList* skList); //MADE BY HENRIK, IMPLEMENTED BY DIMA
    void removePerfume(const StorekeeperList* skList); //MADE BY HENRIK, IMPLEMENTED BY DIMA
    void editPerfume(const StorekeeperList* skList); //MADE BY HENRIK, IMPLEMENTED BY DIMA
    void setDiscount(const Storekeeper *sk, const StorekeeperList* skList);
    void addBalanceCode(BalanceCodesList* BCL);
    int selectStorekeeper(const StorekeeperList* skList);

    void roleSelect(int roleChoice, StorekeeperList* list, Customer* c, BalanceCodesList* BCL);
    void initStorekeeperList(StorekeeperList *list); // FIX BY DIMA
    void addStorekeeper(StorekeeperList *list, Storekeeper sk); // FIX BY DIMA
    void initStorekeeper(Storekeeper *sk); // FIX BY DIMA

    //////////////////////////////////////////////////////////////////////////////////////

    /*Initialization*/

    void defaultCodes(BalanceCodesList* BCL) {
        *(BCL->data + 0) = (BalanceCode){ 135791, 10, 0 };
        *(BCL->data + 1) = (BalanceCode){ 246802, 50, 0 };
        *(BCL->data + 2) = (BalanceCode){ 753197, 100, 0 };
        *(BCL->data + 3) = (BalanceCode){ 579135, 200, 0 };
        *(BCL->data + 4) = (BalanceCode){ 864202, 75, 0 };
        *(BCL->data + 5) = (BalanceCode){ 468024, 67, 0 };
        *(BCL->data + 6) = (BalanceCode){67, 2000000, 0};
        BCL->count = 7;
    }

    // Add hardcoded perfumes
    void defaultPerfumes(Storekeeper* sk) {
            *(sk->stock + 0) = (Perfume){ "Sauvage EDT", "Dior", 137, MENS, 100, 0 };
            *(sk->stock + 1) = (Perfume){ "Elixir EDP", "Yves Saint Laurent", 75, MENS, 50, 0 };
            *(sk->stock + 2) = (Perfume){ "Born In Roma EDT", "Valentino", 80, MENS, 40, 0 };
            *(sk->stock + 3) = (Perfume){ "No. 5 EDP", "Chanel", 135, WOMENS, 20, 0 };
            *(sk->stock + 4) = (Perfume){ "Black Opium EDP", "Yves Saint Laurent", 70, WOMENS, 40, 0 };
            sk->stockCount = 5;
        }

    void defaultPerfumes2(Storekeeper* sk) {
        *(sk->stock + 0) = (Perfume){ "Sauvage EDT", "Dior", 137, 1, 1, 0 };
        sk->stockCount = 1;
    }

    CustomersList largeList;

    CustomersList createCustomerList(int initialCapacity) {
        CustomersList list;
        list.data = malloc(initialCapacity * sizeof(Customer));
        list.count = 0;
        list.capacity = initialCapacity;
        return list;
    }

    void freeCustomerList(){
        free(largeList.data);
        largeList.data = NULL;
        largeList.count = 0;
        largeList.capacity = 0;
    }

    void freeBalanceCode(BalanceCodesList* BCL) {
            if (BCL->data != NULL) {
                free(BCL->data);
                BCL->data = NULL;
                BCL->count = 0;
                BCL->capacity = 0;
            }
        }

    void freeStorekeeper(const StorekeeperList* list) {
            for (int i = 0; i < list->count; i++) {
                if (list->data[i].stock != NULL) {
                    free(list->data[i].stock);
                }
            }
            free(list->data);
        }
    void initStorekeeperList(StorekeeperList *list) {
        list->capacity = 10;
        list->count = 0;
        list->data = malloc(list->capacity * sizeof(Storekeeper));
    }

    void initStorekeeper(Storekeeper *sk) {
        sk->stockCapacity = 100;
        sk->stockCount = 0;
        sk->stock = malloc(sizeof(Perfume) * sk->stockCapacity);
    }

    void initBalanceCodes(BalanceCodesList* BCL) {
            BCL->capacity = 10;
            BCL->count = 0;
            BCL->data = malloc(BCL->capacity * sizeof(BalanceCode));
        }

    void addBalanceCodesToList(BalanceCodesList* BCL) {
        if (BCL->count == BCL->capacity) {
            BCL->capacity *=2;
            BCL->data = realloc(BCL->data, BCL->capacity * sizeof(BalanceCode));
        }
    }

    void addStorekeeper(StorekeeperList *list, Storekeeper sk) {
        if (list->count >= list->capacity) {
            list->capacity *= 2;
            list->data = realloc(list->data, list->capacity * sizeof(Storekeeper));
        }

        list->data[list->count++] = sk;
    }


    // ^ Brand - Name - EDT or EDP - Masculine or Female
    // e.g Dior - Sauvage - EDT - Masculine

    //////////////////////////////////////////////////////////////////////////////////////

    /*Utility*/

    void clearInputBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    // ADDED BY DIMA

    int validNumber(void) {
        int x;
        while (1) {
            // Only integers are allowed!
            if (scanf("%d", &x) == 1) {
                return x;
            }
            else {
                printf("ERROR: Not a valid input! Try again.\n");
                printf("INPUT: ");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {} //Error handling when an input doesn't work!
            }
        }
    }

    float validFloat(void) {
        float x;
        while (1) {
            if (scanf("%f", &x) == 1) {
                return x;
            }
            else {
                printf("ERROR: Not a valid number! Try again.\n");
                printf("INPUT: ");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
            }
        }
    }

    int get_int_input(const char* prompt, int min, int max) {
        int input;
        printf("%s", prompt);
        while (scanf("%d", &input) != 1 || input < min || input > max) {
            printf("Invalid input. Please enter a number between %d and %d: ", min, max);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        while (getchar() != '\n') {}
        return input;
    }

    void clearScreen() {
        for (int i = 0; i < 15; i++) {
            printf("\n");
        }
    }

    float calculateDiscountedPrice(float price, float discount) {
        return price * (1.0 - discount / 100.0);
    } // ADDED BY DIMA

    void encrypt(char password[])
    {
        for(unsigned int i = 0;i<strlen(password);++i)
        {
            password[i] = password[i] - 0xFACA;
        }
    }

    void decrypt(char password[])
    {
        for(unsigned int i = 0;i<strlen(password);++i)
        {
            password[i] = password[i] + 0xFACA;
        }
    }

    Gender getGenderInput() {
            int input;
            scanf("%d", input);
            if (input == 1) return MENS;
            if (input == 0) return WOMENS;
            return UNISEX;
        }

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
                    // New perfume, add it
                    strcpy(perfumes[perfumeCount].name, p->name);
                    strcpy(perfumes[perfumeCount].brand, p->brand);
                    perfumes[perfumeCount].price = p->price;
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
        printf("%-5s %-25s %-20s %-8s %-8s %-8s\n", "No.", "Name", "Brand", "Price", "Stock", "Sex");
        printf("====================================================================================\n");

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

            printf("%-5d %-25s %-20s EUR%-7.2f  %-8d %-8s",
                i + 1,
                perfumes[i].name,
                perfumes[i].brand,
                perfumes[i].price,
                totalStock,
                sex);

            if (perfumes[i].discount != 0) {
                printf(" || Discount: %.2f%%", perfumes[i].discount);
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

    //Shows a menu with all the codes
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

    //////////////////////////////////////////////////////////////////////////////////////

    void customerMenu(const StorekeeperList* list, Customer* c, const BalanceCodesList* BCL) {
        do {
                printf("\n--- Customer Panel ---\n");
                printf("Current balance: %.2f\n", c->balance);
                printf("1. Add a perfume to shopping cart\n");
                printf("2. View all perfumes\n");
                printf("3. View shopping cart\n");
                printf("4. Add balance\n");
                printf("5. Edit address\n");
                printf("6. Exit to main menu\n");
                printf("INPUT: ");

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
                        printf("Exiting customer panel.\n");
                        return;
                    default:
                        printf("ERROR: Invalid choice.\n");
                }
            } while (1);
        }

    void addBalance(Customer* c, BalanceCodesList* BCL) {
            int code = get_int_input("Enter your balance code: ", 0, 999999);
            for (int i = 0; i < BCL->count; i++) {
                if (BCL->data[i].code == code && !BCL->data[i].used) {
                    c->balance += BCL->data[i].value;
                    BCL->data[i].used = 1;
                    printf("Balance updated: %.2f EUR\n", c->balance);
                    return;
                }
            }
            printf("Code invalid or already used.\n");
        }

    int deductFromStores(const StorekeeperList *skList, const Perfume *target, int quantity) {
        int remaining = quantity;

        for (int storeIdx = 0; storeIdx < skList->count; storeIdx++) {
            Storekeeper *sk = &skList->data[storeIdx];

            for (int i = 0; i < sk->stockCount; i++) {
                Perfume *p = &sk->stock[i];
                if (strcmp(p->name, target->name) == 0 && strcmp(p->brand, target->brand) == 0) {
                    if (p->stock >= remaining) {
                        p->stock -= remaining;
                        return 1;
                    } else {
                        remaining -= p->stock;
                        p->stock = 0;
                    }
                }
            }
        }
        return 0;
    }

    void checkout(Customer* c, const StorekeeperList* skList, float* userBalance) {
    if (c->cartItemCount == 0) {
        printf("\nYour cart is empty!\n");
        return;
    }

    float total = 0.0f;

    for (int i = 0; i < c->cartItemCount; i++) {
        int storeIdx = c->cart[i].storekeeperIndex;
        int perfumeIdx = c->cart[i].perfumeIndex;
        if (storeIdx < 0 || storeIdx >= skList->count ||
            perfumeIdx < 0 || perfumeIdx >= skList->data[storeIdx].stockCount) {
            continue;
        }

        Perfume *p = &skList->data[storeIdx].stock[perfumeIdx];
        float discountedPrice = calculateDiscountedPrice(p->price, p->discount);
        total += discountedPrice * c->cart[i].quantity;
    }

    printf("\nTotal cost: EUR %.2f\nYour balance: EUR %.2f\n", total, *userBalance);
    if (*userBalance < total) {
        printf("Insufficient funds! Need EUR %.2f more.\n", total - *userBalance);
        return;
    }

    *userBalance -= total;

    for (int i = 0; i < c->cartItemCount; i++) {
        int remaining = c->cart[i].quantity;
        for (int storeIdx = 0; storeIdx < skList->count && remaining > 0; storeIdx++) {
            Storekeeper *sk = &skList->data[storeIdx];
            for (int j = 0; j < sk->stockCount && remaining > 0; j++) {
                Perfume *p = &sk->stock[j];
                if (strcmp(p->name, skList->data[c->cart[i].storekeeperIndex].stock[c->cart[i].perfumeIndex].name) == 0 &&
                    strcmp(p->brand, skList->data[c->cart[i].storekeeperIndex].stock[c->cart[i].perfumeIndex].brand) == 0) {

                    if (p->stock >= remaining) {
                        p->stock -= remaining;
                        remaining = 0;
                    } else {
                        remaining -= p->stock;
                        p->stock = 0;
                    }
                }
            }
        }
    }

    printf("\nPurchase receipt:\n");
    printf("%-25s %-10s %-10s %-10s %-10s\n", "Perfume", "Price", "Qty", "Subtotal", "Store");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < c->cartItemCount; i++) {
        int storeIdx = c->cart[i].storekeeperIndex;
        int perfumeIdx = c->cart[i].perfumeIndex;
        Perfume *p = &skList->data[storeIdx].stock[perfumeIdx];
        float discountedPrice = calculateDiscountedPrice(p->price, p->discount);
        float subtotal = discountedPrice * c->cart[i].quantity;
        int remaining = c->cart[i].quantity;
        printf("%-25s EUR %-8.2f %-10d EUR %-8.2f", p->name, discountedPrice, c->cart[i].quantity, subtotal);

        int first = 1;
        for (int s = 0; s < skList->count && remaining > 0; s++) {
            Storekeeper *sk = &skList->data[s];
            for (int j = 0; j < sk->stockCount && remaining > 0; j++) {
                Perfume *p2 = &sk->stock[j];
                if (strcmp(p2->name, p->name) == 0 && strcmp(p2->brand, p->brand) == 0) {

                    int taken = (p2->stock >= remaining) ? remaining : p2->stock;

                    if (taken > 0) {
                        if (!first) printf(", ");
                        printf("%s(%d)", sk->name, taken);
                        remaining -= taken;
                        first = 0;
                    }
                }
            }
        }
        printf("\n");
    }

    printf("----------------------------------------------------------\n");
    printf("TOTAL: EUR %.2f\n", total);
    printf("Remaining balance: EUR %.2f\n", *userBalance);
    printf("=======================================================================\n");

    c->cartItemCount = 0;
    printf("\nYour shopping cart has been cleared.\n");
}

    void viewShoppingCart(const StorekeeperList* skList, Customer* c) {
    if (c->cartItemCount == 0) {
        printf("\nYour shopping cart is empty!\n");
        return;
    }

    printf("\n======================== YOUR SHOPPING CART ========================\n");
    printf("%-5s %-25s %-15s %-10s %-10s %-10s\n", "No.", "Perfume", "Store", "Price", "Quantity", "Subtotal");
    printf("--------------------------------------------------------------------------------\n");

    float totalAmount = 0.0f;
    int totalQuantity = 0;

    for (int i = 0; i < c->cartItemCount; i++) {
        int storeIdx = c->cart[i].storekeeperIndex;
        int perfumeIdx = c->cart[i].perfumeIndex;
        if (storeIdx < 0 || storeIdx >= skList->count) {
             printf("Error: Invalid store index for item %d. Skipping.\n", i + 1);
             continue;
        }

        Storekeeper *sk = &skList->data[storeIdx];

        if (perfumeIdx < 0 || perfumeIdx >= sk->stockCount) {
             printf("Error: Invalid perfume index for item %d. Skipping.\n", i + 1);
             continue;
        }

        Perfume *p = &sk->stock[perfumeIdx];
        float discountedPrice = calculateDiscountedPrice(p->price, p->discount);
        float subtotal = discountedPrice * c->cart[i].quantity;

        printf("%-5d %-25s %-15s EUR %-9.2f %-10d EUR %-9.2f\n",
               i + 1,
               p->name,
               sk->name,
               discountedPrice,
               c->cart[i].quantity,
               subtotal);

        totalAmount += subtotal;
        totalQuantity += c->cart[i].quantity;
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("Total amount: EUR %.2f\n", totalAmount);
    printf("Total quantity: %d\n", totalQuantity);
    printf("Your balance: EUR %.2f\n", c->balance);

    char choice;
    printf("\nWould you like to proceed to checkout? (y/n): ");
    if (scanf(" %c", &choice) != 1) {
        clearInputBuffer();
        printf("Invalid input. Returning to menu.\n");
        return;
    }

    if (choice == 'y' || choice == 'Y') {
        checkout(c, skList, &c->balance);
    } else {
        printf("Returning to the customer menu...\n");
    }
}

    void addPerfumeToCart(const StorekeeperList* skList, Customer* c) {
    viewPerfumes(skList);

    int perfumeNum = get_int_input("Enter perfume number (0 to cancel): ", 0, 100);
    if (perfumeNum == 0) return;

    // We need to re-simulate the view logic to find the correct indices
    // based on the number displayed to the user.
    typedef struct {
        char name[50];
        char brand[50];
    } PerfumeIdentity;

    int seenCount = 0;
    int foundStoreIdx = -1;
    int foundPerfumeIdx = -1;

    // Iterate exactly like viewPerfumes to find the 'perfumeNum'-th item
    for (int storeIdx = 0; storeIdx < skList->count; storeIdx++) {
        Storekeeper *sk = &skList->data[storeIdx];
        for (int i = 0; i < sk->stockCount; i++) {
            PerfumeIdentity seen[100];
            Perfume *p = &sk->stock[i];

            // check if this perfume type was already counted
            int alreadySeen = 0;
            for (int k = 0; k < seenCount; k++) {
                if (strcmp(seen[k].name, p->name) == 0 && strcmp(seen[k].brand, p->brand) == 0) {
                    alreadySeen = 1;
                    break;
                }
            }

            if (!alreadySeen) {
                // This is a new entry in the list
                strcpy(seen[seenCount].name, p->name);
                strcpy(seen[seenCount].brand, p->brand);
                seenCount++;

                // If this matches the user's choice
                if (seenCount == perfumeNum) {
                    foundStoreIdx = storeIdx;
                    foundPerfumeIdx = i;
                    goto FOUND;
                }
            }
            // If it was already seen, we technically could allow picking from specific stores
            // but for this simplified implementation, we pick the first occurrence found (Store 1, then Store 2...)
            // if we wanted to find specific store stock for the SAME perfume, logic would be more complex.
            // Current logic: If user picks #1, we grab the first instance of #1 we find.
            else if (seenCount == perfumeNum) {
                // We are looking for stock for the selected item.
                // If the previous store had 0 stock, we might want this one.
                // For now, simple add:
                 foundStoreIdx = storeIdx;
                 foundPerfumeIdx = i;
                 goto FOUND;
            }
        }
    }

FOUND:
    if (foundStoreIdx == -1) {
        printf("Invalid selection.\n");
        return;
    }

    printf("Selected: %s from %s\n", skList->data[foundStoreIdx].stock[foundPerfumeIdx].name, skList->data[foundStoreIdx].name);

    int quantity = get_int_input("Enter quantity: ", 1, 100);

    // Check stock
    if (skList->data[foundStoreIdx].stock[foundPerfumeIdx].stock < quantity) {
        printf("Not enough stock! Only %d available.\n", skList->data[foundStoreIdx].stock[foundPerfumeIdx].stock);
        return;
    }

    // Check cart capacity
    if (c->cartItemCount >= c->cartCapacity) {
        c->cartCapacity *= 2;
        c->cart = realloc(c->cart, c->cartCapacity * sizeof(CartItem));
    }

    // Add to cart
    c->cart[c->cartItemCount].storekeeperIndex = foundStoreIdx;
    c->cart[c->cartItemCount].perfumeIndex = foundPerfumeIdx;
    c->cart[c->cartItemCount].quantity = quantity;
    c->cartItemCount++;

    printf("Added %d x %s to your cart!\n", quantity, skList->data[foundStoreIdx].stock[foundPerfumeIdx].name);
}

    void addCustomer(char* name, char* pwd, char* address, int houseNum) {
        char n[50];
        scanf("%49s", n);
        if (largeList.count < largeList.capacity) {
            strcpy(largeList.data[largeList.count].name,n);
            //etc
            largeList.count++;
        }
    }

    void customerLoginMenu(const StorekeeperList* list, BalanceCodesList* BCL) {

        while (1) {
            printf("\n--- CUSTOMER LOGIN ---\n");
            printf("1. Login\n");
            printf("2. Register\n");
            printf("0. Back\n");
            printf("INPUT: ");

            int choice = validNumber();
            if (choice == 1) {
                int index = customerLogin();
                if (index != -1) {
                    printf("Login successful! Welcome, %s.\n", largeList.data[index].name);
                    // Pass the specific customer from the list
                    customerMenu(list, &largeList.data[index], BCL);
                }
            }
            else if (choice == 2) {
                customerRegister();
            }
            else if (choice == 0) {
                return;
            }
            else {
                printf("Invalid option.\n");
            }
        }
    }

    void customerRegister() {
            if (largeList.count >= largeList.capacity) {
                largeList.capacity *= 2;
                largeList.data = realloc(largeList.data, largeList.capacity * sizeof(Customer));
            }

            Customer* c = &largeList.data[largeList.count];

            printf("Enter username: ");
            scanf("%49s", c->name);

            char pwd[50];
            printf("Enter password: ");
            scanf("%49s", pwd);
            getchar();

            pwdHashing(pwd, c->password);

            printf("Enter address: ");
            fgets(c->address, sizeof(c->address), stdin);
            c->address[strcspn(c->address, "\n")] = '\0';

            printf("House number: ");
            c->houseNum = validNumber();

            printf("Apartment number: ");
            c->apartmentNum = validNumber();

            // Initialize customer's shopping cart
            c->cartCapacity = 10;
            c->cartItemCount = 0;
            c->cart = malloc(c->cartCapacity * sizeof(CartItem));
            c->balance = 0.0f;

            largeList.count++;
            printf("Registration successful!\n");
        }

    int customerLogin() {
        char username[50];
        char password[50];
        char hash[100];

        printf("Username: ");
        scanf("%49s", username);

        printf("Password: ");
        scanf("%49s", password);

        pwdHashing(password, hash);

        for (int i = 0; i < largeList.count; i++) {
            if (strcmp(largeList.data[i].name, username) == 0 &&
                strcmp(largeList.data[i].password, hash) == 0) {

                printf("Login successful!\n");
                return i;
                }
        }

        printf("Invalid username or password.\n");
        return -1;
    }

    void editCustomerAddress(Customer* c) {
            printf("New address: ");
            scanf("%79s", c->address);

            printf("New house number: ");
            c->houseNum = validNumber();

            printf("New apartment number: ");
            c->apartmentNum = validNumber();

            printf("Address updated!\n");
        }

    void pwdHashing(const char* input, char* output) {
            // TEMPORARY HASH for testing
            sprintf(output, "HASH(%s)", input);
        }

    //////////////////////////////////////////////////////////////////////////////////////

    // Storekeeper menu functionality
    void storekeeperMenu(const Storekeeper *sk, const StorekeeperList *skList, BalanceCodesList* BCL) {
        int adminChoice;
        clearScreen();
        do {
            printf("\n--- Storekeeper Panel ---\n");
            printf("What would you like to do?\n");
            printf("1. Add a new perfume\n");
            printf("2. Remove a perfume\n");
            printf("3. Edit a perfume\n");
            printf("4. View all perfumes\n");
            printf("5. Set discount\n");
            printf("6. Add balance code\n");
            printf("7. View balance codes\n");
            printf("8. Exit to main menu\n");
            printf("INPUT (1-8): ");

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
                    setDiscount(sk, skList);
                    break;
                case 6:
                    addBalanceCode(BCL);
                    break;
                case 7:
                    viewCodes(BCL);
                    break;
                case 8:
                    printf("\nExiting storekeeper panel. Goodbye!\n");
                    return;
                default:
                    printf("ERROR: Invalid choice. Please try again.\n");
                    break;
            }
        } while (adminChoice != 8);
    }

    // Password gate for storekeeper access
    void storeKeeperLogin(const StorekeeperList* skList, BalanceCodesList* BCL) {
        char adminPass[20];
        char adminName[20];

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
                    storekeeperMenu(&skList->data[i], skList, BCL);
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

    // Add perfume menu for admin
    void addPerfume(const StorekeeperList* skList) {
        int index = selectStorekeeper(skList);
        if (index == -1) return;

        Storekeeper* sk = &skList->data[index];

        if (sk->stockCount >= sk->stockCapacity) {
            int newCapacity = (sk->stockCapacity == 0) ? 4 : sk->stockCapacity * 2;
            Perfume* temp = realloc(sk->stock, newCapacity * sizeof(Perfume));
            if (!temp) {
                printf("Out of memory! Cannot add perfume.\n");
                return;
            }
            sk->stock = temp;
            sk->stockCapacity = newCapacity;
        }

        Perfume newPerfume;

        printf("Perfume Name: ");
        scanf(" %[^\n]", newPerfume.name);

        printf("Perfume Brand: ");
        scanf(" %[^\n]", newPerfume.brand);

        printf("Price: ");
        scanf("%f", &newPerfume.price);

        printf("Sex (1 for Male, 0 for Female): ");
        int genderInput;
        scanf("%d", &genderInput);
        newPerfume.gender = (genderInput == 1) ? MENS : WOMENS;

        printf("Amount in stock: ");
        scanf("%d", &newPerfume.stock);

        newPerfume.discount = 0;

        sk->stock[sk->stockCount++] = newPerfume;

        printf("\nPerfume added successfully to '%s'!\n\n", sk->name);
        viewPerfumes(skList);
    }

    void removePerfume(const StorekeeperList* skList) {
        if (skList->count == 0) {
            printf("No stores available.\n");
            return;
        }

        printf("\n---- Remove Perfume From Which Store? ----\n");
        for (int i = 0; i < skList->count; i++) {
            printf("%d. %s\n", i + 1, skList->data[i].name);
        }

        int storeIndex = get_int_input("Choice: ", 1, skList->count) - 1;
        Storekeeper* sk = &skList->data[storeIndex];

        if (sk->stockCount == 0) {
            printf("This store has no perfumes.\n");
            return;
        }

        printf("\nCurrent perfumes in %s:\n", sk->name);
        for (int i = 0; i < sk->stockCount; i++) {
            printf("%d. %s (%s)\n", i + 1, sk->stock[i].name, sk->stock[i].brand);
        }

        int perfumeIndex = get_int_input("Enter perfume number to remove: ", 1, sk->stockCount) - 1;

        for (int i = perfumeIndex; i < sk->stockCount - 1; i++) {
            sk->stock[i] = sk->stock[i + 1];
        }
        sk->stockCount--;

        printf("Perfume removed successfully from %s!\n", sk->name);
    }

    void editPerfume(const StorekeeperList* skList) {
        if (skList->count == 0) {
            printf("No stores available.\n");
            return;
        }

        // Select store
        printf("\n---- Edit Perfume In Which Store? ----\n");
        for (int i = 0; i < skList->count; i++) {
            printf("%d. %s\n", i + 1, skList->data[i].name);
        }

        int storeIndex = get_int_input("Choice: ", 1, skList->count) - 1;
        Storekeeper* sk = &skList->data[storeIndex];

        if (sk->stockCount == 0) {
            printf("This store has no perfume.\n");
            return;
        }

        // List perfumes
        printf("\nCurrent perfumes in %s:\n", sk->name);
        for (int i = 0; i < sk->stockCount; i++) {
            printf("%d. %s (%s) - Price: %.2f, Stock: %d\n",
                   i + 1, sk->stock[i].name, sk->stock[i].brand, sk->stock[i].price, sk->stock[i].stock);
        }

        int perfumeIndex = get_int_input("Enter perfume number to edit: ", 1, sk->stockCount) - 1;

        printf("Editing %s (%s)...\n", sk->stock[perfumeIndex].name, sk->stock[perfumeIndex].brand);
        printf("1. Price\n2. Stock\n");
        int editChoice = get_int_input("Choice: ", 1, 2);

        if (editChoice == 1) {
            printf("New Price: ");
            float newPrice;
            scanf("%f", &newPrice);
            sk->stock[perfumeIndex].price = newPrice;
        } else {
            printf("New Stock: ");
            int newStock;
            scanf("%d", &newStock);
            sk->stock[perfumeIndex].stock = newStock;
        }

        printf("Perfume updated successfully.\n");
    }

    void setDiscount(const Storekeeper* sk, const StorekeeperList* skList) {
        viewPerfumes(skList);

        if (sk->stockCount == 0) {
            return;
        }

        int proID = 0;
        int entered = 0;
        while (entered == 0) {
            printf("Enter index of perfume to add a discount: \n");
            proID = validNumber();
            if (proID >= 1 && proID <= sk->stockCount) {
                entered = 1;
            }
        }
        printf("Perfume selected: \n%s\n", sk->stock[proID-1].name);

        int discount = 0;
        int entered2 = 0;
        while (entered2 == 0) {
            printf("Input discount (%%):\n");
            discount = validNumber();
            if (discount > 0 && discount <= 100) {
                entered2 = 1;
            }
            else {
                printf("Enter a number between 1-100\n");
                entered2 = 0;
            }
        }
        sk->stock[proID - 1].discount = (float)discount;
        printf("\nDiscount of %d set for %s\n", discount, sk->stock[proID - 1].name);

        /*
         * one possible way to do it is
         * 1. Error handling, if there are not any perfumes, so perfumeCount == 0 -> return;
         * 2. Call the viewPerfumes(), so the admin understand which perfume he wants to give a discount
         * 3. He enters the corresponding number (e.g. 3 = cool fragrance) and 0 will exit out -> go back the menu
         * 4. perfumeNum - idx, because array, needs to call the calculateDiscountedPrice() function
         */
    }

    void addBalanceCode(BalanceCodesList* BCL) {
        printf("Current balance codes: \n");
        viewCodes(BCL);

        // DIMA add error handling
        printf("\nNew code (6 characters): \n");
        int code = validNumber();
        clearInputBuffer();

        for (int i = 0; i < BCL->count; i++) {
            if (BCL->data[i].code == code) {
                printf("ERROR: This code already exists!\n");
                return;
            }
        }

        printf("\nValue of code: \n");
        float value = validFloat();
        clearInputBuffer();

        if (value <= 0) {
            printf("ERROR: Value must be greater than 0!\n");
            return;
        }

        if (BCL->count >= BCL->capacity) {
            BCL->capacity *= 2;
            BCL->data = realloc(BCL->data, BCL->capacity * sizeof(BalanceCode));
        }

            BCL->data[BCL->count].code = code;
            BCL->data[BCL->count].value = value;
            BCL->data[BCL->count].used = 0;
            BCL->count++;


        viewCodes(BCL);

    }

    int selectStorekeeper(const StorekeeperList* skList) {
            if (skList->count == 0) {
                printf("No storekeepers available!\n");
                return -1;
            }

            printf("\n--- Select Storekeeper ---\n");
            for (int i = 0; i < skList->count; i++) {
                printf("%d. %s | %s\n", i + 1, skList->data[i].name, skList->data[i].address);
            }

            int choice = get_int_input("Choice: ", 1, skList->count) - 1;
            return choice;
        }

    //////////////////////////////////////////////////////////////////////////////////////

    /*Navigation*/

    // Routes user based on their chosen role
    void roleSelect(int roleChoice, StorekeeperList* list, Customer* c, BalanceCodesList* BCL) {
        while (1) {
            if (roleChoice == 1) {
                printf("You are a customer :)\n");
                customerLoginMenu(list, BCL);
                break;
            }
            else if (roleChoice == 2) {
                printf("You are a storekeeper :)\n");
                storeKeeperLogin(list, BCL);
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

    int main(void) {
        BalanceCodesList BCL;
        StorekeeperList skList;

        initBalanceCodes(&BCL);
        defaultCodes(&BCL);
        initStorekeeperList(&skList);

        Storekeeper dflt1 = {
            .name = "Tallinn",
            .pwd = "pass123",
            .address = "Parnu mnt 45, Tallinn, Estonia"
        };
        Storekeeper dflt2 = {
            .name = "Tartu",
            .pwd = "pass123",
            .address = "Ulikooli 18, Tartu, Estonia",
        };
        Storekeeper dflt3 = {
            .name = "Chisinau",
            .pwd = "pass123",
            .address = "Str. Stefan cel Mare 101, Moldova",
        };

        initStorekeeper(&dflt1);
        initStorekeeper(&dflt2);
        initStorekeeper(&dflt3);

        defaultPerfumes2(&dflt1);
        defaultPerfumes(&dflt2);
        defaultPerfumes(&dflt3);

        addStorekeeper(&skList, dflt1);
        addStorekeeper(&skList, dflt2);
        addStorekeeper(&skList, dflt3);

        largeList = createCustomerList(10);

        Customer* currentCustomer = NULL;

        const int roleChoice = welcomeDialog();
        roleSelect(roleChoice, &skList, currentCustomer, &BCL);

        freeCustomerList();
        freeStorekeeper(&skList);
        freeBalanceCode(&BCL);

        return 0;
    }