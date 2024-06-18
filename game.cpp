#include"game.h"

void hideCursor() {
    cout << "\033[?25l"; 
}

int Game :: currentscene = 0;  

int main(){
    hideCursor();
    Game* game = new Game;                     
   
    delete game;
    game = NULL;              
    
    return 0;
}