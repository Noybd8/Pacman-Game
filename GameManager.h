#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "GameObject.h"
#include "Board.h"
#include "pacman.h"
#include "ghost.h"
#include "fruit.h"
#include "Menu.h"
#include "ObjectsMoves.h"

class GameManager {
private:
	Menu menu;
	Fruit fruit;
	Pacman pacman;
	Board board;
	Ghost* ghost;
	objectsMoves moves;
	int life = 3;
	const char* fileName;
	int score = 0;
	int breadScrumbsEaten = 0;
	char lastBoardChar[6] = { '*', '*', '*','*','*','*' }; //saving the boardChar of ea GameObject, the ghosts by thier location and the pacman in the last loc.
	bool m_strike = false;
	int numOfFilesInDirectory = 0;
	vector<string> Files;
	char MenuKeyStroke;
	int numofGhosts;
	bool fruitWasEaten = false;
	bool GameOver = false;
	bool silentCheack = true;




public:
	void run(bool load, bool silent);
	void regularGame();
	void loadMode(bool silent);
	GameManager(bool load);
	GameManager();
	void BuildObjectsByMap();
	bool findSubStringInString(string s, string sub);
	void goOverDirectory();
	void loadFiles(bool load, bool silent);
	bool strike(char symbol, int x, int y); // check if the next step of the pacman is ghost
	bool changeBoolStatus(bool b);
	bool getStrike() {return this->m_strike;}
	bool gameOver();
	void returnToOriginalLoaction();
	void writeTofile();
	void print_GameOver_Message();
	bool mapFinished();
	void decrase_life() { this->life--; };
	void makeMovemntInMap(GameObject* g, char direction);
	bool eatBreadScrumbs(int x, int y, char c);
	void nextStep(GameObject& g, int x, int y, char symbol, char lastBoardChar, int objectNum);//taking care of ea GameObject next step by dividing what can
	//happened if it goona by strike if pacman moving in tunnel if pacman get score...
	void set_LastBoardChar(int x, int y, int loc);// changing the list of lastboardchar
	char get_LastBoardChar(int loc);//get the lastBoardChar bt the location in the array.
	void tunnelMoving(GameObject& g, int x, int y);
	void updateLastBoardChar(int lastLoc_x, int lastLoc_y, char lastBoardChar = ' ');
	bool eatFruit(int x, int y, char symbol);
	char* createNewFileNameToMoves(const char* fileName, bool steps, bool result);
	string getDirectionsFromFile(string objectName, const char* fileName);
	string makeGhostNameByNum(int ghostNum);
	void TakeFruitData(Fruit& f, string line,char direction);
	int winningTimeByFile(const char* fileName);
	int getFruitDataFromFile(Fruit& f,const char* fileName, int rowNumber);
	int getFruitCreatedTime(string line, int& endLoc);
	int getStrikeTime(const char* fileName,int strikeCounter);

};
#endif _GAMEMANAGER_H
