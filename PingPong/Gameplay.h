#pragma once

#include "AssetStorage.h"
#include "FrameBuilder.h"
#include <chrono>

class Gameplay
{
public:
	Gameplay();

	void start();
	void update();

	void keyboardChecks();
	bool collisionChecking(int8_t dX, int8_t dY, uint8_t type);

	void moveBall(float dX, float dY);
	void moveRacket(uint8_t dX, uint8_t player);
	void changeDirection(uint8_t dX, uint8_t dY);

	void botMove();
private:
	AssetStorage _assetStorage;
	FrameBuilder _frameBuilder;

	/*-----Settings-----*/

	uint8_t _frameHeight = 25;
	uint8_t _frameWidth = 16;

	const uint16_t _startGameSpeed = 200;

	/*------------------*/

	std::chrono::time_point<struct std::chrono::system_clock, class std::chrono::duration<__int64, struct std::ratio<1, 10000000>>> _timeStart = std::chrono::system_clock::now();
	std::chrono::time_point<struct std::chrono::system_clock, class std::chrono::duration<__int64, struct std::ratio<1, 10000000>>> _timeEnd = std::chrono::system_clock::now();

	bool _endGame = false;

	char _borderSymbol;
	char _fieldSymbol;
	char _racketSymbol;
	char _ballSymbol;

	std::vector<float> _vectorDirection;
	std::vector<int8_t> _direction;
	std::vector<std::string> _ball;
	std::vector<std::string> _botsRacket;
	std::vector<std::string> _racket;
	std::vector<std::string>* _frame;

	uint8_t _racketX = 0;
	uint8_t _botsRacketX = 0;
	uint8_t _ballX = 0, _ballY = 0;
	float _dirX = 0, _dirY = 0;

	uint16_t _score = 0;
	uint16_t _gameSpeed;

	int8_t clip(int8_t value, int8_t min, int8_t max);
	float clip(float value, float min, float max);
	void getScore(uint8_t x, uint8_t y);
	void scoreUpdate(float bonus = 1);
	float randFloat(float min = 0.0f, float max = 1.0f);
	void setDirection(float direct);
	std::vector<int8_t> moveInDirestion();
	float calculateScore(float _startGameSpeed, float _gameSpeed, int _score);
};

