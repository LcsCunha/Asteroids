#include <stdio.h>
#include <stdlib.h>

//0 = empty space
//1 = spaceship
//2 = asteroids
//3 = spaceship laser

int main(){
    //Function to avoid repeated numbers from rand.
    srand( time (NULL) );

    int matriz[50][50];

    int maxMeteoros = 4, nMeteoros = 0;
    int posX = 25, posY = 40;
    int seed;

    char imput;
    int pontuacao;

    //Generating the primal game's matrix.
    for (int i = 0; i < 50; ++i){
        for (int j = 0; j < 50; ++j)
            matriz[i][j] = 0;
    }

    printf("              Ataque de meteoros!\n\n\n\n");
    printf("Por favor, maximize a tela do console para jogar.\n\n");
    system("pause");

    system("cls");

    pontuacao = 10;

    while (pontuacao > 0){

        printf("                                                             Pontuacao: %i\n\n", pontuacao);

        seed = rand()%50;

        //meteor movement and collision detection with the border of the screen.
        for (int i = 49; i > -1; --i){
            for (int j = 0; j < 50; ++j){
                if (i == 49){
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
        for (int i = 0; i < 50; ++i){
            for (int j = 0; j < 50; ++j){
                if (((j == posX - 1)||(j == posX)||(j == posX + 1))
                &&(i == posY))
                    matriz[i][j] = 1;
                else if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 3)){
                    matriz[i][j] = 0;
                    matriz[i+1][j] = 0;
                    --nMeteoros;
                    pontuacao += 3;
                }else if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 1)){
                    if (i+2 > 49){
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
        for (int i = 0; i < 50; ++i){
            for (int j = 0; j < 50; ++j){
                if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 3)){
                            matriz[i][j] = 0;
                            matriz[i+1][j] = 0;
                            --nMeteoros;
                            pontuacao += 3;
                }else if ((matriz[i][j] == 2)&&(matriz[i+1][j] == 1)){
                    if (i+2 > 49){
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
        for (int i = 0; i < 50; ++i){
            for (int j = 0; j < 50; ++j){
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

        imput = getch();

        if (imput == 'a')
            posX -= 2;
        if (imput == 'd')
            posX += 2;
        if (imput == 'w'){
            posY -= 1;
            if (posY < 0)
                posY += 1;
        }
        if (imput == 's'){
            posY += 1;
            if (posY > 49)
                posY -= 1;
        }
        if (imput == ' '){
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

        posX = (posX < 0)? 49 : posX;
        posX = (posX > 49)? 0 : posX;

        system("cls");
    }

    printf("\t\t\nGame Over!!!\n\n");
    printf("\nVoce deixou muitos asteroides atingirem a Terra e agora a mesma esta em chamas e acabada...\n\n");

    system("pause");

    return 0;

}
