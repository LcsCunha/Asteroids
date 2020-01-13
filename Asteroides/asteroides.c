#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "funcoesAuxiliares.h"
#include "gameplay.h"
#define TAM 30

void gameGenerator (){ //Primal function of the game

	//Function to avoid repeated numbers from rand.
    srand( time (NULL) );

    Game* game = createGame (TAM);
    Player* player = createPlayer (TAM);


    printf("              Ataque de meteoros!\n\n\n\n");
    printf("Por favor, maximize a tela do console para jogar.\n\n");

    player -> points = 10;

    while ((player -> points) > 0){

        printf("                                                             Pontuacao: %i\n\n", player -> points);

        //meteor movement and collision detection with the border of the screen.
        meteorMovement (game -> gameMatrix, game -> size, &game -> meteorNumber, &player -> points);

        //Meteor generation
        meteorGenerator (game -> gameMatrix, game -> size, &game -> maxMeteors, &game -> meteorNumber, &player -> points);
        //

        //Objects movement, player body generation and collisions check.
        gameUpdate (game -> gameMatrix, game -> size, &game -> meteorNumber,  &player -> posX, &player -> posY, &player -> points);

        //Printing the game for the player.
        printGame (game -> gameMatrix, game -> size);

        //Game input and player position update
        playerUpdate (game -> gameMatrix, game -> size, &game -> meteorNumber,  &player -> posX, &player -> posY, &player -> points);
        //

        printf("\n\n\n\n\n\n\n\n");
        clean_stdin();
    }

    printf("\t\t\nGame Over!!!\n\n");
    printf("\nVoce deixou muitos asteroides atingirem a Terra e agora a mesma esta em chamas e acabada...\n\n");

    destroyPlayer (&player);
    destroyGame (&game);
}
