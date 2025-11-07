#ifndef TRAMA_H
#define TRAMA_H

// Forward declarations para evitar inclusión circular
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @file Trama.h
 * @brief Define la jerarquía de clases polimórficas (TramaBase, TramaLoad, TramaMap).
 */

/**
 * @class TramaBase
 * @brief Clase base abstracta para todas las tramas.
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual. Obligatorio para la limpieza polimórfica.
     */
    virtual ~TramaBase() {}

    /**
     * @brief Método virtual puro para procesar la trama.
     * @param carga Puntero a la ListaDeCarga donde se almacena el mensaje.
     * @param rotor Puntero al RotorDeMapeo para decodificar o rotar.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

/**
 * @class TramaLoad
 * @brief Representa una trama de carga (ej. "L,A").
 */
class TramaLoad : public TramaBase {
private:
    char payload; //!< El carácter a cargar (ej. 'A').

public:
    /**
     * @brief Constructor de TramaLoad.
     * @param p El carácter de la trama.
     */
    TramaLoad(char p) : payload(p) {}
    virtual ~TramaLoad() {}

    /**
     * @brief Procesa la trama de carga.
     *
     * Obtiene el mapeo del carácter del payload usando el rotor
     * y lo inserta en la lista de carga.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

/**
 * @class TramaMap
 * @brief Representa una trama de mapeo (ej. "M,5").
 */
class TramaMap : public TramaBase {
private:
    int rotacion; //!< El número de posiciones a rotar (ej. 5 o -3).

public:
    /**
     * @brief Constructor de TramaMap.
     * @param r El valor de rotación.
     */
    TramaMap(int r) : rotacion(r) {}
    virtual ~TramaMap() {}

    /**
     * @brief Procesa la trama de mapeo.
     *
     * Simplemente le dice al rotor que rote N posiciones.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

/**
 * @namespace SerialParser
 * @brief Contiene funciones de utilidad para parsear cadenas C-style.
 */
namespace SerialParser {
    /**
     * @brief Parsea una línea de texto del serial e instancia el objeto Trama correcto.
     * @param linea La cadena C-style leída del serial (ej. "L,A" o "M,-2").
     * @return Un puntero TramaBase* a un objeto (TramaLoad o TramaMap) en el heap.
     * El llamador es responsable de hacer 'delete' a este puntero.
     * Retorna nullptr si la trama está mal formada.
     */
    TramaBase* parse(char* linea);
}

#endif // TRAMA_H