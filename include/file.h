//
// Created by Dima on 11-Dec-25.
//

#ifndef K_FILE_H
#define K_FILE_H

#include <stdio.h>
#include "models.h"

// make this work on windows and linux - dima
    #ifdef _WIN32
    #include <direct.h>  // Windows
    #define MKDIR(path) _mkdir(path)
    #define PATH_SEPARATOR '\\'
    #else
    #include <sys/stat.h>  // Linux/Mac
    #include <sys/types.h>
    #define MKDIR(path) mkdir(path, 0755)
    #define PATH_SEPARATOR '/'
    #endif


int saveAll(const StorekeeperList* skList, const CustomersList* custList, const BalanceCodesList* bcl); // IMPLEMENTED BY BRITTEN & HENRIK
int loadAll(StorekeeperList* skList, CustomersList* custList, BalanceCodesList* bcl); // IMPLEMENTED BY BRITTEN & HENRIK
void saveStorekeepers(FILE* file, const StorekeeperList* list); // IMPLEMENTED BY BRITTEN & HENRIK
void saveCustomers(FILE* file, const CustomersList* list); // IMPLEMENTED BY BRITTEN & HENRIK
void saveBalanceCodes(FILE* file, const BalanceCodesList* bcl); // IMPLEMENTED BY BRITTEN & HENRIK
int loadStorekeepers(FILE* file, StorekeeperList* list); // IMPLEMENTED BY BRITTEN & HENRIK
int loadCustomers(FILE* file, CustomersList* list); // IMPLEMENTED BY BRITTEN & HENRIK
int loadBalanceCodes(FILE* file, BalanceCodesList* bcl); // IMPLEMENTED BY BRITTEN & HENRIK


static void ensure_output_dir(void);
static FILE* fopen_output(const char* filename, const char* mode);

#endif //K_FILE_H