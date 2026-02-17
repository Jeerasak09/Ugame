#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Student{
    public:
    string name;
    string jobClass;
    int hp;
    int maxHp;
    int stamina;
    int maxStamina;
    int power;
    int defense;
    int agility;

    Student(string n, string job, int h, int stam, int atk, int def, int agi){
        name = n;
        jobClass = job;
        maxHp = h;
        hp = h;
        maxStamina = stam;
        stamina = stam;
        power = atk;
        defense = def;
        agility = agi;
    }

    bool isKnockedOut(){
        return hp <= 0;
    }

    void takeHit(int dmg){
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    void recoverFull(){
        hp = maxHp;
        stamina = maxStamina;
    }

    void attack(Student &target, int moveType){
        int dmg = 0;
        int currentPwr = power + (rand()%5);
        bool isCrit = (rand()%100) < agility;
        
        cout << "> " << name << " (" << jobClass << ") ";







    
    






