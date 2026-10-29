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
