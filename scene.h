#include<iostream>
using namespace std;

class Scene{
private:
    string description;
    string choice1;
    string choice2;
    int nextscene1;
    int nextscene2;
    
public:
    int progress;
    int coins;
    int health;
    
    Scene() {
        description = "";
        choice1 = "";
        choice2 = "";
        nextscene1 = -1;
        nextscene2 = -1;
        progress = 0;
        coins = 0;
    }
    
    Scene(string desc, string ch1, string ch2, int next1, int next2, int prog, int coin, int heal) {
        description = desc;
        choice1 = ch1;
        choice2 = ch2;
        nextscene1 = next1;
        nextscene2 = next2;
        progress = prog;
        coins = coin;
        health = heal;
    }
    
    void gameOver() const {
        system("clear");
        cout << "\nGame Over! You are dead.\n";
        cout << "Press 5 to load last saved game!\n";
        cout << "Press 4 to return to main menu!\n";
    }

    void gameComplete() const {
        system("clear");
        cout << "\nYou have already completed the game.\n";
        cout << "Press 4 to return to main menu!\n";
        cout << "Press 0 to exit the game\n";
    }

    void displayScene() const {
        cout << description << endl << endl;
        if (nextscene1 == -3 && nextscene2 == -3) {
            cout << choice1 << endl;
            cout << choice2 << endl;
        } else if (nextscene1 != -1 && nextscene2 != -1) {
            cout << "1. " << choice1 << endl;
            cout << "2. " << choice2 << endl;
        } else {
            cout << "Game over! You have died!\n";
            cout << choice1 << endl;
            cout << choice2 << endl;
        }
    }

    int getnextScene(int choice){
        if (choice == 1) {
            return nextscene1;
        } else if (choice == 2) {
            return nextscene2;
        } else {
            return -1; 
        }
    }
};