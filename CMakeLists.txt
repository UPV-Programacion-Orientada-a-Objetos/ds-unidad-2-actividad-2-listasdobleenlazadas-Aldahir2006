# Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(PRT7_Decoder CXX)

# Usar C++11 o superior
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Definir el ejecutable
add_executable(prt7_decoder)

# Indicar a CMake dónde encontrar los archivos de cabecera (.h)
target_include_directories(prt7_decoder 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Indicar a CMake qué archivos fuente (.cpp) compilar
target_sources(prt7_decoder 
    PRIVATE
    src/main.cpp
    src/DataStructures.cpp
    src/Trama.cpp
    src/SerialPort.cpp
)

# --- Opcional: Configuración de Doxygen ---
# Encontrar Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # Crear un archivo de configuración de Doxygen (Doxyfile)
    # (Puedes personalizarlo o crearlo manualmente)
    if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        execute_process(COMMAND ${DOXYGEN_EXECUTABLE} -g ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        # Configurar Doxyfile: INPUT, OUTPUT_DIRECTORY, etc.
        # Esto es un ejemplo básico, requiere configuración manual del Doxyfile
        configure_file(${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    endif()

    # Añadir un objetivo personalizado para generar la documentación
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generando documentación Doxygen..."
        VERBATIM
    )
    # Hacer que 'doc' dependa del ejecutable
    add_dependencies(doc prt7_decoder)
else()
    message(STATUS "Doxygen no encontrado. El objetivo 'doc' no estará disponible.")
endif()