#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <thread>

#include "engine.h"
#include "utils.h"
#include "game.h"

using std::cout;
using engine::maxX;
using engine::maxY;
using engine::snake;
using engine::fruit;

void getKey();
inline void outputScoreFrSnake(Coord prev);
void update();
void updateWithCls();
void drawBoundary();
void drawMaze();
char drawMenuRtnResponse();
void startGame();

constexpr char body = '\xB2';
constexpr char fr = '\xE8';

game::Player player;
game::Speed speed;

int main()
{
	system("color f2");
	system("title Snake Game");
	setWindowSize(800, 1000);
	setFontSize(12, 35);
	hidecursor();

	bool isReviewInstruc;
	do {
		isReviewInstruc = false;
		switch (drawMenuRtnResponse()) {
		case '1':
			speed.diffi = speed.easy;
			break;
		case '2':
			speed.diffi = speed.medium;
			break;
		case '3':
			speed.diffi = speed.hard;
			break;
		case '4':
			system("cls");
			cout << "    INSTRUCTION\n";
			cout << " Control : Response\n";
			cout << " w\t : UP\n";
			cout << " s\t : DOWN\n";
			cout << " a\t : LEFT\n";
			cout << " d\t : RIGHT\n\n";
			cout << "- Eat a fruit (\xE8) = 1 score.\n";
			cout << "- \xBA is allowed to pass through.\n\n";
			cout << "#WARNING:\n";
			cout << "- Do not hit the maze (=).\n\n";
			system("pause");
			system("cls");
			isReviewInstruc = true;
			break;
		default:
			return 0;
		}
	} while (isReviewInstruc);

	//clear the menu screen
	system("cls");
	startGame();
	cout << '\n';
	//system("pause");
	return 0;
}

void startGame()
{
	drawBoundary();
	drawMaze();
	engine::randFruit();
	//make a new thread to get the key press without interrupt the game updating
	std::thread t1(getKey);

	while (true) {
		//move the snake, test the collision with fruit, its body, or the maze
		//and trigger the sleep for the sake of the speed
		update();
		if (engine::isSelfCollide() || engine::isSnakeMazeCollide()) {
			gotoxy(7, 13);
			t1.detach();
			cout << "YOU LOSE\n";
			return;
		}
	}
}

void updateWithCls()
{
	//get prev to delete it in this func outputScoreFrSnake(prev)
	system("cls");
	const Coord prev = engine::moveRtnPrev();
	if (engine::isSnakeFruitCollide()) {
		engine::addOneLength();
		player.increScore();

		//Change the mazes from 1 - 4
		if (player.getLevel() < 4 && player.getScore() % 15 == 0) {
			player.increLevel();
			//reset snake to 1 length keep score & level
			engine::resetDefault();
		}

		engine::randFruit();
	} //end if (engine::isSnakeFruitCollide())

	drawBoundary();
	drawMaze();
	gotoxy(fruit.x, fruit.y);
	cout << fr;
	//Output Score
	gotoxy(0, maxY + 2);
	cout << "Score: " << player.getScore();
	cout << "\t\b\bLevel: " << player.getLevel();
	for (Coord &c : snake.occupied) {
		gotoxy(c.x, c.y);
		cout << body;
	}

	//trigger the sleep for the speed purpose
	Sleep(speed.calSleepTime(player.getScore(), snake.dir));
}

void update()
{
	//get prev to delete it in this func outputScoreFrSnake(prev)
	const Coord prev = engine::moveRtnPrev();
	if (engine::isSnakeFruitCollide()) {
		engine::addOneLength();
		player.increScore();

		//Change the mazes from 1 - 4
		if (player.getLevel() < 4 && player.getScore() % 15 == 0) {
			player.increLevel();
			//reset snake to 1 length keep score & level
			engine::resetDefault();

			system("cls");
			drawBoundary();
			drawMaze();
		}

		engine::randFruit();
	} //end if (engine::isSnakeFruitCollide())

	outputScoreFrSnake(prev);

	//trigger the sleep for the speed purpose
	Sleep(speed.calSleepTime(player.getScore(), snake.dir));
}

void getKey()
{
	while (true) {
		const char key = _getch();

		switch (tolower(key)) {
			case 'a':
				snake.changeDir(left);
				break;
			case 'd':
				snake.changeDir(right);
				break;
			case 'w':
				snake.changeDir(up);
				break;
			case 's':
				snake.changeDir(down);
				break;
		}

		while (!snake.hasRespondedToChangeDir) {}
	}
}

void outputScoreFrSnake(Coord prev)
{
	//Output Score
	gotoxy(0, maxY + 2);
	cout << "Score: " << player.getScore();
	cout << "\t\b\bLevel: " << player.getLevel();

	//Output the fruit
	gotoxy(fruit.x, fruit.y);
	cout << fr;

	//Output Snake's Head
	gotoxy(snake.occupied[0].x, snake.occupied[0].y);
	cout << body;

	//Remove the last from screen
	if (prev.x != 0 && prev.x != maxX + 1
		&& prev.y != 0 && prev.y != maxY + 1) {
		gotoxy(prev.x, prev.y);
		cout << ' ';
	}
}

char drawMenuRtnResponse()
{
	cout << "1) Easy\n2) Medium\n3) Hard\n4) HOW TO PLAY\n";
	cout << "5) Exit";

	return _getch();
}

void drawBoundary()
{
	//top
	cout << '\xC9';
	for (int i = 0; i < maxX; i++)
		cout << '\xCD';
	cout << '\xBB';

	//bottom
	gotoxy(0, maxY + 1);
	cout << '\xC8';
	for (int i = 0; i < maxX; i++)
		cout << '\xCD';
	cout << '\xBC';

	//left
	for (int i = 0; i < maxY; i++) {
		gotoxy(0, i + 1);
		cout << '\xBA';
	}

	//right
	for (int i = 0; i < maxY; i++) {
		gotoxy(maxX + 1, i + 1);
		cout << '\xBA';
	}
}

void drawMaze()
{
	vector<Coord> mazes = engine::getMazes(player.getLevel());
	for (auto c : mazes) {
		gotoxy(c.x, c.y);
		cout << '=';
	}
}
