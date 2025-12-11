//
// Created by Dima on 11-Dec-25.
//

#ifndef K_MODELS_H
#define K_MODELS_H

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

#endif //K_MODELS_H