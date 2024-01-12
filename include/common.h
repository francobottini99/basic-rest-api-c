#ifndef __COMMON_H__
#define __COMMON_H__

#include <string.h>

// Define colors codes for terminal
#ifndef TERMINAL_TEXT_COLORS
#define TERMINAL_TEXT_COLORS
    #define KDEF  "\x1B[0m"     // Default
    #define KRED  "\x1B[31m"    // Red
    #define KGRN  "\x1B[32m"    // Green
    #define KYEL  "\x1B[33m"    // Yellow
    #define KBLU  "\x1B[34m"    // Blue
    #define KMAG  "\x1B[35m"    // Magenta
    #define KCYN  "\x1B[36m"    // Cyan
    #define KWHT  "\x1B[37m"    // White
#endif

// Define macro to unused variables
#define UNUSED(x) (void)(x)

// Define server port
#define SERVER_PORT 8537

#endif // __COMMON_H__
