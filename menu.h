/*
// voy a dejar las pre y pos para copiar y no escribirlas,
// Pre: 
// Pos: 
*/

#if !defined(MENU_H)
#define MENU_H

#include <iostream>
#include <string>

using namespace std;

const string ARCHIVO_MATERIALES = "materiales.txt";
const string ARCHIVO_EDIFICIOS = "edificios.txt";
int const LISTAR_MATERIAL = 1;
int const CONSTRUIR_EDIFICIO = 2;
int const LISTAR_EDIFICIOS_CONSTRUIDOS = 3;
int const LISTAR_TODOS_EDIFICIOS = 4;
int const DEMOLER_EDIFICIO = 5;
int const GUARDAR_SALIR = 6;

struct material
{
    string nombre;
    int cantidad;
};

struct edificio
{
    string nombre;
    int cantidad_madera;
    int cantidad_piedra;
    int cantidad_metal;
    int cantidad_construidos;
    int max_permitidos;
};

struct ciudad
{
    material ** materiales;
    int cantidad_materiales;
    edificio ** edificios;
    int cantidad_edificios;
};


// Pre: -  
// Pos: Imprime por terminal el menu de opciones
void mostrar_menu();

// Pre: - 
// Pos: Devuelve la opcion elegida , ya validada , del usuario.
int elegir_opcion();

// Pre: Recibe el puntero ciudad ya creado.
// Pos: Guarda la informacion del archivo materiales dentro de la struct ciudad.
void procesar_archivo_materiales(ciudad * andypolis);

// Pre: Recibe el puntero ciudad ya creado.
// Pos: Guarda la informacion del archivo edificios dentro de la struct ciudad.
void procesar_archivo_edificios(ciudad * andypolis);

// Pre: 0 < opcion < 6 , y la ciudad andynopolis con los archivos ya procesados 
// Pos: Se dirige a la opcion elegida por el usuario.
void procesar_opcion(int opcion, ciudad * andypolis);

// Pre: Recibe la ciudad para utilizar la parte de los materiales, el vector materiales.
// Pos: - 
void listar_materiales_construccion(ciudad * andypolis);

int elegir_edificio(ciudad * andypolis);

bool existen_materiales(ciudad * andypolis,int posicion_edificio_elegido);

bool construccion_permitida(ciudad * andypolis,int posicion_edificio);

int obtener_cantidad_material(string material, ciudad * andypolis);

void construir_edificio(ciudad * andypolis,int posicion_edificio);



#endif // MENU_H
