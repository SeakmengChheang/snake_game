#pragma once
#ifndef FRUIT_H
#define FRUIT_H

#include "coord.h"

class Fruit
{
public:
	int x, y;

	Fruit() = default;

	Fruit(Coord c)
	{
		x = c.x;
		y = c.y;
	}

	Coord getFruitCoord()
	{
		return { x, y };
	}
};

#endif // !FRUIT_H
