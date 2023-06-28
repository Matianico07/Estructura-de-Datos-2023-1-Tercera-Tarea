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
        for (int i = 0; i < static_cast<int>(clave.length()); i++) {
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
            cout << "El usuario ya se encuentra registrado" << endl;
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
            cout << "Usuario registrado con exito" << endl;

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
                cout << "sesion iniciada con exito" << endl;
                return true;
            }
            else {
                cout << "La clave ingresada no coincide" << endl;
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
                cout << "Posicion " << i << ": ";
                cout << "Usuario = " << HT[i].info->usuario << ", ";
                cout << "Contrasena = " << HT[i].info->contrasena << ", ";
                cout << "Clave de insercion = " << HT[i].clave << endl;
            }
        }
    }
};

int main() {
    Login login;

    login.crear_nuevo_usuario("Usuario1", "contraseña123");
    login.crear_nuevo_usuario("Usuario2", "contraseña123");
    login.crear_nuevo_usuario("Usuario3", "contraseña123");
    login.crear_nuevo_usuario("Usuario4", "contraseña123");
    login.crear_nuevo_usuario("Usuario5", "contraseña123");
    login.crear_nuevo_usuario("Usuario6", "contraseña123");
    login.crear_nuevo_usuario("Usuario7", "contraseña123");
    login.crear_nuevo_usuario("Usuario8", "contraseña123");
    login.crear_nuevo_usuario("Usuario9", "contraseña123");
    login.crear_nuevo_usuario("Usuario10", "contraseña123");

    login.mostrarTablaHash();

    login.iniciar_sesion("Usuario1", "contraseña123");
    login.iniciar_sesion("Usuario5", "contraseña123");
    login.iniciar_sesion("Usuario10", "contraseña123");
    login.iniciar_sesion("Usuario15", "contraseña123");
    login.iniciar_sesion("Usuario20", "contraseña123");
    login.iniciar_sesion("Usuario25", "contraseña123");
    login.iniciar_sesion("Usuario30", "contraseña1234");
    login.iniciar_sesion("Usuario35", "contraseña123");
    login.iniciar_sesion("Usuario30", "contraseña123");

    login.mostrarTablaHash();

    login.crear_nuevo_usuario("Usuario11", "contraseña123");
    login.crear_nuevo_usuario("Usuario12", "contraseña123");
    login.crear_nuevo_usuario("Usuario13", "contraseña123");
    login.crear_nuevo_usuario("Usuario14", "contraseña123");
    login.crear_nuevo_usuario("Usuario15", "contraseña123");
    login.crear_nuevo_usuario("Usuario16", "contraseña123");
    login.crear_nuevo_usuario("Usuario17", "contraseña123");
    login.crear_nuevo_usuario("Usuario18", "contraseña123");
    login.crear_nuevo_usuario("Usuario19", "contraseña123");
    login.crear_nuevo_usuario("Usuario20", "contraseña123");
    login.crear_nuevo_usuario("Usuario21", "contraseña123");
    login.crear_nuevo_usuario("Usuario22", "contraseña123");
    login.crear_nuevo_usuario("Usuario23", "contraseña123");
    login.crear_nuevo_usuario("Usuario24", "contraseña123");
    login.crear_nuevo_usuario("Usuario25", "contraseña123");
    login.crear_nuevo_usuario("Usuario26", "contraseña123");
    login.crear_nuevo_usuario("Usuario27", "contraseña123");
    login.crear_nuevo_usuario("Usuario28", "contraseña123");
    login.crear_nuevo_usuario("Usuario29", "contraseña123");
    login.crear_nuevo_usuario("Usuario30", "contraseña123");
    login.crear_nuevo_usuario("Usuario30", "contraseña1234");

    login.cambiar_clave("Usuario30", "contraseña1240");
    login.cambiar_clave("Usuario35", "contraseña1234");

    login.iniciar_sesion("Usuario1", "contraseña123");
    login.iniciar_sesion("Usuario5", "contraseña123");
    login.iniciar_sesion("Usuario10", "contraseña123");
    login.iniciar_sesion("Usuario15", "contraseña123");
    login.iniciar_sesion("Usuario20", "contraseña123");
    login.iniciar_sesion("Usuario25", "contraseña123");
    login.iniciar_sesion("Usuario30", "contraseña1234");
    login.iniciar_sesion("Usuario35", "contraseña123");
    login.iniciar_sesion("Usuario30", "contraseña123");


    login.mostrarTablaHash();

    return 0;
}

