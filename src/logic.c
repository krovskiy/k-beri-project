    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include "../include/logic.h"
    #include "../include/models.h"
    #include "../include/ui.h"
    
    /* GLOBAL VARIABLES */

    //ALL GLOBAL VARIABLES REMOVED YEEEEEEAA

    void freeCustomerList(CustomersList* list) {
        if (list->data != NULL) {
            for (int i = 0; i < list->count; i++) {
                if (list->data[i].cart != NULL) {
                    free(list->data[i].cart);
                    list->data[i].cart = NULL;
                }
            }
            free(list->data);
            list->data = NULL;
            list->count = 0;
            list->capacity = 0;
        }
    }

    void freeBalanceCode(BalanceCodesList* BCL) {
            if (BCL->data != NULL) {
                free(BCL->data);
                BCL->data = NULL;
                BCL->count = 0;
                BCL->capacity = 0;
            }
        }

    void freeStorekeeper(StorekeeperList* list) {
            for (int i = 0; i < list->count; i++) {
                if (list->data[i].stock != NULL) {
                    free(list->data[i].stock);
                    list->data[i].stock = NULL;
                }
            }
            free(list->data);
            list->data = NULL;
            list->count = 0;
            list->capacity = 0;
        }

    void initStorekeeperList(StorekeeperList *list) {
        list->capacity = 10;
        list->count = 0;
        list->data = malloc(list->capacity * sizeof(Storekeeper));
        if (list->data == NULL) {
            printf("FATAL: Cannot allocate memory!\n");
            exit(1);
        }
    }

    void initStorekeeper(Storekeeper *sk) {
        sk->stockCapacity = 100;
        sk->stockCount = 0;
        sk->stock = malloc(sizeof(Perfume) * sk->stockCapacity);
        if (sk->stock == NULL) {
            printf("FATAL: Cannot allocate memory!\n");
            exit(1);
        }
    }

    void initCustomerList(CustomersList* list) {
            list->capacity = 10;
            list->count = 0;
            list->data = malloc(list->capacity * sizeof(Customer));
            if (list->data == NULL) {
                printf("FATAL: Cannot allocate memory!\n");
                exit(1);
            }
        }

    void initBalanceCodes(BalanceCodesList* BCL) {
            BCL->capacity = 10;
            BCL->count = 0;
            BCL->data = malloc(BCL->capacity * sizeof(BalanceCode));
            if (BCL->data == NULL) {
                printf("FATAL: Cannot allocate memory!\n");
                exit(1);
            }
        }

    void addStorekeeper(StorekeeperList *list, Storekeeper sk) {
        if (list->count >= list->capacity) {
            list->capacity *= 2;
            Storekeeper* temp = realloc(list->data, list->capacity * sizeof(Storekeeper));

            if (temp == NULL) {
                printf("ERROR: Out of memory!\n");
                return;
            }
            list->data = temp;
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

    void encrypt(char str[])
        {
            for (int i = 0; str[i] != '\0'; i++)
            {
                str[i] = str[i] + 3;
            }
        }

    void decrypt(char str[])
        {
            for (int i = 0; str[i] != '\0'; i++)
            {
                str[i] = str[i] - 3;
            }
        }

    Gender getGenderInput() {
            int input;
            scanf("%d", &input);
            if (input == 1) return MENS;
            if (input == 0) return WOMENS;
            return UNISEX;
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

        // verify all items still have sufficient stock
        for (int i = 0; i < c->cartItemCount; i++) {
            int storeIdx = c->cart[i].storekeeperIndex;
            int perfumeIdx = c->cart[i].perfumeIndex;
            if (storeIdx < 0 || storeIdx >= skList->count ||
                perfumeIdx < 0 || perfumeIdx >= skList->data[storeIdx].stockCount) {
                continue;
            }

            Perfume *p = &skList->data[storeIdx].stock[perfumeIdx];

            // then do a check of total stock across all stores for this perfume
            int totalStock = 0;
            for (int s = 0; s < skList->count; s++) {
                Storekeeper *sk = &skList->data[s];
                for (int j = 0; j < sk->stockCount; j++) {
                    Perfume *p2 = &sk->stock[j];
                    if (strcmp(p2->name, p->name) == 0 && strcmp(p2->brand, p->brand) == 0) {
                        totalStock += p2->stock;
                    }
                }
            }

            if (totalStock < c->cart[i].quantity) {
                printf("ERROR: Not enough stock for %s! Only %d available.\n", p->name, totalStock);
                return;
            }
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
        decrypt(c->address);
        printf("The item(s) will be delivered to: %s, %d, %d in 7-14 business days! \n \n", c->address, c->houseNum, c->apartmentNum);
        printf("\nYour shopping cart has been cleared.\n");
        encrypt(c->address);
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

    typedef struct {
        char name[50];
        char brand[50];
    } PerfumeIdentity;

    PerfumeIdentity seen[100];
    int seenCount = 0;
    int foundStoreIdx = -1;
    int foundPerfumeIdx = -1;
    char selectedName[50] = "";
    char selectedBrand[50] = "";

    for (int storeIdx = 0; storeIdx < skList->count; storeIdx++) {
        Storekeeper *sk = &skList->data[storeIdx];
        for (int i = 0; i < sk->stockCount; i++) {

            Perfume *p = &sk->stock[i];

            int alreadySeen = 0;
            for (int k = 0; k < seenCount; k++) {
                if (strcmp(seen[k].name, p->name) == 0 && strcmp(seen[k].brand, p->brand) == 0) {
                    alreadySeen = 1;
                    break;
                }
            }

            if (!alreadySeen) {
                strcpy(seen[seenCount].name, p->name);
                strcpy(seen[seenCount].brand, p->brand);
                seenCount++;

                if (seenCount == perfumeNum) {
                    foundStoreIdx = storeIdx;
                    foundPerfumeIdx = i;
                    strcpy(selectedName, p->name);
                    strcpy(selectedBrand, p->brand);
                    goto FOUND;
                }
            }

            else if (seenCount == perfumeNum) {
                 foundStoreIdx = storeIdx;
                 foundPerfumeIdx = i;
                 strcpy(selectedName, p->name);
                 strcpy(selectedBrand, p->brand);
                 goto FOUND;
            }
        }
    }

    FOUND:
        if (foundStoreIdx == -1) {
            printf("Invalid selection.\n");
            return;
        }

        printf("Selected: %s from %s\n", selectedName, skList->data[foundStoreIdx].name);

        // Calculate total available stock across ALL stores for this perfume, who cares migbt be a bandaid solution
        int totalStock = 0;
        for (int storeIdx = 0; storeIdx < skList->count; storeIdx++) {
            Storekeeper *sk = &skList->data[storeIdx];
            for (int i = 0; i < sk->stockCount; i++) {
                Perfume *p = &sk->stock[i];
                if (strcmp(p->name, selectedName) == 0 && strcmp(p->brand, selectedBrand) == 0) {
                    totalStock += p->stock;
                }
            }
        }

        printf("Total available stock across all stores: %d\n", totalStock);

        int quantity = get_int_input("Enter quantity: ", 1, 100);

        if (totalStock < quantity) {
            printf("Not enough stock! Only %d available across all stores.\n", totalStock);
            return;
        }

        if (c->cartItemCount >= c->cartCapacity) {
            c->cartCapacity *= 2;
            CartItem* temp = realloc(c->cart, c->cartCapacity * sizeof(CartItem));

            if (temp == NULL) {
                printf("ERROR: Out of memory! Cannot add to cart.\n");
                return;
            }
            c->cart = temp;
        }

        c->cart[c->cartItemCount].storekeeperIndex = foundStoreIdx;
        c->cart[c->cartItemCount].perfumeIndex = foundPerfumeIdx;
        c->cart[c->cartItemCount].quantity = quantity;
        c->cartItemCount++;

        printf("Added %d x %s to your cart!\n", quantity, selectedName);
}

    void customerRegister(CustomersList* custList) {
            Customer newCustomer;
            if (custList->count >= custList->capacity) {
                custList->capacity *= 2;
                Customer* temp = realloc(custList->data, custList->capacity * sizeof(Customer));

                if (temp == NULL) {
                    printf("ERROR: Out of memory! Cannot register.\n");
                    return;
                }
                custList->data = temp;
            }
            printf("Enter username: ");
            scanf("%49s", newCustomer.name);

            char pwd[50];
            printf("Enter password: ");
            scanf("%49s", pwd);
            getchar();

            pwdHashing(pwd, newCustomer.password);

            printf("Enter address: ");
            fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
            newCustomer.address[strcspn(newCustomer.address, "\n")] = '\0';
            encrypt(newCustomer.address);

            printf("House number: ");
            newCustomer.houseNum = validNumber();

            printf("Apartment number: ");
            newCustomer.apartmentNum = validNumber();

            // cart init
            newCustomer.cartCapacity = 10;
            newCustomer.cartItemCount = 0;
            newCustomer.cart = malloc(newCustomer.cartCapacity * sizeof(CartItem));
            newCustomer.balance = 0.0f;

            custList->data[custList->count] = newCustomer;
            custList->count++;
            printf("Registration successful!\n");
        }


    void editCustomerAddress(Customer* c) {
            decrypt(c->address);
            printf("Your current address is: %s, %d, %d \n \n", c->address, c->houseNum, c->apartmentNum);
            clearInputBuffer();
            printf("New address: ");
            fgets(c->address, sizeof(c->address), stdin);
            c->address[strcspn(c->address, "\n")] = '\0';
            encrypt(c->address);

            printf("New house number: ");
            c->houseNum = validNumber();

            printf("New apartment number: ");
            c->apartmentNum = validNumber();

            printf("Address updated!\n");
        }

    void pwdHashing(const char *str, char* output) {
            // TEMPORARY HASH for testing
            uint32_t hash = 5381;
            unsigned char c;
            while ((c = *str++)) {
                hash = ((hash << 5) + hash) + c; // hash * 33 + c
            }
            sprintf(output, "%08x", hash);
        }

    //////////////////////////////////////////////////////////////////////////////////////


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

        int storeIndex = get_int_input("INPUT: ", 1, skList->count) - 1;
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

        int storeIndex = get_int_input("INPUT: ", 1, skList->count) - 1;
        Storekeeper* sk = &skList->data[storeIndex];

        if (sk->stockCount == 0) {
            printf("This store has no perfume.\n");
            return;
        }

        printf("\nCurrent perfumes in %s:\n", sk->name);
        for (int i = 0; i < sk->stockCount; i++) {
            printf("%d. %s (%s) - Price: %.2f, Stock: %d\n",
                   i + 1, sk->stock[i].name, sk->stock[i].brand, sk->stock[i].price, sk->stock[i].stock);
        }

        int perfumeIndex = get_int_input("Enter perfume number to edit: ", 1, sk->stockCount) - 1;

        printf("Editing %s (%s)...\n", sk->stock[perfumeIndex].name, sk->stock[perfumeIndex].brand);
        printf("1. Price\n2. Stock\n");
        int editChoice = get_int_input("INPUT: ", 1, 2);

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

    void setDiscount(const StorekeeperList* skList) {
        if (skList->count == 0) {
            printf("No stores available.\n");
            return;
        }

        int storeIndex = selectStorekeeper(skList);
        if (storeIndex == -1) return;

        Storekeeper* sk = &skList->data[storeIndex];

        if (sk->stockCount == 0) {
            printf("This store has no perfumes.\n");
            return;
        }

        printf("\n--- Perfumes in %s ---\n", sk->name);
        for (int i = 0; i < sk->stockCount; i++) {
            printf("%d. %s (%s) - Price: %.2f, Discount: %.2f%%\n",
                   i + 1, sk->stock[i].name, sk->stock[i].brand, sk->stock[i].price, sk->stock[i].discount);
        }

        int perfumeIndex = get_int_input("Select perfume to set discount: ", 1, sk->stockCount) - 1;

        int discount = get_int_input("Enter discount percentage (1-100): ", 1, 100);

        sk->stock[perfumeIndex].discount = (float)discount;
        printf("Discount of %d%% applied to %s.\n", discount, sk->stock[perfumeIndex].name);
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
            BalanceCode* temp = realloc(BCL->data, BCL->capacity * sizeof(BalanceCode));

                if (temp == NULL) {
                    printf("ERROR: Out of memory! Cannot add code.\n");
                    return;
                }
                BCL->data = temp;
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

            int choice = get_int_input("INPUT: ", 1, skList->count) - 1;
            return choice;
        }
