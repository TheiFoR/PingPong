#include "FrameBuilder.h"

FrameBuilder::FrameBuilder()
{
	_frame = nullptr;

	_ball = _assetStorage.getBall();
	_racket = _assetStorage.getRacket();

	_borderSymbol = _assetStorage.getAssetSymbols()[0];
	_fieldSymbol = _assetStorage.getAssetSymbols()[1];
	_racketSymbol = _assetStorage.getAssetSymbols()[2];
	_ballSymbol = _assetStorage.getAssetSymbols()[3];
}

FrameBuilder::~FrameBuilder()
{
	if (_frame) {
		_frame->clear();
		delete _frame;
	}
}

void FrameBuilder::create(uint8_t height, uint8_t width)
{
	std::vector<std::string> tempFrame;

	tempFrame.emplace_back(std::string(width, _borderSymbol));
	for (int i = 0; i < height-2; i++) {
		tempFrame.emplace_back(std::string(1, _borderSymbol) + std::string(width-2, _fieldSymbol) + std::string(1, _borderSymbol));
	}
	tempFrame.emplace_back(std::string(width, _borderSymbol));

	if (_frame) {
		*_frame = tempFrame;
	}
	else {
		_frame = new std::vector<std::string>(tempFrame);
	}
}

std::vector<std::string>* FrameBuilder::getFrame()
{
	return _frame;
}

void FrameBuilder::setFrame(std::vector<std::string>& frame)
{
	if (_frame) {
		*_frame = frame;
	}
	else {
		_frame = new std::vector<std::string>(frame);
	}
}

void FrameBuilder::setBall(uint8_t x, uint8_t y)
{
	if (x + _ball[0].size() > (*_frame)[0].size())
		return;
	if (y + _ball.size() > (*_frame).size())
		return;

	for (int i = 0; i < _ball.size(); ++i) {
		for (int j = 0; j < _ball[0].size(); ++j) {
			if ((*_frame)[y + i][x + j] != _fieldSymbol)
				return;
		}
	}

	for (int i = 0; i < _ball.size(); ++i) {
		for (int j = 0; j < _ball[0].size(); ++j) {
			(*_frame)[y + i][x + j] = _ball[i][j];
		}
	}
}

void FrameBuilder::removeBall(uint8_t x, uint8_t y)
{
	if (x + _ball[0].size() > (*_frame)[0].size())
		return;
	if (y + _ball.size() > (*_frame).size())
		return;

	for (int i = 0; i < _ball.size(); ++i) {
		for (int j = 0; j < _ball[0].size(); ++j) {
			if ((*_frame)[y + i][x + j] != _ballSymbol)
				return;
		}
	}

	for (int i = 0; i < _ball.size(); ++i) {
		for (int j = 0; j < _ball[0].size(); ++j) {
			(*_frame)[y + i][x + j] = _fieldSymbol;
		}
	}
}

void FrameBuilder::setRacket(uint8_t x, uint8_t y)
{
	if (x + _racket[0].size() > (*_frame)[0].size())
		return;
	if (y + _racket.size() > (*_frame).size())
		return;

	for (int i = 0; i < _racket.size(); ++i) {
		for (int j = 0; j < _racket[0].size(); ++j) {
			if ((*_frame)[y + i][x + j] != _fieldSymbol)
				return;
		}
	}

	for (int i = 0; i < _racket.size(); ++i) {
		for (int j = 0; j < _racket[0].size(); ++j) {
			(*_frame)[y + i][x + j] = _racket[i][j];
		}
	}
}

void FrameBuilder::removeRacket(uint8_t x, uint8_t y)
{
	if (x + _racket[0].size() > (*_frame)[0].size())
		return;
	if (y + _racket.size() > (*_frame).size())
		return;

	for (int i = 0; i < _racket.size(); ++i) {
		for (int j = 0; j < _racket[0].size(); ++j) {
			if ((*_frame)[y + i][x + j] != _racketSymbol)
				return;
		}
	}

	for (int i = 0; i < _racket.size(); ++i) {
		for (int j = 0; j < _racket[0].size(); ++j) {
			(*_frame)[y + i][x + j] = _fieldSymbol;
		}
	}
}

void FrameBuilder::setRow(std::string text)
{
	_consoleOutput.setRow(text);
}

void FrameBuilder::endGame()
{
	HANDLE _console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _pos = { 0, _frame->size() + 2 };
	_consoleOutput.end(_console, _pos);
}

void FrameBuilder::print()
{
	_consoleOutput.print(*_frame);
}
