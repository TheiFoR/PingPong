#pragma once

#include "AssetStorage.h"
#include "ConsoleOutput.h"
#include <windows.h>

class FrameBuilder
{
public:
	FrameBuilder();
	~FrameBuilder();

	void create(uint8_t height, uint8_t width);

	std::vector<std::string>* getFrame();
	void setFrame(std::vector<std::string>& frame);

	void setBall(uint8_t x, uint8_t y);
	void removeBall(uint8_t x, uint8_t y);

	void setRacket(uint8_t x, uint8_t y);
	void removeRacket(uint8_t x, uint8_t y);

	void setRow(std::string text);
	void endGame();
	
	void print();
private:
	AssetStorage _assetStorage;
	ConsoleOutput _consoleOutput;

	std::vector<std::string>* _frame;
	std::vector<std::string> _ball;
	std::vector<std::string> _racket;

	char _borderSymbol;
	char _fieldSymbol;
	char _racketSymbol;
	char _ballSymbol;
};

