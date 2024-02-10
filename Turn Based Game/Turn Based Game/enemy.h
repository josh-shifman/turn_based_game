#pragma once
#include <iostream>
#include <list>
#include <string>
#include "team.h"
#include "monster.h"
#include <random>
#include <numeric>
#include "ability.h"

class enemy
{
public:
	Team enemy_team;
	void generate_team();
};

