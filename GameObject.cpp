#include "GameObject.h"


GameObject::GameObject(int locationX, int locationY, char ch, char direction, char*** board, int numOfRows, int numOfCuls, int objectNum)
{
	this->starting_postion_x = locationX;
	this->starting_postion_y = locationY;
	this->m_x = locationX;
	this->m_y = locationY;
	this->m_symbol = ch;
	this->m_direction = direction;
	this->mapSize[0] = numOfRows;
	this->mapSize[1] = numOfCuls;
	this->objectNum = objectNum;
	this->map = new char** [1];
	*this->map = new char* [numOfRows];
	for (int i = 0; i < numOfRows; i++) {
		(*this->map)[i] = new char[numOfCuls];
	}
	this->map = board;
	this->LastLoc[0] = locationX;
	this->LastLoc[1] = locationY;


}

int GameObject::generateNewDirection() {
	int newDirection = this->get_direction();
	while (newDirection == this->get_direction()) {
		newDirection = rand() % 4;
	}
	return newDirection;
}

void GameObject::move(char keyStroke, int& nextLoc_x, int& nextLoc_Y) {
	int loc_X, loc_Y;
	loc_X = this->get_locationX();
	loc_Y = this->get_locationY();
	this->set_LastLoc(loc_X, loc_Y);
	if (keyStroke == 'w' || keyStroke == 'W' || keyStroke == 0) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X - 1, loc_Y, 0);
		return;
	}
	else if (keyStroke == 'a' || keyStroke == 'A' || keyStroke == 1) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X, loc_Y - 1, 1);
		return;
	}
	else if (keyStroke == 'd' || keyStroke == 'D' || keyStroke == 2) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X, loc_Y + 1, 2);
		return;
	}
	else if (keyStroke == 'x' || keyStroke == 'X' || keyStroke == 3) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X + 1, loc_Y, 3);
		return;
	}
	else if (keyStroke == 's' || keyStroke == 'S' || keyStroke == 4) {
		nextLoc_x = loc_X;
		nextLoc_Y = loc_Y;
		this->set_direction(4);
	}
	else {
		this->set_direction(this->get_direction());
		move(this->get_direction(), nextLoc_x, nextLoc_Y);

	}



}












