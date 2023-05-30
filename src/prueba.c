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
    if (casilla < 1 || casilla > tablero->numCasillas) {
        printf("Error: Casilla inválida\n");
        return;
    }
    tablero->listaAdyacencia[casilla]->ficha = ficha;
}


// Función para añadir una conexión entre dos casillas en el tablero (bidireccional)
void agregarConexion(struct Tablero* tablero, struct Casilla* casilla1, struct Casilla* casilla2) {
    // Añadir conexión desde casilla1 a casilla2
    casilla2->siguiente = tablero->listaAdyacencia[casilla1->indice];
    tablero->listaAdyacencia[casilla1->indice] = casilla2;

    // Añadir conexión desde casilla2 a casilla1
    casilla1->siguiente = tablero->listaAdyacencia[casilla2->indice];
    tablero->listaAdyacencia[casilla2->indice] = casilla1;
}



// Función para crear un tablero con 'numCasillas' casillas
struct Tablero* crearTablero(int profundidad) {
    int numCasillas = (6 * profundidad)+1;
    struct Tablero* tablero = (struct Tablero*)malloc(sizeof(struct Tablero));
    tablero->numCasillas = numCasillas;
    tablero->listaAdyacencia = (struct Casilla**)malloc(numCasillas * sizeof(struct Casilla*));
    
    for (int i = 1; i < numCasillas+1; i++) {
        tablero->listaAdyacencia[i] = crearCasilla(i);
    }
    //conexiones casilla central
    int casillaCentral = ((numCasillas - 1) / 2)+1;
/*
    // Arriba
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral], tablero->listaAdyacencia[casillaCentral - 1]);
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral], tablero->listaAdyacencia[casillaCentral - 2]);
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral], tablero->listaAdyacencia[casillaCentral - 3]);

    // Abajo
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral], tablero->listaAdyacencia[casillaCentral + 1]);
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral], tablero->listaAdyacencia[casillaCentral + 2]);
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral], tablero->listaAdyacencia[casillaCentral + 3]);

    // Conexiones primera fila
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral - 1], tablero->listaAdyacencia[casillaCentral - 2]);
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral - 2], tablero->listaAdyacencia[casillaCentral - 3]);

    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral + 1], tablero->listaAdyacencia[casillaCentral + 2]);
    agregarConexion(tablero, tablero->listaAdyacencia[casillaCentral + 2], tablero->listaAdyacencia[casillaCentral + 3]);



    int columnaActual = 1;

    //Conexiones Arriba
    for (int casillaActual = 1; casillaActual < casillaCentral-3; casillaActual++) {
        if (columnaActual == 1){
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual + 1]);
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual + 3]);
            columnaActual = 2;
            columnaActual = 2;
        }
        else if (columnaActual == 2) {
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual + 1]);
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual + 3]);
            columnaActual = 3;
        }
        else {
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual + 3]);
            columnaActual = 1;
        }
    } 
    columnaActual = 1;

    //Conexiones Abajo
   for (int casillaActual = numCasillas; casillaActual>casillaCentral+3; casillaActual--) {
        if (columnaActual == 1) {
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual - 1]);
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual - 3]);
            columnaActual = 2;
        } else if (columnaActual == 2) {
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual - 1]);
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual - 3]);
            columnaActual = 3;
        } else {
            agregarConexion(tablero, tablero->listaAdyacencia[casillaActual], tablero->listaAdyacencia[casillaActual - 3]);
            columnaActual = 1;
        }
    }*/

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
