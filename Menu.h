#ifndef  _MENU_H
#define _MENU_H
#include "tools.h"
class Menu {
private:
	int gameLevel;
	const char* FileName;
	bool mapChosen;
	bool endGame;
public:
	char GetMenu();
	void printRulesAndKeys();
	int getGameLevel();
	void setGameLevel();
	char* UploadFile();
	const char* getFileName() const { return this->FileName; }
};

#endif   _MENU_H
