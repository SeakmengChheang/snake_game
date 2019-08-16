#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>

#include "coord.h"
#include "snake.h"
#include "fruit.h"
#include "game.h"

namespace engine
{
	Snake snake;
	Fruit fruit(Coord(0, 0));
	vector<Coord> mazes;
	constexpr int maxX = 20, maxY = 10;

	bool isRandFruitOverlaySnakeMazes(Coord f)
	{
		auto it = std::find(snake.occupied.begin(), snake.occupied.end(), f);
		auto it2 = std::find(mazes.begin(), mazes.end(), f);

		return !(it == snake.occupied.end() && it2 == mazes.end());
	}

	bool isSnakeMazeCollide()
	{
		auto it = std::find(mazes.begin(), mazes.end(), snake.occupied[0]);

		return it != mazes.end();
	}

	bool isSelfCollide()
	{
		auto it = std::find(snake.occupied.begin() + 1, snake.occupied.end(), snake.occupied[0]);

		return it != snake.occupied.end();
	}

	bool isSnakeFruitCollide()
	{
		return fruit.x == snake.occupied[0].x && fruit.y == snake.occupied[0].y;
	}

	void addOneLength()
	{
		snake.addOneLength();
	}

	void resetDefault()
	{
		snake.resetDefault();
	}

	void randFruit()
	{
		srand(time(NULL));

		Coord c(rand() % maxX + 1, rand() % maxY + 1);

		//If fruit XY overlays Snake's bodies RERANDOM
		while (isRandFruitOverlaySnakeMazes(c)) {
			c.x = rand() % maxX + 1;
			c.y = rand() % maxY + 1;
		}

		fruit = c;
	}

	void moveHeadOneSpace(Dir direction)
	{
		switch (direction) {
			case left:
				if (snake.occupied[0].x == 1)
					snake.occupied[0].x = maxX + 1;
				snake.occupied[0].x -= 1;
				break;
			case right:
				if (snake.occupied[0].x == maxX)
					snake.occupied[0].x = 0;
				snake.occupied[0].x += 1;
				break;
			case up:
				if (snake.occupied[0].y == 1)
					snake.occupied[0].y = maxY + 1;
				snake.occupied[0].y -= 1;
				break;
			case down:
				if (snake.occupied[0].y == maxY)
					snake.occupied[0].y = 0;
				snake.occupied[0].y += 1;
				break;
		} // end switch
	}

	Coord moveRtnPrev()
	{
		Coord prev = snake.occupied[0];

		moveHeadOneSpace(snake.dir);

		//The back boxes simply just follow the fronts
		Coord tmp(0, 0);
		auto size = snake.occupied.size();
		for (unsigned i = 1; i < size; ++i) {
			tmp = snake.occupied[i];
			snake.occupied[i] = prev;
			prev = tmp;
		}

		snake.hasRespondedToChangeDir = true;

		return prev;
	}

	vector<Coord>& getMazes(int level)
	{
		mazes = game::rtnMazeByLevel(level);

		return mazes;
	}

};

#endif // !ENGINE_H