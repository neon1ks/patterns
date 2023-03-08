#include <conio.h>
#include <windows.h>

#include <chrono>
#include <ctime>
#include <iostream>

#include "MyTools.h"

using namespace std;

namespace MyTools {

Logger logger("log.txt");

//=============================================================================================

void ClrScr()
{
    system("cls");
}

void __fastcall GotoXY(double x, double y)
{
    const COORD cc = { short(x), short(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
}

uint16_t GetMaxX()
{
    HANDLE hWndConsole = GetStdHandle(-12);
    if (hWndConsole) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            return consoleInfo.srWindow.Right;
            int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
    }

    return 0;
}

uint16_t GetMaxY()
{
    HANDLE hWndConsole = GetStdHandle(-12);
    if (hWndConsole) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            return consoleInfo.srWindow.Bottom;
        }
    }

    return 0;
}

void SetColor(ConsoleColor color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    // color =  (WORD)((BackgroundColor << 4) | TextColor))
}

//=============================================================================================

Logger::Logger(const string &FN)
{
    logOut.open(FN, ios_base::out);
}

Logger::~Logger()
{
    if (logOut.is_open()) {
        logOut.close();
    }
}

string Logger::GetCurDateTime()
{
    auto cur = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur);
    char buf[64] = { 0 };
    ctime_s(buf, 64, &time);
    buf[strlen(buf) - 1] = '\0';
    return string(buf);
}

void Logger::WriteToLog(const string &str)
{
    if (logOut.is_open()) {
        logOut << GetCurDateTime() << " - " << str << endl;
    }
}

void Logger::WriteToLog(const string &str, int n)
{
    if (logOut.is_open()) {
        logOut << GetCurDateTime() << " - " << str << n << endl;
    }
}

void Logger::WriteToLog(const string &str, double d)
{
    if (logOut.is_open()) {
        logOut << GetCurDateTime() << " - " << str << d << endl;
    }
}

//=============================================================================================

} // namespace MyTools
