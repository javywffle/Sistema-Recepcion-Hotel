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
