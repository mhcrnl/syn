#include"screen.h"

#ifdef __linux__
#include"_linux.h"
#elif __unix__
#include"_linux.h"
#elif _WIN32
#include"_win32.h"
#elif __APPLE__
    #ifdef TARGET_OS_MAC
    #include"_osx.h"
    #else
    #error "This apple compiler is not supported"
    #endif
#else
#error "Compiler not supported"
#endif

