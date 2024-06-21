/*
-------------------------------------------------------------------------------------------------------
               
               Project title   : Storytelling Game
               Made By         : Muhammad Reyan
               Language used   : C++
               Platform        : Mac os 
               IDE used        : Visual Studio Code
               Date completed  : 2024-05-20
               Storyline       : This game story is inspired from novel "A song of Ice and Fire"

                    Check license and copyright claim opening "License.txt".  

 ------------------------------------------------------------------------------------------------------
*/

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
