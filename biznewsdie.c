#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <termios.h>
#endif
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

int getchr() {
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    return getchar();
#elif defined (_WIN32)
    return _getch();
#endif
}

char *biznews() {
    char *results[] = {"tech", "food", "entertainment", "sports", "tourism", "biznews"};
    int the_num = rand() % 6;
    return results[the_num];
}

int main() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    srand(time(NULL));
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#define STDIN_FILENO 0
    struct termios told, tnew;
    tcgetattr(STDIN_FILENO, &told);
    tnew = told;
    tnew.c_lflag &= (~ECHO & ~ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &tnew);
#undef STDIN_FILENO
#endif
    do {
        printf("\x1b[2K\x1b[G%s", biznews());
    } while (getchr());
    return 0;
}
