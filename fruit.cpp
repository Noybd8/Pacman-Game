#include "fruit.h"
Fruit::Fruit(int locationX, int locationY, char ch, char direction, char*** map, int numOfRows, int numOfCuls, int objectNum)
	:GameObject(locationX, locationY, ch, direction, map, numOfRows, numOfCuls, objectNum) {
	createRandomLocation();

}

void Fruit::checkValidMove(int& x, int& y, int chosen_x, int chosen_y, char direction, int currentLevel) {
	char nextChar = this->getCharInMap(chosen_x, chosen_y);
	if (nextChar == '#' || nextChar == 'X' || chosen_x < 0 || chosen_y < 0 || chosen_x > this->getNumOfRows() - 1 || chosen_y>this->getNumOfCol() - 1 || nextChar == '@' || nextChar == '$' || nextChar == '~') {
		int newDirection = generateNewDirection();
		move(newDirection, x, y);

	}
	else
	{
		x = chosen_x;
		y = chosen_y;
		this->set_direction(direction);
	}

}

void Fruit::createRandomLocation() {
	int x = rand() % this->getNumOfRows();
	int y = rand() % this->getNumOfCol();

	char charInMap = getCharInMap(x, y);
	if (charInMap != '.') {
		createRandomLocation();
		return;
	}
	this->set_location_x(x);
	this->set_location_y(y);
	this->setStarting_position_x(x);
	this->setStarting_position_y(y);

}
char Fruit::createRandomValue() {
	while (fruitValue < '5' || fruitValue > '9') {
		this->fruitValue = (rand() % (5)) + 5 + '0';
	}
	return this->fruitValue;
}
