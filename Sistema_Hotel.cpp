#include <iostream> // Definicion de estructuras, nodos y punteros
#include <string>
using namespace std; 

struct NodoLista {
    int codigo;
    string nombre;
    string documento;
    int tipoCliente;
    int estado;
    int habitacion;
    int codigoLlave;            
    NodoLista* siguiente;       
};

struct NodoCola {
    int codigo;              
    int prioridad;             
    NodoCola* siguiente;      
};

struct NodoPila {
    int codigo;                 
    NodoPila* siguiente;       
};

NodoLista* inicio = NULL;       
NodoLista* fin = NULL;         

NodoCola* frente = NULL;     
NodoCola* finCola = NULL;       

NodoPila* cima = NULL;          

int siguienteCodigo = 1;

NodoLista* buscarHuesped(int codigo) {
    NodoLista* actual = inicio;

    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }

    return NULL;
}

bool codigoExiste(int codigo) {
    if (buscarHuesped(codigo) != NULL) {
        return true;
    }
    return false;
}

void insertarCola(int codigo, int prioridad) {
    NodoCola* nuevo = new NodoCola;
    nuevo->codigo = codigo;
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;

    if (frente == NULL || prioridad < frente->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;

        if (finCola == NULL) {
            finCola = nuevo;
        }
    } else {
        NodoCola* actual = frente;

        while (actual->siguiente != NULL &&
               actual->siguiente->prioridad <= prioridad) {
            actual = actual->siguiente;
        }

        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;

        if (nuevo->siguiente == NULL) {
            finCola = nuevo;
        }
    }
}

void apilarLlave(int codigo) {
    NodoPila* nuevo = new NodoPila;
    nuevo->codigo = codigo;
    nuevo->siguiente = cima;
    cima = nuevo;
}

bool desapilarLlave(int &codigo) {
    if (cima == NULL) {
        return false;
    }

    NodoPila* auxiliar = cima;
    codigo = auxiliar->codigo;
    cima = cima->siguiente;
    delete auxiliar;
    return true;
}

bool pilaVacia() {
    return cima == NULL;
}

void inicializarLlaves() {
    for (int i = 1; i <= 10; i++) {
        apilarLlave(i);
    }
}

void mostrarDatosHuesped(NodoLista* huesped) {
    cout << "\nCodigo: " << huesped->codigo << endl;
    cout << "Nombre: " << huesped->nombre << endl;
    cout << "Documento: " << huesped->documento << endl;

    if (huesped->tipoCliente == 1) {
        cout << "Tipo de cliente: VIP" << endl;
    } else {
        cout << "Tipo de cliente: Regular" << endl;
    }

    if (huesped->estado == 1) {
        cout << "Estado: En espera" << endl;
    } else if (huesped->estado == 2) {
        cout << "Estado: Atendido" << endl;
    } else if (huesped->estado == 3) {
        cout << "Estado: Alojado" << endl;
    } else if (huesped->estado == 4) {
        cout << "Estado: Finalizado" << endl;
    } else {
        cout << "Estado: Espera cancelada" << endl;
    }

    cout << "Habitacion: " << huesped->habitacion << endl;
    cout << "Codigo de llave: " << huesped->codigoLlave << endl;
}

void registrarHuesped() {
    NodoLista* nuevo = new NodoLista;
    nuevo->codigo = siguienteCodigo;
    siguienteCodigo++;

    cout << "Ingrese el nombre del huesped: ";
    getline(cin, nuevo->nombre);

    cout << "Ingrese el documento del huesped: ";
    getline(cin, nuevo->documento);

    cout << "Tipo de cliente (1 = VIP, 2 = Regular): ";
    cin >> nuevo->tipoCliente;

    while (nuevo->tipoCliente != 1 && nuevo->tipoCliente != 2) {
        cout << "Opcion no valida. Ingrese 1 para VIP o 2 para Regular: ";
        cin >> nuevo->tipoCliente;
    }
    cin.ignore(10000, '\n');

    nuevo->estado = 1;
    nuevo->habitacion = 0;
    nuevo->codigoLlave = 0;
    nuevo->siguiente = NULL;

    if (inicio == NULL) {
        inicio = nuevo;
        fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        fin = nuevo;
    }

    insertarCola(nuevo->codigo, nuevo->tipoCliente);

    cout << "Huesped registrado correctamente." << endl;
    cout << "Su codigo es: " << nuevo->codigo << endl;
}

void buscarHuespedMenu() {
    int codigo;
    cout << "Ingrese el codigo del huesped: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    NodoLista* huesped = buscarHuesped(codigo);

    if (huesped == NULL) {
        cout << "No se encontro el huesped.\n";
    } else {
        mostrarDatosHuesped(huesped);
    }
}

void mostrarHuespedes() {
    if (inicio == NULL) {
        cout << "No hay huespedes registrados.\n";
        return;
    }

    NodoLista* actual = inicio;
    while (actual != NULL) {
        mostrarDatosHuesped(actual);
        cout << "--------------------------\n";
        actual = actual->siguiente;
    }
}

void recorrerLista() {
    if (inicio == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }

    NodoLista* actual = inicio;
    cout << "Recorrido de la lista de huespedes:\n";
    while (actual != NULL) {
        cout << "Codigo: " << actual->codigo
             << " | Nombre: " << actual->nombre << endl;
        actual = actual->siguiente;
    }
}

void contarHuespedes() {
    int contador = 0;
    NodoLista* actual = inicio;

    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }

    cout << "Total de huespedes registrados: " << contador << endl;
}

void verificarCodigoHuesped() {
    int codigo;
    cout << "Ingrese el codigo que desea verificar: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    if (codigoExiste(codigo)) {
        cout << "El codigo ya esta registrado.\n";
    } else {
        cout << "El codigo no esta registrado.\n";
    }
}

void actualizarHuesped() {
    int codigo;
    cout << "Ingrese el codigo del huesped que desea actualizar: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    NodoLista* huesped = buscarHuesped(codigo);
    if (huesped == NULL) {
        cout << "No se encontro el huesped.\n";
        return;
    }

    cout << "Ingrese el nuevo nombre: ";
    getline(cin, huesped->nombre);
    cout << "Ingrese el nuevo documento: ";
    getline(cin, huesped->documento);
    cout << "Datos del huesped actualizados correctamente.\n";
}

void eliminarHuesped() {
    int codigo;
    cout << "Ingrese el codigo del huesped que desea eliminar: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    NodoLista* actual = inicio;
    NodoLista* anterior = NULL;

    while (actual != NULL && actual->codigo != codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "No se encontro el huesped.\n";
        return;
    }

    if (actual->estado != 4 && actual->estado != 5) {
        cout << "Solo se pueden eliminar estadias finalizadas o esperas canceladas.\n";
        return;
    }

    if (anterior == NULL) {
        inicio = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    if (actual == fin) {
        fin = anterior;
    }

    delete actual;
    cout << "Huesped eliminado correctamente.\n";
}
