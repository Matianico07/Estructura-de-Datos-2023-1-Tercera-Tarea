#include <iostream>
#include <string>
using namespace std;

#define VACIO -1

struct Info {
    string usuario;
    string contrasena;
};

struct Elemento {
    int clave;
    Info* info;
};

class Login {
private:
    Elemento* HT;
    int capacidad;
    int total;

public:
    Login() {
        capacidad = 31; // Capacidad inicial de la tabla hash
        total = 0;
        HT = new Elemento[capacidad];

        for (int i = 0; i < capacidad; i++) {
            HT[i].clave = VACIO;
            HT[i].info = nullptr;
        }
    }

    ~Login() {
        for (int i = 0; i < capacidad; i++) {
            if (HT[i].info != nullptr) {
                delete HT[i].info;
            }
        }

        delete[] HT;
    }

    int p(string clave, int capacidad) {
        int suma = 0;
        for (int i = 0; i < clave.length(); i++) {
            suma += int(clave[i]);
        }

        return suma % capacidad;
    }

    double factorCarga() {
        return (double)total / capacidad;
    }

    void redimensionarTabla() {
        int nuevaCapacidad = capacidad * 2;
        Elemento* nuevaHT = new Elemento[nuevaCapacidad];

        for (int i = 0; i < nuevaCapacidad; i++) {
            nuevaHT[i].clave = VACIO;
            nuevaHT[i].info = nullptr;
        }

        for (int i = 0; i < capacidad; i++) {
            if (HT[i].info != nullptr) {
                int pos = p(HT[i].info->usuario, nuevaCapacidad);
                int j = 1;
                int inicio = pos;

                while (nuevaHT[pos].clave != VACIO) {
                    pos = (inicio + j * j) % nuevaCapacidad;
                    j++;
                }

                nuevaHT[pos].clave = HT[i].clave;
                nuevaHT[pos].info = HT[i].info;
            }
        }

        delete[] HT;

        HT = nuevaHT;
        capacidad = nuevaCapacidad;
    }

    bool crear_nuevo_usuario(string usuario, string clave) {
        int pos = p(usuario, capacidad);
        int i = 1;
        int inicio = pos;

        while (HT[pos].clave != VACIO && HT[pos].info->usuario != usuario) {
            pos = (inicio + i * i) % capacidad;
            i++;
        }

        if (HT[pos].info != nullptr && HT[pos].info->usuario == usuario) {
            cout << "El usuario ya existe" << endl;
            return false;
        }
        else {
            if (clave.length() < 8) {
                cout << "La clave debe tener al menos 8 caracteres" << endl;
                return false;
            }

            HT[pos].clave = pos;
            HT[pos].info = new Info;
            HT[pos].info->usuario = usuario;
            HT[pos].info->contrasena = clave;
            total++;
            cout << "Usuario registrado con éxito" << endl;

            if (factorCarga() > 0.7) {
                redimensionarTabla();
            }

            return true;
        }
    }

    bool iniciar_sesion(string usuario, string clave) {
        int pos = p(usuario, capacidad);
        int i = 1;
        int inicio = pos;

        while (HT[pos].clave != VACIO && HT[pos].info->usuario != usuario) {
            pos = (inicio + i * i) % capacidad;
            i++;
        }

        if (HT[pos].info != nullptr && HT[pos].info->usuario == usuario) {
            if (HT[pos].info->contrasena == clave) {
                cout << "Inicio de sesión exitoso" << endl;
                return true;
            }
            else {
                cout << "Clave incorrecta" << endl;
                return false;
            }
        }
        else {
            cout << "El usuario no se encuentra registrado" << endl;
            return false;
        }
    }

    bool cambiar_clave(string usuario, string nuevaClave) {
        int pos = p(usuario, capacidad);
        int i = 1;
        int inicio = pos;

        while (HT[pos].clave != VACIO && HT[pos].info->usuario != usuario) {
            pos = (inicio + i * i) % capacidad;
            i++;
        }

        if (HT[pos].info != nullptr && HT[pos].info->usuario == usuario) {
            if (nuevaClave.length() < 8) {
                cout << "La clave debe tener al menos 8 caracteres" << endl;
                return false;
            }

            HT[pos].info->contrasena = nuevaClave;
            cout << "Cambio de clave exitoso" << endl;
            return true;
        }
        else {
            cout << "El usuario no se encuentra registrado" << endl;
            return false;
        }
    }

    void mostrarTablaHash() {
        for (int i = 0; i < capacidad; i++) {
            if (HT[i].info != nullptr) {
                cout << "Posición " << i << ": ";
                cout << "Usuario = " << HT[i].info->usuario << ", ";
                cout << "Contraseña = " << HT[i].info->contrasena << ", ";
                cout << "Clave de inserción = " << HT[i].clave << endl;
            }
        }
    }
};

int main() {
    Login login;

    login.crear_nuevo_usuario("Scathach", "contraseña123");
    login.crear_nuevo_usuario("quiet", "contraseña123");
    login.crear_nuevo_usuario("daphne", "contraseña123");
    login.crear_nuevo_usuario("ishtar", "contraseña123");
    login.crear_nuevo_usuario("thor", "contraseña123");
    login.crear_nuevo_usuario("Matias", "contraseña123");
    login.crear_nuevo_usuario("arkantos", "contraseña123");
    login.crear_nuevo_usuario("alice", "contraseña123");
    login.crear_nuevo_usuario("ereshkigal", "contraseña123");

    login.mostrarTablaHash();

    login.iniciar_sesion("selendis", "saludo");
    login.iniciar_sesion("ishtar", "contraseña123");
    login.iniciar_sesion("arkantos", "contraseña123");
    login.iniciar_sesion("Matias", "contraseña123");
    login.iniciar_sesion("leia", "saludo");
    login.iniciar_sesion("quiet", "contraseña123");
    login.iniciar_sesion("Walker", "patata");
    login.iniciar_sesion("loki", "patata");

    login.cambiar_clave("thor", "nuevaclave");
    login.cambiar_clave("arkantos", "nuevaclave");

    login.iniciar_sesion("thor", "contraseña123");
    login.iniciar_sesion("thor", "nuevaclave");

    login.mostrarTablaHash();

    return 0;
}

