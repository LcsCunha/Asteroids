#include <stdio.h>
#include <stdlib.h>
#include "game.h" 

/**
For more comments information visit game.h
*/
Game* createGame (int size){ //Function that creates a new Game data structure

	Game* newGame = (Game*) malloc (sizeof(Game)); //Creating a new game data structure
	
	newGame -> gameMatrix = (int**) malloc (size*sizeof(int*));

	for (int i = 0; i < size; i++){
		newGame -> gameMatrix[i] = (int*) malloc (size*sizeof(int));
	}

	//Generating the primal game's matrix.
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            newGame -> gameMatrix[i][j] = 0;
        }
    }

    newGame -> maxMeteors = 4;
    newGame -> meteorNumber = 0;
    newGame -> size = size;

    return newGame;
}

int destroyGame (Game** game){ //Function that desallocates from memory a dataStructure game

	if ((*game) == NULL) return 0;

	Game* gameAux = *game;

	for (int i = 0; i < (gameAux -> size); i++){
		if (gameAux -> gameMatrix[i] != NULL){
			free(gameAux -> gameMatrix[i]);
		}
	}

	free(gameAux);
	*game = NULL;

	return 1;
}

Player* createPlayer (int sizeGame){ //Function that creates a new Player data structure 

	Player* newPlayer = (Player*) malloc (sizeof(Player));

	newPlayer -> posX = sizeGame/2;
	newPlayer -> posY = sizeGame - 10;
	newPlayer -> points = 0;

	return newPlayer;
}

int destroyPlayer (Player** player){

	if ((*player) == NULL) return 0;

	Player* playerAux = *player;

	free(playerAux);
	*player = NULL;

	return 1;
}