#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

//ค่าพลังของตัวละคร
class Student {
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

    Student(string n, string job, int h, int stam, int atk, int def, int agi) {
        name = n; 
        jobClass = job;
        maxHp = h; hp = h;
        maxStamina = stam; stamina = stam;
        power = atk;
        defense = def;
        agility = agi;
    }

    bool isKnockedOut() { return hp <= 0; }

    void takeHit(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    void recoverFull() {
        hp = maxHp;
        stamina = maxStamina;
    }

    void attack(Student &target, int moveType) {
        int dmg = 0;
        int currentPwr = power + (rand() % 5); 
        bool isCrit = (rand() % 100) < agility; 

        cout << "  > " << name << " ";

        if (moveType == 1) { 
            cout << "พุ่งเข้าไปต่อยธรรมดา!\n";
            dmg = currentPwr - (target.defense / 3);
            stamina += 5; 
        } else if (moveType == 2) { 
            if (stamina >= 15) {
                stamina -= 15;
                cout << "ใช้สุดยอดท่าไม้ตาย!!!\n";
                dmg = (int)(currentPwr * 1.8) - (target.defense / 3);
            } else {
                cout << "พยายามใช้ท่าไม้ตาย... แต่หอบกิน (พลังกายไม่พอ)!\n";
                dmg = 5;
            }
        }

        // ระบบหลบหลีก
        int dodgeChance = target.agility / 2; 
        if (dodgeChance > 40) dodgeChance = 40; // ตันที่40% 
        
        if (rand() % 100 < dodgeChance) {
            cout << "  *** ฟึ่บ! เฉียดไปนิดเดียว!" << target.name << " อาศัยความไวหลบการโจมตีได้อย่างหวุดหวิด! ***\n";
            return; 
        }

        // คำนวณคริติคอล
        if (isCrit) {
            dmg *= 2;
            cout << "  *** คริติคอลฮิต! (เข้าจุดอ่อน) ***\n";
        }

        if (dmg < 1) dmg = 1; 
        target.takeHit(dmg);
        cout << "  > ผลลัพธ์: " << target.name << " โดนดาเมจไป " << dmg << " หน่วย\n";
        if (stamina > maxStamina) stamina = maxStamina; 
    }
};

// ระบบแถบเลือด

string drawBar(int current, int max, int length) {
    if (max <= 0) return "";
    int fill = (current * length) / max;
    if (fill < 0) fill = 0;
    if (fill > length) fill = length;
    
    string bar = "";
    for (int i = 0; i < fill; i++) bar += "█";   
    for (int i = fill; i < length; i++) bar += "░"; 
    return bar;
}

void showBattleUI(Student &player, Student &enemy) {
    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "   [ทีมผู้เล่น] " << player.name << " (" << player.jobClass << ") | โจมตี: " << player.power << " | ความเร็ว: " << player.agility << "\n";
    cout << "   HP:  [" << drawBar(player.hp, player.maxHp, 20) << "] " << player.hp << "/" << player.maxHp << "\n";
    cout << "   SP:  [" << drawBar(player.stamina, player.maxStamina, 20) << "] " << player.stamina << "/" << player.maxStamina << "\n";
    cout << "╠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╣\n";
    cout << "   [ศัตรู] " << enemy.name << " (" << enemy.jobClass << ")\n";
    cout << "   HP:  [" << drawBar(enemy.hp, enemy.maxHp, 20) << "] " << enemy.hp << "/" << enemy.maxHp << "\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
}

Student createCharacter(string name, int classChoice) {
    if (classChoice == 1) return Student(name, "เทพมวย", 100, 40, 28, 10, 10); 
    else if (classChoice == 2) return Student(name, "กัปตันรักบี้", 160, 50, 15, 20, 5); 
    else if (classChoice == 3) return Student(name, "เอซกรีฑา", 80, 60, 20, 8, 30); 
    return Student(name, "เด็กใหม่", 100, 50, 20, 10, 10); 
}

bool isPartyWipedOut(vector<Student> &party) {
    for (int i = 0; i < party.size(); i++) {
        if (!party[i].isKnockedOut()) return false; 
    }
    return true;
}

void visitCanteen(vector<Student> &party, int &money) {
    while (true) {
        cout << "\n┌────────────────────────────────────────┐\n";
        cout << "│        === โรงอาหารของโรงเรียน ===     │\n";
        cout << "└────────────────────────────────────────┘\n";
        cout << " เงินค่าขนมของคุณ: " << money << " เยน\n\n";
        int healCost = party.size() * 100; 
        
        cout << " 1. ยากิโซบะปัง (ฟื้น HP/SP ทั้งแก๊ง) - " << healCost << " เยน\n";
        cout << " 2. สนับมือเหล็ก (+พลังโจมตี 10)     - 200 เยน\n";
        cout << " 3. รองเท้าไนกี้แพนด้า (+ความเร็ว 10)  - 200 เยน\n";
        cout << " 4. เสื้อแจ็คเกตเฟอรารี่ (+พลังป้องกัน 10) - 200 เยน\n";
        cout << " 0. ออกจากร้านไปลุยต่อ\n";
        cout << " เลือกซื้อสินค้า (0-4): ";
        int choice; cin >> choice;

        if (choice == 0) {
            break; 
        } 
        else if (choice == 1) {
            if (money >= healCost) {
                money -= healCost;
                for (int i = 0; i < party.size(); i++) party[i].recoverFull();
                cout << " >> ทุกคนกินอิ่ม... พร้อมลุยต่อแล้ว!\n";
            } else cout << " >> เงินไม่พอ!\n";
        } 
        else if (choice >= 2 && choice <= 4) {
            if (money >= 200) {
                cout << "\n จะซื้อไอเทมชิ้นนี้ให้ใครดี?\n";
                for (int i = 0; i < party.size(); i++) {
                    cout << "  " << i + 1 << ". " << party[i].name << " (โจมตี: " << party[i].power << " | ป้องกัน: " << party[i].defense << " | ความเร็ว: " << party[i].agility << ")\n";
                }
                cout << " เลือกสมาชิก (1-" << party.size() << "): ";
                int target; cin >> target;
                target--; 

                if (target >= 0 && target < party.size()) {
                    money -= 200;
                    if (choice == 2) {
                        party[target].power += 10;
                        cout << " >> " << party[target].name << " สวมสนับมือ พลังโจมตีเพิ่มเป็น " << party[target].power << "!\n";
                    } else if (choice == 3) {
                        party[target].agility += 10;
                        cout << " >> " << party[target].name << " ใส่รองเท้าไนกี้ ความเร็วเพิ่มเป็น " << party[target].agility << "!\n";
                    } else if (choice == 4) {
                        party[target].defense += 10;
                        cout << " >> " << party[target].name << " สวมเสื้อแจ็คเก็ต พลังป้องกันเพิ่มเป็น " << party[target].defense << "!\n";
                    }
                } else cout << " >> เลือกเป้าหมายไม่ถูกต้อง... ยกเลิกการซื้อ\n";
            } else cout << " >> เงินไม่พอ!\n";
        } else {
            cout << " >> เลือกเมนูไม่ถูกต้อง\n";
        }
    }
}

void recruitMenu(vector<Student> &party, int reputation) {
    if (party.size() >= 3) return; 

    int requiredRep = party.size() * 300; 
    
    if (reputation >= requiredRep) {
        cout << "\n========================================\n";
        cout << "[!] ค่าชื่อเสียงของคุณ (" << reputation << ") ดึงดูดความสนใจจากนักเรียนคนอื่น!!\n";
        cout << "ต้องการรับลูกน้องเพิ่มไหม?\n1. เคน (เทพมวย)\n2. บาจิ (กัปตันรักบี้)\n0. ข้ามไปก่อน\nเลือก: ";
        int choice; cin >> choice;
        
        if (choice == 1) party.push_back(createCharacter("เคน", 1));
        else if (choice == 2) party.push_back(createCharacter("บาจิ", 2));
        
        if (choice != 0) cout << ">> ลูกน้องใหม่เข้าร่วมแก๊งแล้ว!!\n";
        cout << "========================================\n";
    }
}

//เริ่มต้นโปรแกรม
int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    srand(time(0)); 
    int money = 150;
    int reputation = 0;

    cout << "╔════════════════════════════════════════╗\n";
    cout << "║    มัธยมซูซูรัน: ศึกวัยรุ่นนักเลง      ║\n";
    cout << "╚════════════════════════════════════════╝\n";

    cout << "\nกรุณาใส่ชื่อของคุณ: ";
    string pName; cin >> pName;
    
    cout << "\n┌────────────────────────────────────────┐\n";
    cout << "│ เลือกสายการเล่น                        │\n";
    cout << "│ 1. เทพมวย (โจมตีรุนแรง)                │\n";
    cout << "│ 2. กัปตันรักบี้ (ถึกทนทาน)               │\n";
    cout << "│ 3. เอซกรีฑา (รวดเร็ว/คริติคอล)        │\n";
    cout << "└────────────────────────────────────────┘\n";
    cout << "เลือก (1-3): ";
    int pClass; cin >> pClass;

    vector<Student> party;
    party.push_back(createCharacter(pName, pClass));

    vector<Student> enemies;
    // พารามิเตอร์: ชื่อ, ฉายา, HP, Stamina, โจมตี, ป้องกัน, ความเร็ว
    enemies.push_back(Student("ยามาดะ", "เด็กเกเรหน้าห้อง", 100, 0, 18, 8, 10)); // ด่าน 1
    enemies.push_back(Student("ทานากะ", "สารวัตรนักเรียน", 150, 0, 25, 12, 15)); // ด่าน 2
    enemies.push_back(Student("เคนจิ", "รองหัวหน้าแก๊ง", 220, 0, 32, 18, 20)); // ด่าน 3
    enemies.push_back(Student("ริว", "หัวหน้าแก๊งสายชั้น", 350, 50, 42, 25, 30)); // ด่าน 4
    enemies.push_back(Student("ไทกิ", "บอสใหญ่ประจำโรงเรียน", 550, 100, 55, 35, 40)); // ด่าน 5

    int stage = 0;

    while (stage < enemies.size() && !isPartyWipedOut(party)) {
        
        if (stage > 0) recruitMenu(party, reputation); 

        Student &enemy = enemies[stage];
        cout << "\n\n████████████████████████████████████████████████████████\n";
        cout << "  STAGE " << stage + 1 << " ปะทะ " << enemy.name << " (" << enemy.jobClass << ")\n";
        cout << "████████████████████████████████████████████████████████\n";

        while (!enemy.isKnockedOut() && !isPartyWipedOut(party)) {
            
            // เทิร์นของผู้เล่น
            for (int i = 0; i < party.size(); i++) {
                if (party[i].isKnockedOut()) continue; 

                showBattleUI(party[i], enemy);

                cout << "┌────────────────────────────────┐\n";
                cout << "│ ตัวเลือกการต่อสู้              │\n";
                cout << "│ 1. โจมตีธรรมดา (ฟื้น SP +5)    │\n";
                cout << "│ 2. ท่าไม้ตาย!! (ใช้ SP 15)       │\n";
                cout << "└────────────────────────────────┘\n";
                cout << ">> " << party[i].name << " จะทำอะไรดี?: ";
                
                int act; cin >> act;
                cout << "\n";
                party[i].attack(enemy, act);
                
                if (enemy.isKnockedOut()) break; 
            }

            if (enemy.isKnockedOut()) {
                cout << "\n *** " << enemy.name << " ถูกจัดการแล้ว!!! *** \n";
                int repGain = 150 * (stage + 1);
                int moneyGain = 200 * (stage + 1);
                reputation += repGain;
                money += moneyGain;
                cout << "ได้รับชื่อเสียง " << repGain << " แต้ม!! (รวม: " << reputation << ")\n";
                cout << "ไถเงินมาได้ " << moneyGain << " เยน!! (รวม: " << money << " เยน)\n";
                break; 
            }

            // เทิร์นของศัตรู
            cout << "\n[เทิร์นของศัตรู]\n";
            int targetIndex;
            do { targetIndex = rand() % party.size(); } while (party[targetIndex].isKnockedOut()); 
            enemy.attack(party[targetIndex], 1);
        }
        
        stage++; 

        // แวะโรงอาหาร
        if (stage < enemies.size() && !isPartyWipedOut(party)) {
            visitCanteen(party, money);
        }
    }

    cout << "\n=========================================================================================\n";
    if (isPartyWipedOut(party)) {
        cout << R"(
   _____          __  __  ______    ____  _    _ ______ _____  
  / ____|   /\   |  \/  ||  ____|  / __ \| |  | |  ____|  __ \ 
 | |  __   /  \  | \  / || |__    | |  | | |  | | |__  | |__) |
 | | |_ | / /\ \ | |\/| ||  __|   | |  | | |  | |  __| |  _  / 
 | |__| |/ ____ \| |  | || |____  | |__| \ \_/ /| |____| | \ \ 
  \_____/_/    \_\_|  |_||______|  \____/ \___/ |______|_|  \_\
        )" << "\n\n";
        cout << "\t[ จบเกม... เส้นทางนักเลงจบลงแค่นี้ ]\n";
        cout << "\tแก๊งของคุณโดนกระทืบจมกองเลือด หยอดน้ำข้าวต้มไปอีกนานไอ้พวกอ่อนหัด!\n";
    } else {
        cout << R"(
 __      __ _____  _____  _______  ____   _____ __     __  _ 
 \ \    / /|_   _|/ ____||__   __|/ __ \ |  __ \\ \   / / | |
  \ \  / /   | | | |        | |  | |  | || |__) |\ \_/ /  | |
   \ \/ /    | | | |        | |  | |  | ||  _  /  \   /   | |
    \  /    _| |_| |____    | |  | |__| || | \ \   | |    |_|
     \/    |_____|\_____|   |_|   \____/ |_|  \_\  |_|    (_)
        )" << "\n\n";
        cout << "\t*** โคตรตึง โคตรอันตราย!! ไม่มีใครหยุดคุณได้อีกแล้ว!! ***\n";
        cout << "\tคุณล้มบอสใหญ่ และก้าวขึ้นสู่จุดสูงสุดของซูซูรันได้สำเร็จ!!\n";
    }
    cout << "=========================================================================================\n\n";

    return 0;
}





                











    
    






