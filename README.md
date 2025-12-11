# TEAM 5 - C PROGRAMMING PROJECT

university group project developed for a c programming course, spanning across 4 releases. (September - December)

## TEAM MEMBERS
Dumitru Ciobanu, Aleksander Ader, Andreas Müller, Britten Remmelkoor, Henrik Timmermann

## PROJECT OVERVIEW

a command-line interface application written in c designed to simulate a digital perfume marketplace. this project demonstrates the implementation of dynamic data structures, memory management, and user authentication logic without external dependencies.

## TECHNICAL IMPLEMENTATION

c (standard libraries only), use of malloc and realloc for dynamic arrays, custom text-based file handling to save and load system state

## PROJECT STRUCTURE

```
k/
├── main.c                
├── CMakeLists.txt         
├── include/              
│   ├── models.h          # data structures
│   ├── logic.h           # core business logic functions
│   ├── ui.h              # user interface and menu functions
│   ├── file.h            # file i/o and persistence
│   └── init.h            # initialization and default data
├── src/                  
│   ├── logic.c           # business logic implementations
│   ├── ui.c              # ui menus and display functions
│   ├── file.c            # file save/load implementations
│   └── init.c            # program initialization
└── cmake-build-debug/     
    └── output/           
```

## COMPILATION

compile with gcc:

`gcc -std=c11 -o k.exe main.c src/logic.c src/file.c src/ui.c src/init.c -I.`

or use cmake:

```
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .
```

## RUNNING THE APPLICATION

### windows
```powershell
.\k.exe
```

### linux/macos
```bash
./k
```

## RELEASES OVERVIEW

- **release 1** - basic project structure, user roles, menu system, input validation
- **release 2** - shopping cart, perfume browsing, checkout, balance codes, discounts
- **release 3** - enhanced file i/o, multiple stores, inventory management
- **release 4** - final refinement, security improvements, cross-platform support

## DEPENDENCIES

none - project uses only standard c libraries (stdio.h, string.h, stdlib.h, stdint.h, errno.h) with platform-specific support for windows and linux/macos

## NOTES

- all data is stored in text format in output/ directory for easy inspection
- passwords are hashed before storage
- system uses dynamic arrays with malloc/realloc for memory management


