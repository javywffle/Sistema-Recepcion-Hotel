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
}void consultarCima() {
    if (pilaVacia()) {
        cout << "No hay llaves disponibles para consultar.\n";
        return;
    }
    cout << "La llave que esta en la cima es: " << cima->codigo << endl;
}

void mostrarLlaves() {
    if (pilaVacia()) {
        cout << "No hay llaves disponibles.\n";
        return;
    }

    NodoPila* actual = cima;
    cout << "Llaves disponibles desde la cima:\n";
    while (actual != NULL) {
        cout << actual->codigo << endl;
        actual = actual->siguiente;
    }
}

void contarLlaves() {
    int contador = 0;
    NodoPila* actual = cima;

    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }

    cout << "Llaves disponibles: " << contador << endl;
}

bool habitacionOcupada(int numero) {
    NodoLista* actual = inicio;

    while (actual != NULL) {
        if (actual->estado == 3 && actual->habitacion == numero) {
            return true;
        }
        actual = actual->siguiente;
    }

    return false;
}

void realizarCheckIn() {
    int codigo;
    cout << "Ingrese el codigo del huesped: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    NodoLista* huesped = buscarHuesped(codigo);
    if (huesped == NULL) {
        cout << "No se encontro el huesped.\n";
        return;
    }
    if (huesped->estado != 2) {
        cout << "El huesped debe ser atendido antes del check-in.\n";
        return;
    }
    if (pilaVacia()) {
        cout << "No hay llaves disponibles.\n";
        return;
    }

    int habitacion;
    cout << "Ingrese el numero de habitacion: ";
    cin >> habitacion;
    cin.ignore(10000, '\n');

    if (habitacion <= 0) {
        cout << "El numero de habitacion debe ser mayor que cero.\n";
        return;
    }

    if (habitacionOcupada(habitacion)) {
        cout << "Esa habitacion ya esta ocupada.\n";
        return;
    }

    int codigoLlave;
    if (desapilarLlave(codigoLlave)) {
        huesped->habitacion = habitacion;
        huesped->codigoLlave = codigoLlave;
        huesped->estado = 3;
        cout << "Check-in realizado correctamente.\n";
        cout << "Habitacion asignada: " << habitacion << endl;
        cout << "Llave entregada: " << codigoLlave << endl;
    } else {
        cout << "No hay llaves disponibles.\n";
    }
}

void realizarCheckOut() {
    int codigo;
    cout << "Ingrese el codigo del huesped: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    NodoLista* huesped = buscarHuesped(codigo);
    if (huesped == NULL) {
        cout << "No se encontro el huesped.\n";
        return;
    }
    if (huesped->estado != 3) {
        cout << "El huesped no tiene una habitacion asignada.\n";
        return;
    }

    apilarLlave(huesped->codigoLlave);
    cout << "Llave devuelta: " << huesped->codigoLlave << endl;
    huesped->codigoLlave = 0;
    huesped->habitacion = 0;
    huesped->estado = 4;
    cout << "Check-out realizado correctamente.\n";
}

void mostrarMenu() {
    cout << "\n====================================================\n";
    cout << "          SISTEMA DE RECEPCION DEL HOTEL\n";
    cout << "             CHECK-IN Y CHECK-OUT\n";
    cout << "====================================================\n";
    cout << "1. Recepcion y registro de huespedes\n";
    cout << "2. Cola de atencion\n";
    cout << "3. Check-in y check-out\n";
    cout << "4. Control de llaves\n";
    cout << "0. Salir del sistema\n";
    cout << "Seleccione una seccion: ";
}

void mostrarMenuHuespedes() {
    cout << "\n===== RECEPCION Y REGISTRO DE HUESPEDES =====\n";
    cout << "1. Registrar huesped\n";
    cout << "2. Buscar huesped por codigo\n";
    cout << "3. Mostrar huespedes\n";
    cout << "4. Actualizar datos del huesped\n";
    cout << "5. Eliminar huesped finalizado o con espera cancelada\n";
    cout << "6. Recorrer lista de huespedes\n";
    cout << "7. Contar huespedes registrados\n";
    cout << "8. Verificar si un codigo existe\n";
    cout << "0. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuCola() {
    cout << "\n===== COLA DE ATENCION EN RECEPCION =====\n";
    cout << "1. Mostrar cola de recepcion\n";
    cout << "2. Consultar huesped al frente\n";
    cout << "3. Contar huespedes en espera\n";
    cout << "4. Buscar huesped en la cola\n";
    cout << "5. Cancelar espera de un huesped\n";
    cout << "6. Atender siguiente huesped\n";
    cout << "0. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuEstadia() {
    cout << "\n===== CHECK-IN Y CHECK-OUT =====\n";
    cout << "1. Realizar check-in\n";
    cout << "2. Realizar check-out\n";
    cout << "0. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuLlaves() {
    cout << "\n===== CONTROL DE LLAVES =====\n";
    cout << "1. Mostrar llaves disponibles\n";
    cout << "2. Consultar llave en la cima\n";
    cout << "3. Verificar si la pila esta vacia\n";
    cout << "4. Contar llaves disponibles\n";
    cout << "0. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    int seccion = -1;
    int opcion;
    inicializarLlaves();

    do {
        mostrarMenu();
        cin >> seccion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion no valida. Ingrese un numero.\n";
            seccion = -1;
            continue;
        }
        cin.ignore(10000, '\n');

        if (seccion == 1) {
            do {
                mostrarMenuHuespedes();
                cin >> opcion;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Opcion no valida. Ingrese un numero.\n";
                    opcion = -1;
                    continue;
                }
                cin.ignore(10000, '\n');
                switch (opcion) {
                    case 1: registrarHuesped(); break;
                    case 2: buscarHuespedMenu(); break;
                    case 3: mostrarHuespedes(); break;
                    case 4: actualizarHuesped(); break;
                    case 5: eliminarHuesped(); break;
                    case 6: recorrerLista(); break;
                    case 7: contarHuespedes(); break;
                    case 8: verificarCodigoHuesped(); break;
                    case 0: break;
                    default: cout << "Opcion no valida.\n";
                }
            } while (opcion != 0);
        } else if (seccion == 2) {
            do {
                mostrarMenuCola();
                cin >> opcion;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Opcion no valida. Ingrese un numero.\n";
                    opcion = -1;
                    continue;
                }
                cin.ignore(10000, '\n');
                switch (opcion) {
                    case 1: mostrarCola(); break;
                    case 2: consultarFrenteCola(); break;
                    case 3: contarEnCola(); break;
                    case 4: buscarHuespedEnCola(); break;
                    case 5: cancelarEspera(); break;
                    case 6: atenderHuesped(); break;
                    case 0: break;
                    default: cout << "Opcion no valida.\n";
                }
            } while (opcion != 0);
        } else if (seccion == 3) {
            do {
                mostrarMenuEstadia();
                cin >> opcion;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Opcion no valida. Ingrese un numero.\n";
                    opcion = -1;
                    continue;
                }
                cin.ignore(10000, '\n');
                switch (opcion) {
                    case 1: realizarCheckIn(); break;
                    case 2: realizarCheckOut(); break;
                    case 0: break;
                    default: cout << "Opcion no valida.\n";
                }
            } while (opcion != 0);
        } else if (seccion == 4) {
            do {
                mostrarMenuLlaves();
                cin >> opcion;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Opcion no valida. Ingrese un numero.\n";
                    opcion = -1;
                    continue;
                }
                cin.ignore(10000, '\n');
                switch (opcion) {
                    case 1: mostrarLlaves(); break;
                    case 2: consultarCima(); break;
                    case 3:
                        if (pilaVacia()) {
                            cout << "La pila esta vacia.\n";
                        } else {
                            cout << "La pila contiene llaves disponibles.\n";
                        }
                        break;
                    case 4: contarLlaves(); break;
                    case 0: break;
                    default: cout << "Opcion no valida.\n";
                }
            } while (opcion != 0);
        } else if (seccion != 0) {
            cout << "Opcion no valida. Seleccione una seccion del 1 al 4 o 0 para salir.\n";
        }
    } while (seccion != 0);

    cout << "Saliendo del sistema.\n";
    return 0;
}
