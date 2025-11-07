#include <stdio.h> // Para printf
#include "DataStructures.h"
#include "Trama.h"
#include "SerialPort.h"

int main() {
    // 1. Inicialización
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    SerialPort serial;

    printf("Iniciando Decodificador PRT-7.\n");

    // 2. Conexión Serial (Simulada)
    // En una implementación real, aquí iría el nombre real del puerto
    const char* port = "COM3"; // Para Windows
    // const char* port = "/dev/ttyUSB0"; // Para Linux
    
    if (!serial.connect(port, 9600)) {
        printf("Error: No se pudo conectar al puerto %s.\n", port);
        return -1;
    }

    printf("Conexión establecida. Esperando tramas...\n\n");

    // Buffer para leer las líneas (C-style)
    char buffer[256];

    // 3. Bucle de Procesamiento
    while (serial.readLine(buffer, 256)) {
        
        printf("Trama recibida: [%s]", buffer);

        // 4. Parsear e Instanciar (Polimorfismo)
        TramaBase* trama = SerialParser::parse(buffer);

        if (trama != nullptr) {
            // 5. Ejecutar
            printf(" -> Procesando...");
            trama->procesar(&miListaDeCarga, &miRotorDeMapeo);

            // Imprimir estado actual del mensaje
            printf(" Mensaje: [");
            miListaDeCarga.imprimirMensaje();
            printf("]\n");

            // 6. Limpiar
            delete trama;
        } else {
            printf(" -> TRAMA MAL FORMADA. Ignorando.\n");
        }
    }

    // 7. Resultado Final
    printf("\n---\nFlujo de datos terminado.\n");
    printf("MENSAJE OCULTO ENSAMBLADO:\n");
    miListaDeCarga.imprimirMensaje();
    printf("\n---\n");

    serial.close();
    printf("Liberando memoria... Sistema apagado.\n");

    // Los destructores de miListaDeCarga y miRotorDeMapeo se llaman aquí
    // limpiando toda la memoria de los nodos.
    return 0;
}