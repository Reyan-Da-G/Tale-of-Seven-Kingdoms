#include<iostream>
using namespace std;
// This the character class 
class Character{
protected:
    string name;
    string filename;
    string weapon;
    int health;
    int progress;
    int coins;
public: 
    // Default constructor to initialize member variables
    Character(){
        name = "";
        filename = "";
        weapon = "";
        health = 100;
        progress = 0;
        coins = 0;
    }

    // This function is used when selecting the character
    void updateName(string name, string weapon, string file){
        this->name = name;
        this->weapon = weapon;
        filename = file;
    }

    // Function used to display current progress and stats during gameplay
    void displayStats() const {
        cout << "Progress - " << progress << "%";
        cout << "\t\t <- " << name << " ->";
        cout << "\t\t    Health - " << health << "%\n\n";
        cout << "Coins - " << coins;
        cout << "\t\t\t\t\t    Weapon - " << weapon << endl;
        cout << "------------------------------------------------------------------\n";
        cout << "Press (3) to recover health\t\t    Press (4) for main menu\n";
        cout << "------------------------------------------------------------------\n\n";
    }

    // Function to recover health any time during gameplay
    void recoverhealth(int coin){
        if(health >= 100){
            cout << "Health is already full!\n";
            sleep(1);
        }else if(coin >= 200){
            health += 20;
            if(health > 100) health = 100;
            coins -= 200;
            cout << "\nHealth recovered!\n";
            sleep(1);
        }
        else{
            cout << "\nInsufficient coins! Cannot recover health!\n";
            sleep(1);
        }
    }

    // Function to set values when game is loaded from saved file
    void setValues(string name, string weapon, string file, int heal, int prog, int coin){
        this->name = name;
        this->weapon = weapon;
        filename = file;
        health = heal;
        progress = prog;
        coins = coin;
    }

    // Function to update current stats after each scene during gameplay
    void updateStats(int prog, int heal, int coin){
        progress += prog;
        if(progress > 100) progress = 100;
        
        health += heal;
        if(health < 0) health = 0;
        else if (health > 100) health = 100;

        coins += coin;  
    }
    
};
