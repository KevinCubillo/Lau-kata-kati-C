
void printBoard(struct Board* board, int depth) {
    struct Cell* current = board->root;
    int centralSpaces = 2 * depth;
    int leftSpaces = 0;
    int cellIndex = 0;

    // Imprimir Triángulo superior
    for (int i = 0; i < depth; i++) {
        printf("\n\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            if (current->token == 0) {
                printf("( )");
            } else if (current->token == 1) {
                printf("(X)");
            } else if (current->token == 2) {
                printf("(O)");
            }

            if (j < 2) {
                printVerticalSpaces(centralSpaces);
            }

            current = current->next;
        }

        printf("\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            printf(" %d ", cellIndex);
            cellIndex++;
            if (j < 2) {
                printVerticalSpaces(centralSpaces);
            }
        }

        centralSpaces -= 2;
        leftSpaces += 2;
    }

    // Imprimir casilla central
    printf("\n\n");
    printVerticalSpaces(leftSpaces + 1);

    if (current->token == 0) {
        printf("( )");
    } else if (current->token == 1) {
        printf("(X)");
    } else if (current->token == 2) {
        printf("(O)");
    }

    printf("\n");
    printVerticalSpaces(leftSpaces + 1);
    printf(" %d ", cellIndex);
    cellIndex++;

    // Restaurar valores iniciales para el Triángulo inferior
    centralSpaces = 2;
    leftSpaces -= 2;

    // Imprimir Triángulo inferior
    for (int i = 0; i < depth; i++) {
        printf("\n\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            if (current->token == 0) {
                printf("( )");
            } else if (current->token == 1) {
                printf("(X)");
            } else if (current->token == 2) {
                printf("(O)");
            }

            if (j < 2) {
                printVerticalSpaces(centralSpaces);
            }

            current = current->next;
        }

        printf("\n");
        printVerticalSpaces(leftSpaces);

        for (int j = 0; j < 3; j++) {
            printf(" %d ", cellIndex);
            cellIndex++;
            if (j < 2) {
                printVerticalSpaces(centralSpaces);
            }
        }

        centralSpaces += 2;
        leftSpaces -= 2;
    }
}

