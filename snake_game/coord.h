#pragma once
#ifndef COORD_H
#define COORD_H

class Coord
{
public:
	int x;
	int y;

	Coord(int xCoord, int yCoord) {
		x = xCoord;
		y = yCoord;
	}

	bool operator==(const Coord& c2)
	{
		if (x == c2.x && y == c2.y)
			return true;
		return false;
	}
};

#endif // !COORD_H
