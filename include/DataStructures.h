#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

/**
 * @file DataStructures.h
 * @brief Define las estructuras de datos manuales (ListaDeCarga y RotorDeMapeo).
 */

// --- Nodo para la Lista de Carga ---

/**
 * @struct NodoCarga
 * @brief Nodo para la lista doblemente enlazada (ListaDeCarga).
 */
struct NodoCarga {
    char dato;          //!< El carácter decodificado.
    NodoCarga* previo;  //!< Puntero al nodo anterior.
    NodoCarga* siguiente; //!< Puntero al nodo siguiente.

    /**
     * @brief Constructor del NodoCarga.
     * @param d El carácter a almacenar.
     */
    NodoCarga(char d) : dato(d), previo(nullptr), siguiente(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Implementación de una lista doblemente enlazada para almacenar el mensaje.
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza; //!< Puntero al primer nodo.
    NodoCarga* cola;   //!< Puntero al último nodo.

public:
    ListaDeCarga();
    ~ListaDeCarga();

    /**
     * @brief Inserta un carácter al final de la lista.
     * @param dato El carácter decodificado a insertar.
     */
    void insertarAlFinal(char dato);

    /**
     * @brief Imprime el mensaje ensamblado en la consola.
     */
    void imprimirMensaje();
};

// --- Nodo para el Rotor de Mapeo ---

/**
 * @struct NodoRotor
 * @brief Nodo para la lista circular doblemente enlazada (RotorDeMapeo).
 */
struct NodoRotor {
    char dato;        //!< El carácter del alfabeto (A-Z).
    NodoRotor* previo;    //!< Puntero al nodo anterior.
    NodoRotor* siguiente; //!< Puntero al nodo siguiente.

    /**
     * @brief Constructor del NodoRotor.
     * @param d El carácter a almacenar.
     */
    NodoRotor(char d) : dato(d), previo(nullptr), siguiente(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Implementación de una lista circular doblemente enlazada (disco de cifrado).
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza; //!< Puntero 'cero' actual del rotor (a qué se mapea 'A').

public:
    RotorDeMapeo();
    ~RotorDeMapeo();

    /**
     * @brief Rota el puntero 'cabeza' N posiciones.
     * @param N Número de posiciones a rotar (positivo o negativo).
     */
    void rotar(int N);

    /**
     * @brief Obtiene el carácter mapeado según la rotación actual.
     * @param in El carácter de entrada (payload de TramaLoad).
     * @return El carácter decodificado.
     */
    char getMapeo(char in);
};

#endif // DATASTRUCTURES_H