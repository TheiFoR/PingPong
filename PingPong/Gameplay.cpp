#include "Gameplay.h"

Gameplay::Gameplay()
{
    
}

void Gameplay::start()
{
    srand(time(0));
	_frameBuilder.create(_frameHeight, _frameWidth);

    _frame = _frameBuilder.getFrame();
    
    _gameSpeed = _startGameSpeed;

    float direct = randFloat(-1, 1);
    if(direct < 0)
        direct = clip(direct, -0.25, 0.75);
    else
        direct = clip(direct, -0.75, 0.25);

    setDirection(direct);

    _dirY = _ballY = (_frameHeight - 2) / 2 + 1;
    _dirX = _ballX = (rand() % (_frameWidth-1))+1;

    _botsRacketX = _frameWidth / 2 - _assetStorage.getRacket()[0].size() / 2;

    _racketX = _frameWidth / 2 - _assetStorage.getRacket()[0].size() / 2;

    _frameBuilder.setBall(_ballX, _ballY);
    _frameBuilder.setRacket(_racketX, _frameHeight - 2);
    _frameBuilder.setRacket(_botsRacketX, 1);

    _ball = _assetStorage.getBall();
    _botsRacket = _assetStorage.getRacket();
    _racket = _assetStorage.getRacket();

    _borderSymbol = _assetStorage.getAssetSymbols()[0];
    _fieldSymbol = _assetStorage.getAssetSymbols()[1];
    _racketSymbol = _assetStorage.getAssetSymbols()[2];
    _ballSymbol = _assetStorage.getAssetSymbols()[3];
    _frameBuilder.print();
	update();
}

void Gameplay::update()
{
	while (!_endGame) {
        _timeEnd = std::chrono::system_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(_timeEnd - _timeStart).count() > _gameSpeed){
            _direction = moveInDirestion();
            if (collisionChecking(_direction[0], _direction[1], 0)) {
                moveBall(_direction[0], _direction[1]);
                if (_ballY < 2 || _ballY > _frameHeight - 3) {
                    _endGame = true;
                }
            }
            if(_ballY < _frameHeight / 2)
                botMove();
            keyboardChecks();

            _frameBuilder.setRow("Score: " + std::to_string(_score));

            _timeStart = std::chrono::system_clock::now();
            _frameBuilder.print();
        }
	}
	_frameBuilder.endGame();
}

void Gameplay::keyboardChecks()
{
    if (GetAsyncKeyState(VK_RIGHT) && (std::chrono::duration_cast<std::chrono::milliseconds>(_timeEnd - _timeStart).count() > _gameSpeed)) {
        if (collisionChecking(1, 0, 1)) {
            moveRacket(1, 1);
        }
    }
    if (GetAsyncKeyState(VK_LEFT) && (std::chrono::duration_cast<std::chrono::milliseconds>(_timeEnd - _timeStart).count() > _gameSpeed))
    {
        if (collisionChecking(-1, 0, 1)) {
            moveRacket(-1, 1);
        }
    }
}

bool Gameplay::collisionChecking(int8_t dX, int8_t dY, uint8_t type)
{
    bool isChangeDirectionX = false;
    bool isChangeDirectionY = false;

    std::vector<std::string> figure;
    uint8_t x, y;

    switch (type)
    {
    case 0:
        figure = _ball;
        x = _ballX;
        y = _ballY;
        break;
    case 1:
        figure = _racket;
        x = _racketX;
        y = _frameHeight - 2;
        break;
    case 2:
        figure = _racket;
        x = _botsRacketX;
        y = 1;
        break;
    }
    
    if (dX != 0 && dY != 0) {
        if ((*_frame)[y + dY][x + dX] != _fieldSymbol) {
            if ((*_frame)[y][x + dX] != _fieldSymbol && (*_frame)[y + dY][x] == _fieldSymbol) {
                if (y > _frameHeight - 4) {
                    getScore(x, y + dY);
                }
                changeDirection(1, 0);
                return true;
            }
            if ((*_frame)[y + dY][x] != _fieldSymbol && (*_frame)[y][x + dX] == _fieldSymbol) {
                if (y > _frameHeight - 4) {
                    getScore(x, y + dY);
                }
                changeDirection(0, 1);
                return true;
            }
            if (y > _frameHeight - 4) {
                getScore(x, y + dY);
            }
            changeDirection(1, 1);
            return true;
        }
    }
    if (dX != 0) {
        if ((*_frame)[y][x + dX] != _fieldSymbol) {
            if (!type) {
                changeDirection(1, 0);
                return true;
            }
            else {
                if (dX > 0 && (*_frame)[y][x + _racket[0].size()] != _fieldSymbol)
                    return false;
                if (dX < 0 && (*_frame)[y][x - 1] != _fieldSymbol)
                    return false;
            }
        }
    }
    if (dY != 0) {
        if ((*_frame)[y + dY][x] != _fieldSymbol) {
            if (!type) {
                if (y > _frameHeight - 4) {
                    getScore(x, y + dY);
                }
                changeDirection(0, 1);
                return true;
            }
            else {
                return false;
            }
        }
    }

    return true;
}

void Gameplay::moveBall(float dX, float dY)
{
    _frameBuilder.removeBall(_ballX, _ballY);

    _ballX += dX;
    _ballY += dY;

    _dirX += _vectorDirection[0];
    _dirY += _vectorDirection[1];

    _frameBuilder.setBall(_ballX, _ballY);
}

void Gameplay::moveRacket(uint8_t dX, uint8_t player)
{
    if (player - 1) {
        _frameBuilder.removeRacket(_botsRacketX, 1);
        _botsRacketX += dX;
        _frameBuilder.setRacket(_botsRacketX, 1);
    }
    else {
        _frameBuilder.removeRacket(_racketX, _frameHeight - 2);
        _racketX += dX;
        _frameBuilder.setRacket(_racketX, _frameHeight - 2);
    }
}

void Gameplay::changeDirection(uint8_t dX, uint8_t dY)
{
    if (rand() % 100 < 100) {
        if(_vectorDirection[0] != 1)
            _vectorDirection[0] += clip(randFloat(-0.1, 0.1), -1, 1);

        if (_vectorDirection[1] != 1)
            _vectorDirection[1] += clip(randFloat(-0.1, 0.1), -1, 1);
    }
    _direction = { dX == 1 ? _direction[0] * -1 : _direction[0], dY == 1 ? _direction[1] * -1 : _direction[1] };
    _vectorDirection = { dX == 1 ? _vectorDirection[0] * -1 : _vectorDirection[0], dY == 1 ? _vectorDirection[1] * -1 : _vectorDirection[1] };
}

void Gameplay::botMove()
{
    int8_t dX = _ballX - (_botsRacketX + _racket[0].size()/2 + ((_racket[0].size() & 1) == 1 ? 1 : 0)-1);
    dX = clip(dX, -1, 1);
    if (rand() % 100 < 0)
        dX = 0;
    if(collisionChecking(dX, 0, 2))
        moveRacket(dX, 2);
}

int8_t Gameplay::clip(int8_t value, int8_t min, int8_t max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}
float Gameplay::clip(float value, float min, float max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

void Gameplay::scoreUpdate(float bonus)
{
    _score += calculateScore(_startGameSpeed, _gameSpeed, (float)_score*bonus);
    if(_gameSpeed > 20)
        _gameSpeed -= 2;
}

float Gameplay::randFloat(float min, float max)
{
    float result = ( ( float ) ( rand() % ( uint8_t ) ( max * 100.0 + 1.0 ) + ( min * 100.0 ) ) ) / 100.0;
    return result;
}

void Gameplay::setDirection(float direct)
{
    direct = clip(direct, -1, 1);
    float dirX = abs(4.0 * direct - 2.0) + abs(4.0 * direct + 6.0) - abs(-2 - 4.0 * direct) - 6;
    float dirY = abs(4.0 * direct) - 2;
    dirX = clip(dirX, -1, 1);
    dirY = clip(dirY, -1, 1);
    _vectorDirection = { dirX, dirY };
}

void Gameplay::getScore(uint8_t x, uint8_t y)
{
    if ((*_frame)[y][x - 1] == _fieldSymbol || (*_frame)[y][x + 1] == _fieldSymbol)
        scoreUpdate(1.1*(float)_startGameSpeed / (float)_gameSpeed);
    else
        scoreUpdate();
}

std::vector<int8_t>Gameplay::moveInDirestion()
{
    std::vector<int8_t> result = { 0, 0 };

    uint8_t startDirX = _dirX, startDirY = _dirY;

    if (startDirX != (uint8_t)(_dirX + _vectorDirection[0])) {
        result[0] ^= 1;
    }
    if (startDirY != (uint8_t)(_dirY + _vectorDirection[1])) {
        result[1] ^= 1;
    }
    if (_vectorDirection[0] < 0) {
        result[0] *= -1;
    }
    if (_vectorDirection[1] < 0) {
        result[1] *= -1;
    }
    return result;
}

float Gameplay::calculateScore(float _startGameSpeed, float _gameSpeed, int _score) {
    return 2*sqrt(sqrt(0.001 * _score * _score * _score) + 1);
}
