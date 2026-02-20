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

        if (moveType == 1) {
            cout << "Basic Strike!\n";
            dmg = currentPwr - (target.defense / 3);
            stamina += 5;
            } else if (moveType == 2) {
                if (stamina >= 15) {
                    stamina -= 15;
                    cout << "SIGNATURE MOVE!\n";
                    dmg = (int)(currentPwr * 1.8) - (target.defense / 3);
                    } else {
                        cout << "Signature Move... but not enough Stamina! (Weak attack)\n";
                        dmg = 5;
                    }
                }
                if (isCrit) {
                    dmg *= 2;
                    cout << "   *** CRITICAL HIT! ***\n";
                }

                if (dmg < 1) dmg = 1;
                target.takeHit(dmg);
                cout << "   Result: " << target.name << " took " << dmg << " damage.\n";
                if (stamina > maxStamina) stamina = maxStamina;
            }
        };









    
    






