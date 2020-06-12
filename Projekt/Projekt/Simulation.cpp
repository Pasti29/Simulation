#include "Simulation.h"

Simulation::Simulation(int s, int m)
{
	this->s = s;
	this->m = m;
}

bool Simulation::areAlive(vector <Unit*> units) { return units.empty(); }

vector <Unit*>& Simulation::getSoldiers() { return soldiers; }

vector <Unit*>& Simulation::getMonsters() { return monsters; }

void Simulation::setsoldiers(Map& map)
{
	UnitFactory* factory;
	factory = new SoldierFactory;
	factory->makeFirst_type((ceil((double)s / 2)), soldiers);
	factory->makeSecond_type((s / 2), soldiers);
	for (int i = 0; i < s; i++) //Initiates unit's position then check if they are occupied
	{
		do {
			soldiers[i]->setFirstX(map.getX());
			soldiers[i]->setFirstY(map.getY());
		} while (map.IsOccupied(soldiers, monsters, soldiers[i]->getXpos(), soldiers[i]->getYpos(), i, 'S'));
		map.setMap(soldiers[i]->getYpos(), soldiers[i]->getXpos(), soldiers[i]->getPoint());
	}
}

void Simulation::setmonsters(Map& map)
{
	UnitFactory* factory;
	factory = new MonsterFactory;
	factory->makeFirst_type((ceil((double)m / 2)), monsters);
	factory->makeSecond_type((m / 2), monsters);
	for (int i = 0; i <m; i++) //Initiates unit's position then check if they are occupied
	{
		do {
			monsters[i]->setFirstX(map.getX());
			monsters[i]->setFirstY(map.getY());
		} while (map.IsOccupied(soldiers, monsters, monsters[i]->getXpos(), monsters[i]->getYpos(), i, 'M'));
		map.setMap(monsters[i]->getYpos(), monsters[i]->getXpos(), monsters[i]->getPoint());
	}
}

void Simulation::moveunits(vector <Unit*>& friendly, vector <Unit*>& enemy, Map& map)
{
	for (int i = 0; i < friendly.size(); i++) //Searches for nearest enemy
	{
		int distm = 1000, idenemy = 0;
		for (int j = 0; j < enemy.size(); j++) //Calculates distance between every unit and its enemies
		{
			int distm_temp = sqrt(pow((friendly[i]->getXpos() - enemy[j]->getXpos()), 2) + pow((friendly[i]->getYpos() - enemy[j]->getYpos()), 2));
			if (distm_temp < distm) 
			{
				distm = distm_temp;
				idenemy = j; //Saves the nearest enemy's id
			}
		}
		if ((distm == 1) && (friendly[i]->getXpos() == enemy[idenemy]->getXpos() || friendly[i]->getYpos() == enemy[idenemy]->getYpos())) //Checks if enemy is near enough to attack
		{
			friendly[i]->attack(enemy[idenemy]);
			if (enemy[idenemy]->getHealth() <= 0)
			{
				map.setMap(enemy[idenemy]->getYpos(), enemy[idenemy]->getXpos(), ' ');
				enemy.erase(enemy.begin() + idenemy); //Erases enemy unit from vector if it's dead
				if (areAlive(enemy)) break;
			}
		}
		//movement:
		else
		{
			map.setMap(friendly[i]->getYpos(), friendly[i]->getXpos(), ' '); //Changes previously occupied position on map to an empty space


			if (friendly[i]->getXpos() < enemy[idenemy]->getXpos() && friendly[i]->getXpos() < (map.getX() + 1)) //Moves the unit one point right if the nearest enemy is in this direction
			{
				if (map.getMap(friendly[i]->getYpos(), friendly[i]->getXpos() + 1) != ' ') friendly[i]->setXpos(friendly[i]->getXpos()); //Makes sure two units don't stand on the same position
				else friendly[i]->setXpos(friendly[i]->getXpos() + 1);
			}
			else if (friendly[i]->getXpos() > enemy[idenemy]->getXpos() && friendly[i]->getXpos() > 0)
			{
				if (map.getMap(friendly[i]->getYpos(), friendly[i]->getXpos() - 1) != ' ') friendly[i]->setXpos(friendly[i]->getXpos());
				else friendly[i]->setXpos(friendly[i]->getXpos() - 1);
			}
			else if (friendly[i]->getYpos() < enemy[idenemy]->getYpos() && friendly[i]->getYpos() < (map.getY() + 1))
			{
				if (map.getMap(friendly[i]->getYpos() + 1, friendly[i]->getXpos()) != ' ') friendly[i]->setYpos(friendly[i]->getYpos());
				else friendly[i]->setYpos(friendly[i]->getYpos() + 1);
			}
			else  if (friendly[i]->getYpos() > enemy[idenemy]->getYpos() && friendly[i]->getYpos() > 0)
			{
				if (map.getMap(friendly[i]->getYpos() - 1, friendly[i]->getXpos()) != ' ') friendly[i]->setYpos(friendly[i]->getYpos());
				else friendly[i]->setYpos(friendly[i]->getYpos() - 1);
			}

			map.setMap(friendly[i]->getYpos(), friendly[i]->getXpos(), friendly[i]->getPoint()); //Changes position on the map to unit's point - its visual representation
		}
	}
}
