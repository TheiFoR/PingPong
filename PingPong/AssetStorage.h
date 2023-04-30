#pragma once

#include <vector>
#include <string>

class AssetStorage
{
public:
	AssetStorage();
	std::vector<char> getAssetSymbols();
	std::vector<std::string> getBall();
	std::vector<std::string> getRacket();
private:
	const uint8_t _racketHeight = 1;
	const uint8_t _racketWidth = 3;
	
	const uint8_t _ballHeight = 1;
	const uint8_t _ballWidth = 1;

	const char _borderSymbol = '#';
	const char _fieldSymbol = ' ';
	const char _racketSymbol = 219;
	const char _ballSymbol = 219;

	std::vector<std::string> _ball;
	std::vector<std::string> _racket;
};