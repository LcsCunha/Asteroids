void meteorMovement (int** matrix, int size, int* meteorNumber, int* points); //Meteor movement and collision detection with the border of the screen.
void meteorGenerator (int** matrix, int size, int* maxMeteors, int* meteorNumber, int* points); //Meteor generation
void gameUpdate (int** matrix, int size, int* meteorNumber,  int* posX, int* posY, int* points); //Objects movement, player body generation and collisions check.
void printGame (int** matrix, int size); //Printing the game for the player
void playerUpdate (int** matrix, int size, int* meteorNumber, int* posX, int* posY, int* points); //Game input and player position update