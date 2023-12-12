
#include "GameManager.h"
GameManager::GameManager(bool load)
{
	if (!load) {
		this->MenuKeyStroke = this->menu.GetMenu();
	}

}
void GameManager::BuildObjectsByMap() {
	//this->board = Board(this->fileName);
	Board* b = new Board(this->fileName);
	this->board = *b;
	int ghostNum = this->board.getNumOfGhost();
	this->numofGhosts = ghostNum;
	this->moves = objectsMoves(ghostNum);
	this->pacman = Pacman(this->board.get_Pacman_Starting_position()[0], this->board.get_Pacman_Starting_position()[1], '@', 's', this->board.getBoardGame(), this->board.getNumOfRows(), this->board.getNumOfCul(), numofGhosts + 1);
	this->ghost = new Ghost[ghostNum];
	for (int i = 0; i < numofGhosts; i++) {
		ghost[i] = Ghost(this->board.get_Ghost_Starting_position(i)[0], this->board.get_Ghost_Starting_position(i)[1], '$', char(rand() % 4), this->board.getBoardGame(), this->board.getNumOfRows(), this->board.getNumOfCul(), this->menu.getGameLevel(), i);
	}
	this->fruit = Fruit(0, 0, this->fruit.createRandomValue(), char(rand() % 4), this->board.getBoardGame(), this->board.getNumOfRows(), this->board.getNumOfCul(), numofGhosts);
}

bool GameManager::changeBoolStatus(bool b) {
	if (b)
		return false;
	return true;
}
bool GameManager::strike(const char symbol, int x, int y) {
	if (symbol == '@') {
		if (this->board.getCharInBoard(x, y) == '$') {
			returnToOriginalLoaction();
			this->decrase_life();
			this->m_strike = changeBoolStatus(this->m_strike);
			return true;
		}
		return false;
	}
	else if (symbol == '$') {
		if (this->board.getCharInBoard(x, y) == '@') {
			returnToOriginalLoaction();
			this->decrase_life();
			this->m_strike = changeBoolStatus(this->m_strike);
			return true;
		}
		return false;
	}
	return false;
}

void GameManager::returnToOriginalLoaction() {
	this->updateLastBoardChar(this->pacman.get_locationX(), this->pacman.get_locationY());
	this->pacman.set_location_x(this->pacman.get_starting_position_x());
	this->pacman.set_location_y(this->pacman.get_starting_position_y());
	this->set_LastBoardChar(this->pacman.get_starting_position_x(), this->pacman.get_starting_position_y(), this->numofGhosts + 1);
	for (int i = 0; i < numofGhosts; i++) {
		char c = this->get_LastBoardChar(i);
		this->updateLastBoardChar(this->ghost[i].get_locationX(), this->ghost[i].get_locationY(), c);
		this->ghost[i].set_location_x(this->ghost[i].get_starting_position_x());
		this->ghost[i].set_location_y(this->ghost[i].get_starting_position_y());
		this->set_LastBoardChar(this->ghost[i].get_starting_position_x(), this->ghost[i].get_starting_position_y(), i);
	}
	char c = this->get_LastBoardChar(numofGhosts);
	this->updateLastBoardChar(this->fruit.get_locationX(), this->fruit.get_locationY(), c);
	this->fruit.set_location_x(this->fruit.get_starting_position_x());
	this->fruit.set_location_y(this->fruit.get_starting_position_y());
	this->set_LastBoardChar(this->fruit.get_starting_position_x(), this->fruit.get_starting_position_y(), numofGhosts);
}

void GameManager::print_GameOver_Message() {
	gotoxy(8, 40);
	std::cout << "GAME OVER!!!!!";
	gotoxy(9, 40);
	std::cout << "YOU LOST";
}
bool GameManager::mapFinished() {
	if (this->breadScrumbsEaten == this->board.getBreadCount()) {
		return true;
	}
	return false;
}

bool  GameManager::gameOver() {
	if (this->life == 0) {
		print_GameOver_Message();
		return true;
	}
	return false;
}
bool GameManager::eatBreadScrumbs(int x, int y, char c) {

	if (this->board.getCharInBoard(x, y) == '.') {
		if (c == '$' || (c >= '5' && c <= '9')) {
			return true;
		}
		this->score++;
		this->breadScrumbsEaten++;
		return true;
	}
	return false;

}
bool GameManager::eatFruit(int x, int y, char symbol) {
	if (symbol == '@' && this->board.getCharInBoard(x, y) >= '5' && this->board.getCharInBoard(x, y) <= '9') {
		this->score += this->board.getCharInBoard(x, y) - '0';
		fruitWasEaten = true;
		return true;
	}
	else if (symbol == '$' && this->board.getCharInBoard(x, y) >= '5' && this->board.getCharInBoard(x, y) <= '9') {
		fruitWasEaten = true;
		return true;
	}
	return false;
}

void GameManager::tunnelMoving(GameObject& g, int x, int y) {
	int numOfRows = this->board.getNumOfRows();
	int numOfCuls = this->board.getNumOfCul();
	if (x == 0) {
		g.set_location_x(numOfRows - 2);
		g.set_location_y(y);
	}
	else if (x == numOfRows - 1) {
		g.set_location_x(1);
		g.set_location_y(y);
	}
	else if (y == 0) {
		g.set_location_x(x);
		g.set_location_y(numOfCuls - 2);
	}
	else if (y == numOfCuls - 1) {
		g.set_location_x(x);
		g.set_location_y(1);
	}

}
void GameManager::updateLastBoardChar(int lastLoc_x, int lastLoc_y, char lastBoardChar) {
	if (lastBoardChar == '@' || lastBoardChar == '$')//taking care of not creating a problem by putting the pacman as lastBoardChar.
	{
		this->board.SetCharInBoard(lastLoc_x, lastLoc_y, ' ');

	}
	else {
		this->board.SetCharInBoard(lastLoc_x, lastLoc_y, lastBoardChar);
		gotoxy(lastLoc_x, lastLoc_y);
		std::cout << lastBoardChar;
	}

}

void GameManager::nextStep(GameObject& g, int x, int y, const char symbol, char lastBoardChar, int objectNum) {
	set_LastBoardChar(x, y, objectNum);
	int lastLoc_x = g.getLastLoc()[0];
	int lastLoc_y = g.getLastLoc()[1];
	bool b = eatBreadScrumbs(x, y, symbol);
	bool ghostEatFruit = false;
	if (this->strike(symbol, x, y) == true) {
		return;
	}
	if (symbol == '@' && this->board.getCharInBoard(x, y) == '~') {
		tunnelMoving(g, x, y);
		updateLastBoardChar(lastLoc_x, lastLoc_y);
		return;
	}
	else {
		if (eatFruit(x, y, symbol) == true) {
			if (symbol == '@') {
				if (get_LastBoardChar(numofGhosts) == '.') { // see if before the fruit there was a bread scrumbs and if there was so the score is updated
					this->breadScrumbsEaten++;
					this->score++;
				}
			}
			else {
				ghostEatFruit = true;
			}
		}
		g.set_location_x(x);
		g.set_location_y(y);

	}
	this->board.SetCharInBoard(x, y, symbol);
	updateLastBoardChar(lastLoc_x, lastLoc_y);
	gotoxy(x, y);
	std::cout << symbol;
	if (symbol == '$' || (symbol >= '5' && symbol <= '9')) {
		if (lastBoardChar == '*') {
			lastBoardChar = '.';
		}
		else if (ghostEatFruit == true) {
			this->lastBoardChar[g.getObjectNum()] = this->lastBoardChar[numofGhosts]; //gives the last board char that the fruit possesed to the ghost that ate it.
			return;

		}
		updateLastBoardChar(lastLoc_x, lastLoc_y, lastBoardChar);
	}
	else if ((b == true && symbol == '@') || (symbol == '@' && lastBoardChar == '*')) {
		{
			updateLastBoardChar(lastLoc_x, lastLoc_y);
		}
	}
}

void GameManager::makeMovemntInMap(GameObject* g, char direction) {
	int nextLoc_x;
	int nextLoc_Y;
	g->move(direction, nextLoc_x, nextLoc_Y);
	char c = this->get_LastBoardChar(g->getObjectNum());
	if (g->get_direction() == 4 && (g->getSymbol() == '@' || g->getSymbol() == '$')) {                    
		gotoxy(nextLoc_x, nextLoc_Y);
		cout << g->getSymbol();
	}
	else {
		nextStep(*g, nextLoc_x, nextLoc_Y, g->getSymbol(), c, g->getObjectNum());
	}
}

void GameManager::set_LastBoardChar(int x, int y, int loc) {
	char c = this->board.getCharInBoard(x, y);
	if (c == '@' || c == '$') {
		lastBoardChar[loc] = ' ';
	}
	else if (c >= '5' && c <= '9') {
		lastBoardChar[loc] = lastBoardChar[numofGhosts]; // if 
	}
	else {
		lastBoardChar[loc] = this->board.getCharInBoard(x, y);
	}
}
char GameManager::get_LastBoardChar(int loc) {
	return this->lastBoardChar[loc];
}
char* GameManager::createNewFileNameToMoves(const char* fileName, bool steps, bool result) {
	string str = fileName;
	size_t found = str.find(".s");
	string stepsFileName;
	char* newFileName;
	for (int i = 0; i <= found; i++)
	{
		stepsFileName += fileName[i];
	}
	if (steps) {
		stepsFileName += "steps.txt";
		newFileName = new char[11 + found];
		strcpy_s(newFileName, 11 + found, stepsFileName.c_str());
	}
	else { //there are only 2 option if steps is true otherwise result is true.
		stepsFileName += "result.txt";
		newFileName = new char[12 + found];
		strcpy_s(newFileName, 12 + found, stepsFileName.c_str());
	}
	return newFileName;
}
int GameManager::getFruitDataFromFile(Fruit& f, const char* fileName, int rowNumber) {
	string compareTo = "created";
	std::ifstream file(fileName, ios::in);
	std::string line;
	int createdCounter = 0, counter = 0, endLoc = 0;
	while (createdCounter != rowNumber) {
		getline(file, line);
		if (line == compareTo) {
			createdCounter++;
		}
	}
	getline(file, line);
	int direction = this->moves.makeStringToInt(line, 0, line.length() - 1);
	getline(file, line);
	counter = getFruitCreatedTime(line, endLoc);
	TakeFruitData(f, line, direction);
	return counter;


}

void GameManager::TakeFruitData(Fruit& f, string line, char direction) {
	char value = 0;
	int locX = 0, locY = 0;
	this->moves.takeResultFromLine(line, value, locX, locY);
	f = Fruit(locX, locY, value, direction, this->board.getBoardGame(), this->board.getNumOfRows(), this->board.getNumOfCul(), numofGhosts);

}
int GameManager::getFruitCreatedTime(string line, int& endLoc) {
	int counter = 0;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ') {
			endLoc = i - 1;
			counter = this->moves.makeStringToInt(line, 0, endLoc);
			endLoc++;
		}
	}
	return counter;
}

string GameManager::makeGhostNameByNum(int ghostNum) {
	string name = "Ghost";
	name += ghostNum + '0';
	return name;
}
void GameManager::writeTofile() {
	const char* newStepsFileName = createNewFileNameToMoves(this->fileName, true, false);
	const char* newResultFileName = createNewFileNameToMoves(this->fileName, false, true);
	ofstream StepsFile(newStepsFileName + 2);
	StepsFile << "pacman" << endl;
	StepsFile << this->moves.getSringByLoc(numofGhosts + 1) << endl;
	StepsFile << "\n\n\n";
	for (int i = 0; i < numofGhosts; i++) {
		StepsFile << "Ghost" << i << endl;
		StepsFile << this->moves.getSringByLoc(i) << endl;
		StepsFile << "\n\n\n";
	}
	StepsFile << "fruit" << endl;
	StepsFile << this->moves.getSringByLoc(numofGhosts);
	StepsFile << "\n\n\n";
	StepsFile.close();
	ofstream ResultFile(newResultFileName + 2);
	ResultFile << this->moves.getWinningTime() << endl;
	ResultFile << this->moves.getFruitResult() << endl;
	ResultFile << this->moves.getResults() << endl;
	ResultFile.close();

}
int GameManager::getStrikeTime(const char* fileName,int strikeCounter) {
	int counter = 0;
	int strikeTime;
	std::ifstream file(fileName, ios::in);
	std::string line;
	while (counter != strikeCounter) {
		getline(file, line);
		if (line == "There Was a strike here:") {
			counter++;
		}
	}
	getline(file, line);
	strikeTime = this->moves.makeStringToInt(line, 0, line.length() - 1);
	return strikeTime;
		
}


void GameManager::regularGame()
{
	int fruitTimeOut = rand() % 10, timeOutCounter = 0;
	bool pauseGame = false;
	bool endGame = false;
	int counter = 1;
	system("CLS");
	this->board.printBoard();
	gotoxy(this->fruit.get_starting_position_x(), this->fruit.get_starting_position_y());
	std::cout << this->fruit.getSymbol();
	char c = getKey();
	while (!endGame) {
		Sleep(100);
		if (_kbhit()) {
			c = getKey();
			if (c == 27) {
				c = this->pacman.get_direction();
				pauseGame = this->changeBoolStatus(pauseGame);
			}
			else if (c != 27 && pauseGame == true) {
				pauseGame = this->changeBoolStatus(pauseGame);
			}

		}
		if (pauseGame == false) {
			makeMovemntInMap(&this->pacman, c);
			counter++;
			this->moves.writeToString(this->pacman.get_direction(), numofGhosts + 1);
			for (int i = 0; i < numofGhosts; i++) {
				this->ghost[i].set_pacmanLoc(this->pacman.get_locationX(), this->pacman.get_locationY());
			}
			if (getStrike() == true)
			{
				this->moves.writeToString(5, numofGhosts + 1,counter);
				pauseGame = true;
				this->m_strike = changeBoolStatus(this->m_strike);
				this->board.SetCharInBoard(this->pacman.get_starting_position_x(), this->pacman.get_starting_position_y(), '@');
				gotoxy(this->pacman.get_starting_position_x(), this->pacman.get_starting_position_y());
				std::cout << '@';
			}

			Sleep(100);
			if ((counter % 2 )==0&& pauseGame != true) {
				if (fruitWasEaten == true) {
					if (timeOutCounter == fruitTimeOut) {
						this->moves.writeToString(5, numofGhosts,counter-timeOutCounter,fruit.getSymbol() - '0',this->fruit.get_locationX(), this->fruit.get_locationY());
						timeOutCounter = 0;
						fruitWasEaten = false;
						this->fruit = Fruit(0, 0, this->fruit.createRandomValue(), char(rand() % 4), this->board.getBoardGame(), this->board.getNumOfRows(), this->board.getNumOfCul(), numofGhosts);
						this->moves.writeToString(this->fruit.get_direction(), numofGhosts, counter, fruit.getSymbol() - '0', this->fruit.get_locationX(), this->fruit.get_locationY());
					}
					else {
						timeOutCounter++;
					}
				}
				else {
					makeMovemntInMap(&this->fruit, this->fruit.get_direction());
					this->moves.writeToString(this->fruit.get_direction(), numofGhosts);
				}
				for (int i = 0; i < numofGhosts; i++) {
					makeMovemntInMap(&this->ghost[i], this->ghost[i].get_direction());
					this->moves.writeToString(this->ghost[i].get_direction(), i);
					if (this->ghost[i].get_direction() == 4) {
						gotoxy(this->ghost[i].get_locationX(), this->ghost[i].get_locationY());
						cout << '$';
					}
					this->ghost[i].set_moveCounter(this->ghost[i].get_moveCounter() + 1);
					if (getStrike() == true)
					{
						this->moves.writeToString(5, numofGhosts + 1,counter);
						pauseGame = true;
						this->m_strike = changeBoolStatus(this->m_strike);
						for (int j = 0; j < numofGhosts; j++) {
							gotoxy(this->ghost[j].get_starting_position_x(), this->ghost[j].get_starting_position_y());
							cout << '$';
							this->board.SetCharInBoard(this->ghost[j].get_starting_position_x(), this->ghost[j].get_starting_position_y(), '$');
						}
						break;
					}

				}
			}
			gotoxy(this->board.getLocOfLegendX(), this->board.getLocOfLegendY());
			std::cout << "the score is : " << this->score;
			gotoxy(this->board.getLocOfLegendX() + 1, this->board.getLocOfLegendY());
			std::cout << "your life is: " << this->life;
			if (gameOver() == true) {
				
				Sleep(5000);
				endGame = true;
				this->GameOver = true;
			}
			if (mapFinished() == true) {
				endGame = true;
			}
			
		}
	}
	this->moves.TakeWinningTime(counter);
	writeTofile();
}
void GameManager::loadMode(bool silent) {
	const char* resultsFile = createNewFileNameToMoves(this->fileName, false, true);
	const char* stepsFile = createNewFileNameToMoves(this->fileName, true, false);
	int winningTime = winningTimeByFile(resultsFile);
	string pacmanMoves;
	string fruitMoves;
	string* ghostsMoves;
	ghostsMoves = new string[numofGhosts];
	bool fruitInTimeOut = false;
	int* ghostMoveCounter = new int[numofGhosts];
	for (int i = 0; i < numofGhosts; i++) {
		ghostMoveCounter[i] = 0;
	}
	int counter = 1, pacmanMovesCounter = 0,  fruitMoveCounter = 0, fruitEatenCounter = 1,createdFruitTime = 0;
	int strikeCounter = 1, strikeTime;
	system("CLS");
	if (!silent) {
		this->board.printBoard();
		gotoxy(this->fruit.get_starting_position_x(), this->fruit.get_starting_position_y());
		std::cout << this->fruit.getSymbol();
	}
	pacmanMoves = getDirectionsFromFile("pacman", stepsFile);
	fruitMoves = getDirectionsFromFile("fruit", stepsFile);
	for (int i = 0; i < numofGhosts; i++) {
		ghostsMoves[i] = getDirectionsFromFile(makeGhostNameByNum(i), stepsFile);
	}
	while (counter != winningTime) {
		if (!silent) {
			Sleep(100);
		}
		if (pacmanMoves[pacmanMovesCounter] == '\n') {
			pacmanMovesCounter++;
		}
		makeMovemntInMap(&this->pacman, pacmanMoves[pacmanMovesCounter] - '0');
		pacmanMovesCounter++;
		if (getStrike() == true) {
			this->m_strike = changeBoolStatus(this->m_strike);
			this->board.SetCharInBoard(this->pacman.get_starting_position_x(), this->pacman.get_starting_position_y(), '@');
			if (!silent) {
				gotoxy(this->pacman.get_starting_position_x(), this->pacman.get_starting_position_y());
				std::cout << '@';
			}
			else {
				strikeTime = getStrikeTime(resultsFile, strikeCounter);
				if (counter != strikeTime) {
					silentCheack = false;
				}
			}

		}
		if ((counter % 2) == 0) {
			if (fruitMoves[fruitMoveCounter] == '\n') {
				fruitMoveCounter++;
			}
			if (fruitWasEaten == true && createdFruitTime != 0) {
				createdFruitTime = getFruitDataFromFile(this->fruit, resultsFile, fruitEatenCounter);
				fruitWasEaten = false;
				fruitInTimeOut = true;
				fruitEatenCounter++;
			}
			else if (counter == createdFruitTime && fruitInTimeOut) {
				makeMovemntInMap(&this->fruit, fruitMoves[fruitMoveCounter] - '0');
				fruitMoveCounter++;
				fruitInTimeOut = false;
				createdFruitTime = 0;
			}
			else {
				makeMovemntInMap(&this->fruit, fruitMoves[fruitMoveCounter] - '0');
				fruitMoveCounter++;
			}
			for (int i = 0; i < numofGhosts; i++) {
				if (ghostsMoves[i][ghostMoveCounter[i]] == '\n') {
					ghostMoveCounter[i]++;
				}
				makeMovemntInMap(&this->ghost[i], ghostsMoves[i][ghostMoveCounter[i]] - '0');
				ghostMoveCounter[i]++;
				if (this->ghost[i].get_direction() == 4 && !silent) {
					gotoxy(this->ghost[i].get_locationX(), this->ghost[i].get_locationY());
					cout << '$';
				}
				this->ghost[i].set_moveCounter(this->ghost[i].get_moveCounter() + 1);
				if (getStrike() == true)
				{
					this->m_strike = changeBoolStatus(this->m_strike);
					for (int j = 0; j < numofGhosts; j++) {
						if (!silent) {
							gotoxy(this->ghost[j].get_starting_position_x(), this->ghost[j].get_starting_position_y());
							cout << '$';
						}
						else {
							strikeTime = getStrikeTime(resultsFile, strikeCounter);
							if (counter != strikeTime) {
								silentCheack = false;
							}
						}
						this->board.SetCharInBoard(this->ghost[j].get_starting_position_x(), this->ghost[j].get_starting_position_y(), '$');
					}
					break;
				}


			}


		}
		counter++;
		if (!silent) {
			gotoxy(this->board.getLocOfLegendX(), this->board.getLocOfLegendY());
			std::cout << "the score is : " << this->score;
			gotoxy(this->board.getLocOfLegendX() + 1, this->board.getLocOfLegendY());
			std::cout << "your life is: " << this->life;
		}
		else {
			system("CLS");
		}
		if (silent && !silentCheack) {
			cout << "the cheack has filed";
			return;
		}

	}
}

bool GameManager::findSubStringInString(string s, string sub) {
	size_t found = s.find(sub);
	if (found != std::string::npos)
	{
		numOfFilesInDirectory++;
		Files.push_back(s);
		return true;
	}
	return false;

}
void GameManager::goOverDirectory() {
	string path = ".";
	string fileName;
	for (const auto& file : directory_iterator(path))
	{
		fileName = file.path().string();
		findSubStringInString(fileName, "screen");


	}


}
void GameManager::loadFiles(bool load,bool silent) {
	goOverDirectory();

	for (string i : Files)
	{
		if (GameOver && !silent) {
			print_GameOver_Message();
			Sleep(500);
			return;
		}
		this->fileName = i.c_str();
		this->breadScrumbsEaten = 0;
		if (!load && !silent) {
			BuildObjectsByMap();
			regularGame();
		}
		else {
			BuildObjectsByMap();
			loadMode(silent);
			if (!silentCheack) {
				return;
			}
		}
		
 //		delete& this->board;
	}
}

void GameManager::run(bool load,bool silent) {
	if (load) {
		loadFiles(load, silent);
	}
	else if (this->menu.getFileName()[0] == 'b' ||this->menu.getFileName()[0]=='B') {
		loadFiles(load,silent);
	}
	else {
		this->fileName = this->menu.getFileName();
		BuildObjectsByMap();
		regularGame();
	}
}
string GameManager::getDirectionsFromFile(string objectName, const char* fileName) {
	string objectSteps;
	std::ifstream file(fileName, ios::in);
	std::string line;
	while (line != objectName) {
		std::getline(file, line);
	}
	while (line != "") {
		std::getline(file, line);
		objectSteps += line;
	}
	file.close();
	return objectSteps;
}
int GameManager:: winningTimeByFile(const char* fileName)
{
	
	std::ifstream file(fileName, ios::in);
	string str;
	getline(file, str);
	return this->moves.makeStringToInt(str, 0,str.length()-1);
	

}




