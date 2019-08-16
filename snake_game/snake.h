#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "coord.h"

using std::vector;

enum Dir
{
	left,
	right,
	up,
	down
};

struct Snake
{
	Dir dir;
	bool hasRespondedToChangeDir = false;
	vector<Coord> occupied;

	Snake()
	{
		dir = right;

		Coord c{ c.x = 10, c.y = 2 };
		occupied.push_back(c);
	}

	void addOneLength()
	{
		int lastX = occupied[occupied.size() - 1].x;
		int lastY = occupied[occupied.size() - 1].y;

		switch (dir) {
			case left:
				occupied.emplace_back(lastX + 1, lastY);
				break;
			case right:
				occupied.emplace_back(lastX - 1, lastY);
				break;
			case up:
				occupied.emplace_back(lastX, lastY + 1);
				break;
			case down:
				occupied.emplace_back(lastX, lastY - 1);
				break;
		} // end switch
	}

	void resetDefault()
	{
		occupied.clear();
		dir = right;

		Coord c{ c.x = 10, c.y = 2 };
		occupied.push_back(c);
	}

	void changeDir(Dir direction)
	{
		switch (direction) {
			case left:
				if (dir != right)
					dir = left;
				break;
			case right:
				if (dir != left)
					dir = right;
				break;
			case up:
				if (dir != down)
					dir = up;
				break;
			case down:
				if (dir != up)
					dir = down;
				break;
		} // end switch
		hasRespondedToChangeDir = false;
	}

};

#endif // !SNAKE_H

