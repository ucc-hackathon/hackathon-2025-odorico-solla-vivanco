#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_LIBROS = 50;
const int MAX_USUARIOS = 30;


class Libro {
private:
    int codigo;
    string titulo;
    string autor;
    int anioPublicacion;
    string categoria;
    bool prestado;
    int vecesPrestado;
    int legajoPrestador;

public:
    Libro();
    void cargar();
    void prestar(int legajo);
    void devolver();
    void mostrar();
    string getTitulo();
    string getAutor();
    string getCategoria();
    bool estaPrestado();
    int getVecesPrestado();
};

Libro::Libro() {
    codigo = 0;
    titulo = "";
    autor = "";
    anioPublicacion = 0;
    categoria = "";
    prestado = false;
    vecesPrestado = 0;
    legajoPrestador = 0;
}

void Libro::cargar() {
    cout << "Codigo: ";
    cin >> codigo;
    cin.ignore();
    cout << "Titulo: ";
    getline(cin, titulo);
    cout << "Autor: ";
    getline(cin, autor);
    cout << "Anio de publicación: ";
    cin >> anioPublicacion;
    cin.ignore();
    cout << "Categoria: ";
    getline(cin, categoria);
    prestado = false;
    vecesPrestado = 0;
    legajoPrestador = 0;
}

void Libro::prestar(int legajo) {
    if (!prestado) {
        prestado = true;
        vecesPrestado++;
        legajoPrestador = legajo;
        cout << "Libro prestado con exito.\n";
    } else {
        cout << "El libro ya esta prestado.\n";
    }
}

void Libro::devolver() {
    if (prestado) {
        prestado = false;
        legajoPrestador = 0;
        cout << "Libro devuelto con exito.\n";
    } else {
        cout << "El libro no estaba prestado.\n";
    }
}

void Libro::mostrar() {
    cout << "\nCodigo: " << codigo;
    cout << "\nTítulo: " << titulo;
    cout << "\nAutor: " << autor;
    cout << "\nAño: " << anioPublicacion;
    cout << "\nCategoría: " << categoria;
    cout << "\nPrestado: " << (prestado ? "Si" : "No");
    if (prestado)
        cout << " (Legajo usuario: " << legajoPrestador << ")";
    cout << "\n";
}

string Libro::getTitulo() { return titulo; }
string Libro::getAutor() { return autor; }
string Libro::getCategoria() { return categoria; }
bool Libro::estaPrestado() { return prestado; }
int Libro::getVecesPrestado() { return vecesPrestado; }


class Usuario {
private:
    string nombre;
    int legajo;
    string tipo; 
    int prestamos;
    string extra; 

public:
    Usuario();
    void cargar();
    void mostrar();
    void sumarPrestamo();
    int getLegajo();
    string getTipo();
    string getNombre();
    int getPrestamos();
};

Usuario::Usuario() {
    nombre = "";
    legajo = 0;
    tipo = "";
    prestamos = 0;
    extra = "";
}

void Usuario::cargar() {
    cout << "Ingrese tipo de usuario (1=Alumno, 2=Profesor): ";
    int op;
    cin >> op;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Legajo: ";
    cin >> legajo;
    cin.ignore();

    if (op == 1) {
        tipo = "Alumno";
        cout << "Anio de cursado: ";
        getline(cin, extra);
    } else {
        tipo = "Profesor";
        cout << "Area de especialización: ";
        getline(cin, extra);
    }

    prestamos = 0;
}

void Usuario::mostrar() {
    cout << "\nTipo: " << tipo;
    cout << "\nNombre: " << nombre;
    cout << "\nLegajo: " << legajo;
    if (tipo == "Alumno")
        cout << "\nAño de cursado: " << extra;
    else
        cout << "\nArea: " << extra;
    cout << "\nLibros prestados: " << prestamos << "\n";
}

int Usuario::getLegajo() { return legajo; }
string Usuario::getTipo() { return tipo; }
string Usuario::getNombre() { return nombre; }
void Usuario::sumarPrestamo() { prestamos++; }
int Usuario::getPrestamos() { return prestamos; }






class Biblioteca {
private:
    Libro libros[MAX_LIBROS];
    Usuario usuarios[MAX_USUARIOS];
    int cantidadLibros;
    int cantidadUsuarios;

public:
    Biblioteca();
    void registrarLibro();
    void registrarUsuario();
    void mostrarLibros();
    void mostrarUsuarios();
    void prestarLibro();
    void devolverLibro();
    void listarLibrosDisponibles();
    void listarLibrosPrestados();
    void buscarPorCategoria();
    void buscarPorAutor();
    void top3MasPrestados();
    void usuarioConMasPrestamos();
};

Biblioteca::Biblioteca() {
    cantidadLibros = 0;
    cantidadUsuarios = 0;
}

void Biblioteca::registrarLibro() {
    if (cantidadLibros < MAX_LIBROS) {
        cout << "\n--- Registrar nuevo libro ---\n";
        libros[cantidadLibros].cargar();
        cantidadLibros++;
    } else {
        cout << "Limite de libros alcanzado.\n";
    }
}

void Biblioteca::registrarUsuario() {
    if (cantidadUsuarios < MAX_USUARIOS) {
        cout << "\n--- Registrar nuevo usuario ---\n";
        usuarios[cantidadUsuarios].cargar();
        cantidadUsuarios++;
    } else {
        cout << "Limite de usuarios alcanzado.\n";
    }
}

void Biblioteca::mostrarLibros() {
    if (cantidadLibros == 0)
        cout << "No hay libros registrados.\n";
    else
        for (int i = 0; i < cantidadLibros; i++)
            libros[i].mostrar();
}

void Biblioteca::mostrarUsuarios() {
    if (cantidadUsuarios == 0)
        cout << "No hay usuarios registrados.\n";
    else
        for (int i = 0; i < cantidadUsuarios; i++)
            usuarios[i].mostrar();
}

void Biblioteca::prestarLibro() {
    int legajo;
    string titulo;
    cout << "Legajo del usuario: ";
    cin >> legajo;
    cin.ignore();
    cout << "Titulo del libro: ";
    getline(cin, titulo);

    int posUsuario = -1;
    for (int i = 0; i < cantidadUsuarios; i++)
        if (usuarios[i].getLegajo() == legajo)
            posUsuario = i;

    if (posUsuario == -1) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    for (int i = 0; i < cantidadLibros; i++) {
        if (libros[i].getTitulo() == titulo) {
            libros[i].prestar(legajo);
            usuarios[posUsuario].sumarPrestamo();
            return;
        }
    }
    cout << "Libro no encontrado.\n";
}

void Biblioteca::devolverLibro() {
    string titulo;
    cout << "Titulo del libro a devolver: ";
    cin.ignore();
    getline(cin, titulo);

    for (int i = 0; i < cantidadLibros; i++) {
        if (libros[i].getTitulo() == titulo) {
            libros[i].devolver();
            return;
        }
    }
    cout << "Libro no encontrado.\n";
}

void Biblioteca::listarLibrosDisponibles() {
    cout << "\n--- Libros disponibles ---\n";
    for (int i = 0; i < cantidadLibros; i++)
        if (!libros[i].estaPrestado())
            libros[i].mostrar();
}

void Biblioteca::listarLibrosPrestados() {
    cout << "\n--- Libros prestados ---\n";
    for (int i = 0; i < cantidadLibros; i++)
        if (libros[i].estaPrestado())
            libros[i].mostrar();
}

void Biblioteca::buscarPorCategoria() {
    string cat;
    cout << "Ingrese categoria a buscar: ";
    cin.ignore();
    getline(cin, cat);
    for (int i = 0; i < cantidadLibros; i++)
        if (libros[i].getCategoria() == cat)
            libros[i].mostrar();
}

void Biblioteca::buscarPorAutor() {
    string aut;
    cout << "Ingrese autor a buscar: ";
    cin.ignore();
    getline(cin, aut);
    for (int i = 0; i < cantidadLibros; i++)
        if (libros[i].getAutor() == aut)
            libros[i].mostrar();
}

void Biblioteca::top3MasPrestados() {
    if (cantidadLibros == 0) {
        cout << "No hay libros cargados.\n";
        return;
    }
    for (int i = 0; i < cantidadLibros - 1; i++) {
        for (int j = 0; j < cantidadLibros - i - 1; j++) {
            if (libros[j].getVecesPrestado() < libros[j + 1].getVecesPrestado()) {
                Libro temp = libros[j];
                libros[j] = libros[j + 1];
                libros[j + 1] = temp;
            }
        }
    }
    cout << "\n--- Top 3 libros mas prestados ---\n";
    int limite = (cantidadLibros < 3) ? cantidadLibros : 3;
    for (int i = 0; i < limite; i++)
        libros[i].mostrar();
}

void Biblioteca::usuarioConMasPrestamos() {
    if (cantidadUsuarios == 0) {
        cout << "No hay usuarios registrados.\n";
        return;
    }
    int maxPrestamos = -1;
    int posMax = 0;
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].getPrestamos() > maxPrestamos) {
            maxPrestamos = usuarios[i].getPrestamos();
            posMax = i;
        }
    }
    cout << "\nUsuario con mas prestamos:\n";
    usuarios[posMax].mostrar();
}






int main() {
    Biblioteca b;
    int op;

    do {
        cout << "\n===== MENU BIBLIOTECA DIGITAL =====\n";
        cout << "1. Registrar libro\n";
        cout << "2. Registrar usuario\n";
        cout << "3. Mostrar libros\n";
        cout << "4. Mostrar usuarios\n";
        cout << "5. Prestar libro a usuario\n";
        cout << "6. Devolver libro\n";
        cout << "7. Listar libros disponibles\n";
        cout << "8. Listar libros prestados\n";
        cout << "9. Buscar por categoria\n";
        cout << "10. Buscar por autor\n";
        cout << "11. Top 3 libros más prestados\n";
        cout << "12. Usuario con mas prestamos\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
        case 1: b.registrarLibro(); break;
        case 2: b.registrarUsuario(); break;
        case 3: b.mostrarLibros(); break;
        case 4: b.mostrarUsuarios(); break;
        case 5: b.prestarLibro(); break;
        case 6: b.devolverLibro(); break;
        case 7: b.listarLibrosDisponibles(); break;
        case 8: b.listarLibrosPrestados(); break;
        case 9: b.buscarPorCategoria(); break;
        case 10: b.buscarPorAutor(); break;
        case 11: b.top3MasPrestados(); break;
        case 12: b.usuarioConMasPrestamos(); break;
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opción inválida.\n";
        }

    } while (op != 0);

    return 0;
}
