#include "AssetStorage.h"

AssetStorage::AssetStorage()
{
	for (int i = 0; i < _ballHeight; i++) {
		_ball.emplace_back(std::string(_ballWidth, _ballSymbol));
	}
	for (int i = 0; i < _racketHeight; i++) {
		_racket.emplace_back(std::string(_racketWidth, _racketSymbol));
	}
}

std::vector<char> AssetStorage::getAssetSymbols()
{
	std::vector<char> result = { _borderSymbol, _fieldSymbol, _racketSymbol, _ballSymbol };
	return result;
}

std::vector<std::string> AssetStorage::getBall()
{
	return _ball;
}

std::vector<std::string> AssetStorage::getRacket()
{
	return _racket;
}
