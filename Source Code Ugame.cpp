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

        Student createCharacter(string name, int classChoice) {
            if (classChoice == 1) {
                return Student(name, "Slugger", 100, 40, 28, 10, 10);
            } else if (classChoice == 2){
                return Student(name, "Judo Captain", 160, 50, 15, 20, 5);
            } else if (classChoice == 3){
                return Student(name, "Skater Boy", 80, 60, 20, 8, 30);
            }
            return Student(name, "Transfer Student", 100, 50, 20, 10, 10);
        }

        bool isPartyWipedOut(vector<Student> &party) {
            for (int i = 0; i < party.size(); i++) {
                if (!party[i].isKnockedOut()) return false;
            }
            return true;
        }

        void visitCanteen(vector<Student> &party, int &money) {
            cout << "\n=== SCHOOL CANTEEN ===\n";
            cout << "You have " << money << " Yen.\n";
            int cost = party.size() * 100;
    
        cout << "Cost to feed your gang (Full HP/Stamina): " << cost << " Yen.\n";
        if (money >= cost) {
            cout << "Buy food? (1 = Yes, 0 = No): ";
            int choice;
            cin >> choice;
            if (choice == 1) {
                money -= cost;
                for (int i = 0; i < party.size(); i++) party[i].recoverFull();
                cout << "Everyone ate Yakisoba Bread and recovered full HP & Stamina!\n";
            }
        } else {
            cout << "Not enough money to feed the gang...\n";
        }
    }

    void recruitMenu(vector<Student> &party, int reputation) {
        if (party.size() >= 3) return;

        int requiredRep = party.size() * 300;
        if (reputation >= requiredRep) {
            cout << "\n[!] Your Reputation (" << reputation << ") attracts a new follower!\n";
            cout << "Recruit a new member?\n 1. Ken (Slugger)\n 2. Goro (Judo Captain)\n 0. Skip\nSelect: ";
            int choice; cin >> choice;
            if (choice == 1) party.push_back(createCharacter("Ken", 1));
            else if (choice == 2) party.push_back(createCharacter("Goro", 2));

            if (choice != 0) cout << "New member joined the gang!\n";
        }
    }





                











    
    






