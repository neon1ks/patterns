#include "ScreenSingleton.h"

#include <conio.h>
#include <windows.h>

#include <chrono>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

void ScreenSingleton::ClrScr()
{
    system("cls");
}

void __fastcall ScreenSingleton::GotoXY(double x, double y)
{
    const COORD cc = { static_cast<short>(x), static_cast<short>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
}

uint16_t ScreenSingleton::GetMaxX()
{
    HANDLE hWndConsole = GetStdHandle(-12);
    if (hWndConsole) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            return consoleInfo.srWindow.Right;
            int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
    }

    return uint16_t{ 0 };
}

uint16_t ScreenSingleton::GetMaxY()
{
    HANDLE hWndConsole = GetStdHandle(-12);
    if (hWndConsole) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            return consoleInfo.srWindow.Bottom;
        }
    }
    return uint16_t{ 0 };
}

void ScreenSingleton::SetColor(ConsoleColor color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,
                            color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
}
