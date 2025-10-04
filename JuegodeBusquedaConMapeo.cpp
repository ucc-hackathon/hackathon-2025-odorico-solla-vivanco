#include <iostream>
#include <string> //para los nombres de las habitaciones
#include <cstdlib> //para poder usar variables aleatorias
#include <ctime>
using namespace std;

class Habitacion
{
private:
    string nombre;
    string elemento;
    bool tomado; //para ver si el elemento se recogio

public:
    int norte, sur, este, oeste;

    Habitacion()
    {
        nombre = "";
        elemento = "";
        tomado = false;
        norte = sur = este = oeste = -1; //indicar que no hay conexion
    }

    Habitacion(string n)
    {
        nombre = n;
        tomado = false;
        norte = sur = este = oeste = -1;
        int aleatorio = rand() % 3; //randomizar elementos
        if (aleatorio == 1) 
            elemento = "alimento";//si es 1 en la habitacion hay alimento
        else if (aleatorio == 2)
            elemento = "arma";//si es 2 en la habitacion hay alimento
    }

    string getNombre() { return nombre; }
    string getElemento() { return elemento; }
    bool tieneElemento() { return (elemento != "" && !tomado); } //cambiar el estado a true si fue tomado para que no se recoga el mismo objeto

    void tomarElemento() { tomado = true; }
};

int main()
{
    srand(time(0)); //para que todos los elementos sean aleatorios x partida

    Habitacion habs[8];
    habs[1] = Habitacion("Habitacion 1");
    habs[2] = Habitacion("Habitacion 2");
    habs[3] = Habitacion("Habitacion 3");
    habs[4] = Habitacion("Habitacion 4");
    habs[5] = Habitacion("Habitacion 5");
    habs[6] = Habitacion("Habitacion 6");
    habs[7] = Habitacion("Habitacion 7");

    habs[1].sur = 3; //conexiones
    habs[2].sur = 4;
    habs[3].norte = 1;
    habs[3].este = 4;
    habs[4].norte = 2;
    habs[4].oeste = 3;
    habs[4].este = 5;
    habs[4].sur = 6;
    habs[5].oeste = 4;
    habs[6].norte = 4;
    habs[6].este = 7;
    habs[7].oeste = 6;

    int pasos = 10; //variables del juego, con max de 12 pasos y puntos iniciales 0 y la pose inicial es en 1
    int puntos = 0;
    int actual = 1;

    cout << "=== JUEGO DE BUSQUEDA ===" << endl;
    cout << "Comandos: Norte, Sur, Este, Oeste, Tomar, Salir" << endl;

    while (pasos > 0)
    {
        cout << "\nEstas ubicado en " << habs[actual].getNombre() << endl;
        if (habs[actual].tieneElemento())
        {
            cout << "Hay un " << habs[actual].getElemento() << " en esta habitacion." << endl;
        }

        cout << "Pasos restantes: " << pasos << " | Puntos: " << puntos << endl;
        cout << ">> ";
        string accion;
        cin >> accion;

        if (accion == "Norte")
        {
            if (habs[actual].norte != -1)
            {
                actual = habs[actual].norte;
                cout << "Te moves al norte." << endl;
            }
            else
                cout << "No podes avanzar al norte." << endl;
        }
        else if (accion == "Sur")
        {
            if (habs[actual].sur != -1)
            {
                actual = habs[actual].sur;
                cout << "Te moves al sur." << endl;
            }
            else
                cout << "No podes avanzar al sur." << endl;
        }
        else if (accion == "Este")
        {
            if (habs[actual].este != -1)
            {
                actual = habs[actual].este;
                cout << "Te moves al este." << endl;
            }
            else
                cout << "No podes avanzar al este." << endl;
        }
        else if (accion == "Oeste")
        {
            if (habs[actual].oeste != -1)
            {
                actual = habs[actual].oeste;
                cout << "Te moves al oeste." << endl;
            }
            else
                cout << "No podes avanzar al oeste." << endl;
        }
        else if (accion == "Tomar")
        {
            if (habs[actual].tieneElemento())
            {
                string elem = habs[actual].getElemento();
                habs[actual].tomarElemento();
                if (elem == "alimento")
                    puntos += 5;
                else if (elem == "arma")
                    puntos += 15;
                cout << "Has tomado un " << elem << ". Puntos +"
                     << (elem == "alimento" ? 5 : 15) << endl;
            }
            else
            {
                cout << "No hay nada que tomar aca" << endl;
            }
        }
        else if (accion == "Salir")
        {
            cout << "Has decidido salir del juego." << endl;
            break;
        }
        else
        {
            cout << "Comando no valido." << endl;
        }

        pasos--;
    }

    cout << "\n=== FIN DEL JUEGO ===" << endl;
    cout << "Puntaje final: " << puntos << endl;
    cout << "Gracias por jugar!" << endl;

    return 0;
}
