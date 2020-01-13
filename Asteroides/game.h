#ifndef GAME
#define GAME
/** Here are defined some data structures and their functions that will be reused through all the code*/

typedef struct _Game_ {

	int** gameMatrix; //Matrix were the game is being generated
	int maxMeteors; //Max number of meteors at the screen
	int meteorNumber; //Actual number of meteors at the screen
	int size;
}Game;

typedef struct _Player_ {

	int posX; //X position of the player on the matrix
	int posY; //Y position of the player on the matrix
	int points; //Ponctuation of the player
}Player;

Game* createGame (int size); //Function that creates a new Game data structure
int destroyGame (Game** game); //Function that desallocates from memory a data structure Game

Player* createPlayer (int sizeGame); //Function that creates a new Player data structure 
int destroyPlayer (Player** player); //Function that desallocates from memory a data structure Player

#endif