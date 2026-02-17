#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Student {
    public:
    string name;
    string jobClass;
    int stamina;
    int maxStamina;
    int power;
    int agility;

    Student(string n, string job, int hp, int atk, int agi) {
        name = n;
        jobClass = job;
        stamina = hp;
        maxStamina = hp;
        power = atk;
        agility = agi;
    }
    






