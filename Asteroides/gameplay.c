#include <stdio.h>
#include <stdlib.h>

void meteorMovement (int** matrix, int size, int* meteorNumber, int* points){ //Meteor movement and collision detection with the border of the screen.

	

	for (int i = (size - 1); i > -1; --i){
        for (int j = 0; j < size; ++j){
            if (i == (size - 2)){ //Caso faca para size - 1 dará erro de memória
                if (matrix[i][j] == 2){
                    matrix[i][j] = 0;
                    --(*meteorNumber);
                    (*points) -= 5;
                }
            }else if (matrix[i][j] == 2){
                matrix[i][j] = 0;
                matrix[i+1][j] = 2;
            }
        }
    }

    printf("\n\n\n");
}

void meteorGenerator (int** matrix, int size, int* maxMeteors, int* meteorNumber, int* points) { //Meteor generation

	int seed = rand()%size;

	(*maxMeteors) = ((*points) < 20)? 2:
                  ((*points) < 35)? 3:
                  ((*points) < 50)? 4:
                  ((*points) < 80)? 6:
                  ((*points) < 100)? 8:10;

    if ((*meteorNumber) < (*maxMeteors)){
        if (seed%2 == 0){
            matrix[0][seed] = 2;
            ++(*meteorNumber);
        }
    }
}

void gameUpdate (int** matrix, int size, int* meteorNumber,  int* posX, int* posY, int* points) { //Objects movement, player body generation and collisions check.

        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                if (((j == (*posX) - 1)||(j == (*posX))||(j == (*posX) + 1))
                &&(i == (*posY))){
                    matrix[i][j] = 1;
                }
                else if ((matrix[i][j] == 2)&&(matrix[i+1][j] == 3)){
                    matrix[i][j] = 0;
                    matrix[i+1][j] = 0;
                    --(*meteorNumber);
                    (*points) += 3;
                }
                else if ((matrix[i][j] == 2)&&(matrix[i+1][j] == 1)){
                    if (i+2 > size - 1){
                        matrix[i][j] = 0;
                        --(*meteorNumber);
                        (*points) -= 5;
                    }else{
                        matrix[i][j] = 0;
                        matrix[i+2][j] = 2;
                    }
                }else if (matrix[i][j] == 3){
                    if (i != 0){
                        matrix[i-1][j] = 3;
                        matrix[i][j] = 0;
                    }
                    else{
                        matrix[i][j] = 0;
                    }
                }
                else if ((matrix[i][j] != 2)&&(matrix[i][j] != 3)){
                    matrix[i][j] = 0;
                }
            }
        }

        //Extra collisions check for bug fixing.
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                if ((matrix[i][j] == 2)&&(matrix[i+1][j] == 3)){
                        matrix[i][j] = 0;
                        matrix[i+1][j] = 0;
                        --(*meteorNumber);
                        (*points) += 3;
                }
                else if ((matrix[i][j] == 2)&&(matrix[i+1][j] == 1)){
                    if (i+2 > size - 1){
                        matrix[i][j] = 0;
                        --(*meteorNumber);
                        (*points) -= 5;
                    }
                    else{
                        matrix[i][j] = 0;
                        matrix[i+2][j] = 2;
                    }
                }
            }
        }
}

void printGame (int** matrix, int size) { //Printing the game for the player

	
	for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            if (matrix[i][j] == 1){
                printf("=");
            }
            else if (matrix[i][j] == 2){
                printf("*");
            }
            else if (matrix[i][j] == 3){
                printf("T");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}

void playerUpdate (int** matrix, int size, int* meteorNumber, int* posX, int* posY, int* points) { //Game input and player position update

		char input;
		scanf("%c", &input);

        if (input == 'a'){
            (*posX) -= 2;
        }
        if (input == 'd'){
            (*posX) += 2;
        }
        if (input == 'w'){
            (*posY) -= 1;
	        if ((*posY) < 0){
	            (*posY) += 1;
	        }
        }
        if (input == 's'){
            (*posY) += 1;
            if ((*posY) > size - 1){
                (*posY) -= 1;
            }
        }
        if (input == ' '){
            //Bug fixing:
            //The meteor used to not be destroyed when the laser were generated immediately in it's position.
            if ((matrix[(*posY) - 1][(*posX)] == 2)||(matrix[(*posY) - 1][(*posX) - 1] == 2)||(matrix[(*posY) - 1][(*posX) + 1] == 2)){
                matrix[(*posY) - 1][(*posX)] = matrix[(*posY) - 1][(*posX) - 1] = matrix[(*posY) - 1][(*posX) + 1] = 0;
                --(*meteorNumber);
                (*points) += 3;
            }
            //Generating the laser.
            matrix[(*posY) - 1][(*posX)] = 3;
            matrix[(*posY) - 1][(*posX) - 1] = 3;
            matrix[(*posY) - 1][(*posX) + 1] = 3;
            (*points) -= 2;
        }

        (*posX) = ((*posX) < 0)? size - 1 : (*posX);
        (*posX) = ((*posX) > size - 1)? 0 : (*posX);
}