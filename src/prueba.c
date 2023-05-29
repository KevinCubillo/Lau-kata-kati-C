#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura Casilla
struct Casilla {
    int indice;
    int ficha;
    struct Casilla* siguiente;
};



// Definición de la estructura Tablero
struct Tablero {
    int numCasillas;
    struct Casilla** listaAdyacencia;
};

// Función para crear una nueva casilla
struct Casilla* crearCasilla(int indice) {
    struct Casilla* casilla = (struct Casilla*)malloc(sizeof(struct Casilla));
    casilla->indice = indice;
    casilla->ficha = 0;
    casilla->siguiente = NULL;
    return casilla;
}


void colocarFicha(struct Tablero* tablero, int casilla, int ficha) {
    // Verificar si la casilla existe en el tablero
    if (casilla < 0 || casilla >= tablero->numCasillas) {
        printf("Casilla inválida.\n");
        return;
    }
    // Buscar la casilla en la lista de adyacencia
    struct Casilla* actual = tablero->listaAdyacencia[casilla];
    while (actual) {
        // Actualizar la ficha de la casilla encontrada
        if (actual->indice == casilla) {
            actual->ficha = ficha;
            printf("Ficha colocada en la casilla %d.\n", casilla);
            return;
        }
        actual = actual->siguiente;
    }

    // Si no se encontró la casilla en la lista de adyacencia
    printf("Casilla no encontrada en el tablero.\n");
}

// Función para añadir una conexión entre dos casillas en el tablero (bidireccional)
void agregarConexion(struct Tablero* tablero, int casilla1, int casilla2) {
    // Añadir conexión desde casilla1 a casilla2
    struct Casilla* nuevaCasilla = crearCasilla(casilla2);
    nuevaCasilla->siguiente = tablero->listaAdyacencia[casilla1];
    tablero->listaAdyacencia[casilla1] = nuevaCasilla;

    // Añadir conexión desde casilla2 a casilla1
    nuevaCasilla = crearCasilla(casilla1);
    nuevaCasilla->siguiente = tablero->listaAdyacencia[casilla2];
    tablero->listaAdyacencia[casilla2] = nuevaCasilla;
}



// Función para crear un tablero con 'numCasillas' casillas
struct Tablero* crearTablero(int profundidad) {
    int numCasillas = (6 * profundidad)+1;
    struct Tablero* tablero = (struct Tablero*)malloc(sizeof(struct Tablero));
    tablero->numCasillas = numCasillas;
    tablero->listaAdyacencia = (struct Casilla**)malloc(numCasillas * sizeof(struct Casilla*));
    
    for (int i = 1; i < numCasillas+1; i++) {
        tablero->listaAdyacencia[i] = NULL;
    }
   // tablero->listaAdyacencia[numCasillas - 1] = NULL;

    //conexiones casilla central
    int casillaCentral = ((numCasillas - 1) / 2)+1;

    // Arriba
    agregarConexion(tablero, casillaCentral, casillaCentral - 1);
    agregarConexion(tablero, casillaCentral, casillaCentral -2);
    agregarConexion(tablero, casillaCentral, casillaCentral -3);

    //Abajo
    agregarConexion(tablero, casillaCentral, casillaCentral + 1);
    agregarConexion(tablero, casillaCentral, casillaCentral + 2);
    agregarConexion(tablero, casillaCentral, casillaCentral + 3);

    //Conexiones primer fila
    agregarConexion(tablero, casillaCentral - 1, casillaCentral - 2);
    agregarConexion(tablero, casillaCentral - 2, casillaCentral - 3);

    agregarConexion(tablero, casillaCentral + 1, casillaCentral + 2);
    agregarConexion(tablero, casillaCentral + 2, casillaCentral + 3);


    int columnaActual = 1;

    //Conexiones Arriba
    for (int casillaActual = 1; casillaActual < casillaCentral-3; casillaActual++) {
        if (columnaActual == 1){
            agregarConexion(tablero, casillaActual, casillaActual + 1);
            agregarConexion(tablero, casillaActual, casillaActual + 3);
            columnaActual = 2;
        }
        else if (columnaActual == 2) {
            agregarConexion(tablero, casillaActual, casillaActual + 1);
            agregarConexion(tablero, casillaActual, casillaActual + 3);
            columnaActual = 3;
        }
        else {
            agregarConexion(tablero, casillaActual, casillaActual + 3);
            columnaActual = 1;
        }
    } 
    columnaActual = 1;

    //Conexiones Abajo
    for (int casillaActual = numCasillas; casillaActual > casillaCentral+3; casillaActual--) {
        if (columnaActual == 1) {
            agregarConexion(tablero, casillaActual, casillaActual - 1);
            agregarConexion(tablero, casillaActual, casillaActual - 3);
            columnaActual = 2;
        }
        else if (columnaActual == 2) {
            agregarConexion(tablero, casillaActual, casillaActual - 1);
            agregarConexion(tablero, casillaActual, casillaActual - 3);
            columnaActual = 3;
        }
        else{
            agregarConexion(tablero, casillaActual, casillaActual - 3);
            columnaActual = 1;
        }
    }
    return tablero;
}

void imprimirTablero(struct Tablero* tablero) {
    for (int i = 1; i <tablero->numCasillas+1; i++) { 
        struct Casilla* actual = tablero->listaAdyacencia[i];
        printf("Conexiones de la casilla %d: ", i);
        while (actual) {
            printf("%d, ", actual->indice);
            actual = actual->siguiente;
        }
        printf("\n");
    }
}

int main() {
    int profundidad = 3;
    struct Tablero* tablero = crearTablero(profundidad);

   imprimirTablero(tablero);

    return 0;
}
