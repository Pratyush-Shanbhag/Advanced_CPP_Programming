#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

enum COLOR
{
	// Text foreground colors
	// Standard text colors
	GRAY_TEXT = 8, 
	BLUE_TEXT, 
	GREEN_TEXT,
	CYAN_TEXT, 
	RED_TEXT, 
	MAGENTA_TEXT,
	YELLOW_TEXT, 
	WHITE_TEXT,
	// Faded text colors
	BLACK_TEXT = 0, 
	BLUE_FADE_TEXT, 
	GREEN_FADE_TEXT,
	CYAN_FADE_TEXT,
	RED_FADE_TEXT, 
	MAGENTA_FADE_TEXT,
	YELLOW_FADE_TEXT, 
	WHITE_FADE_TEXT,
	// Standard text background color
	GRAY_BACKGROUND = GRAY_TEXT << 4, 
	BLUE_BACKGROUND = BLUE_TEXT << 4,
	GREEN_BACKGROUND = GREEN_TEXT << 4, 
	CYAN_BACKGROUND = CYAN_TEXT << 4,
	RED_BACKGROUND = RED_TEXT << 4, 
	MAGENTA_BACKGROUND = MAGENTA_TEXT << 4,
	YELLOW_BACKGROUND = YELLOW_TEXT << 4, 
	WHITE_BACKGROUND = WHITE_TEXT << 4,
	// Faded text background color
	BLACK_BACKGROUND = BLACK_TEXT << 4, 
	BLUE_FADE_BACKGROUND = BLUE_FADE_TEXT << 4,
	GREEN_FADE_BACKGROUND = GREEN_FADE_TEXT << 4, 
	CYAN_FADE_BACKGROUND = CYAN_FADE_TEXT << 4,
	RED_FADE_BACKGROUND = RED_FADE_TEXT << 4, 
	MAGENTA_FADE_BACKGROUND = MAGENTA_FADE_TEXT << 4,
	YELLOW_FADE_BACKGROUND = YELLOW_FADE_TEXT << 4, 
	WHITE_FADE_BACKGROUND = WHITE_FADE_TEXT << 4
};

inline ostream& purple(ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, MAGENTA_TEXT);
	return s;
}

inline ostream& cyan(ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, CYAN_TEXT);
	return s;
}

inline ostream& backblue(ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, CYAN_TEXT | BLUE_BACKGROUND);
	return s;
}

inline ostream& blue(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, BLUE_TEXT);
    return s;
}

inline ostream& red(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, RED_TEXT);
    return s;
}

inline ostream& green(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, GREEN_TEXT);
    return s;
}

inline ostream& yellow(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, YELLOW_TEXT);
    return s;
}

inline ostream& white(ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, WHITE_TEXT);
	return s;
}

inline ostream& backwhite(ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, WHITE_FADE_BACKGROUND);
	return s;
}

// experimental
inline ostream& orange(ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, YELLOW_FADE_TEXT);
	return s;
}

struct color 
{
    color(WORD attribute) : m_color(attribute) { };
    WORD m_color;
	ostream& operator()(ostream& os)
	{
		return os;
	}
};


template <typename _Elem, class _Traits>
basic_ostream<_Elem,_Traits>& operator<<(basic_ostream<_Elem,_Traits>& s, color& c)
{
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute( hStdout, c.m_color );
    return s;
}




