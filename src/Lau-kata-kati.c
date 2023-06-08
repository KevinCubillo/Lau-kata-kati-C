#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definición de la estructura Casilla
struct Cell {
    int token;
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


int moveToken (int source, int destination, struct Board* board){
    struct Cell* sourceCell = goTopos(board, source);
    struct Cell* destinationCell = goTopos(board, destination);
    struct Cell* intermediateCell;
    int centralCell = ((board->numCells - 1) / 2); //Calculo de la casilla central


    if (destinationCell->token == 0){

        //MOVIMINETOS SIMPLES//
        //MOVIMIENTOS SOBRE LA CASILLA CENTRAL//
        if ((destination == centralCell+1 || destination == centralCell-1 || destination == centralCell+2 || destination == centralCell-2 ||
                destination == centralCell+3 || destination == centralCell-3) && source == centralCell){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                printf("Movimiento exitoso\n");
                return 1;
        
        }
        if ((source == centralCell+1 || source == centralCell-1 || source == centralCell+2 || source == centralCell-2 || 
             source == centralCell+3 || source == centralCell-3) && destination == centralCell){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                printf("Movimiento exitoso\n");
                return 1;
        }
  
        // MOVIMINETOS EN EL RESTO DEL TABLERO
        if (destination == source + 1 || destination == source - 1) {
            if ((source / 3 == destination / 3  && source < centralCell) || ((destination % 3 == 2 || source % 3 == 2) && source > centralCell)){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                printf("Movimiento exitoso\n");
                return 1;
            }
        }
        if ((destination == source + 3 || destination == source - 3) && ((source<centralCell && destination<centralCell) || (source>centralCell && destination>centralCell))){
            destinationCell->token = sourceCell->token;
            sourceCell->token = 0;
            printf("Movimiento exitoso\n");
            return 1;
        }

        //CAPTURAS

        //CAPTURAS SOBRE LA CASILLA CENTRAL//
        if ((source == centralCell+1 && destination == centralCell-1) || (source == centralCell-1 && destination == centralCell+1) ||
            (source == centralCell+2 && destination == centralCell-2) || (source == centralCell-2 && destination == centralCell+2) ||
            (source == centralCell+3 && destination == centralCell-3) || (source == centralCell-3 && destination == centralCell+3)){
            intermediateCell = goTopos(board, centralCell);
            if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                intermediateCell->token = 0;
                printf("Movimiento exitoso, captura realizada\n");
                return 1;
            }
        }
        if (source == centralCell && (abs(centralCell-destination) == 4 || abs(centralCell-destination) == 5) || abs(centralCell-destination) == 6){
            if (destination == centralCell+6)
                intermediateCell = goTopos(board, centralCell+3);
            if (destination == centralCell-6)
                intermediateCell = goTopos(board, centralCell-3);
            if (destination == centralCell+5)
                intermediateCell = goTopos(board, centralCell+2);
            if (destination == centralCell-5)
                intermediateCell = goTopos(board, centralCell-2);
            if (destination == centralCell+4)
                intermediateCell = goTopos(board, centralCell+1);
            if (destination == centralCell-4)
                intermediateCell = goTopos(board, centralCell-1);        
            if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                intermediateCell->token = 0;
                printf("Movimiento exitoso, captura realizada\n");
                return 1;
            }      
        }  
        if (destination == centralCell && (abs(centralCell-source) == 5 || abs(centralCell-source) == 4 || abs(centralCell-source) == 6)){
            if (source == centralCell+6)
                intermediateCell = goTopos(board, centralCell+3);
            if (source == centralCell-6)
                intermediateCell = goTopos(board, centralCell-3);
            if (source == centralCell+5)
                intermediateCell = goTopos(board, centralCell+2);
            if (source == centralCell-5)
                intermediateCell = goTopos(board, centralCell-2);
            if (source == centralCell+4)
                intermediateCell = goTopos(board, centralCell+1);
            if (source == centralCell-4)
                intermediateCell = goTopos(board, centralCell-1);
           
            if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                intermediateCell->token = 0;
                printf("Movimiento exitoso, captura realizada\n");
                return 1;
            }   
        }

        //CAPTURAS EN EL RESTO DEL TABLERO//
        
        //CAPTURAS VERTICALES//
        if (destination == source+6 && ((source> centralCell && destination>centralCell) || (source<centralCell && destination<centralCell))){
            intermediateCell = goTopos(board, source+3);
            if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                intermediateCell->token = 0;
                printf("Movimiento exitoso, captura realizada\n");
                return 1;
            }
        }
        if (destination == source-6 && ((source> centralCell && destination>centralCell) || (source<centralCell && destination<centralCell))){
            intermediateCell = goTopos(board, source-3);
            if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
                destinationCell->token = sourceCell->token;
                sourceCell->token = 0;
                intermediateCell->token = 0;
                printf("Movimiento exitoso, captura realizada\n");
                return 1;
            }
        }

        //CAPTURAS HORIZONTALES//
        if (source%3 == 0|| destination%3 == 0){
            if (destination == source+2){
                intermediateCell = goTopos(board, source+1);
                if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
                    destinationCell->token = sourceCell->token;
                    sourceCell->token = 0;
                    intermediateCell->token = 0;
                    printf("Movimiento exitoso, captura realizada\n");
                    return 1;
                }
            }
            if (destination == source-2){
                intermediateCell = goTopos(board, source-1);
                if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
                    destinationCell->token = sourceCell->token;
                    sourceCell->token = 0;
                    intermediateCell->token = 0;
                    printf("Movimiento exitoso, captura realizada\n");
                    return 1;
                }
            }
        }
    }
    printf("Movimiento inválido\n");
    return 0;
}

int isValidMove(int source, int destination, struct Board* board) {
    struct Cell* sourceCell = goTopos(board, source);
    struct Cell* destinationCell = goTopos(board, destination);
    struct Cell* intermediateCell;
    int centralCell = ((board->numCells - 1) / 2); // Cálculo de la casilla central

    if (destinationCell->token != 0) {
        // La casilla de destino ya está ocupada, el movimiento no es válido
        return 0;
    }
    // MOVIMIENTOS SIMPLES
    // MOVIMIENTOS SOBRE LA CASILLA CENTRAL
    if ((destination == centralCell + 1 || destination == centralCell - 1 || destination == centralCell + 2 || destination == centralCell - 2 ||
         destination == centralCell + 3 || destination == centralCell - 3) && source == centralCell) {
        return 1;
    }
    if ((source == centralCell + 1 || source == centralCell - 1 || source == centralCell + 2 || source == centralCell - 2 ||
         source == centralCell + 3 || source == centralCell - 3) && destination == centralCell) {
        return 1;
    }
    // MOVIMIENTOS EN EL RESTO DEL TABLERO
    if (destination == source + 1 || destination == source - 1) {
        if ((source / 3 == destination / 3 && source < centralCell) || ((destination % 3 == 2 || source % 3 == 2) && source > centralCell)) {
            return 1;
        }
    }
    if ((destination == source + 3 || destination == source - 3) && ((source < centralCell && destination < centralCell) || (source > centralCell && destination > centralCell))) {
        return 1;
    }
    // CAPTURAS
    // CAPTURAS SOBRE LA CASILLA CENTRAL
    if ((source == centralCell + 1 && destination == centralCell - 1) || (source == centralCell - 1 && destination == centralCell + 1) ||
        (source == centralCell + 2 && destination == centralCell - 2) || (source == centralCell - 2 && destination == centralCell + 2) ||
        (source == centralCell + 3 && destination == centralCell - 3) || (source == centralCell - 3 && destination == centralCell + 3)) {
        intermediateCell = goTopos(board, centralCell);
        if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token) {
            return 1;
        }
    }
    if (source == centralCell && (abs(centralCell - destination) == 4 || abs(centralCell - destination) == 5) || abs(centralCell - destination) == 6) {
        if (destination == centralCell + 6)
            intermediateCell = goTopos(board, centralCell + 3);
        if (destination == centralCell - 6)
            intermediateCell = goTopos(board, centralCell - 3);
        if (destination == centralCell + 5)
            intermediateCell = goTopos(board, centralCell + 2);
        if (destination == centralCell - 5)
            intermediateCell = goTopos(board, centralCell - 2);
        if (destination == centralCell + 4)
            intermediateCell = goTopos(board, centralCell + 1);
        if (destination == centralCell - 4)
            intermediateCell = goTopos(board, centralCell - 1);
        if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token) {
            return 1;
        }
    }
    // CAPTURAS VERTICALES
    if (destination == source+6 && ((source> centralCell && destination>centralCell) || (source<centralCell && destination<centralCell))){
        intermediateCell = goTopos(board, source+3);
        if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
            return 1;
        }
    }
    if (destination == source-6 && ((source> centralCell && destination>centralCell) || (source<centralCell && destination<centralCell))){
        intermediateCell = goTopos(board, source-3);
        if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
            return 1;
        }
    }
    // CAPTURAS HORIZONTALES
    if (destination == source+2 && ((source/3 == destination/3 && source < centralCell) || ((destination%3 == 2 || source%3 == 2) && source > centralCell))){
        intermediateCell = goTopos(board, source+1);
        if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
            return 1;
        }
    }
    if (destination == source-2 && ((source/3 == destination/3 && source < centralCell) || ((destination%3 == 2 || source%3 == 2) && source > centralCell))){
        intermediateCell = goTopos(board, source-1);
        if (intermediateCell->token != 0 && intermediateCell->token != sourceCell->token){
            return 1;
        }
    }
    return 0;
}


int hasValidMoves(int player, struct Board* board) {
    struct Cell* current = board->root;

    for (int i = 0; i < board->numCells; i++) {
        if (current->token == player) {
            for (int j = 0; j < board->numCells; j++) {
                if (isValidMove(i, j, board)){
                    return 1; // Se ha encontrado un movimiento valido para el jugador
                }
            }
        }
        current = current->next;
    }
    return 0; // No valid moves found for the player
}


int checkWinner(struct Board* board) {
    int player1 = 0; // Contador de fichas del jugador 1
    int player2 = 0; // Contador de fichas del jugador 2
    struct Cell* current = board->root;

    for (int i = 0; i < board->numCells; i++) { // Recorremos todas las celdas y contamos las fichas de cada jugador
        if (current->token == 1) {
            player1++; 
        }
        if (current->token == 2) {
            player2++;
        }
        current = current->next;
    }

    // Comprobamos si alguno de los jugadores se ha quedado sin fichas
    if (player1 == 0) {
        return 2; // Jugador 2 gana
    }
    if (player2 == 0) {
        return 1; // Jugador 1 gana
    }

    // Comprobamos si alguno de los jugadores no tiene movimientos posibles
    int player1HasMoves , player2HasMoves ;
    player1HasMoves = hasValidMoves(1, board);
    player2HasMoves = hasValidMoves(2, board);

    if (!player1HasMoves && !player2HasMoves){
        return 3; // Empate, ninguno tiene movimientos posibles 
    }
    if (!player1HasMoves) {
        return 2; // Jugador 2 gana
    }
    if (!player2HasMoves){
        return 1; // Jugador 1 gana
    }
    return 0; // No hay ganador aun
}   

struct Board* createBoard(int depth, int topPlayer) {
    int numCells = (6 * depth)+1;
    struct Board* board = (struct Board*)malloc(sizeof(struct Board));
    board->numCells = numCells;
    board->root = createCell(0);
    struct Cell* current = board->root;


    //Colocar las fichas iniciales
    int bottomPlayer;
    if (topPlayer == 1){
        bottomPlayer = 2;
    }
    else{
        bottomPlayer = 1;
    }   
    for (int i = 1; i < numCells+1; i++) {
         if (i<10){
            current->token = topPlayer;   
        }
        if (i>numCells-9){
            current->token = bottomPlayer;
        }
        current->next = createCell(i);
        current = current->next;    
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
            if (cellIndex%100>=10){
                printVerticalSpaces(centralSpaces-1);
            }
            else{
                printVerticalSpaces(centralSpaces);
            }
        }    
        centralSpaces -= 2;
        leftSpaces += 2;
    }

    //Imprimir casilla central
    printf("\n\n");
    printVerticalSpaces(leftSpaces + 3);
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
    current = current->next;

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
            if (cellIndex%100>=10){
                printVerticalSpaces(centralSpaces-1);
            }
            else{
                printVerticalSpaces(centralSpaces);
            }
        }    
        centralSpaces += 2;
        leftSpaces -= 2;
    }
    return;
}
  
int main(){
    int currentPlayer = 0, depth = 0, source = 0, destination = 0, topPlayer = 0, winner = 0; //profundidad del tablero, casiila de origen y casilla de destino
    printf("\nBIENVENIDO A LAU-KATA-KATI\n");
    while (depth<3){
        printf("\nDigite la profundidad del tablero: ");
        scanf("%d", &depth);
        if (depth<2)
            printf("ERROR: Profundidad inválida\n\n");
    }
  
    while (currentPlayer != 1 && currentPlayer != 2){
        printf("\n 1. Jugador X \n 2. Jugador O \n Digite quien mueve primero: ");
        scanf("%d", &currentPlayer);
        if (currentPlayer != 1 && currentPlayer != 2)
            printf("ERROR: Jugador inválido\n\n");
    }
    
    while (topPlayer != 1 && topPlayer != 2){
        printf(" \n 1. Jugador X \n 2. Jugador O \nDigite quien juega en lado de arriba del tablero: ");
        scanf("%d", &topPlayer);
        if (topPlayer != 1 && topPlayer != 2)
            printf("ERROR: Jugador inválido\n\n");
    }
    
    struct Board* board = createBoard(depth,topPlayer); //Creación del tablero

   while (winner == 0){
        printBoard(board, depth); //Imprimir tablero
        if (currentPlayer == 1){
            printf("\n\nJugador X, digite la casilla de origen: ");
            scanf("%d", &source);
            if (source > board->numCells || source < 0){
                printf("ERROR: Casilla inválida\n");
                continue;
            }
            if (goTopos(board, source)->token != 1){
                printf("ERROR: Solo puedes mover tus propias fichas\n");
                continue;
            }
            printf("Jugador X, digite la casilla de destino: ");
            scanf("%d", &destination);
        }
        else{
            printf("\n\nJugador O, digite la casilla de origen: ");
            scanf("%d", &source);
            if (source > board->numCells || source < 0){
                printf("ERROR: Casilla inválida\n");
                continue;
            }
            if (goTopos(board, source)->token != 2){
                printf("ERROR: Solo puedes mover tus propias fichas\n"); //CORREGIR MENSAJE
                continue;
            }
            printf("Jugador O, digite la casilla de destino: ");
            scanf("%d", &destination);
        }
        if (moveToken(source, destination, board) == 0){//Mover ficha
            continue;
        }
        if (currentPlayer == 1){
            currentPlayer = 2;
        }
        else{
            currentPlayer = 1;
        }
        winner = checkWinner(board);
    }

    printBoard(board, depth);
    if (winner == 1){
        printf("\n\n¡Ganó el jugador X!\n");
    }
    else if (winner == 2){
        printf("\n\n¡Ganó el jugador O!\n");
    }
    else{
        printf("\n\n¡Hay un Empate!\n");
    }
    return 0;

}

