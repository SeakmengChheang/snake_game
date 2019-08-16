#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "coord.h"

using std::vector;

namespace game
{
	class Player
	{
	private:
		int score = 0;
		int level = 1;

	public:
		void increScore() { ++score; }
		int getScore() { return score; }

		void increLevel() { ++level; }
		int getLevel() { return level; }
	};

	class Speed
	{
	public:
		enum Difficulty{easy = 50, medium = 30, hard = 20,};
		Difficulty diffi;

		int calSleepTime(int score, Dir dir)
		{
			double time = (score - diffi) / -0.1;
			if (time < 75) //time is measured in ms
				//return 75;
				return dir == up || dir == down ? 100 : 75;

			return dir == up || dir == down ? time * 1.4 : time;
		}
	};

	vector<Coord> rtnMazeByLevel(int level)
	{
		vector<Coord> rtn;
		switch (level)
		{
			case 1:
				for (int i = 0; i < 5; i++) {
					rtn.emplace_back(i + 3, 3);
					rtn.emplace_back(i + 3, 8);
					rtn.emplace_back(i + 14, 3);
					rtn.emplace_back(i + 14, 8);
				}
				break;
			case 2:
				for (int i = 0; i < 10; i++) {
					rtn.emplace_back(i + 6, 3);
					rtn.emplace_back(i + 6, 7);
				}
				break;
			case 3:
				for (int i = 0; i < 3; i++) {
					rtn.emplace_back(i + 5, 3);
					rtn.emplace_back(i + 15, 3);
					rtn.emplace_back(i + 5, 8);
					rtn.emplace_back(i + 15, 8);
				}
				for (int i = 0; i < 4; i++) {
					rtn.emplace_back(4, i + 4);
					rtn.emplace_back(18, i + 4);
				}
				break;
			case 4:
				for (int i = 0; i < 10; i++) {
					rtn.emplace_back(i + 6, 1);
					rtn.emplace_back(i + 6, 10);
				}
				for (int i = 0; i < 4; i++) {
					rtn.emplace_back(1, i + 4);
					rtn.emplace_back(20, i + 4);
				}
				break;
			default:
				break;
		}

		return rtn;
	}

}

#endif // !GAME_H
