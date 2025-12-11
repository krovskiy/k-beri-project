//
// Created by Dima on 11-Dec-25.
//

#ifndef K_UI_H
#define K_UI_H

#include "../include/models.h"

// Display Functions
int welcomeDialog(); // RELEASE 1
void viewPerfumes(const StorekeeperList* list); // RELEASE 2
void viewCodes(const BalanceCodesList* BCL); // RELEASE 2
void displayStorekeepers(const StorekeeperList* list); // DONE BY DIMA
void displayCustomer(const Customer* c); // DONE BY DIMA
void displayCustomers(const CustomersList* custList); // DONE BY DIMA, FOR ADMIN

void customerMenu(const StorekeeperList* list, Customer* c, BalanceCodesList* BCL); //RELEASE 1
int customerLogin(CustomersList* custlist); //IMPLEMENTED BY BRITTEN
void customerLoginMenu(const StorekeeperList* list, BalanceCodesList* BCL, CustomersList* custlist); //IMPLEMENTED BY BRITTEN
void storekeeperMenu(const Storekeeper *sk, const StorekeeperList *skList, BalanceCodesList* BCL, const CustomersList* custlist); //RELEASE 1
void storeKeeperLogin(const StorekeeperList* skList, BalanceCodesList* BCL, const CustomersList* custlist); //FIX BY DIMA
void roleSelect(int roleChoice, StorekeeperList* list, BalanceCodesList* BCL, CustomersList* custList); //RELEASE 1


#endif //K_UI_H