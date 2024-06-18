#include<iostream>
#include<fstream>
#include<unistd.h>    // for sleep function
#include"character.h"
#include"scene.h"
#include"enemy.h"

class Game : public Character{   

private:
    
    static const int scenessize = 200;     // Size of total scenes
    static int currentscene;       
    Scene *scenes;            
    bool autoSave;


public:
    Game(){       
        scenes = new Scene[scenessize];
        autoSave = false;
        displayMainMenu();       
    }
    
    ~Game(){
        delete []scenes;
    }
 
void autoSavegame() const {
    ofstream file("savegame.txt");
    if (file.is_open()) {
        file << name << endl;
        file << weapon << endl;
        file << filename << endl;
        file << health << endl;
        file << progress << endl;
        file << coins << endl;
        file << currentscene;
        file.close();
    } else cout << "Error opening file!";
}

void loadScenes(const string filename){
    
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < scenessize; i++) {
            string desc;
            getline(file,desc);

            string choice1, choice2;
            getline(file, choice1);
            getline(file, choice2);

            int next1, next2;
            file >> next1 >> next2;
            file.ignore();
            
            int progress, coins, health;
            file >> progress >> coins >> health;
            file.ignore();
            
            scenes[i] = Scene(desc, choice1, choice2, next1, next2, progress, coins, health);
        }
        file.close();
    }
    else cout << "Unable to open scenes file";
}

void displayMainMenu(){
    int choice;
    
    do {
        system("clear");
        
        ifstream file("mainmenu.txt");        
        if(file.is_open()){
            string line;
            while(getline(file,line)){
                cout << line << endl;
            }
            file.close();
        } else cout << "Error opening main menu file!\n";
        
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                startNewGame();
                break;
            case 2:
                loadGame();
                break;
            case 3:
                displayInstructions();
                break;
            case 4:
                exitGame();
            default:
                cout << "Invalid choice! Please try again.\n";
                sleep(1);
        }

    } while (choice != 4);
}

void startNewGame() {
    
    system("clear");
    cout << "\n\t\t\tStarting a new game...\n";
    sleep(1);
    
    // Intro for the game
    system("clear");
    ifstream intro_file("intro.txt");      
    if(intro_file.is_open()){
        string line;
        while(getline(intro_file,line)){
            cout << line << endl;
            // sleep(1); 
        }
        intro_file.close();
    } else cout << "Error opening intro file!";
    
    // Character selection
    system("clear");
    ifstream file("charactermenu.txt");     
    if(file.is_open()){
        string line;
        while(getline(file,line)){   
            cout << line << endl;
        }
        file.close();
    } else cout << "Error opening character file!\n";
    
    // Character input validation check
    while(true){
        cout << "Choose your character: ";
        char choice;
        cin >> choice;
        if(choice == '1'){
            updateName("Jon Snow","Sword","JONSNOW.txt");
            break;
        } else if (choice == '2'){
            updateName("Rob Stark","Bow","ROBSTARK.txt");
            break;
        } else {
            cout << "Invalid choice! Choose between above 2\n";
            sleep(1);
        }
    }
    
    // Load scene in backend based on character selected
    loadScenes(filename);      
    
    cout << "\n\nYou have choosen " << name << endl;
    cout << "\n\nDo you want to turn on the autosave feature?\n";
    cout << "\nPress (Y) for yes and (N) for no...";

    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') {
        cout << "\nAuto save feature turned on!\n";
        autoSave = true;
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    else if (ch == 'N' || ch == 'n') {
        cout << "\nAuto save feature is off! \nYou can still save the game manually by pressing (6) anytime.\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    } else {
        cout << "Invalid choice!\n";
        cout << "\nStarting new game without autosave...\n";
        sleep(1);
    }

    playGame(0);      
}

void combat() {
    Enemy enemy(name);
    system("clear");
    cout << "You have encountered " << enemy.getName() << " in a direct combat!\n";
    cout << "\\t\t\tnIts time to fight!\n";
    sleep(2);
    while (enemy.getHealth() > 0 && health > 0) {
        system("clear");
        cout << "======================== < - " << enemy.getName() << " - > =======================\n\n";
        cout << "\nEnemy Health: " << enemy.getHealth() << "\t\t\t\tYour Health: " << health << "\n";
        cout << "\nYour weapon: " << weapon << "\t\t\t\tYour coins: " << coins << "\n";
        cout << "\n 1. Attack \n 2. Defend \n 3. Recover health\n" ;
        int choice;
        cin >> choice;
        if (choice == 1) {
            int damage = rand() % 20 + 10; // Player attack damage
            enemy.takeDamage(damage);
            cout << "You attacked the enemy and dealt " << damage << " damage.\n";
            sleep(1);
            if (enemy.getHealth() > 0) {
                health -= enemy.attack();
                cout << "Enemy attacked you and dealt " << enemy.attack() << " damage.\n";
                sleep(1);
            }
        } else if (choice == 2) {
            cout << "You defended enemy attack!\n";
            sleep(1);
            continue;
        }else if (choice == 3){
            recoverhealth(coins);
            continue;
        } else {
            cout << "Invalid choice!\n";
            continue;
        }
            sleep(1);
    }
    
    if (health <= 0) {
        cout << "You have been defeated by " << enemy.getName() << "!\n";
        sleep(1);
        handleGameOver();
    } else if (enemy.getHealth() <= 0) {
        cout << "Congratulations! You have defeated the enemy!\n";
        coins += 300; // Reward for defeating the enemy
    }
    sleep(2);
}

void handleGamecomplete(){
    while (true) {
        string input;
        int choice = -1;
        scenes[currentscene].gameComplete();
        cout << "Enter your choice: ";
        cin >> input;
        if (input.size() == 1 && input[0] >= '0' && input[0] <= '5') {
            choice = input[0] - '0';
        } else {
            cout << "Invalid choice! Please enter a valid number.\n";
            sleep(1);
            continue; 
        }
        if (choice == 4) {
            displayMainMenu();
            return; 
        } else if (choice == 0) {
            exitGame();
        } else {
            cout << "Invalid choice! Please enter 4 or 0 to exit.\n";
        }
    }
}

void handleGameOver() {
    while (true) {
        string input;
        int choice;
        scenes[currentscene].gameOver();
        cout << "Current health: " << health << endl;
        cout << "Enter your choice: ";
        cin >> input;
        if (input.size() == 1 && input[0] >= '0' && input[0] <= '5') {
            choice = input[0] - '0';
        } else {
            cout << "Invalid choice! Please enter a valid number.\n";
            sleep(1);
            continue; 
        }
        if (choice == 5) {
            loadGame();
            break; 
        } else if (choice == 4) {
            displayMainMenu();
            return; 
        } else {
            std::cout << "Invalid choice! Please enter 4 or 5.\n";
        }
    }
}

void playGame(int sceneIndex) {
    while (true) {
        system("clear");
        
        displayStats();     
        scenes[sceneIndex].displayScene();    
        
        string input;
        int choice = -1;
        cout << "\nChoose an option: ";
        cin >> input;

        // Checking if the input is in range and not a string
        if (input.size() == 1 && input[0] >= '0' && input[0] <= '6') {
            choice = input[0] - '0';
        } else {
            cout << "Invalid choice! Please enter a valid number between 0 and 6.\n";
            sleep(1);
            continue; 
        }

        // Storing current scene number for backup
        currentscene = sceneIndex;
        
        // Checking user input from 3-6
        switch(choice){
            case 0:
                exitGame();
            case 3:
                recoverhealth(coins);
                continue;
            case 4:
                displayMainMenu();
                return;
            case 5:
                loadGame();
                continue;
            case 6:
                saveGame();
                continue;                
        }

        int nextScene = scenes[sceneIndex].getnextScene(choice);

        // Checking player health
        if (health <= 0) {
            handleGameOver();
            continue;
        } 
        
        if (nextScene == -1) {
            handleGameOver();
            continue;
        } else if (nextScene == -3) {
            handleGamecomplete();
            continue;
        } else if (nextScene == 110) {
            combat();
        }

        // Upadates player stats accoring to scene
        updateStats(scenes[sceneIndex].progress, scenes[sceneIndex].health, scenes[sceneIndex].coins);

        if (autoSave) {   
            autoSavegame();      // Saves game automatically if enabled
        }

        sceneIndex = nextScene;   // Changing next scene index   
    } 
}

void loadGame(){
    system("clear");
    cout << "Loading game...\n";
    
    ifstream file("savegame.txt");
    if(file.is_open()){
        
        string name,weapon,filenm;
        int health,progress,coins,sceneno;
        getline(file,name);
        getline(file,weapon);       
        getline(file,filenm);
        file >> health >> progress >> coins >> sceneno;
        
        progress = progress - 5;
        setValues(name,weapon,filenm,health,progress,coins);
        
        loadScenes(filename);
        currentscene = sceneno;
        
        file.close();
        
        sleep(1);
        cout << "Game loaded successfuly!\n";
        cout << "\nPress Enter to continue...";
        cin.ignore(); 
        cin.get();
        
        playGame(currentscene); 
    }
    else {
        sleep(1);
        cout << "No saved game found!\n";
        cout << "\nPress Enter to return to main menu...";
        cin.ignore();
        cin.get();
    }
}

void saveGame(){
    cout << "\nSaving game...\n";
    sleep(1);
    
    ofstream file("savegame.txt");
    if(file.is_open()){
        file << name << endl;
        file << weapon << endl;
        file << filename << endl;
        file << health << endl;
        file << progress << endl;
        file << coins << endl;
        file << currentscene;
        file.close();
    } else cout << "Error opening file!";
    
    cout << "Game saved successfully...\n";
    sleep(2);
    
    playGame(currentscene); 
}

void displayInstructions(){
    system("clear");
    
    ifstream file("instructions.txt");
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            cout << line << endl;
        }
        file.close();
    }
    else cout << "Error opening file\n";
        
    cout << "\n\n\nPress Enter to return to main menu...";
    cin.ignore();
    cin.get();
}

void exitGame(){
    cout << "\nExisting game!\n";
    exit(0);
}

};