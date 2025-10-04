#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MIN_TAM = 8;
const int MAX_TAM = 20;

int main() {
    srand(time(0));

    int tam;
    cout << "Ingrese el tamaño del tablero (8 a 20): ";
    cin >> tam;

    if (tam < MIN_TAM || tam > MAX_TAM) {
        cout << "Tamaño inválido.\n";
        return 0;
    }

    char tablero[MAX_TAM][MAX_TAM];

 
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            tablero[i][j] = '.';
        }
    }

    int piezas[] = {185, 186, 187, 188, 200, 201, 202, 203, 204, 205, 206};
    int numPiezas = sizeof(piezas) / sizeof(piezas[0]);

    cout << "\n=== PIEZAS DISPONIBLES ===\n";
    for (int i = 0; i < numPiezas; i++) {
        cout << i + 1 << ") " << (char)piezas[i] << "  (ASCII " << piezas[i] << ")\n";
    }

   
    cout << "\n=== TABLERO INICIAL ===\n";
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }

    int fila, col, eleccion;

    
    while (true) {
        cout << "\nIngrese la fila  (0-" << tam - 1 << ", o -1 para salir): "<<endl;
        cin >> fila;

        if (fila == -1) {
            cout << "\nSaliendo del juego...\n";
            break;
        }
 cout<<"columna donde colocar la pieza";
        cin >> col;

        cout << "Elija el número de pieza que desea colocar (1-" << numPiezas << "): ";
        cin >> eleccion;

        if (fila >= 0 && fila < tam &&
            col >= 0 && col < tam &&
            eleccion >= 1 && eleccion <= numPiezas) {

            tablero[fila][col] = (char)piezas[eleccion - 1];
        } else {
            cout << "Entrada inválida.\n";
            continue;
        }

      
        cout << "\n=== TABLERO ACTUALIZADO ===\n";
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                cout << tablero[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
