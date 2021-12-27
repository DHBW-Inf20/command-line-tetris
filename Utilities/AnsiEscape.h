//https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/
#include <stdio.h>
#include <iostream>

enum ClearCodes {
  CLEAR_FROM_CURSOR_TO_END,
  CLEAR_FROM_CURSOR_TO_BEGIN,
  CLEAR_ALL
};

 void clearScreen(void) {
	printf("\x1b[%dJ", CLEAR_ALL);
}

void hideCursor() //https://rosettacode.org/wiki/Terminal_control/Hiding_the_cursor
{
    printf("\u001B[?25l");
}

void moveRight(int positions)
{
    printf("\x1b[%dC", positions); 
}
void moveUp(int positions)
{
    printf("\x1b[%dA", positions);
}

void clearLine(void) {
 	printf("\x1b[%dK", CLEAR_ALL);
}

void moveDown(int positions)
{
    printf("\x1b[%dB", positions);
}

void moveLeft(int positions)
{
    printf("\x1b[%dD", positions);
}

void moveTo(int row, int col)
{
    printf("\x1b[%d;%df", row, col);
}
