#include"game.h"

// Function to hide cursor for smooth gameplay
void hideCursor() {
    cout << "\033[?25l";    // ANSI code for hiding the cursor
}

int Game :: currentscene = 0;  

int main(){
    hideCursor();
    Game* game = new Game;    // Dynamically creating object using class pointer                  
   
    delete game;
    game = NULL;              
    
    return 0;
}
