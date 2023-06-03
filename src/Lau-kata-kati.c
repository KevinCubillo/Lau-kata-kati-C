#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura Casilla
struct Cell {
   // int index;
    int token;
    int neighbors[6];
    int numNeighbors;
    struct Cell* next;
    struct Cell* prev;
};

// Definición de la estructura Tablero
struct Board {
    int numCells;
    struct Cell* root;
};


struct Cell* createCell(int index) {
    struct Cell* cell = (struct Cell*)malloc(sizeof(struct Cell));
    //cell->index = index;
    cell->token = 0;
    cell->next = NULL;
    cell->prev = NULL;
    cell->numNeighbors = 0;
    return cell;
}

struct Cell* goTopos(struct Board* board, int pos) {
    if (pos < 0 || pos > board->numCells) {
        printf("Error: Casilla inválida\n");
        return NULL;
    }
    struct Cell* current = board->root;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    return current;
}

void placeToken(struct Board* board, int cell, int token) {
    struct Cell* current = goTopos(board, cell);
    current->token = token;
}

int isNeighbor(int cell1, int cell2, struct Board* board) {
    struct Cell* current = goTopos(board, cell1);
    for (int i = 0; i < current->numNeighbors; i++) {
        if (current->neighbors[i] == cell2) {
            return 1;
        }
    }
    return 0;
}

void moveToken (int source, int destination, struct Board* board){
    struct Cell* sourceCell = goTopos(board, source);
    struct Cell* destinationCell = goTopos(board, destination);
    struct Cell* intermediateCell;

    if (isNeighbor(source, destination, board) == 1 && destinationCell->token == 0){ //Caso en el que la casilla de destino es vecina de la casilla de origen
        destinationCell->token = sourceCell->token;
        sourceCell->token = 0; 
        printf("Movimiento exitoso\n"); 
        return;
    }
    //recorre los vecinos de la casilla de origen
    
    for (int i = 0; i < destinationCell->numNeighbors; i++){
        intermediateCell = goTopos(board, destinationCell->neighbors[i]);

        if (isNeighbor(source, destinationCell->neighbors[i], board) && intermediateCell->token != 0 && intermediateCell->token != sourceCell->token && destinationCell->token == 0){
            destinationCell->token = sourceCell->token;
            sourceCell->token = 0;
            intermediateCell->token = 0;
            printf("Movimiento exitoso\n");
            return;
        }
    }
    printf("Movimiento inválido\n");
    return;
}

int checkWinner (struct Board* board){
    int player1 = 0;
    int player2 = 0;
    struct Cell* current = board->root;
    for (int i = 0; i < board->numCells; i++){
        if (current->token == 1){
            player1++;
        }
        if (current->token == 2){
            player2++;
        }
        current = current->next;
    }
    if (player1 == 0){
        return 2;
    }
    if (player2 == 0){
        return 1;
    }
    return 0;
}


void addConnection(struct Board* board, int cell1, int cell2) {
    struct Cell* cell_1 = goTopos(board, cell1);
    struct Cell* cell_2 = goTopos(board, cell2);
    cell_1->neighbors[cell_1->numNeighbors] = cell2;
    cell_2->neighbors[cell_2->numNeighbors] = cell1;
    cell_1->numNeighbors++;
    cell_2->numNeighbors++;
}


struct Board* createBoard(int depth) {
    int numCells = (6 * depth)+1;
    struct Board* board = (struct Board*)malloc(sizeof(struct Board));
    board->numCells = numCells;
    board->root = createCell(0);
    struct Cell* current = board->root;

    //Colocar las fichas iniciales
    for (int i = 1; i < numCells+1; i++) {
         if (i<10){
            current->token = 1;   
        }
        if (i>numCells-9){
            current->token = 2;
        }
        current->next = createCell(i);
        current = current->next;    
    }

    //Agregar conexiones
    int centralCell = ((numCells - 1) / 2);

    //primer nivel superior
    addConnection(board, centralCell, centralCell-1);
    addConnection(board, centralCell, centralCell-2);
    addConnection(board, centralCell, centralCell-3);
    addConnection(board, centralCell-1, centralCell-2);
    addConnection(board, centralCell-2, centralCell-3);

    //primer nivel inferior
    addConnection(board, centralCell, centralCell+1);
    addConnection(board, centralCell, centralCell+2);
    addConnection(board, centralCell, centralCell+3);
    addConnection(board, centralCell+1, centralCell+2);
    addConnection(board, centralCell+2, centralCell+3);

    int currentColumn = 1;

    //Conexiones Arriba
    for (int currentCell = 0; currentCell < centralCell-3; currentCell++) {
        if (currentColumn == 1 || currentColumn ==2 ){
            addConnection(board, currentCell, currentCell+1);
            addConnection(board, currentCell, currentCell+3);
            currentColumn++;
        }
        else{
            addConnection(board, currentCell, currentCell+3);
            currentColumn = 1;
        }
    }
    currentColumn = 1;

    //Conexiones Abajo
    for (int currentCell = numCells-1; currentCell>centralCell+3; currentCell--) {
        if (currentColumn == 1 || currentColumn ==2 ){
            addConnection(board, currentCell, currentCell-1);
            addConnection(board, currentCell, currentCell-3);
            currentColumn++;
        }
        else{
            addConnection(board, currentCell, currentCell-3);
            currentColumn = 1;
        }
    }
    return board;
}

void printVerticalSpaces(int amount){
    for (int i = 0; i <amount; i++) {
        printf(" ");
    }
    return;
}

void printBoard(struct Board* board, int depth) {
    struct Cell* current = board->root;
    int centralSpaces = 2*depth;
    int leftSpaces = 0;
    int cellIndex = 0;

    //Imprimir Triangulo superior
    for (int i = 0; i <depth; i++) {
        printf("\n\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            if (current->token == 0){
                printf("( )");
            }
            if (current->token == 1){
                printf("(X)");
            }
            if (current->token == 2){
                printf("(O)");
            }
            printVerticalSpaces(centralSpaces);
            current = current->next;
        }

        printf("\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            printf(" %d ", cellIndex);
            cellIndex++;
            printVerticalSpaces(centralSpaces);
        }    
        centralSpaces -= 2;
        leftSpaces += 2;
    }

    //Imprimir casilla central
    printf("\n\n");
    printVerticalSpaces(leftSpaces + 3);
    current = current->next;
    if (current->token == 0){
            printf("( )");
        }
        if (current->token == 1){
                printf("(X)");
        }
        if (current->token == 2){
            printf("(O)");
        } 
    printf("\n");
    printVerticalSpaces(leftSpaces+3);
    printf(" %d ", cellIndex);
    cellIndex++;

    // Restaurar valores iniciales para el Triángulo inferior
    centralSpaces = 2;
    leftSpaces -= 2;


    //Imprimir Triangulo inferior
    for (int i = 0; i <depth; i++) {
        printf("\n\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            if (current->token == 0){
                printf("( )");
            }
            if (current->token == 1){
                printf("(X)");
            }
            if (current->token == 2){
                printf("(O)");
            }
            printVerticalSpaces(centralSpaces);
            current = current->next;
        }

        printf("\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            printf(" %d ", cellIndex);
            cellIndex++;
            printVerticalSpaces(centralSpaces);
        }    
        centralSpaces += 2;
        leftSpaces -= 2;
    }
    return;

}
  


int main(){
    int currentPlayer = 1; //Jugador actual
    int depth, source, destination; ; //profundidad del tablero, casiila de origen y casilla de destino

    printf("Digite la profundidad del tablero: ");
    scanf("%d", &depth);

    struct Board* board = createBoard(depth); //Creación del tablero
    printBoard(board, depth); //Impresión del tablero

    
    return 0;
}
