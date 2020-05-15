#pragma once
class Simulation
{
	int num_soldiers; //how many soldiers
	int num_monsters; //how many monsters
	int days; //how long simulation will take

public:
	Simulation(int, int, int);

	void startsim();
	void setsize(int, int);
	void setsoldiers(int);
	void setmonsters(int);
	void countdays();
	void endsim();
};

