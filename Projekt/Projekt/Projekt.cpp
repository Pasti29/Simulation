﻿#include <iostream>
#include "Map.h"
#include "Simulation.h"
#include <time.h>
#include <limits>

using namespace std;

int main()
{
#undef max
    srand(time(NULL));
    int x, y, s, m;

    do {
        cout << "Map width from 2 to 50 (X): ";
        cin >> x;
        if (cin.fail()) //Check if user enter valid input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max() , '\n');
        }
    } while (x < 2 || x > 50);
    do {
        cout << "Map height from 2 to 50 (Y): ";
        cin >> y;
        if (cin.fail()) //Check if user enter valid input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (y < 2 || y > 50);
    do {
        cout << "Set number of soldiers (Max " << (x * y) - 1 << " soldiers): " << endl;
        cin >> s;
        if (cin.fail()) //Check if user enter valid input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (s < 1 || s >(x * y) - 1);
    do {
        cout << "Set number of monsters (Max " << (x * y) - s << " monsters): " << endl;
        cin >> m;
        if (cin.fail()) //Check if user enter valid input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (m < 1 || m> (x * y) - s);

    Map map(x, y);
    Simulation sim(s, m);
    sim.setsoldiers(map);
    sim.setmonsters(map);
    map.draw();
    while(!sim.areAlive(sim.getSoldiers())&&!sim.areAlive(sim.getMonsters()))
    {
        sim.moveunits(sim.getSoldiers(), sim.getMonsters(), map);
        sim.moveunits(sim.getMonsters(), sim.getSoldiers(), map);
        map.draw();
        cout << endl;
    }
    if (sim.areAlive(sim.getSoldiers()))
    {
        Sleep(500);
        system("cls");
        cout << "Monsters won";
    }
    else
    {
        Sleep(500);
        system("cls");
        cout << "Soldiers won";
    }
}

