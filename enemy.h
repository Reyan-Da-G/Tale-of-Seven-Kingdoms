#include<iostream>
using namespace std;

class Enemy {
private:
    string name;
    int health;
    int attackPower;

public:
    
// Default constructor that initialized according to current player
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
   // Function to decrease health of enemy
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }
    // Function to decrease health of player
    int attack() const {
        return attackPower;
    }
};
