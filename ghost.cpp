#include "ghost.h"


Ghost::Ghost(int locationX, int locationY, char ch, char direction, char*** map, int numOfRows, int numOfCuls, int level, int ghostNum)
	:GameObject(locationX, locationY, ch, direction, map, numOfRows, numOfCuls, ghostNum) {
	this->gameLevel = level;
	this->ghostNum = ghostNum;
}

void Ghost::checkValidMove(int& x, int& y, int chosen_x, int chosen_y, char direction, int currentLevel) {
	char nextChar = this->getCharInMap(chosen_x, chosen_y);
	if (nextChar == '#' || nextChar == 'X' || chosen_x < 0 || chosen_y < 0 || chosen_x > this->getNumOfRows() - 1 || chosen_y>this->getNumOfCol() - 1 || nextChar == '$' || nextChar == '~' || direction == -1) {
		if (currentLevel == 1 || currentLevel == 0) {
			moveGhost(4, x, y, 1);
			this->set_direction(4);
			return;
		}
		if (currentLevel == 3) {
			if (direction == this->smartDirection[0] || smartDirection[0] == -1) {
				this->smartDirection[0] = 4;                              //in evrey line like that in this function we take care that the function wont go on a loop.
				moveGhost(this->smartDirection[1], x, y, currentLevel);
				return;
			}
			else if ((direction == this->smartDirection[1] || this->smartDirection[1] == -1)) {
				this->gotStuck = true;
				this->smartDirection[1] = 5;
				this->newSmartDirection[0] = ChooseDirectionWhileStuck(this->smartDirection[0], this->smartDirection[1]);
				moveGhost(this->newSmartDirection[0], x, y, currentLevel);
				return;
			}
			else if (gotStuck && direction == newSmartDirection[0]) {
				this->newSmartDirection[0] = 6;
				this->newSmartDirection[1] = chooseLastDirection();
				moveGhost(this->newSmartDirection[1], x, y, currentLevel);
				return;

			}
			else if (direction == newSmartDirection[1] && gotStuck) {
				if (stuckCounter < 5) {
					stuckCounter++;
					moveGhost(this->newSmartDirection[1], x, y, currentLevel);
					return;
				}
				else {
					stuckCounter = 0;
					gotStuck = false;
					takeDierctionByPacmanLoc(this->pacmamLoc[0], this->pacmamLoc[1]);
					moveGhost(this->smartDirection[0], x, y, currentLevel);
					return;
				}
			}
		}

	}
	else
	{
		x = chosen_x;
		y = chosen_y;
		this->set_direction(direction);
	}

}
void Ghost::move(char direction, int& x, int& y) {
	switch (this->gameLevel) {
	case 1:
		Level_1_move(direction, x, y);
		break;
	case 2:
		Level_2_move(direction, x, y);
		break;
	case 3:
		Level_3_move(direction, x, y);
		break;
	default:
		moveGhost(direction, x, y, 0);
		return;
	}
	
}

void Ghost::Level_1_move(char direction, int& x, int& y) {
	direction = this->get_direction();
	if (this->moveCounter % 20 != 0) {
		moveGhost(direction, x, y, 1);
	}
	else {
		this->moveCounter = 1;
		int newDirection = generateNewDirection();
		moveGhost(newDirection, x, y, 1);
	}
}
void Ghost::Level_2_move(char direction, int& x, int& y) {
	if (this->moveCounter % 20 != 0 && goDumb == false) {
		Level_3_move(direction, x, y);
	}
	else if (this->moveCounter % 20 == 0 && goDumb == false) {
		this->moveCounter = 0;
		this->goDumb = true;
		Level_1_move(generateNewDirection(), x, y);
	}
	else {
		if (this->moveCounter % 5 != 0) {
			Level_1_move(direction, x, y);
		}
		else {
			goDumb = false;
			this->moveCounter = 1;
			Level_3_move(direction, x, y);
		}
	}
}
void Ghost::Level_3_move(char direction, int& x, int& y) {
	takeDierctionByPacmanLoc(this->pacmamLoc[0], this->pacmamLoc[1]);
	moveGhost(this->smartDirection[0], x, y, 3);


}
int Ghost::takeDierctionByPacmanLoc(int pacman_Loc_x, int pacman_Loc_y) {
	if (pacman_Loc_x > this->get_locationX()) {
		this->smartDirection[0] = 3;
	}
	else if (pacman_Loc_x < this->get_locationX()) {
		this->smartDirection[0] = 0;
	}
	else {
		this->smartDirection[0] = -1;
	}
	if (pacman_Loc_y > this->get_locationY()) {
		this->smartDirection[1] = 2;
	}
	else if (pacman_Loc_y < this->get_locationY()) {
		this->smartDirection[1] = 1;
	}
	else {
		this->smartDirection[1] = -1;
	}
	return 3;

}
int Ghost::ChooseDirectionWhileStuck(int direction_1, int direction_2) {
	int newDirection = rand() % 4;
	while (newDirection == direction_1 || newDirection == direction_2) {
		int newDirection = rand() % 4;
	}
	return newDirection;

}
void Ghost::moveGhost(char direction, int& nextLoc_x, int& nextLoc_Y, int currentLevel) {
	int loc_X, loc_Y;
	loc_X = this->get_locationX();
	loc_Y = this->get_locationY();
	this->set_LastLoc(loc_X, loc_Y);
	if (direction == 0) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X - 1, loc_Y, 0, currentLevel);
		return;
	}
	else if (direction == 1) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X, loc_Y - 1, 1, currentLevel);
		return;
	}
	else if (direction == 2) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X, loc_Y + 1, 2, currentLevel);
		return;
	}
	else if (direction == 3) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X + 1, loc_Y, 3, currentLevel);
		return;
	}
	else if (direction == 4) {
		nextLoc_x = loc_X;
		nextLoc_Y = loc_Y;
		gotoxy(loc_X, loc_Y);
	}
	else if (direction == -1) {
		checkValidMove(nextLoc_x, nextLoc_Y, loc_X, loc_Y, -1, currentLevel);
	}
}
int Ghost::chooseLastDirection() {
	int newDirection = rand() % 4;
	while (newDirection == this->smartDirection[0] || newDirection == this->smartDirection[1] || newDirection == this->newSmartDirection[0]) {
		newDirection = rand() % 4;
	}
	return newDirection;
}



