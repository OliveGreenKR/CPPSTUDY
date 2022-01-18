#pragma once

//미리 컴파일-> 공용사용할 것들 넣어주기

#include <Windows.h>
#include <iostream>
#include <vector>
#include "types.h"
#include <queue>
#include <map>

using namespace std;

struct Pos
{
	bool operator==(Pos& pos)
	{return pos.x == x && pos.y == y ;}

	bool operator!=(Pos& pos)
	{return !( *this == pos); }

	bool operator<(const Pos& other) const 
	{
		if (y != other.y)
			return y < other.y;
		else
			return x < other.x;
	}

	Pos operator+(Pos& pos)
	{
		Pos tmp;
		tmp.y = y + pos.y;
		tmp.x = x + pos.x;

		return tmp;
	}

	Pos operator-(Pos& pos)
	{
		Pos tmp;
		tmp.y = y - pos.y;
		tmp.x = x - pos.x;
		return tmp;
	}

	Pos& operator+=(Pos& pos)
	{
		x += pos.x;
		y += pos.y;
		return *this;
	}

	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4,
};