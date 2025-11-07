#include "SerialPort.h"
#include <stdio.h> // Para printf
#include <string.h> // Para strcpy

// Cross-platform sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// --- DATOS DE SIMULACIÓN (del ejemplo del prompt) ---
const char* g_simData[] = {
    "L,H",
    "L,O",
    "L,L",
    "M,2",
    "L,A",
    "L,Space",
    "L,W",
    "M,-2",
    "L,O",
    "L,R",
    "L,L",
    "L,D",
    nullptr // Marcador de fin de flujo
};

SerialPort::SerialPort() : simData(g_simData), simIndex(0) {}

SerialPort::~SerialPort() {
    // Nada que limpiar en la simulación
}

bool SerialPort::connect(const char* portName, int baudRate) {
    printf("Simulando conexión a %s con %d baudios...\n", portName, baudRate);
    this->simIndex = 0;
    return true; // Siempre exitoso en simulación
}

void SerialPort::close() {
    printf("Simulando cierre de puerto...\n");
}

bool SerialPort::readLine(char* buffer, int bufferSize) {
    // Simular el delay del Arduino
    #ifdef _WIN32
        Sleep(1000); // 1000 milisegundos
    #else
        sleep(1);    // 1 segundo
    #endif

    if (simData[simIndex] == nullptr) {
        return false; // Fin del flujo de datos
    }

    // Copia segura C-style (simplificada, asumiendo bufferSize es suficiente)
    if (strlen(simData[simIndex]) < bufferSize) {
        strcpy(buffer, simData[simIndex]);
        simIndex++;
        return true;
    }

    return false; // Error o buffer muy pequeño
}