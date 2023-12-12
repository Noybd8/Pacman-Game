#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "tools.h"
class GameObject {
private:
	int starting_postion_x, starting_postion_y;
	int m_x, m_y;
	char m_symbol;
	char m_direction;
	int LastLoc[2];
	char*** map;
	int mapSize[2]; // mapSize[0] = num of Rows, mapSize[1] = num of Culs.
	int objectNum;


public:
	GameObject() {}
	GameObject(int locationX, int locationY, char ch, char direction, char*** board, int numOfRows, int numOfCuls, int objectNum);
	int generateNewDirection();
	int get_starting_position_x()const { return this->starting_postion_x; }
	int get_starting_position_y() const { return this->starting_postion_y; }
	int getNumOfRows()const {
		return this->mapSize[0];
	}
	int getNumOfCol()const {
		return this->mapSize[1];
	}
	void set_location_x(int n) { this->m_x = n; }
	void set_LastLoc(int x, int y) { this->LastLoc[0] = x; this->LastLoc[1] = y; }
	void set_location_y(int n) { this->m_y = n; }
	void set_direction(char direction) { this->m_direction = direction; }
	char get_direction()const { return this->m_direction; }
	int get_locationX()const { return this->m_x; }
	int get_locationY() const { return this->m_y; }
	char getSymbol()const { return this->m_symbol; }
	int* getLastLoc() { return this->LastLoc; }
	virtual void move(char keyStroke, int& nextLoc_x, int& nextLoc_Y);
	virtual void checkValidMove(int& x, int& y, int chosen_x, int chosen_y, char direction, int currentLevel = 1) = 0;
	char getCharInMap(int x, int y) const { return (*map)[x][y]; }
	void setStarting_position_x(int x) { this->starting_postion_x = x; }
	void setStarting_position_y(int y) { this->starting_postion_y = y; }
	int getObjectNum()const { return this->objectNum; }


};

#endif _GAMEOBJECT_H


