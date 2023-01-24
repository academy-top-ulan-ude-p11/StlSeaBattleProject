#pragma once
#include <iostream>
#include <Windows.h>

const char VERTICAL = 179;
const char HORIZONTAL = 196;
const char CENTERMIDDLE = 197;
const char WATER = 176;
const char DESK = 219;

using namespace std;

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
};

