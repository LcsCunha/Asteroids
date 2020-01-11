#include <stdio.h>
#include <stdlib.h>
#include "funcoesAuxiliares.h"
#define TAM 30

void game (){ //Primal function of the game

	//Function to avoid repeated numbers from rand.
    srand( time (NULL) );

    int matriz[TAM][TAM];
    int maxMeteoros = 4, nMeteoros = 0;
    int posX = TAM/2, posY = TAM - 10;
    int seed;

    char input;
    int pontuacao;

    //Generating the primal game's matrix.
    for (int i = 0; i < TAM; ++i){
        for (int j = 0; j < TAM; ++j)
            matriz[i][j] = 0;
    }

    printf("              Ataque de meteoros!\n\n\n\n");
    printf("Por favor, maximize a tela do console para jogar.\n\n");

    pontuacao = 10;

    while (pontuacao > 0){

        printf("                                                             Pontuacao: %i\n\n", pontuacao);

        seed = rand()%TAM;

        //meteor movement and collision detection with the border of the screen.
        for (int i = TAM - 1; i > -1; --i){
            for (int j = 0; j < TAM; ++j){
                if (i == TAM - 1){
                    if (matriz[i][j] == 2){
                        matriz[i][j] = 0;
                        --nMeteoros;
                        pontuacao -= 5;
                    }
                }else if (matriz[i][j] == 2){
                    matriz[i][j] = 0;
                    matriz[i+1][j] = 2;
                }
            }
        }

        maxMeteoros = (pontuacao < 20)? 2:
                      (pontuacao < 35)? 3:
                      (pontuacao < 50)? 4:
                      (pontuacao < 80)? 6:
                      (pontuacao < 100)? 8:10;

        if (nMeteoros < maxMeteoros){
            if (seed%2 == 0){
                matriz[0][seed] = 2;
                ++nMeteoros;
            }
        }

        //Objects movement, player body generation and collisions check.
        for (int i = 0; i < TAM; ++i){
            for (int j = 0; j < TAM; ++j){
                if (((j == posX - 1)||(j == posX)||(j == posX + 1))
                &&(i == posY))
                    matriz[i][j] = 1;
                else if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 3)){
                    matriz[i][j] = 0;
                    matriz[i+1][j] = 0;
                    --nMeteoros;
                    pontuacao += 3;
                }else if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 1)){
                    if (i+2 > TAM - 1){
                        matriz[i][j] = 0;
                        --nMeteoros;
                        pontuacao -= 5;
                    }else{
                        matriz[i][j] = 0;
                        matriz[i+2][j] = 2;
                    }
                }else if (matriz[i][j] == 3){
                    if (i != 0){
                        matriz[i-1][j] = 3;
                        matriz[i][j] = 0;
                    }else
                        matriz[i][j] = 0;
                }else if ((matriz[i][j] != 2)&&(matriz[i][j] != 3))
                    matriz[i][j] = 0;
            }
        }

        //Extra collisions check for bug fixing.
        for (int i = 0; i < TAM; ++i){
            for (int j = 0; j < TAM; ++j){
                if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 3)){
                            matriz[i][j] = 0;
                            matriz[i+1][j] = 0;
                            --nMeteoros;
                            pontuacao += 3;
                }else if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 1)){
                    if (i+2 > TAM - 1){
                        matriz[i][j] = 0;
                        --nMeteoros;
                        pontuacao -= 5;
                    }else{
                        matriz[i][j] = 0;
                        matriz[i+2][j] = 2;
                    }
                }
            }
        }

        //Printing the game for the player.
        for (int i = 0; i < TAM; ++i){
            for (int j = 0; j < TAM; ++j){
                if (matriz[i][j] == 1)
                    printf("=");
                else if (matriz[i][j] == 2)
                    printf("*");
                else if (matriz[i][j] == 3)
                    printf("T");
                else
                    printf(" ");
            }
            printf("\n");
        }

        scanf("%c", &input);

        if (input == 'a')
            posX -= 2;
        if (input == 'd')
            posX += 2;
        if (input == 'w'){
            posY -= 1;
            if (posY < 0)
                posY += 1;
        }
        if (input == 's'){
            posY += 1;
            if (posY > TAM - 1)
                posY -= 1;
        }
        if (input == ' '){
            //Bug fixing:
            //The meteor used to not be destroyed when the laser were generated immediately in it's position.
            if ((matriz[posY - 1][posX] == 2)||(matriz[posY - 1][posX - 1] == 2)||(matriz[posY - 1][posX + 1] == 2)){
                matriz[posY - 1][posX] = matriz[posY - 1][posX - 1] = matriz[posY - 1][posX + 1] = 0;
                --nMeteoros;
                pontuacao += 3;
            }
            //Generating the laser.
            matriz[posY - 1][posX] = 3;
            matriz[posY - 1][posX - 1] = 3;
            matriz[posY - 1][posX + 1] = 3;
            pontuacao -= 2;
        }

        posX = (posX < 0)? TAM - 1 : posX;
        posX = (posX > TAM - 1)? 0 : posX;

        printf("\n\n\n\n\n\n\n\n");
        clean_stdin();
    }

    printf("\t\t\nGame Over!!!\n\n");
    printf("\nVoce deixou muitos asteroides atingirem a Terra e agora a mesma esta em chamas e acabada...\n\n");

    return 0;

}
