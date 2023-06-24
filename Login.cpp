#include <iostream>
#include <string>
#define VACIO " "

using namespace std;

typedef string tipoClave;

struct tipoInfo {
    string usuario;
    string contrasena;
};

struct ranura {
    tipoClave clave;
    tipoInfo *info;
};

class Login {
private:
    static const int Capacidad_Inicial = 32;  // Tamaño inicial del arreglo
    ranura* HT;  // Puntero al arreglo
    int capacidad;  // Capacidad actual del arreglo
    float total, conocidos, desconocidos;

public:
    Login() {
        capacidad = Capacidad_Inicial;
        HT = new ranura[capacidad];  // Asigna memoria para el arreglo
        for (int i = 0; i < capacidad; i++) {
            HT[i].clave = VACIO;
            HT[i].info = nullptr;  // Inicializa el puntero como nullptr
        }
    }

    int h(string x) {
        int i, sum;
        for (sum = 0, i = 0; x[i] != '\0'; i++) {
            sum += (int)x[i];
        }
        return sum;
    }

    int p(const tipoClave& clave) {
        int index = h(clave) % capacidad;
        int i = 1;
        int originalIndex = index;

        while (HT[index].clave != VACIO) {
            index = (originalIndex + i * i) % capacidad; // próxima ranura en la secuencia
            i++;
        }
        return index;
    }

    bool crear_nuevo_usuario(string usuario, string clave) {
        // Verificar el factor de carga, si supera el factor de carga duplicar el tamaño de la tabla hash
        double factorCarga = total / capacidad;
        if (factorCarga > 0.7) {
            duplicarCapacidad();
        }

        // Insertar el elemento en el arreglo
        int inicio, i;
        int pos = inicio = h(usuario);
        for (i = 1; HT[pos].clave != VACIO && HT[pos].clave != usuario; i++) {
            pos = (inicio + i * i) % capacidad; // próxima ranura en la secuencia
        }
        if (HT[pos].clave == usuario) {
            // Clave repetida, crear un nuevo objeto tipoInfo solo si el puntero es nullptr
            if (HT[pos].info == nullptr) {
                HT[pos].info = new tipoInfo();
            }
            else {
                return false; // inserción no exitosa: clave repetida
            }
        }
        else {
            HT[pos].info = new tipoInfo(); // Crear un nuevo objeto tipoInfo
        }

        HT[pos].clave = usuario;
        HT[pos].info->usuario = usuario;
        HT[pos].info->contrasena = clave;

        // Actualizar contadores
        total++;
        conocidos++;

        return true; // inserción exitosa
    }

    void duplicarCapacidad() {
        int nuevaCapacidad = capacidad * 2;
        ranura* newHT = new ranura[nuevaCapacidad];

        // Copiar los elementos existentes al nuevo arreglo
        for (int i = 0; i < capacidad; i++) {
            newHT[i].clave = HT[i].clave;
            newHT[i].info = HT[i].info;
        }

        // Inicializar los nuevos espacios en el arreglo
        for (int i = capacidad; i < nuevaCapacidad; i++) {
            newHT[i].clave = VACIO;
            newHT[i].info = nullptr; // Inicializar los punteros como nullptr
        }

        // Liberar memoria del arreglo anterior
        delete[] HT;

        // Actualizar puntero y capacidad
        HT = newHT;
        capacidad = nuevaCapacidad;
    }

    bool iniciar_sesion(string usuario, string clave) {
        // Dado el nombre usuario, verificar si el usuario está registrado
        int pos = h(usuario);
        int i = 1;
        int inicio = pos;

        while (HT[pos].clave != VACIO && HT[pos].clave != usuario) {
            pos = (inicio + i * i) % capacidad; // Próxima ranura en la secuencia
            i++;
        }

        if (HT[pos].clave == usuario) {
            if (HT[pos].info->contrasena == clave) {
                cout << "Sesion iniciada con exito" << endl;
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
};

int main() {
    Login login;

    // Insertar elementos de prueba
    login.crear_nuevo_usuario("1", "contraseña123");
    login.crear_nuevo_usuario("2", "patata");
    login.crear_nuevo_usuario("3", "contraseña123");
    login.crear_nuevo_usuario("4", "contraseña123");
    login.crear_nuevo_usuario("hola", "saludo");

    // Iniciar sesión
    login.iniciar_sesion("1", "contraseña123");
    login.iniciar_sesion("2", "contraseña123");
    login.iniciar_sesion("3", "contraseña123");
    login.iniciar_sesion("4", "contraseña123");
    login.iniciar_sesion("5", "sb");
    login.iniciar_sesion("36", "ADM");
    login.iniciar_sesion("hola", "saludo");


    return 0;
}


