#include<iostream>
using namespace std;

class Enemy {
private:
    string name;
    int health;
    int attackPower;

public:
    Enemy(string playername) {
        if(playername == "Jon Snow"){
            name = "Night King";
            health = 100;
            attackPower = 20;
        }else if (playername == "Rob Stark"){
            name = "The Hound";
            health = 85;
            attackPower = 10;
        }
    }

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    int attack() const {
        return attackPower;
    }
};