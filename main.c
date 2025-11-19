#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Separate data nd utility functions into modules (headers.h, foo.c)
 * input-cleaning code could later be replaced by a unified handler using fgets for better consistency.
 * Simple enums, such as GenderType { Male, Female }
 * Static arrays: inventory, codes and shoppingCart with malloc and realloc
 * Use index access a[i] and pointer access *(a + i)
 * FEEDBACK FROM RELEASE 2 ^^^
 * Login system
 * Password encryption
 * User & Storekeeper Info
 * removeProduct(), editProduct() for Storekeeper
 *
 */

// ALL IMPLEMENTED SO IGNORE

////////////////////////////////////////////////////////////////////////////////////
// TEAM RESPONSIBILITIES — RELEASE 3
// Dima
//
// - add Henrik's code (removeProduct(), editProduct())
// - SRS & Code review from the group
// - start working on header files (MAYBE!)
//
// STEPS TO ACHIEVE THIS:
//
// 1. Integrate removeProduct() and editProduct() functions into the current project.
// 2. Test these functions with sample products to ensure correctness.
// 3. Coordinate with Henrik to understand how his code handles product IDs and inventory.
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
// - Display which store has those products, and which store doesn't
// - try to use dynamic memory allocation (malloc, calloc, free, etc.).
// - CHECK Release 3 Dynamic Memory Allocation (Extended Track).pdf!!!!!!
//
// STEPS TO ACHIEVE THIS:
// 1. implement StorekeeperLogin() and RegisterStorekeeper() functions.
// 2. create Storekeeper and StoresList structures to track multiple storekeepers and stores.
// 3. add functions to let storekeepers add new stores.
// 4. implement a function to display product availability by store (e.g., showStoreInventory(productID)).
// 5. test program
////////////////////////////////////////////////////////////////////////////////////

/* STRUCTURES */

typedef struct {
    char name[50];
    char brand[50];
    float price;
    int sex;           // 1 = Male, 0 = Female
    int stock;
    float discount;    // Percentage (0-100)
} Perfume;

typedef struct {
    int code;
    float value;
    int used;          // 0 = not used, 1 = redeemed
} BalanceCode;

typedef struct {
    int perfumeIndex;  //Added by dima
    int quantity;
} CartItem;

typedef struct {
    char name[50];
    char pwd[30];
    char address[80];
    int houseNum;
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
Storekeeper sk;
StorekeeperList skList;

BalanceCode codes[100];
int codeCount = 0;

CartItem shoppingCart[100];
int cartItemCount = 0;

float userBalance = 0.0f;

//////////////////////////////////////////////////////////////////////////////////////

// Initialization
void defaultPerfumes(Storekeeper* sk);
void defaultLogin(Storekeeper* sk); // DONE
void defaultCodes();  // DONE

// Utility Functions
int validNumber(void);  // DONE
float validFloat(void);
int get_int_input(const char* prompt, int min, int max); // DONE BY HENRIK
void clearInputBuffer();  //  DIMA
float calculateDiscountedPrice(float price, float discount); // DONE

// Display Functions
int welcomeDialog();  // DONE
void viewProducts();  // DONE
void viewCodes(); // FOR ADMIN, WORK ON - SASHA

// Customer Functions
void customerMenu(); // DONE
void addProductToCart(); // DONE BY BRITTEN
void viewShoppingCart(); // DONE BY BRITTEN
void checkout(const CartItem* cart, int* cartItemCount, Perfume* inventory, int perfumeCount, float* userBalance); // DONE
void addBalance(); //DONE

// Storekeeper Functions
void storekeeperMenu();  // DONE
void storeKeeperPassCheck();  // DONE
void addPerfume(); //DONE
void setDiscount(); // DONE BY ANDREAS
void addBalanceCode(); // DONE BY ANDREAS

//Henrik's code had 2 additional functions: editProduct(), removeProduct() - I'm not sure if we should add it yet, because it uses
//different variables and structures that I cannot yet replicate without spending 2 hours trying to understand how to take A and put it in B

void roleSelect(int roleChoice); // DONE
void initStorekeeperList(StorekeeperList *list);
void addStorekeeper(StorekeeperList *list, Storekeeper sk);

//////////////////////////////////////////////////////////////////////////////////////

/*Initialization*/

void defaultCodes() {
    codes[0] = (BalanceCode){ 135791, 10, 0 };
    codes[1] = (BalanceCode){ 246802, 50, 0 };
    codes[2] = (BalanceCode){ 753197, 100, 0 };
    codes[3] = (BalanceCode){ 579135, 200, 0 };
    codes[4] = (BalanceCode){ 864202, 75, 0 };
    codes[5] = (BalanceCode){ 468024, 67, 0 };
    codeCount = 6;
}

// Add hardcoded perfumes
void defaultPerfumes(Storekeeper* sk) {
    sk->stock[0] = (Perfume){ "Sauvage EDT", "Dior", 137, 1, 100, 0 };
    sk->stock[1] = (Perfume){ "Elixir EDP", "Yves Saint Laurent", 75, 1, 50, 0 };
    sk->stock[2] = (Perfume){ "Born In Roma EDT", "Valentino", 80, 1, 40, 0 };
    sk->stock[3] = (Perfume){ "No. 5 EDP", "Chanel", 135, 0, 20, 0 };
    sk->stock[4] = (Perfume){ "Black Opium EDP", "Yves Saint Laurent", 70, 0, 40, 0 };
    sk->stockCount = 5;
}

void defaultLogin(Storekeeper* sk) {
    strcpy(sk->name, "Tallinn");
    strcpy(sk->pwd, "shrek123");
    strcpy(sk->address, "Narva mnt 95");
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

void initStorekeeperList(StorekeeperList *list) {
    list->capacity = 10;
    list->count = 0;
    list->data = malloc(list->capacity * sizeof(Storekeeper));
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

int clearScreen() {
    for (int i = 0; i < 15; i++) {
        printf("\n");
    }
}

float calculateDiscountedPrice(float price, float discount) {
    return price * (1.0 - discount / 100.0);
} // ADDED BY DIMA

void encrypt(char password[])
{
    unsigned int i;
    for(i=0;i<strlen(password);++i)
    {
        password[i] = password[i] - 0xFACA;
    }
}

void decrypt(char password[])
{
    unsigned int i;
    for(i=0;i<strlen(password);++i)
    {
        password[i] = password[i] + 0xFACA;
    }
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

// Customer viewing products
void viewProducts() {
    printf("\nAvailable Perfumes\n");
    printf("%-5s %-25s %-20s %-8s %-8s %-8s\n", "No.", "Name", "Brand", "Price", "Stock", "Sex");
    printf("====================================================================================\n");

    for (int i = 0; i < sk.stockCount; i++) {
        char sex[7];
        if (sk.stock[i].sex == 1) {
            strcpy(sex, "Male");
        }
        else {
            strcpy(sex, "Female");
        }

        printf("%-5d %-25s %-20s EUR%-7.2f  %-8d %-8s",
            i + 1,
            sk.stock[i].name,
            sk.stock[i].brand,
            sk.stock[i].price,
            sk.stock[i].stock,
            sex);
        if (sk.stock[i].discount != 0) {
            printf(" || Discount: %.2f", sk.stock[i].discount);
        }
        printf("\n");
    }
    printf("\n");
}

//Shows a menu with all the codes
void viewCodes() {

    printf("\n======================= BALANCE CODES =======================\n");
    printf("%-5s %-12s %-12s %-10s\n", "No.", "Code", "Value (EUR)", "Status");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < codeCount; ++i) {
        const char *status = codes[i].used ? "USED" : "NOT USED";

        printf("%-5d %-12d %-12.2f %-10s\n",
               i + 1,
               codes[i].code,
               codes[i].value,
               status);
    }

    printf("-------------------------------------------------------------\n");
    printf("Total codes: %d\n", codeCount);
    printf("=============================================================\n");
}

//////////////////////////////////////////////////////////////////////////////////////

void customerMenu() {
    printf("You are now in the customer section. You can browse and make purchases.\n");

    int userChoice;
    do {
        printf("\n--- Customer Panel ---\n");
        printf("Current balance: %.2f\n", userBalance);
        printf("1. Add a product to shopping cart\n");
        printf("2. View all products\n");
        printf("3. View shopping cart\n");
        printf("4. Add balance\n");
        printf("5. Exit to main menu\n");
        printf("INPUT: ");

        if (scanf("%d", &userChoice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("ERROR: Please enter a number.\n");
            continue;
        }

        switch (userChoice) {
        case 1:
            addProductToCart();
            break;
        case 2:
            viewProducts();
            break;
        case 3:
            viewShoppingCart();
            break;
        case 4:
            addBalance();
            break;
        case 5:
            printf("Exiting customer panel. Goodbye!\n");
            const int roleChoice = welcomeDialog();
            roleSelect(roleChoice);
            break;
        default:
            printf("ERROR: Invalid choice. Please try again.\n");
            break;
        }
    } while (userChoice != 5);
}

void addBalance() {
    int found = 0;

    int enteredCode = get_int_input("Enter your balance code: ", 0, 999999);

    for (int i = 0; i < codeCount; i++) {
        if (enteredCode == codes[i].code) {
            if (codes[i].used == 0) {
                userBalance += codes[i].value;
                codes[i].used = 1;
                printf("Code accepted! Your balance increased by %.2f EUR.\n", codes[i].value);
                printf("Your new balance: %.2f EUR\n", userBalance);
            }
            else {
                printf("This code has already been used!\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Code does not exist!\n");
    }
}

void checkout(const CartItem* cart, int* cartItemCount, Perfume* inventory, int perfumeCount, float* userBalance) {
    if (*cartItemCount == 0) {
        printf("\nYour cart is empty! Add some products before checking out.\n");
        return;
    }

    float total = 0.0f;

    for (int i = 0; i < *cartItemCount; i++) {
        int index = cart[i].perfumeIndex;

        if (index < 0 || index >= perfumeCount) {
            printf("ERROR: Invalid perfume index (%d). Skipping item.\n", index);
            continue;
        }

        Perfume *p = &sk.stock[index];
        float discountedPrice = calculateDiscountedPrice(p->price, p->discount);
        float subtotal = discountedPrice * cart[i].quantity;
        total += subtotal;
    }

    printf("\n==============================================================\n");
    printf("Total cost of your purchase: EUR %.2f\n", total);
    printf("Your current balance: EUR %.2f\n", *userBalance);

    if (*userBalance < total) {
        printf("Insufficient funds! You need EUR %.2f more to complete the purchase.\n", total - *userBalance);
        printf("==============================================================\n");
        return;
    }

    *userBalance -= total;

    for (int i = 0; i < *cartItemCount; i++) {
        int index = cart[i].perfumeIndex;

        if (index < 0 || index >= perfumeCount)
            continue;

        Perfume *p = &sk.stock[index];
        if (p->stock >= cart[i].quantity)
            p->stock -= cart[i].quantity;
        else
            p->stock = 0;
    }

    printf("\nPurchase successful! Here’s your receipt:\n");
    printf("--------------------------------------------------------------\n");
    printf("%-25s %-10s %-10s %-10s\n", "Product", "Price", "Qty", "Subtotal");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < *cartItemCount; i++) {
        Perfume *p = &sk.stock[cart[i].perfumeIndex];
        float discountedPrice = calculateDiscountedPrice(p->price, p->discount);
        float subtotal = discountedPrice * cart[i].quantity;

        printf("%-25s EUR %-9.2f %-10d EUR %-9.2f\n",
               p->name, discountedPrice, cart[i].quantity, subtotal);
    }

    printf("--------------------------------------------------------------\n");
    printf("TOTAL: EUR %.2f\n", total);
    printf("Remaining balance: EUR %.2f\n", *userBalance);
    printf("==============================================================\n");

    *cartItemCount = 0;
    printf("\nYour shopping cart has been cleared.\n");
}

void viewShoppingCart() {

    if (cartItemCount == 0) {
        printf("\nYour shopping cart is empty!\n");
        return;
    }

    printf("\n======================== YOUR SHOPPING CART ========================\n");
    printf("%-5s %-25s %-10s   %-10s %-10s\n", "No.", "Product", "Price", "Quantity", "Subtotal");
    printf("--------------------------------------------------------------------\n");

    float totalAmount = 0.0f;
    int totalQuantity = 0;

    for (int i = 0; i < cartItemCount; i++) {
        int index = shoppingCart[i].perfumeIndex;
        Perfume *p = &sk.stock[index];
        float discountedPrice = calculateDiscountedPrice(p->price, p->discount);
        float subtotal = discountedPrice * shoppingCart[i].quantity;

        printf("%-5d %-25s EUR %-9.2f %-10d EUR %-9.2f\n",
               i + 1,
               p->name,
               discountedPrice,
               shoppingCart[i].quantity,
               subtotal);

        totalAmount += subtotal;
        totalQuantity += shoppingCart[i].quantity;
    }

    printf("--------------------------------------------------------------------\n");
    printf("Total amount: EUR %.2f\n", totalAmount);
    printf("Total quantity: %d\n", totalQuantity);
    printf("Your balance: EUR %.2f\n", userBalance);

    char choice;
    printf("\nWould you like to proceed to checkout? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        checkout(shoppingCart, &cartItemCount, sk.stock, sk.stockCount, &userBalance);
    } else {
        printf("Returning to the customer menu...\n");
    }
}

void addProductToCart() {
    viewProducts();

    if (sk.stockCount == 0) {
        printf("No products available! \n");
        return;
    }

    printf("Enter product number (0 to cancel):");
    int productNum = validNumber();

    if (productNum == 0) {
        printf("Action cancelled.\n");
        return;
    }

    if (productNum < 1 || productNum > sk.stockCount) {
        printf("ERROR: Invalid product number!\n");
        return;
    }

    int index = productNum -1;

    if (sk.stock[index].stock <= 0) {
        printf("ERROR: OUT OF STOCK!\n");
        return;
    }

    printf("Enter quantity: ");
    int quantity = validNumber();

    if (quantity <= 0) {
        printf("ERROR: Quantity must be greater than 0.\n");
        return;
    }

    if (quantity > sk.stock[index].stock) {
        printf("ERROR: Not enough stock! Only %d left.\n", sk.stock[index].stock);
        return;
    }

    for (int i = 0; i < cartItemCount; i++) {
        if (shoppingCart[i].perfumeIndex == index) {
            int newTotal = shoppingCart[i].quantity + quantity;
            if (newTotal > sk.stock[index].stock) {
                printf("ERROR: Not enough stock! You already have %d in your cart, only %d left.\n",
                       shoppingCart[i].quantity, sk.stock[index].stock);
                return;
            }

            shoppingCart[i].quantity = newTotal;
            printf("Updated quantity of %s to %d.\n",
                   sk.stock[index].name, shoppingCart[i].quantity);
            return;
        }
    }

    if (cartItemCount >= 100) {
        printf("ERROR: Cart is full!\n");
        return;
    }

    shoppingCart[cartItemCount].perfumeIndex = index;
    shoppingCart[cartItemCount].quantity = quantity;
    cartItemCount++;

    printf("Added %d x %s to your cart!\n", quantity, sk.stock[index].name);
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

//////////////////////////////////////////////////////////////////////////////////////


// Storekeeper menu functionality
void storekeeperMenu() {
    int adminChoice;
    clearScreen();
    do {
        printf("\n--- Storekeeper Panel ---\n");
        printf("What would you like to do?\n");
        printf("1. Add a new product\n");
        printf("2. View all products\n");
        printf("3. Set discount\n");
        printf("4. Add balance code\n");
        printf("5. View balance codes\n");
        printf("6. Exit to main menu\n");
        printf("INPUT: ");

        if (scanf("%d", &adminChoice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("ERROR: Please enter a number.\n");
            continue;
        }

        switch (adminChoice) {
        case 1:
            addPerfume();
            break;
        case 2:
            viewProducts();
            break;
        case 3:
            setDiscount();
            break;
        case 4:
            addBalanceCode();
            break;
        case 5:
            viewCodes();
            break;
        case 6:
            printf("\nExiting storekeeper panel. Goodbye!\n");
            const int roleChoice = welcomeDialog();
            roleSelect(roleChoice);
            return;
        default:
            printf("ERROR: Invalid choice. Please try again.\n");
            break;
        }
    } while (adminChoice != 6);
}

// Password gate for storekeeper access
void storeKeeperLogin() {
    char adminPass[20];
    char adminName[20];

    printf("Insert the admin username to access the panel!\n");
    printf("USERNAME: ");
    scanf("%19s", adminName);

    printf("Insert the admin password to access the panel!\n");
    printf("PASSWORD: ");
    scanf("%19s", adminPass);

    int found = 0;

    for (int i = 0; i < skList.count; i++) {
        if (strcmp(skList.data[i].name, adminName) == 0) {
            found = 1;
            if (strcmp(skList.data[i].pwd, adminPass) == 0) {
                printf("Succesfully logged in!");
                storekeeperMenu();
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
void addPerfume() {
    if (sk.stockCount >= 100) {
        printf("ERROR: Inventory is full!\n");
        return;
    }

    char name[50];
    printf("Perfume Name: ");
    scanf("%49s", name);
    clearInputBuffer();

    char brand[50];
    printf("Perfume Brand: ");
    scanf("%49s", brand);
    clearInputBuffer();

    float price;
    printf("Enter price: ");
    scanf("%f", &price);
    clearInputBuffer();

    int sex;
    printf("Sex (1 for Male, 0 for Female): ");
    scanf("%d", &sex);
    clearInputBuffer();

    int stock;
    printf("Amount in stock: ");
    scanf("%d", &stock);
    clearInputBuffer();

    int a = sk.stockCount;
    strcpy(sk.stock[a].name, name);
    strcpy(sk.stock[a].brand, brand);
    sk.stock[a].price = price;
    sk.stock[a].sex = sex;
    sk.stock[a].stock = stock;
    sk.stock[a].discount = 0;
    sk.stockCount += 1;

    printf("\nPerfume added successfully!\n\n");
    viewProducts();
}

// Sets a discount for a product
void setDiscount() {
    viewProducts();

    if (sk.stockCount == 0) {
        return;
    }

    int proID = 0;
    int entered = 0;
    while (entered == 0) {
        printf("Enter index of product to add a discount: \n");
        proID = validNumber();
        if (proID >= 1 && proID <= sk.stockCount) {
            entered = 1;
        }
    }
    printf("Product selected: \n%s\n", sk.stock[proID-1].name);

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
    sk.stock[proID - 1].discount = (float)discount;
    printf("\nDiscount of %d set for %s\n", discount, sk.stock[proID - 1].name);

    /*
     * one possible way to do it is
     * 1. Error handling, if there are not any products, so perfumeCount == 0 -> return;
     * 2. Call the viewProducts(), so the admin understand which perfume he wants to give a discount
     * 3. He enters the corresponding number (e.g. 3 = cool fragrance) and 0 will exit out -> go back the menu
     * 4. productNum - idx, because array, needs to call the calculateDiscountedPrice() function
     */
}

void addBalanceCode() {
    printf("Current balance codes: \n");
    viewCodes();

    // DIMA add error handling
    printf("\nNew code (6 characters): \n");
    int code = validNumber();
    clearInputBuffer();

    for (int i = 0; i < codeCount; i++) {
        if (codes[i].code == code) {
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

        codes[codeCount].code = code;
        codes[codeCount].value = value;
        codes[codeCount].used = 0;
        codeCount++;


    viewCodes();

}



//////////////////////////////////////////////////////////////////////////////////////

/*Navigation*/

// Routes user based on their chosen role
void roleSelect(int roleChoice) {
    while (1) {
        if (roleChoice == 1) {
            printf("You are a customer :)\n");
            customerMenu();
            break;
        }
        else if (roleChoice == 2) {
            printf("You are a storekeeper :)\n");
            storeKeeperLogin();
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


// MAIN
int main(void) {
    sk.stockCapacity = 100;
    sk.stock = malloc(sizeof(Perfume) * sk.stockCapacity);

    initStorekeeperList(&skList);

    Storekeeper dflt1 = {
        .name = "Tallinn",
        .pwd = "shrek123",
        .address = "default address",
        .stock = NULL,
        .stockCount = 0,
        .stockCapacity = 0
    };
    Storekeeper dflt2 = {
        .name = "Tartu",
        .pwd = "shrek123",
        .address = "default address",
        .stock = NULL,
        .stockCount = 0,
        .stockCapacity = 0
    };

    addStorekeeper(&skList, dflt1);
    addStorekeeper(&skList, dflt2);
    defaultPerfumes(&sk);
    defaultLogin(&sk);

    defaultCodes();

    largeList = createCustomerList(10);

    const int roleChoice = welcomeDialog();
    roleSelect(roleChoice);

    freeCustomerList();

    return 0;
}