#ifndef SERIALPORT_H
#define SERIALPORT_H

/**
 * @file SerialPort.h
 * @brief Abstracción del puerto serial (Versión Simulada).
 */

class SerialPort {
private:
    // Datos de simulación
    const char** simData;
    int simIndex;

public:
    SerialPort();
    ~SerialPort();

    /**
     * @brief (Simulado) "Conecta" al puerto.
     * @param portName Nombre del puerto (ej. "COM3" o "/dev/ttyUSB0").
     * @param baudRate El baud rate (ej. 9600).
     * @return true si la conexión fue exitosa.
     */
    bool connect(const char* portName, int baudRate);

    /**
     * @brief Cierra la conexión serial.
     */
    void close();

    /**
     * @brief (Simulado) Lee una línea del puerto serial.
     * @param buffer Puntero a un buffer donde se almacenará la línea.
     * @param bufferSize Tamaño del buffer.
     * @return true si se leyó una línea, false si se terminó el flujo.
     */
    bool readLine(char* buffer, int bufferSize);
};

#endif // SERIALPORT_H