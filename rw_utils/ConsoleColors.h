/*		ConsoleColors.h 	Source rewritten from: https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout
*		Dff structure documentation http://www.chronetal.co.uk/gta/index.php?page=dff
*		Created on 02/06/2017 (MM/DD/YYYY)
*/

#pragma once

#include <iostream>
#include <windows.h>

namespace rw_io_colors {
	inline std::ostream& blue(std::ostream &s) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& red(std::ostream &s) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& green(std::ostream &s) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& yellow(std::ostream &s) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& white(std::ostream &s) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		return s;
	}

	struct color {
		color(WORD attribute) : m_color(attribute) { };
		WORD m_color;
	};

	template <class _Elem, class _Traits>
	std::basic_ostream<_Elem, _Traits>& operator <<(std::basic_ostream<_Elem, _Traits> &i, color &c) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, c.m_color);
		return i;
	}
}

