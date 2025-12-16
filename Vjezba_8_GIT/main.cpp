#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. Forward deklaracije - ovo rjesava tvoj error 'Unknown type name'
class Enemy;
class Player;

// 2. Apstraktna bazna klasa
class GameCharacter {
protected:
    string name;
    int health;
    int maxHealth;
public:
    GameCharacter(string n, int h) : name(n), health(h), maxHealth(h) {}
    virtual ~GameCharacter() {}

    virtual void displayStatus() const = 0;
    virtual void specialAbility() = 0;

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
    int getHealth() const { return health; }
};

// 3. Apstraktna klasa Enemy (mora biti prije Playera ako Player koristi Enemy*)
class Enemy : public GameCharacter {
protected:
    int difficulty;
public:
    Enemy(string n, int h, int d) : GameCharacter(n, h), difficulty(d) {}
    virtual void attackPlayer(Player* target) = 0;
};

// 4. Apstraktna klasa Player
class Player : public GameCharacter {
protected:
    int score;
public:
    Player(string n, int h) : GameCharacter(n, h), score(0) {}
    virtual void attackEnemy(Enemy* target) = 0;
    void addScore(int points) { score += points; }
};

// --- Konkretne klase ---

class Warrior : public Player {
    bool shieldActive = false;
public:
    Warrior(string n) : Player(n, 120) {}
    void displayStatus() const override {
        cout << "[Warrior] " << name << " | HP: " << health << " | Score: " << score << endl;
    }
    void attackEnemy(Enemy* target) override {
        if (target && target->isAlive()) {
            target->takeDamage(20);
            if (!target->isAlive()) addScore(10);
        }
    }
    void specialAbility() override { shieldActive = true; cout << name << " dize stit!\n"; }
};

class Mage : public Player {
    int mana = 100;
public:
    Mage(string n) : Player(n, 80) {}
    void displayStatus() const override {
        cout << "[Mage] " << name << " | HP: " << health << " | Mana: " << mana << endl;
    }
    void attackEnemy(Enemy* target) override {
        if (target && target->isAlive()) {
            int damage = (mana >= 20) ? 40 : 20;
            if (mana >= 20) mana -= 20;
            target->takeDamage(damage);
            if (!target->isAlive()) addScore(10);
        }
    }
    void specialAbility() override { if (health > 50) cout << name << " se teleportira!\n"; }
};

class Gnome : public Enemy {
public:
    Gnome(string n) : Enemy(n, 90, 3) {}
    void displayStatus() const override {
        cout << "[Gnome] " << name << " | HP: " << health << endl;
    }
    void attackPlayer(Player* target) override {
        if (target && target->isAlive()) target->takeDamage(5 * difficulty);
    }
    void specialAbility() override { if (health > 20) cout << name << " svira trubu!\n"; }
};

class Boss : public Enemy {
public:
    Boss(string n) : Enemy(n, 300, 8) {}
    void displayStatus() const override {
        cout << "[BOSS] " << name << " | HP: " << health << endl;
    }
    void attackPlayer(Player* target) override {
        if (target && target->isAlive()) target->takeDamage(10 * difficulty);
    }
    void specialAbility() override {
        health = min(300, health + 50);
        cout << name << " se regenerira!\n";
    }
};

int main() {
    Warrior* conan = new Warrior("Conan");
    Mage* merlin = new Mage("Merlin");
    Gnome* gnomeo = new Gnome("Gnomeo");
    Gnome* sneaky = new Gnome("Sneaky");
    Boss* dragon = new Boss("Dragon");

    vector<GameCharacter*> likovi = {conan, merlin, gnomeo, sneaky, dragon};

    // Simulacija borbe iz zadatka
    conan->attackEnemy(gnomeo);
    merlin->attackEnemy(sneaky);
    gnomeo->attackPlayer(conan);
    dragon->attackPlayer(merlin);

    cout << "\n--- Status nakon borbe ---" << endl;
    for (auto l : likovi) l->displayStatus();

    for (auto l : likovi) delete l;
    return 0;
}