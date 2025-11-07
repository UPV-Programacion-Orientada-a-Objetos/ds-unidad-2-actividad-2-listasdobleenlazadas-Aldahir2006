#include "DataStructures.h"
#include <stdio.h> // Para printf

// --- ListaDeCarga ---

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        NodoCarga* aBorrar = actual;
        actual = actual->siguiente;
        delete aBorrar;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    if (cabeza == nullptr) {
        // La lista está vacía
        cabeza = nuevo;
        cola = nuevo;
    } else {
        // La lista no está vacía
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
}

void ListaDeCarga::imprimirMensaje() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        printf("%c", actual->dato);
        actual = actual->siguiente;
    }
}

// --- RotorDeMapeo ---

RotorDeMapeo::RotorDeMapeo() {
    cabeza = nullptr;
    NodoRotor* previo = nullptr;

    // Crear el alfabeto A-Z
    for (char c = 'A'; c <= 'Z'; ++c) {
        NodoRotor* nuevo = new NodoRotor(c);
        if (cabeza == nullptr) {
            cabeza = nuevo; // 'A' es la cabeza inicial
        }
        if (previo != nullptr) {
            previo->siguiente = nuevo;
            nuevo->previo = previo;
        }
        previo = nuevo;
    }

    // Unir la cola ('Z') con la cabeza ('A') para hacerlo circular
    NodoRotor* cola = previo;
    if (cabeza != nullptr && cola != nullptr) {
        cola->siguiente = cabeza;
        cabeza->previo = cola;
    }
}

RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;

    // Romper el ciclo para evitar un bucle infinito
    NodoRotor* cola = cabeza->previo;
    cola->siguiente = nullptr;

    NodoRotor* actual = cabeza;
    while (actual != nullptr) {
        NodoRotor* aBorrar = actual;
        actual = actual->siguiente;
        delete aBorrar;
    }
}

void RotorDeMapeo::rotar(int N) {
    if (cabeza == nullptr) return;

    if (N > 0) {
        for (int i = 0; i < N; ++i) {
            cabeza = cabeza->siguiente;
        }
    } else if (N < 0) {
        for (int i = 0; i < -N; ++i) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char in) {
    // Caracteres especiales (como 'Space') no se mapean
    if (in < 'A' || in > 'Z') {
        return in;
    }

    // Calcular el offset (A=0, B=1, ...)
    int offset = in - 'A';

    // Encontrar el carácter mapeado
    NodoRotor* mapeado = cabeza;
    for (int i = 0; i < offset; ++i) {
        mapeado = mapeado->siguiente;
    }

    return mapeado->dato;
}