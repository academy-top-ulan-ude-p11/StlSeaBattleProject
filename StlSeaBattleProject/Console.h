#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

const char VERTICAL = 179;
const char HORIZONTAL = 196;
const char CENTERMIDDLE = 197;
const char WATER = 176;
const char DESK = 219;

enum KeyCode
{
    ArrowUp = 72,
    ArrowDown = 80,
    ArrowLeft = 75,
    ArrowRight = 77,
    Enter = 13,
    Space = 32,
    Esc = 27
};

enum Colors
{
    Gray,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White
};

class Console
{
    HANDLE descriptor;
    COORD coordinate;
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
public:
    Console()
    {
        descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    HANDLE& GetDescriptor() { return descriptor; }

    void Clear()
    {
        system("cls");
    }

    void CursorGoTo(int row, int col)
    {
        coordinate.Y = row;
        coordinate.X = col;
        SetConsoleCursorPosition(descriptor, coordinate);
    }

    void WriteGoTo(int row, int col, string str)
    {
        CursorGoTo(row, col);
        cout << str;
    }

    void WriteGoTo(int row, int col, char symbol)
    {
        CursorGoTo(row, col);
        cout << symbol;
    }

    void SetForeground(Colors color, bool brightness = false)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(descriptor, &info);
        int currBack = info.wAttributes & (15 << 4);

        int colorText = color + (brightness ? 8 : 0);
        SetConsoleTextAttribute(descriptor, colorText | currBack);
    }

    void SetBackground(Colors color, bool brightness = false)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(descriptor, &info);
        int currText = info.wAttributes & 15;

        int colorBack = (color + (brightness ? 8 : 0)) << 4;
        SetConsoleTextAttribute(descriptor, colorBack | currText);
    }

    void SetColors(Colors back, bool backBrightness, Colors text, bool textBrightness)
    {
        SetBackground(back, backBrightness);
        SetForeground(text, textBrightness);
    }
};

