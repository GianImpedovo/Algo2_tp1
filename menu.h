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

void procesar_archivo_materiales(ciudad * andynopolis);


#endif // MENU_H
