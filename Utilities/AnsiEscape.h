#ifndef ANSIESCAPE_H
#define ANSIESCAPE_H

//Quelle: https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__CYGWIN__)
#define  _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__CYGWIN__)
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle, stdinHandle;
static DWORD outModeInit, inModeInit;

void setupConsole(void);


void restoreConsole(void);

void getCursorPosition(int* row, int* col);

enum Colors {
    RESET_COLOR,
    BLACK_TXT = 30,
    RED_TXT,
    GREEN_TXT,
    YELLOW_TXT,
    BLUE_TXT,
    MAGENTA_TXT,
    CYAN_TXT,
    WHITE_TXT,

    BLACK_BKG = 40,
    RED_BKG,
    GREEN_BKG,
    YELLOW_BKG,
    BLUE_BKG,
    MAGENTA_BKG,
    CYAN_BKG,
    WHITE_BKG    
};

enum ClearCodes 
{
  CLEAR_FROM_CURSOR_TO_END,
  CLEAR_FROM_CURSOR_TO_BEGIN,
  CLEAR_ALL
};

void setBackgroundColor(int code);


void setTextColor(int code);

void setTextColorBright(int code);

void clearScreen(void);
 
void clearScreenToBottom(void);

void clearScreenToTop(void);

void hideCursor();

void showCursor();

void moveRight(int positions);

void moveUp(int positions);

void clearLine(void);

void moveDown(int positions);

void moveLeft(int positions);

void moveTo(int row, int col);
#endif

#endif  //ANSIESCAPE_H
