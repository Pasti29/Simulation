#pragma once
#include <vector>
#include "Unit.h"

using namespace std;

class UnitFactory
{
public:
	virtual void makeFirst_type(int, vector <Unit*>&) = 0; //Creates unit objects in certain first type (Sergeant or Zombie)
	virtual void makeSecond_type(int, vector <Unit*>&) = 0; //Creates unit objects in certain second type (Officer or Demon)
};

