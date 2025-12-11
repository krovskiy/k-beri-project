    #include "../include/models.h"
    #include "../include/logic.h"
    #include "../include/file.h"
    #include "../include/ui.h"

    /*Initialization*/

    void defaultCodes(BalanceCodesList* BCL) {
        *(BCL->data + 0) = (BalanceCode){ 135791, 10, 0 };
        *(BCL->data + 1) = (BalanceCode){ 246802, 50, 0 };
        *(BCL->data + 2) = (BalanceCode){ 753197, 100, 0 };
        *(BCL->data + 3) = (BalanceCode){ 579135, 200, 0 };
        *(BCL->data + 4) = (BalanceCode){ 864202, 75, 0 };
        *(BCL->data + 5) = (BalanceCode){ 468024, 67, 0 };
        *(BCL->data + 6) = (BalanceCode){ 67, 2000000, 0}; // MIGHT BE THE MOST IMPORTANT PART OF THE CODE
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

    /* Default values */
    void startProgram() {
        BalanceCodesList BCL;
        StorekeeperList skList;
        CustomersList largeList;

        initBalanceCodes(&BCL);
        initStorekeeperList(&skList);
        initCustomerList(&largeList);

        if (!loadAll(&skList, &largeList, &BCL)) {
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
            defaultCodes(&BCL);

            addStorekeeper(&skList, dflt1);
            addStorekeeper(&skList, dflt2);
            addStorekeeper(&skList, dflt3);
        }


        while (1) {
            const int roleChoice = welcomeDialog();
            if (roleChoice == 0) {
                break;
            }
            roleSelect(roleChoice, &skList, &BCL, &largeList);
            saveAll(&skList, &largeList, &BCL);
        }

        saveAll(&skList, &largeList, &BCL);
        freeCustomerList(&largeList);
        freeStorekeeper(&skList);
        freeBalanceCode(&BCL);

    }
