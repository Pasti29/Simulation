#pragma once
#include <vector>
#include <iostream>
#include "Unit.h"
#include "UnitFactory.h"
#include "SoldierFactory.h"
#include "MonsterFactory.h"
#include "Map.h"

using namespace std;

class Simulation
{
	int s, m; //s - innitial number of soldiers; m - initial number of monsters
	vector <Unit*> soldiers, monsters; //Vector with certain type of objects

public:
	Simulation(int = 2, int = 2);

	bool areAlive(vector <Unit*>); //Returns true when given vector is not empty
	vector <Unit*>& getSoldiers(); //Gets referention of vector soldiers
	vector <Unit*>& getMonsters(); //Gets referention of vector soldiers
	void setsoldiers(Map&); //Creates all soldier objects, gives them initial position and updates elements from map array used by soldiers
	void setmonsters(Map&); //Creates all monster objects, gives them initial position and updates elements from map array used by monsters
	void moveunits(vector <Unit*>&, vector <Unit*>&, Map&); //Self explenatory
};

