#include <iostream>
#include <map>
using namespace std;
class Equipo {
    private:
        string nombre;
    public:
        Equipo(string n) { 
            nombre = n; 
        }
        string getNombre() const {
             return nombre; 
            }
    };
    
    class Partido {
    private:
        Equipo equipo1;
        Equipo equipo2;
        int golesEquipo1;
        int golesEquipo2;
    public:
        Partido(Equipo eq1, Equipo eq2, int g1, int g2)
            : equipo1(eq1), equipo2(eq2), golesEquipo1(g1), golesEquipo2(g2) {}
    
        Equipo getEquipo1() const {
             return equipo1;
             }
        Equipo getEquipo2() const { 
            return equipo2; 
        }
        int getGolesEquipo1() const {
             return golesEquipo1; 
            }
        int getGolesEquipo2() const { 
            return golesEquipo2; 
        }
    
        int getTotalGoles() const { 
            return golesEquipo1 + golesEquipo2;
         }
    };
    struct Estadistica {
        int puntos = 0;
        int golesAFavor = 0;
        int golesEnContra = 0;
    };
    void ordenarPartidos(vector<Partido> &partidos) {
        for (int i = 0; i < partidos.size() - 1; i++) {
            for (int j = 0; j < partidos.size() - i - 1; j++) {
                if (partidos[j].getTotalGoles() < partidos[j + 1].getTotalGoles()) {
                    Partido temp = partidos[j];
                    partidos[j] = partidos[j + 1];
                    partidos[j + 1] = temp;
                }
            }
        }
    };

    void ordenarPorPuntos(vector<pair<string, Estadistica>> &equipos) {
        for (int i = 0; i < equipos.size() - 1; i++) {
            for (int j = 0; j < equipos.size() - i - 1; j++) {
                if (equipos[j].second.puntos < equipos[j + 1].second.puntos) {
                    swap(equipos[j], equipos[j + 1]);
                }
            }
        }
    };
    int main() {
        Equipo UCC("UCC"), UNC("UNC"), UTN("UTN"), UNRC("UNRC"), UBP("UBP"), UES21("UES21");
    
        vector<Partido> partidos = {
            Partido(UNRC, UBP, 0, 0),
            Partido(UCC, UNRC, 3, 0),
            Partido(UTN, UBP, 0, 2),
            Partido(UNC, UES21, 3, 1),
            Partido(UBP, UES21, 2, 1),
            Partido(UNC, UNRC, 2, 2),
            Partido(UCC, UBP, 0, 2),
            Partido(UNC, UTN, 0, 1),
            Partido(UTN, UNRC, 0, 1),
            Partido(UCC, UNC, 2, 1),
            Partido(UCC, UES21, 2, 2),
            Partido(UNC, UBP, 1, 3),
            Partido(UTN, UES21, 1, 0),
            Partido(UNRC, UES21, 2, 3)
        };
    
        map<string, Estadistica> tabla;
    
        for (auto &p : partidos) {
            string e1 = p.getEquipo1().getNombre();
            string e2 = p.getEquipo2().getNombre();
            int g1 = p.getGolesEquipo1();
            int g2 = p.getGolesEquipo2();
    
            tabla[e1].golesAFavor += g1;
            tabla[e1].golesEnContra += g2;
            tabla[e2].golesAFavor += g2;
            tabla[e2].golesEnContra += g1;
    
            if (g1 > g2) tabla[e1].puntos += 3;
            else if (g2 > g1) tabla[e2].puntos += 3;
            else { tabla[e1].puntos++; tabla[e2].puntos++; }
        }

    ordenarPartidos(partidos);
    
        cout << "=== Partidos ordenados por cantidad total de goles ===\n";
        for (auto &p : partidos) {
            cout << p.getEquipo1().getNombre() << " " << p.getGolesEquipo1()
                 << " - " << p.getGolesEquipo2() << " " << p.getEquipo2().getNombre()
                 << " (Total: " << p.getTotalGoles() << ")\n";
        }

vector<pair<string, Estadistica>> ranking(tabla.begin(), tabla.end());
ordenarPorPuntos(ranking);

cout << "\n=== Tabla de posiciones (ordenada por puntos) ===\n";
for (int i = 0; i < ranking.size(); i++) {
    cout << i + 1 << ". " << ranking[i].first
         << " - " << ranking[i].second.puntos << " puntos"
         << " (" << ranking[i].second.golesAFavor << " GF, "
         << ranking[i].second.golesEnContra << " GC)" << endl;
}

return 0;
}
    

    