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

void printBoard(struct Board* board) {
    struct Cell* current = board->root;
    for (int i = 0; i < board->numCells; i++) {
        printf("%d: ", i);
        for (int j = 0; j < current->numNeighbors; j++) {
            printf("%d ", current->neighbors[j]);
        }
        printf(" Token: %d", current->token);
        printf("\n");
        current = current->next;
    }
}

void placeToken(struct Board* board, int cell, int token) {
    struct Cell* current = goTopos(board, cell);
    current->token = token;
}

int main(){
    int depth = 5;
    struct Board* board = createBoard(depth);
    printBoard(board);
    printf("numCells: %d\n", board->numCells);
    return 0;
}

  