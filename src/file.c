    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <errno.h>
    #include "../include/file.h"
    #include "../include/models.h"
    #include "../include/logic.h"

    int saveAll(const StorekeeperList* skList, const CustomersList* custList, const BalanceCodesList* bcl) {
        FILE *fsk = fopen_output("storekeepers.txt", "w");
        FILE *fc = fopen_output("customers.txt", "w");
        FILE *fb = fopen_output("balancecodes.txt", "w");

        if (!fsk || !fc || !fb) {
            if (fsk) fclose(fsk);
            if (fc) fclose(fc);
            if (fb) fclose(fb);
            return 0;
        }

        saveStorekeepers(fsk, skList);
        saveCustomers(fc, custList);
        saveBalanceCodes(fb, bcl);

        fclose(fsk);
        fclose(fc);
        fclose(fb);
        return 1;
    }

    int loadAll(StorekeeperList* skList, CustomersList* custList, BalanceCodesList* bcl) {
        FILE *fsk = fopen_output("storekeepers.txt", "r");
        FILE *fc = fopen_output("customers.txt", "r");
        FILE *fb = fopen_output("balancecodes.txt", "r");

        if (!fsk || !fc || !fb) {
            if (fsk) fclose(fsk);
            if (fc) fclose(fc);
            if (fb) fclose(fb);
            return 0;
        }

        freeStorekeeper(skList);
        initStorekeeperList(skList);

        int ok1 = loadStorekeepers(fsk, skList);
        int ok2 = loadCustomers(fc, custList);
        int ok3 = loadBalanceCodes(fb, bcl);

        fclose(fsk);
        fclose(fc);
        fclose(fb);

        return (ok1 && ok2 && ok3) ? 1 : 0;
    }

    void saveStorekeepers(FILE* file, const StorekeeperList* list) {
        for (int i = 0; i < list->count; ++i) {
            const Storekeeper *sk = &list->data[i];
            fprintf(file, "STORE|%s|%s|%s|%d\n", sk->name, sk->pwd, sk->address, sk->stockCount);
            for (int j = 0; j < sk->stockCount; ++j) {
                const Perfume *p = &sk->stock[j];
                fprintf(file, "PERF|%s|%s|%f|%d|%d|%f\n",
                        p->name, p->brand, p->price, (int)p->gender, p->stock, p->discount);
            }
        }
    }

    void saveCustomers(FILE* file, const CustomersList* list) {
        for (int i = 0; i < list->count; ++i) {
            const Customer *c = &list->data[i];
            fprintf(file, "CUST|%s|%s|%s|%d|%d|%f|%d\n",
                    c->name, c->password, c->address, c->houseNum, c->apartmentNum, c->balance, c->cartItemCount);
            for (int j = 0; j < c->cartItemCount; ++j) {
                const CartItem *ci = &c->cart[j];
                fprintf(file, "CART|%d|%d|%d\n", ci->storekeeperIndex, ci->perfumeIndex, ci->quantity);
            }
        }
    }

    void saveBalanceCodes(FILE* file, const BalanceCodesList* bcl) {
        for (int i = 0; i < bcl->count; ++i) {
            const BalanceCode *bc = &bcl->data[i];
            fprintf(file, "%d|%f|%d\n", bc->code, bc->value, bc->used);
        }
    }

    int loadStorekeepers(FILE* file, StorekeeperList* list) {
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = '\0';
            if (strncmp(line, "STORE|", 6) == 0) {
                char *saveptr = NULL;
                char *token = strtok_r(line + 6, "|", &saveptr);
                if (!token) continue;
                Storekeeper sk;
                memset(&sk, 0, sizeof(sk));
                strncpy(sk.name, token, sizeof(sk.name) - 1);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                strncpy(sk.pwd, token, sizeof(sk.pwd) - 1);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                strncpy(sk.address, token, sizeof(sk.address) - 1);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                int stockCount = atoi(token);

                initStorekeeper(&sk);
                sk.stockCount = 0;

                for (int s = 0; s < stockCount; ++s) {
                    if (!fgets(line, sizeof(line), file)) break;
                    line[strcspn(line, "\r\n")] = '\0';
                    if (strncmp(line, "PERF|", 5) != 0) continue;
                    char *pcur = line + 5;
                    char *tok2;
                    tok2 = strtok_r(pcur, "|", &saveptr); if (!tok2) continue;
                    Perfume pf;
                    memset(&pf, 0, sizeof(pf));
                    strncpy(pf.name, tok2, sizeof(pf.name) - 1);

                    tok2 = strtok_r(NULL, "|", &saveptr); if (!tok2) continue;
                    strncpy(pf.brand, tok2, sizeof(pf.brand) - 1);

                    tok2 = strtok_r(NULL, "|", &saveptr); if (!tok2) continue;
                    pf.price = (float)atof(tok2);

                    tok2 = strtok_r(NULL, "|", &saveptr); if (!tok2) continue;
                    pf.gender = (Gender)atoi(tok2);

                    tok2 = strtok_r(NULL, "|", &saveptr); if (!tok2) continue;
                    pf.stock = atoi(tok2);

                    tok2 = strtok_r(NULL, "|", &saveptr); if (!tok2) continue;
                    pf.discount = (float)atof(tok2);

                    if (sk.stockCount >= sk.stockCapacity) {
                        int newCap = (sk.stockCapacity == 0) ? 4 : sk.stockCapacity * 2;
                        Perfume* tmp = realloc(sk.stock, newCap * sizeof(Perfume));
                        if (!tmp) return 0;
                        sk.stock = tmp;
                        sk.stockCapacity = newCap;
                    }
                    sk.stock[sk.stockCount++] = pf;
                }

                addStorekeeper(list, sk);
            }
        }
        return 1;
    }

    int loadCustomers(FILE* file, CustomersList* list) {
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = '\0';
            if (strncmp(line, "CUST|", 5) == 0) {
                char *saveptr = NULL;
                char *token = strtok_r(line + 5, "|", &saveptr);
                if (!token) continue;
                Customer c;
                memset(&c, 0, sizeof(c));
                strncpy(c.name, token, sizeof(c.name) - 1);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                strncpy(c.password, token, sizeof(c.password) - 1);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                strncpy(c.address, token, sizeof(c.address) - 1);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                c.houseNum = atoi(token);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                c.apartmentNum = atoi(token);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                c.balance = (float)atof(token);

                token = strtok_r(NULL, "|", &saveptr); if (!token) continue;
                int cartCount = atoi(token);

                c.cartCapacity = cartCount > 0 ? cartCount : 10;
                c.cartItemCount = 0;
                c.cart = malloc(c.cartCapacity * sizeof(CartItem));
                if (!c.cart) return 0;

                for (int i = 0; i < cartCount; ++i) {
                    if (!fgets(line, sizeof(line), file)) break;
                    line[strcspn(line, "\r\n")] = '\0';
                    if (strncmp(line, "CART|", 5) != 0) continue;
                    char *pc = line + 5;
                    char *sv = NULL;
                    char *t1 = strtok_r(pc, "|", &sv); if (!t1) continue;
                    char *t2 = strtok_r(NULL, "|", &sv); if (!t2) continue;
                    char *t3 = strtok_r(NULL, "|", &sv); if (!t3) continue;

                    CartItem ci;
                    ci.storekeeperIndex = atoi(t1);
                    ci.perfumeIndex = atoi(t2);
                    ci.quantity = atoi(t3);

                    if (c.cartItemCount >= c.cartCapacity) {
                        c.cartCapacity *= 2;
                        CartItem* tmp = realloc(c.cart, c.cartCapacity * sizeof(CartItem));
                        if (!tmp) return 0;
                        c.cart = tmp;
                    }
                    c.cart[c.cartItemCount++] = ci;
                }

                if (list->count >= list->capacity) {
                    list->capacity *= 2;
                    Customer* tmp = realloc(list->data, list->capacity * sizeof(Customer));
                    if (!tmp) return 0;
                    list->data = tmp;
                }
                list->data[list->count++] = c;
            }
        }
        return 1;
    }

    int loadBalanceCodes(FILE* file, BalanceCodesList* bcl) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = '\0';
            if (strlen(line) == 0) continue;
            char *saveptr = NULL;
            char *t1 = strtok_r(line, "|", &saveptr); if (!t1) continue;
            char *t2 = strtok_r(NULL, "|", &saveptr); if (!t2) continue;
            char *t3 = strtok_r(NULL, "|", &saveptr); if (!t3) continue;

            BalanceCode bc;
            bc.code = atoi(t1);
            bc.value = (float)atof(t2);
            bc.used = atoi(t3);

            if (bcl->count >= bcl->capacity) {
                bcl->capacity *= 2;
                BalanceCode* tmp = realloc(bcl->data, bcl->capacity * sizeof(BalanceCode));
                if (!tmp) return 0;
                bcl->data = tmp;
            }
            bcl->data[bcl->count++] = bc;
        }
        return 1;
    }

static void ensure_output_dir(void) {
        if (MKDIR("output") != 0) {
            if (errno != EEXIST) {
                printf("Warning: cannot create 'output' directory (errno=%d)\n", errno);
            }
        }
    }

static FILE* fopen_output(const char* filename, const char* mode) {
        char path[260];
        ensure_output_dir();
        snprintf(path, sizeof(path), "output\\%s", filename);
        return fopen(path, mode);
    }

