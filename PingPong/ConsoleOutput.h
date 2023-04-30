#pragma once

#include <iostream>
#include <windows.h>
#include <vector>

class ConsoleOutput
{
public:
	void setRow(std::string str);
	void end(HANDLE console, COORD position);
	void print(std::vector<std::string>& frame);
private:
	HANDLE _console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _pos = { 0, 0 };

	const double _horizontalRatio = 2;

	std::string _row;
};