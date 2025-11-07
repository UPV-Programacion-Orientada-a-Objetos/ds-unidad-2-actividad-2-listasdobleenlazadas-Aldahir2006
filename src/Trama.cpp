#include "Trama.h"
#include "DataStructures.h"
#include <stdio.h> // Para printf
#include <string.h> // Para strcmp
#include <stdlib.h> // Para atoi

// --- Implementación de TramaLoad ---

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char decodificado = rotor->getMapeo(this->payload);
    carga->insertarAlFinal(decodificado);

    // Imprimir feedback como en el ejemplo
    if (this->payload == ' ') {
        printf(" -> Fragmento 'Space' decodificado como ' '.");
    } else {
        printf(" -> Fragmento '%c' decodificado como '%c'.", this->payload, decodificado);
    }
}

// --- Implementación de TramaMap ---

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    rotor->rotar(this->rotacion);

    // Imprimir feedback como en el ejemplo
    printf(" -> ROTANDO ROTOR %+d.", this->rotacion);
}

// --- Implementación del SerialParser ---

TramaBase* SerialParser::parse(char* linea) {
    if (linea == nullptr || linea[0] == '\0') {
        return nullptr; // Trama vacía
    }

    // Usar sscanf es una forma C-style robusta de parsear
    // PERO no maneja "L,Space". Lo haremos manualmente.
    // Prohibido usar strtok porque modifica la cadena original (problemas si la cadena es const)
    // Usaremos punteros manuales.

    if (linea[0] == 'L' && linea[1] == ',') {
        // Es una TramaLoad
        char* payload = &linea[2]; // Puntero al carácter después de la coma

        if (strcmp(payload, "Space") == 0) {
            return new TramaLoad(' ');
        } else if (payload[0] != '\0' && payload[1] == '\0') {
            // Asegura que es un solo carácter
            return new TramaLoad(payload[0]);
        }
    } else if (linea[0] == 'M' && linea[1] == ',') {
        // Es una TramaMap
        char* payload = &linea[2]; // Puntero al número (ej. "5" o "-3")
        
        // atoi es la función C-style para convertir string a int
        int rotacion = atoi(payload);
        return new TramaMap(rotacion);
    }

    return nullptr; // Trama mal formada
}