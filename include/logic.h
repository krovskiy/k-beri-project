//
// Created by Dima on 11-Dec-25.
//

#ifndef K_LOGIC_H
#define K_LOGIC_H

#include "models.h"

int validNumber(void); //RELEASE 1
float validFloat(void); //RELEASE 2
int get_int_input(const char* prompt, int min, int max); //RELEASE 1
void clearInputBuffer();  //RELEASE 1
float calculateDiscountedPrice(float price, float discount);
Gender getGenderInput(); //RELEASE 3
void clearScreen(); //RELEASE 3
void encrypt(char str[]); // IMPLEMENTED BY SASHA
void decrypt(char str[]); // IMPLEMENTED BY SASHA
void addPerfumeToCart(const StorekeeperList* list, Customer* c); //RELEASE 2
void viewShoppingCart(const StorekeeperList* list, Customer* c); //RELEASE 2
void checkout(Customer* c, const StorekeeperList* skList, float* userBalance); //RELEASE 2
void addBalance(Customer *c, BalanceCodesList* BCL); //RELEASE 2
void addStorekeeper(StorekeeperList *list, Storekeeper sk); // FIX BY DIMA
void customerRegister(CustomersList* custList); //IMPLEMENTED BY BRITTEN
void pwdHashing(const char* str, char* output); //IMPLEMENTED BY BRITTEN, NEEDS IMPROVEMENT *FREE SPOT*
void editCustomerAddress(Customer* c); //IMPLEMENTED BY BRITTEN
void addPerfume(const StorekeeperList* skList); //MADE BY HENRIK, IMPLEMENTED BY DIMA
void removePerfume(const StorekeeperList* skList); //MADE BY HENRIK, IMPLEMENTED BY DIMA
void editPerfume(const StorekeeperList* skList); //MADE BY HENRIK, IMPLEMENTED BY DIMA
void setDiscount(const StorekeeperList* skList); //RELEASE 2
void addBalanceCode(BalanceCodesList* BCL); //RELEASE 2
int selectStorekeeper(const StorekeeperList* skList); //RELEASE 1
void initStorekeeper(Storekeeper *sk); // FIX BY DIMA
void initStorekeeperList(StorekeeperList *list); // FIX BY DIMA
void initBalanceCodes(BalanceCodesList* BCL);
void initCustomerList(CustomersList* list);
void freeCustomerList(CustomersList* list);
void freeBalanceCode(BalanceCodesList* BCL);
void freeStorekeeper(StorekeeperList* list);

#endif //K_LOGIC_H