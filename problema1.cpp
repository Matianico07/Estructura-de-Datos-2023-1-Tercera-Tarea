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

/*****
*   constructor Login
*****
*   constructor de la clase Login
*   crea la tabla de hash y coloca todos sus ranuras vacias
*****
*   Input:
*       void
*****
*   Returns:
*       void
*****/

    Login() {
        capacidad = 31; // Capacidad inicial de la tabla hash
        total = 0;
        HT = new Elemento[capacidad];

        for (int i = 0; i < capacidad; i++) {
            HT[i].clave = VACIO;
            HT[i].info = nullptr;
        }
    }

/*****
*   Destructor Login
*****
*   Vacia la tabla hash y la elimina el puntero
*****
*   Input:
*       void
*****
*   Returns:
*       void
*****/

    ~Login() {
        for (int i = 0; i < capacidad; i++) {
            if (HT[i].info != nullptr) {
                delete HT[i].info;
            }
        }

        delete[] HT;
    }

/*****
*   int p
*****
*   es la estrategia de resolucion de colisiones 
*****
*   Input:
*       string clave :  string para definir la ranura de la tabla hash a insertar la informacion
*       int capacidad : tamano de la tabla de hash 
*****
*   Returns:
*       int (suma%capacidad) : posicion en la tabla hash a insertar
*****/

    int p(string clave, int capacidad) {
        int suma = 0;
        for (int i = 0; i < static_cast<int>(clave.length()); i++) {
            suma += int(clave[i]);
        }

        return suma % capacidad;
    }

/*****
*   double factorCArga
*****
*   Calcular el factor de carga de la tabla de hash
*****
*   Input:
*       void
*****
*   Returns:
*       double (total/capacidad) : factor de carga actual de la tabla de hash
*****/

    double factorCarga() {
        return (double)total / capacidad;
    }

/*****
*   void redimensionarTabla
*****
*   Duplicar la capacidad de la tabla de hash
*****
*   Input:
*       void
*****
*   Returns:
*       void
*****/

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

/*****
*   bool crear_nuevo_usuario
*****
*   crear una nueva cuenta de usuario e insertar en la tabla de hash
*   
*****
*   Input:
*       string usuario : nombre de usuario que tendra la cuenta
*       string clave : la contrasena que tendra la cuenta
*****
*   Returns:
*       bool : verdadero si el registro fue exitoso, falso en caso contrario
*****/

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
            if (usuario.length() > 32) {
                cout << "El nombre de usuario debe tener maximo 32 caracteres" << endl;
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

/*****
*   bool iniciar_sesion
*****
*   iniciar sesion de una cuenta contenida en la tabla de hash
*****
*   Input:
*       string usuario : nombre de usuario de la persona que quiere iniciar sesion
*       string clave : contrasena de la persona que quiere iniciar sesion
*****
*   Returns:
*       bool : verdadero si el inicio de sesion fue exitoso, falso en caso contrario
*****/

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

/*****
*   bool cambiar_clave
*****
*   Funcion que cambia la contrasena que usa un usuario para iniciar sesion
*****
*   Input:
*       string usuario : nombre del usuario que desea cambiar contrasena   
*       string nuevaClave : nueva contrasena que desea usar el usuario
*****
*   Returns:
*       bool : verdadero si el cambio de clave fue exitoso, falso en caso contrario
*****/

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

/*****
*   void mostrarTablaHash
*****
*   Funcion que muestra la informacion contenida dentro de las ranuras de la tabla de hash
*****
*   Input:
*       void
*****
*   Returns:
*       void
*****/

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

/*****
*   int main
*****
*   Funcion para usar la terminal y usar las funciones del TDA login
*****
*   Input:
*       void
*****
*   Returns:
*       int : ejecucion exitosa del programa
*****/

int main() {
    Login login;
    bool flag = true;
    string instruccion, nombre_usuario, contrasenas;
    while (flag){
        cin >> instruccion;     
        if(instruccion == "FINALIZAR"){
            break;
        }
        if (instruccion == "REGISTRAR"){
            cin >> nombre_usuario >> contrasenas;
            login.crear_nuevo_usuario(nombre_usuario, contrasenas);
        } else if(instruccion == "INICIAR_SESION"){
            cin >> nombre_usuario >> contrasenas;
            login.iniciar_sesion(nombre_usuario, contrasenas);
        } else if(instruccion == "ACTUALIZAR"){
            cin >> nombre_usuario >> contrasenas;
            login.cambiar_clave(nombre_usuario, contrasenas);
        }  
    }
    return 0;
}


